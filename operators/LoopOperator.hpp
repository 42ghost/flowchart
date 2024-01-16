#ifndef LOOPOPERATOR_HPP
#define LOOPOPERATOR_HPP

#include "BaseOperator.hpp"

class LoopOperator : public BaseOperator{
private:
protected:
    std::string condition;
    std::vector<BaseOperator*> body;
public:
    LoopOperator(std::string);

    std::vector<BaseOperator*> getBodyBranch();
    std::string getCondition();
    std::string getText() override;

    void setCondition();
    void setBody();
};

#endif
