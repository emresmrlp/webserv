#include <iostream>
#include <iomanip>
#include <vector>
#include "../../include/config/Token.hpp" // Ensure this includes your Token class and Tokenize function
#include "../../include/config/Parser.hpp"

int	main(int argc, char **argv)
{
	config::Parser test("../../conf/default.conf");
    test.parse();
}
