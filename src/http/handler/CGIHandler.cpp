/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:02:19 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/24 13:26:33 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGIHandler.hpp"
#include "ResponseFactory.hpp"
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include "Util.hpp"
#include <fcntl.h>
#include <sys/wait.h>
#include <fstream>

namespace http
{
	CGIHandler::CGIHandler(ResponseFactory &factory) : _factory(factory) {}

	CGIHandler::~CGIHandler() {}

	http::IResponse *CGIHandler::handle(const config::ConfigServer *config, const config::ConfigLocation *configLoc,
		http::Request *request) const
	{
		CGIResult inputResult;
		CGIResult outputResult;

		std::vector<std::string> envValues = this->buildEnv(config, request);
		std::vector<char *> envp((envValues.size() + 1), NULL);
		for (size_t i = 0; i < envValues.size(); i++)
			envp[i] = (const_cast<char *>(envValues[i].c_str()));

		inputResult = this->prepareInput(request);
		if (inputResult.status == false)
			return (this->_factory.createStatusResponse(config, request, http::INTERNAL_SERVER_ERROR));
		
		std::string resolvedPath = util::getRelativeConfigPath(config, configLoc) + request->getPath();
		if (resolvedPath.find_first_of("?") != std::string::npos)
			resolvedPath = resolvedPath.substr(0, resolvedPath.find_first_of("?"));

		std::string interpreterPath = configLoc->getCgiPass(util::getExtension(request->getPath()));
		outputResult = this->executeCgi(resolvedPath, interpreterPath, inputResult.output, &envp[0]);
		if (outputResult.status == false)
			return (this->_factory.createStatusResponse(config, request, http::INTERNAL_SERVER_ERROR));

		return (this->_factory.createSuccessResponseWithPath(config, request, outputResult.output));
	}

	CGIResult CGIHandler::prepareInput(http::Request *request) const
	{
		CGIResult result;
		result.status = false;
		result.output = "";

		if (request->getBody().empty())
		{
			result.status = true;
			return (result);
		}
		static unsigned long cgiInCounter = 0;
		std::string tmpInFileName = "tmp/cgiTmpIn_" + util::toString(cgiInCounter++);
		std::ofstream file(tmpInFileName.c_str(), std::ios::binary);
		if (!file.is_open())
			return (result);
		file.write(request->getBody().c_str(), request->getBody().size());
		if (file.fail())
		{
			file.close();
			std::remove(tmpInFileName.c_str());
			return (result);
		}
		file.close();

		result.status = true;
		result.output = tmpInFileName;
		return (result);
	}

	CGIResult CGIHandler::executeCgi(std::string resolvedPath, std::string interpreterPath, std::string tmpInFile, char *const *envp) const
	{
		CGIResult result;
		result.status = false;
		result.output = "";

		static unsigned long cgiOutCounter = 0;
		std::string tmpOutFile = "tmp/cgiTmpOut_" + util::toString(cgiOutCounter++);
		std::ofstream file(tmpOutFile.c_str(), std::ios::binary);
		if (!file.is_open())
			return (result);
		file.close();

		pid_t pid = fork();
		if (pid == -1)
		{
			std::remove(tmpInFile.c_str());
			return (result);
		}
		if (pid == 0)
		{
			int inputFd = open(tmpInFile.c_str(), O_RDONLY);
			if (inputFd == -1)
				exit(1);
			if (dup2(inputFd, STDIN_FILENO) == -1)
				exit(1);
			close(inputFd);

        	int outputFd = open(tmpOutFile.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0600);
			if (outputFd == -1)
				exit(1);
			if (dup2(outputFd, STDOUT_FILENO) == -1)
				exit(1);
			close(outputFd);

			char *argv[] =
			{
				const_cast<char *>(interpreterPath.c_str()),
				const_cast<char *>(resolvedPath.c_str()),
				NULL
			};
			
			execve(interpreterPath.c_str(), argv, envp);
			exit(1);
		}
		int status;
		waitpid(pid, &status, 0);

		std::remove(tmpInFile.c_str());
		result.status = true;
		result.output = tmpOutFile;
		return (result);
	}

	std::vector<std::string> CGIHandler::buildEnv(const config::ConfigServer *config, http::Request *request) const
	{
		std::vector<std::string> envValues;

		std::string resolvedPath = request->getPath();
		
		if (resolvedPath.find_first_of("?") != std::string::npos)
			resolvedPath = resolvedPath.substr(0, resolvedPath.find_first_of("?"));

		envValues.push_back("REQUEST_METHOD=" + request->getMethod());
		envValues.push_back("QUERY_STRING=" + this->getQuery(request->getPath()));
		envValues.push_back("SERVER_PROTOCOL=" + config->getHttpVersion());
		envValues.push_back("SCRIPT_NAME=" + resolvedPath);
		envValues.push_back("GATEWAY_INTERFACE=CGI/1.1");
		envValues.push_back("SERVER_SOFTWARE=YECS-BME-Webserv/1.0");
		if (request->getMethod() == "POST" || request->getMethod() == "PUT")
			envValues.push_back("CONTENT_LENGTH=" + util::toString(request->getBody().size()));
		return (envValues);
	}

	const std::string CGIHandler::getQuery(const std::string &path) const
	{
		std::size_t	queryPos;
		std::string	result;

		queryPos = path.find_first_of("?");
		if (queryPos == std::string::npos || queryPos + 1 == std::string::npos)
			return ("");
		return (path.substr(queryPos + 1));
	}
}