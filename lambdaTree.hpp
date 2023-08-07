#include <memory>
#include <string>

class LambdaElem {
    public:
    virtual std::unique_ptr<LambdaElem> eval() = 0;
    virtual std::unique_ptr<LambdaElem> apply(std::unique_ptr<LambdaElem> arg) = 0;
    virtual std::unique_ptr<LambdaElem> apply(std::string name, std::unique_ptr<LambdaElem> arg) = 0;
    virtual std::string serialize() = 0;
    virtual int getType() = 0;
};

class LambdaNode {

    public:
    LambdaNode eval();
    LambdaNode apply(LambdaNode arg);
    LambdaNode apply(std::string name, LambdaNode arg) ;
    std::string serialize();
    int getType();
};

class LambdaName : public virtual LambdaElem {
    const std::string name;
    public:
    LambdaName(std::string name) noexcept;
    std::string serialize() override;
    std::unique_ptr<LambdaElem> eval() override;
    std::unique_ptr<LambdaElem> apply(std::unique_ptr<LambdaElem> arg) override;
    std::unique_ptr<LambdaElem> apply(std::string subst_name, std::unique_ptr<LambdaElem> arg) override;
    std::string getName();
    int getType() override;
};

class LambdaFunc : public virtual LambdaElem {
    LambdaName arg;
    std::unique_ptr<LambdaElem> body;
    public:
    //LambdaFunc(LambdaName arg, LambdaElem body) noexcept;
    LambdaFunc(LambdaName arg, std::unique_ptr<LambdaElem>&& body) noexcept;
    std::string serialize() override;
    std::unique_ptr<LambdaElem> eval() override;
    std::unique_ptr<LambdaElem> apply(std::unique_ptr<LambdaElem> arg) override;
    std::unique_ptr<LambdaElem> apply(std::string name, std::unique_ptr<LambdaElem> arg) override;
    int getType() override;
};

class LambdaApply : public virtual LambdaElem {
    std::unique_ptr<LambdaElem> func;
    std::unique_ptr<LambdaElem> arg;
    public:
    LambdaApply(std::unique_ptr<LambdaElem> func, std::unique_ptr<LambdaElem> arg) noexcept;
    std::string serialize() override;
    std::unique_ptr<LambdaElem> eval() override;
    std::unique_ptr<LambdaElem> apply(std::unique_ptr<LambdaElem> arg) override;
    std::unique_ptr<LambdaElem> apply(std::string name, std::unique_ptr<LambdaElem> arg) override;
    int getType() override;
};

