#include <iostream>
#include <iomanip>
#include <vector>
#include "../../include/config/Token.hpp" // Ensure this includes your Token class and Tokenize function

// Helper to convert enum to readable string
std::string	tokenTypeToString(config::TokenType type) {
	switch (type) {
		case config::OPEN_BLOCK:  return "OPEN_BLOCK";
		case config::CLOSE_BLOCK: return "CLOSE_BLOCK";
		case config::SEMICOLON:   return "SEMICOLON";
		case config::KEYWORD:     return "KEYWORD\t";
		case config::VALUE:       return "VALUE\t";
		case config::COMMENT:     return "COMMENT\t";
		case config::END_OF_FILE: return "END_OF_FILE";
		default:          return "UNKNOWN";
	}
}

int	main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: ./tokenizer [config_file]" << std::endl;
		return 1;
	}

	// Assuming Tokenize returns std::vector<Token>
	std::vector<config::Token> tokens = config::Tokenize(argv[1]);

	std::cout << "--\t----\t----\t\t---" << std::endl;
	std::cout << "NO\tLINE\tTYPE\t\tSTR" << std::endl;
	std::cout << "--\t----\t----\t\t---" << std::endl;
	for (size_t i = 0; i < tokens.size(); ++i) {
		std::cout << (i + 1) << "\t" << tokens[i].getLine() << "\t"
		<< tokenTypeToString(tokens[i].getType()) << "\t"
		<< tokens[i].getStr() << "" 
		<< std::endl;
	}

	return 0;
}