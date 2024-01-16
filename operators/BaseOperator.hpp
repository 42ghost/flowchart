#ifndef BASEOPERATOR_HPP
#define BASEOPERATOR_HPP

#include <vector>
#include <string>


enum id_operator
{
    start,
    end,
    input_op,
    output_op,
    if_op,
    loop_op,
    other_op
};

class BaseOperator{
private:
protected:
    id_operator type;
    std::string text;
public:
    BaseOperator();
    BaseOperator(id_operator);
    BaseOperator(std::string);

    id_operator getType();
    virtual std::string getText();
};

#endif
