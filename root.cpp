#include <deque>
#include <iostream>
#include <fstream>
#include <iterator>
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include "token.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"

void evalText() {
    std::string input;
    std::getline(std::cin, input);

    if (std::cin.fail()) {
        std::cout << "Failed to read input" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::deque<std::unique_ptr<BaseToken>> tokenBuffer;
    Lam::tokenize(tokenBuffer, input);
    std::unique_ptr<LambdaElem> ast(parse(tokenBuffer));
    std::cout << ast->eval()->serialize() << std::endl;
}

int main() {
    evalText();
    return 0;
}