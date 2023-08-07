#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include "lambdaTree.hpp"

const int LAMBDA_NAME = 1;
const int LAMBDA_FUNC = 2;
const int LAMBDA_APPLY = 3;

LambdaName::LambdaName(std::string name) noexcept : name(name) {};
std::string LambdaName::serialize() {
    return name;
}
std::unique_ptr<LambdaElem> LambdaName::eval() {
    return std::make_unique<LambdaName>(LambdaName(name));
}
std::unique_ptr<LambdaElem> LambdaName::apply(std::unique_ptr<LambdaElem> arg) {
    return arg;
}

std::unique_ptr<LambdaElem> LambdaName::apply(std::string subst_name, std::unique_ptr<LambdaElem> arg) {
    if (name.compare(subst_name) == 0) {
        return arg;
    }

    return std::make_unique<LambdaName>(LambdaName(name));
}

int LambdaName::getType() {
    return LAMBDA_NAME;
}

std::string LambdaName::getName() {
    return name;
}

//LambdaFunc::LambdaFunc(LambdaName arg, LambdaElem body) noexcept : arg(arg), body(std::make_unique<LambdaElem>(body)) {};
LambdaFunc::LambdaFunc(LambdaName arg, std::unique_ptr<LambdaElem>&& body) noexcept : arg(arg), body(std::move(body)) {};
//LambdaFunc::LambdaFunc(LambdaName arg, LambdaElem&& body) noexcept : arg(arg), body(std::make_unique<LambdaElem>(body)) {};

std::string LambdaFunc::serialize() {
    return "fn " + arg.serialize() + "." + body->serialize();
}

std::unique_ptr<LambdaElem> LambdaFunc::eval() {
    return std::make_unique<LambdaFunc>(LambdaFunc(arg, body->eval()));
}

std::unique_ptr<LambdaElem> LambdaFunc::apply(std::unique_ptr<LambdaElem> subst_arg) {
    return body->apply(arg.getName(), std::move(subst_arg));
}

std::unique_ptr<LambdaElem> LambdaFunc::apply(std::string name, std::unique_ptr<LambdaElem> subst_arg) {
    if (name.compare(arg.getName()) == 0) {
        return std::unique_ptr<LambdaFunc>(this);
    }

    return std::make_unique<LambdaFunc>(LambdaFunc(arg, body->apply(name, std::move(subst_arg))));
}

int LambdaFunc::getType() {
    return LAMBDA_FUNC;
}

LambdaApply::LambdaApply(std::unique_ptr<LambdaElem> func, std::unique_ptr<LambdaElem> arg) noexcept : func(std::move(func)), arg(std::move(arg)) {}; 

std::unique_ptr<LambdaElem> LambdaApply::eval() {
    return func->eval()->apply(arg->eval());
}

std::unique_ptr<LambdaElem> LambdaApply::apply(std::unique_ptr<LambdaElem> subst_arg) {
    return std::unique_ptr<LambdaApply>(this);
}

std::unique_ptr<LambdaElem> LambdaApply::apply(std::string name, std::unique_ptr<LambdaElem>  subst_arg) {
    return std::make_unique<LambdaApply>(func->apply(name, std::move(subst_arg)), arg->apply(name, std::move(subst_arg)));
}

std::string LambdaApply::serialize() {
    return "(" + func->serialize() + ") " + arg->serialize();
}

int LambdaApply::getType() {
    return LAMBDA_APPLY;
}