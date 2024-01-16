#include "BaseOperator.hpp"

BaseOperator::BaseOperator(){}

BaseOperator::BaseOperator(id_operator id){
    type = id;
    if (id == start){
        text = "Начало";
    } else if (id == end) {
        text = "Конец";
    }
}

BaseOperator::BaseOperator(std::string op){
    type = other_op;
    text = op;
}

id_operator BaseOperator::getType(){
    return type;
}

std::string BaseOperator::getText(){
    return text;
}
