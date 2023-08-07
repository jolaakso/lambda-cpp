#pragma once
#include "token.hpp"
#include "lambdaTree.hpp"
#include <deque>
#include <memory>

std::unique_ptr<LambdaElem> parse(std::deque<std::unique_ptr<BaseToken>>& tokens);

std::unique_ptr<LambdaElem> parseElem(std::deque<std::unique_ptr<BaseToken>>& tokens);

std::unique_ptr<LambdaElem> parseName(std::deque<std::unique_ptr<BaseToken>>& tokens);

std::unique_ptr<LambdaElem> parseFunc(std::deque<std::unique_ptr<BaseToken>>& tokens);

std::unique_ptr<LambdaElem> parseParen(std::deque<std::unique_ptr<BaseToken>>& tokens);