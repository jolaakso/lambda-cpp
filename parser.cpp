#include "token.hpp"
#include "parser.hpp"
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <deque>
#include <memory>

std::unique_ptr<LambdaElem> parse(std::deque<std::unique_ptr<BaseToken>>& tokens) {
        std::unique_ptr<LambdaElem> elem(parseElem(tokens));

        if (!tokens.empty()) {
            return std::make_unique<LambdaApply>(std::move(elem), parse(tokens));
        }

        return elem;
}

std::unique_ptr<LambdaElem> parseElem(std::deque<std::unique_ptr<BaseToken>>& tokens) {
    if (tokens.front()->getTokenType() == BaseToken::TokenTypes::name) {
        return parseName(tokens);
    } else if (tokens.front()->getTokenType() == BaseToken::TokenTypes::func) {
        return parseFunc(tokens);
    } else if (tokens.front()->getTokenType() == BaseToken::TokenTypes::parenOpen) {
        return parseParen(tokens);
    } else {
        std::cout << "Unexpected beginning of sequence" << std::endl;
        exit(EXIT_FAILURE);
    }
}

std::unique_ptr<LambdaElem> parseName(std::deque<std::unique_ptr<BaseToken>>& tokens) {
    std::unique_ptr<NameToken> nameToken(dynamic_cast<NameToken*>(tokens.front().release()));
    std::unique_ptr<LambdaName> nameElem(std::make_unique<LambdaName>(nameToken->getName()));
    tokens.pop_front();

    return nameElem;
}

std::unique_ptr<LambdaElem> parseParen(std::deque<std::unique_ptr<BaseToken>>& tokens) {
    tokens.pop_front();
    std::unique_ptr<LambdaElem> tree(parseElem(tokens));
    if (tokens.front()->getTokenType() == BaseToken::TokenTypes::parenClose) {
        tokens.pop_front();
        return tree;
    }

    std::unique_ptr<LambdaElem> arg(parseElem(tokens));

    if (tokens.front()->getTokenType() == BaseToken::TokenTypes::parenClose) {
        tokens.pop_front();
    }

    return std::make_unique<LambdaApply>(std::move(tree), std::move(arg));
}

//std::unique_ptr<LambdaElem> parseApply(std::deque<std::unique_ptr<BaseToken>>& tokens) {
//}

std::unique_ptr<LambdaElem> parseFunc(std::deque<std::unique_ptr<BaseToken>>& tokens) {
    tokens.pop_front();
    if (tokens.front()->getTokenType() != BaseToken::TokenTypes::name) {
        std::cout << "Unexpected token, expected name token" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::unique_ptr<LambdaName> nameElem(dynamic_cast<LambdaName*>(parseName(tokens).release()));

    if (tokens.front()->getTokenType() != BaseToken::TokenTypes::dot) {
        std::cout << "Unexpected token, expected dot token" << std::endl;
        exit(EXIT_FAILURE);
    }
    tokens.pop_front();

    std::unique_ptr<LambdaElem> bodyElem(parseElem(tokens));

    return std::make_unique<LambdaFunc>(*nameElem, std::move(bodyElem));
}
