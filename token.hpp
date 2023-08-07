#pragma once
#include <string>

class BaseToken {
    public:
    enum class TokenTypes { parenOpen, parenClose, func, name, dot };
    const virtual TokenTypes getTokenType() = 0;
};

class ParenOpenToken : public virtual BaseToken {
    public:
    const TokenTypes getTokenType() override;
};

class ParenCloseToken : public virtual BaseToken {
    public:
    const TokenTypes getTokenType() override;
};

class FuncToken : public virtual BaseToken {
    const std::string varNameText;

    public:
    const TokenTypes getTokenType() override;
};

class DotToken : public virtual BaseToken {
    public:
    const TokenTypes getTokenType() override;
};

class NameToken : public virtual BaseToken {
    const std::string nameText;
    public:
    const std::string getName();
    const TokenTypes getTokenType() override;
    NameToken(std::string givenName) noexcept;
};