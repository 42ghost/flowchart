#ifndef FLOWCHART_HPP
#define FLOWCHART_HPP

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
    switch_op,
};

class Flowchart
{
private:
protected:
    id_operator type;
    std::string text;
public:
    std::string leftText;
    std::string rightText;
    //std::vector<Flowchart> opBody;
    //std::vector<Flowchart> rightbranch;
    //std::vector<Flowchart> leftbranch;
    Flowchart();
    Flowchart(id_operator id);
    Flowchart(id_operator id, std::string);
};

#endif
