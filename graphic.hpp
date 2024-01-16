#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include "operators/BaseOperator.hpp"
#include "operators/IfOperator.hpp"
#include "operators/LoopOperator.hpp"
#include "blocks/Block.hpp"

#include <vector>

#include <QImage>
#include <QPainter>
#include <QFontMetrics>


class Graphic {
private:
protected:
    int wImage, hImage;
    std::vector<Block*> tree;
public:
    int x, y;

    Graphic(int = 0, int = 0);

    std::vector<Block*> getTree();

    std::vector<Block*> create(std::vector<BaseOperator*>, int = 0, int = 0);
    void draw(QString);
    int calcMaxWidth(std::vector<BaseOperator*>);
    void drawTree(QPainter&, std::vector<Block*>);
};

#endif
