#include <iostream>
#include <iomanip>
#include <vector>
#include "../../include/config/Token.hpp" // Ensure this includes your Token class and Tokenize function
#include "../../include/config/Parser.hpp"

int	main(int argc, char **argv) {
	config::Parser test("../../conf/default.conf");
    if (test.parse())
    {
        std::cout << "\n[SUCCESS] Parsing islemi basarili!" << std::endl;
    }
    else
    {
        std::cout << "\n[FAILURE] Parsing islemi basarisiz oldu veya dosya bos." << std::endl;
    }
}