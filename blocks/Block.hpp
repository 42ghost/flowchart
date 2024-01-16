#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "operators/BaseOperator.hpp"

#include <vector>
#include <string>

enum id_shape {
    elipse,
    paral,
    rhomb,
    loop,
    rect,
};

class Block {
private:
public:
    std::pair<int, int> coords_xy;
    std::pair<int, int> size;
    id_shape shape;
    std::string text;

    std::vector<Block*> subtree;
    std::vector<Block*> elseBranch;
public:
};

#endif
