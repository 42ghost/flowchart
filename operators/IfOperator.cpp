#include "analyzer.hpp"
#include "IfOperator.hpp"

IfOperator::IfOperator(std::string src){
    type = if_op;
    text = src;
    leftText = "Да";
    rightText = "Нет";

    setCondition();
    setIfBranch();
}

void IfOperator::setCondition(){
    size_t start = text.find('(');
    for (size_t i = start+1; i < text.length(); i++){
        if (text[i] == ')'){
            condition = text.substr(start, i - start + 1);
            return;
        }
    }
}

void IfOperator::setIfBranch(){
    size_t start = text.find('{');
    size_t end = text.rfind('}');

    FileAnalyzer* analyzer = new FileAnalyzer(text.substr(start, end - start + 1));
    ifBranch = analyzer->getBlocks();
    delete analyzer;
}

void IfOperator::setElseBranch(std::vector<BaseOperator*> branch){
    if (branch.size() > 0){
        elseBranch = branch;
    }
}

std::string IfOperator::getCondition(){
    return condition;
}

std::string IfOperator::getText(){
    return condition;
}

std::vector<BaseOperator*> IfOperator::getBodyBranch(){
    return ifBranch;
}

std::vector<BaseOperator*> IfOperator::getRightBranch(){
    return elseBranch;
}

