#include "token.hpp"
#include "tokenizer.hpp"
#include <cctype>
#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <process.h>
#include <string>
#include <deque>
#include <regex>
#include <cassert>

using namespace Lam;

void Lam::tokenize(std::deque<std::unique_ptr<BaseToken>> &result, std::string unparsed) {
    const std::regex whitespace("^\\s+", std::regex::ECMAScript);
    const std::regex parenOpen("^[(]", std::regex::ECMAScript);
    const std::regex parenClose("^[)]", std::regex::ECMAScript);
    const std::regex func("^fn", std::regex::ECMAScript);
    const std::regex dot("^[.]", std::regex::ECMAScript);
    const std::regex name("^[A-Za-z0-9_\\-/:]+", std::regex::ECMAScript);

    while (unparsed.length() > 0) {
        std::smatch match;
        int previousLen = unparsed.length();

        if (std::regex_search(unparsed, match, whitespace)) {
            unparsed = match.suffix().str();
        } else if (std::regex_search(unparsed, match, parenOpen)) {
            unparsed = match.suffix().str();
            result.push_back(std::make_unique<ParenOpenToken>());
        } else if (std::regex_search(unparsed, match, parenClose)) {
            unparsed = match.suffix().str();
            result.push_back(std::make_unique<ParenCloseToken>());
        } else if (std::regex_search(unparsed, match, func)) {
            unparsed = match.suffix().str();
            result.push_back(std::make_unique<FuncToken>());
        } else if (std::regex_search(unparsed, match, dot)) {
            unparsed = match.suffix().str();
            result.push_back(std::make_unique<DotToken>());
        } else if (std::regex_search(unparsed, match, name)) {
            result.push_back(std::make_unique<NameToken>(match.str()));
            unparsed = match.suffix().str();
        } else {
            std::cout << "Syntax error" << std::endl;
            exit(1);
        }
    }
}