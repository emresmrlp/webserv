/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:02:19 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/25 19:03:56 by ysumeral         ###   ########.fr       */
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
		
		std::string relativePath = request->getPath().substr(configLoc->getExecutePath().length());
		std::string resolvedPath = util::getRelativeConfigPath(config, configLoc) + "/" + relativePath;
		ParsedURI URI = this->parseURI(util::getFixedRoute(resolvedPath));

		std::cout << "! DEBUG: p: " << URI.pathInfo << std::endl;
		std::cout << "! DEBUG: s " << URI.scriptPath << std::endl;
		std::cout << "! DEBUG: q: " << URI.queryString << std::endl;
		
		std::vector<std::string> envValues = this->buildEnv(config, request, URI);
		std::vector<char *> envp((envValues.size() + 1), NULL);
		for (size_t i = 0; i < envValues.size(); i++)
			envp[i] = (const_cast<char *>(envValues[i].c_str()));

		inputResult.output = "";
		inputResult.status = true;
		if (request->getMethod() != "GET" && request->getMethod() != "HEAD")
		{
			inputResult = this->prepareInput(request);
			if (inputResult.status == false)
				return (this->_factory.createStatusResponse(config, request, http::INTERNAL_SERVER_ERROR));
		}

		std::string interpreterPath = configLoc->getCgiPass(util::getExtension(URI.scriptPath));
		outputResult = this->executeCgi(URI.scriptPath, interpreterPath, inputResult.output, &envp[0]);
		if (outputResult.status == false)
			return (this->_factory.createStatusResponse(config, request, http::INTERNAL_SERVER_ERROR));

		return (this->_factory.createCGIResponse(config, request, outputResult.output));
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

		bool	hasInput = !tmpInFile.empty();

		static unsigned long cgiOutCounter = 0;
		std::string tmpOutFile = "tmp/cgiTmpOut_" + util::toString(cgiOutCounter++);
		std::ofstream file(tmpOutFile.c_str(), std::ios::binary);
		if (!file.is_open())
			return (result);
		file.close();

		pid_t pid = fork();
		if (pid == -1)
		{
			if (hasInput)
				std::remove(tmpInFile.c_str());
			return (result);
		}
		if (pid == 0)
		{
			if (hasInput)
			{
				int inputFd = open(tmpInFile.c_str(), O_RDONLY);
				if (inputFd == -1)
					exit(1);
				if (dup2(inputFd, STDIN_FILENO) == -1)
					exit(1);
				close(inputFd);
			}
			else
				close(STDIN_FILENO);

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
	
			execve(interpreterPath.c_str(), argv, &envp[0]);
			exit(1);
		}
		int status;
		waitpid(pid, &status, 0);

		if (hasInput)
			std::remove(tmpInFile.c_str());
		result.status = true;
		result.output = tmpOutFile;
		return (result);
	}
	
	ParsedURI CGIHandler::parseURI(const std::string &path)
	{
		ParsedURI result;
		result.pathInfo = "";
		result.queryString = "";
		result.scriptPath = "";
		
		std::string fullPath = path;

		std::size_t	queryPos;
		queryPos = fullPath.find_first_of("?");
		if (queryPos == std::string::npos || queryPos + 1 == std::string::npos)
			result.queryString = "";
		else
		{
			result.queryString = fullPath.substr(queryPos + 1);
			fullPath.erase(queryPos);
		}

		std::size_t dotPos = fullPath.find_last_of(".");
		if (dotPos != std::string::npos)
		{
			std::size_t slashPos = fullPath.find("/", dotPos);
			if (slashPos == std::string::npos)
				result.scriptPath = fullPath;
			else
			{
				result.scriptPath = fullPath.substr(0, slashPos);
				result.pathInfo = fullPath.substr(slashPos);
			}
		}

		return (result);
	}

	std::vector<std::string> CGIHandler::buildEnv(const config::ConfigServer *config, http::Request *request, ParsedURI URI) const
	{
		std::vector<std::string> envValues;

		envValues.push_back("REQUEST_METHOD=" + request->getMethod());
		envValues.push_back("QUERY_STRING=" + URI.queryString);
		envValues.push_back("SERVER_PROTOCOL=" + config->getHttpVersion());
		envValues.push_back("SCRIPT_NAME=" + URI.scriptPath);
		envValues.push_back("GATEWAY_INTERFACE=CGI/1.1");
		envValues.push_back("SERVER_SOFTWARE=YECS-BME-Webserv/1.0");
		envValues.push_back("REDIRECT_STATUS=200");
		if (URI.pathInfo == "")
		{
			envValues.push_back("REQUEST_URI=" + URI.scriptPath + URI.pathInfo);
			envValues.push_back("PATH_INFO=" + URI.scriptPath);
		}
		else
		{
			envValues.push_back("REQUEST_URI=" + URI.pathInfo);
			envValues.push_back("PATH_INFO=" + URI.pathInfo);	
		}
		if (request->getMethod() == "POST" || request->getMethod() == "PUT")
			envValues.push_back("CONTENT_LENGTH=" + util::toString(request->getBody().size()));
		return (envValues);
	}
}