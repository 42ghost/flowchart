#ifndef IFOPERATOR_HPP
#define IFOPERATOR_HPP

#include "BaseOperator.hpp"

class IfOperator : public BaseOperator{
private:
protected:
    std::string leftText;
    std::string rightText;
    std::string condition;
    std::vector<BaseOperator*> ifBranch;
    std::vector<BaseOperator*> elseBranch;
public:
    IfOperator(std::string);

    std::string getCondition();
    std::string getText() override;
    std::vector<BaseOperator*> getBodyBranch();
    std::vector<BaseOperator*> getRightBranch();

    void setCondition();
    void setIfBranch();
    void setElseBranch(std::vector<BaseOperator*>);

};

#endif
