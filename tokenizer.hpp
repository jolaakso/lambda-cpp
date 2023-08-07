#pragma once
#include "token.hpp"
#include <deque>
#include <memory>

namespace Lam {
    void tokenize(std::deque<std::unique_ptr<BaseToken>> &result, std::string unparsed);
}