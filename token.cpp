#include <string>
#include "token.hpp"

const BaseToken::TokenTypes ParenOpenToken::getTokenType() {
    return BaseToken::TokenTypes::parenOpen;
}

const BaseToken::TokenTypes ParenCloseToken::getTokenType() {
    return BaseToken::TokenTypes::parenClose;
}

const BaseToken::TokenTypes FuncToken::getTokenType() {
    return BaseToken::TokenTypes::func;
}

const BaseToken::TokenTypes NameToken::getTokenType() {
    return BaseToken::TokenTypes::name;
}

const BaseToken::TokenTypes DotToken::getTokenType() {
    return BaseToken::TokenTypes::dot;
}

NameToken::NameToken(std::string givenName) noexcept : nameText{givenName} {};

const std::string NameToken::getName() {
    return nameText;
}