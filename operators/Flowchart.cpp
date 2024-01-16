#include "Flowchart.hpp"

Flowchart::Flowchart(){

}

Flowchart::Flowchart(id_operator id){
    type = id;
    if (id == start){
        text = "Начало";
    } else if (id == end) {
        text = "Конец";
    }
}

Flowchart::Flowchart(id_operator id, std::string src){
    type = id;
    text = src;
}
