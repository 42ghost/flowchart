#include "analyzer.hpp"
#include "LoopOperator.hpp"

void LoopOperator::setCondition(){
    size_t start = text.find('(');
    for (size_t i = start+1; i < text.length(); i++){
        if (text[i] == ')'){
            condition = text.substr(start, i - start + 1);
            return;
        }
    }
}

LoopOperator::LoopOperator(std::string src){
    type = loop_op;
    text = src;
    setCondition();
    setBody();
}

std::vector<BaseOperator*> LoopOperator::getBodyBranch(){
    return body;
}

void LoopOperator::setBody(){
    size_t start = text.find('{');
    size_t end = text.rfind('}');

    FileAnalyzer* analyzer = new FileAnalyzer(text.substr(start, end - start + 1));
    body = analyzer->getBlocks();
    delete analyzer;
}

std::string LoopOperator::getCondition(){
    return condition;
}

std::string LoopOperator::getText(){
    return condition;
}
