#include "graphic.hpp"

Graphic::Graphic(int x, int y){
    this->x = x;
    this->y = y;
}

std::vector<Block*> Graphic::getTree(){
    return tree;
}

std::vector<Block*> Graphic::create(std::vector<BaseOperator*> ops, int xBorder, int yBorder){
    wImage = calcMaxWidth(ops);
    Graphic *tempGraphic, *tempGraphic2;

    for (auto op : ops) {
        Block* tmp = new Block();

        QFont font("Arial", 25);
        QFontMetrics fontMetrics(font);
        switch (op->getType()) {
            case(start):
                tmp->shape = elipse;

                tmp->size.first = fontMetrics.horizontalAdvance(QString::fromStdString(op->getText())) * 1.1;
                tmp->size.second = 40;

                tmp->coords_xy.first = wImage / 2 - tmp->size.first / 2 + xBorder;
                tmp->coords_xy.second = y;

                y = y + 40 + tmp->size.second;
                break;
            case(end):
                tmp->shape = elipse;
                tmp->size.first = fontMetrics.horizontalAdvance(QString::fromStdString(op->getText())) * 1.3;
                tmp->size.second = 40;

                tmp->coords_xy.first = wImage / 2 - tmp->size.first / 2 + xBorder;
                tmp->coords_xy.second = y;

                y = y + 40 + tmp->size.second;
                break;
            case(input_op):
                tmp->shape = paral;
                tmp->size.first = fontMetrics.horizontalAdvance(QString::fromStdString(op->getText())) * 1.12;
                tmp->size.second = 43;

                tmp->coords_xy.first = wImage / 2 - tmp->size.first / 2 + xBorder;
                tmp->coords_xy.second = y;

                y = y + 40 + tmp->size.second;
                break;
            case(output_op):
                tmp->shape = rect;
                tmp->size.first = fontMetrics.horizontalAdvance(QString::fromStdString(op->getText())) * 1.12;
                tmp->size.second = 43;

                tmp->coords_xy.first = wImage / 2 - tmp->size.first / 2 + xBorder;
                tmp->coords_xy.second = y;

                y = y + 40 + tmp->size.second;
                break;
            case(other_op):
                tmp->shape = rect;
                tmp->size.first = fontMetrics.horizontalAdvance(QString::fromStdString(op->getText())) * 1.13;
                tmp->size.second = 46;

                tmp->coords_xy.first = wImage / 2 - tmp->size.first / 2 + xBorder;
                tmp->coords_xy.second = y;

                y = y + 40 + tmp->size.second;
                break;
            case(if_op):
                tmp->shape = rhomb;
                tmp->size.first = fontMetrics.horizontalAdvance(QString::fromStdString(op->getText())) * 1.15;
                tmp->size.second = 55;

                tmp->coords_xy.first = wImage / 2 - tmp->size.first / 2 + xBorder;
                tmp->coords_xy.second = y;

                y = y + 40 + tmp->size.second;

                //xBorder = tmp->coords_xy.first + tmp->size.first / 2;
                tempGraphic = new Graphic(x, y);
                tempGraphic->create(((IfOperator*)op)->getBodyBranch(), xBorder, yBorder);
                tmp->subtree = tempGraphic->getTree();

                if ((((IfOperator*)op)->getRightBranch()).size() != 0){
                    tempGraphic2 = new Graphic(tempGraphic->wImage + xBorder + 50, y);
                    tempGraphic2->create(((IfOperator*)op)->getRightBranch(), tempGraphic2->x + xBorder, yBorder);
                    tmp->elseBranch = tempGraphic2->getTree();
                    y = tempGraphic->y > tempGraphic2->y ? tempGraphic->y : tempGraphic2->y ;
                } else {
                    y = tempGraphic->y;
                }
                break;
            case(loop_op):
                tmp->shape = loop;
                tmp->size.first = fontMetrics.horizontalAdvance(QString::fromStdString(op->getText())) * 1.15;
                tmp->size.second = 55;

                tmp->coords_xy.first = wImage / 2 - tmp->size.first / 2 + xBorder;
                tmp->coords_xy.second = y;

                y = y + 40 + tmp->size.second;

                tempGraphic = new Graphic(x, y);
                tempGraphic->create(((LoopOperator*)op)->getBodyBranch(), xBorder, yBorder);
                tmp->subtree = tempGraphic->getTree();

                y = tempGraphic->y;
                delete tempGraphic;
                break;
        }
        tmp->text = op->getText();
        tree.push_back(tmp);
    }
    hImage = y;

    return tree;
}



void Graphic::draw(QString filename){
    QImage image(wImage, hImage, QImage::Format_RGB32);
    QPainter painter(&image);

    painter.fillRect(image.rect(), Qt::white);

    drawTree(painter, tree);

    image.save(filename + "34567");
}

void Graphic::drawTree(QPainter& painter, std::vector<Block*> tree){
    QFont font("Arial", 16);
    QFontMetrics fontMetrics(font);
    painter.setFont(font);

    QString text;
    int textX, textY;
    int textW, textH;

    for (size_t i = 0 ; i < tree.size(); ++ i){
        QPolygon p;

        if (tree[i] == NULL){
            continue;
        }
        text = QString::fromStdString(tree[i]->text);
        textW = fontMetrics.horizontalAdvance(text);
        textH = fontMetrics.height();
        textX = tree[i]->coords_xy.first + tree[i]->size.first * 0.5 - textW / 2;
        textY = tree[i]->coords_xy.second + tree[i]->size.second / 2 + textH / 3;

        painter.drawText(textX, textY, text);

        if (tree[i]->shape == elipse){
            painter.drawEllipse(tree[i]->coords_xy.first, tree[i]->coords_xy.second, tree[i]->size.first, tree[i]->size.second);
        } else if (tree[i]->shape == paral){
            p << QPoint(tree[i]->coords_xy.first + tree[i]->size.first * 0.1, tree[i]->coords_xy.second);
            p << QPoint(tree[i]->coords_xy.first + tree[i]->size.first, tree[i]->coords_xy.second);
            p << QPoint(tree[i]->coords_xy.first + tree[i]->size.first * 0.8, tree[i]->coords_xy.second + tree[i]->size.second);
            p << QPoint(tree[i]->coords_xy.first - tree[i]->size.first * 0.1, tree[i]->coords_xy.second + tree[i]->size.second);
            painter.drawPolygon(p);
        } else if (tree[i]->shape == rhomb){
            p << QPoint(tree[i]->coords_xy.first +tree[i]->size.first * 0.5, tree[i]->coords_xy.second);
            p << QPoint(tree[i]->coords_xy.first +tree[i]->size.first, tree[i]->coords_xy.second + tree[i]->size.second * 0.5);
            p << QPoint(tree[i]->coords_xy.first +tree[i]->size.first * 0.5, tree[i]->coords_xy.second + tree[i]->size.second);
            p << QPoint(tree[i]->coords_xy.first, tree[i]->coords_xy.second + tree[i]->size.second * 0.5);

            painter.drawPolygon(p);

            if (tree[i]->subtree.size()){
                tree[0]->subtree.push_back(tree[i+1]);
                drawTree(painter, tree[i]->subtree);
            }

            if (tree[i]->elseBranch.size()){
                tree[0]->elseBranch.push_back(tree[i+1]);
                drawTree(painter, tree[i]->elseBranch);
            }

        } else if (tree[i]->shape == loop) {
            p << QPoint(tree[i]->coords_xy.first +tree[i]->size.first * 0.1, tree[i]->coords_xy.second);
            p << QPoint(tree[i]->coords_xy.first +tree[i]->size.first * 0.9, tree[i]->coords_xy.second);
            p << QPoint(tree[i]->coords_xy.first +tree[i]->size.first, tree[i]->coords_xy.second + tree[i]->size.second * 0.5);
            p << QPoint(tree[i]->coords_xy.first +tree[i]->size.first, tree[i]->coords_xy.second + tree[i]->size.second);
            p << QPoint(tree[i]->coords_xy.first, tree[i]->coords_xy.second + tree[i]->size.second);
            p << QPoint(tree[i]->coords_xy.first, tree[i]->coords_xy.second + tree[i]->size.second * 0.5);

            painter.drawPolygon(p);

            if (tree[i]->subtree.size()){
                drawTree(painter, tree[i]->subtree);
            }
        } else if (tree[i]->shape == rect){
                painter.drawRect(tree[i]->coords_xy.first, tree[i]->coords_xy.second, tree[i]->size.first, tree[i]->size.second);
        }
    }

    for (size_t i = 0; i < tree.size() - 1; ++i){
        if (tree[i]->shape == loop){
            QPoint p1 = QPoint(tree[i]->coords_xy.first + tree[i]->size.first, tree[i]->coords_xy.second + tree[i]->size.second / 2);
            QPoint p2 = QPoint(tree[i]->coords_xy.first + tree[i]->size.first * 2, tree[i]->coords_xy.second + tree[i]->size.second / 2);
            QPoint p3 = QPoint(tree[i]->coords_xy.first + tree[i]->size.first * 2, tree[i + 1]->coords_xy.second + tree[i + 1]->size.second / 2);
            QPoint p4 = QPoint(tree[i + 1]->coords_xy.first + tree[i + 1]->size.first, tree[i + 1]->coords_xy.second + tree[i + 1]->size.second / 2);
            painter.drawLine(p1, p2);
            painter.drawLine(p2, p3);
            painter.drawLine(p3, p4);

            //body
            Block* body = tree[i]->subtree[0];
            if (abs((tree[i]->coords_xy.first + tree[i]->size.first / 2) - (body->coords_xy.first + body->size.first / 2)) < 10){
                p1 = QPoint(tree[i]->coords_xy.first + tree[i]->size.first / 2, tree[i]->coords_xy.second + tree[i]->size.second);
                p2 = QPoint(body->coords_xy.first + body->size.first / 2, body->coords_xy.second);
                painter.drawLine(p1, p2);
            } else {
                p1 = QPoint(tree[i]->coords_xy.first + tree[i]->size.first / 2, tree[i]->coords_xy.second + tree[i]->size.second);
                p2 = QPoint(tree[i]->coords_xy.first + tree[i]->size.first / 2, tree[i]->coords_xy.second + tree[i]->size.second);
                p3 = QPoint(body->coords_xy.first + body->size.first / 2, tree[i]->coords_xy.second + tree[i]->size.second);
                p4 = QPoint(body->coords_xy.first + body->size.first / 2, body->coords_xy.second);
                painter.drawLine(p1, p2);
                painter.drawLine(p2, p3);
                painter.drawLine(p3, p4);
            }
        } else if (tree[i]->shape == rhomb){
            // left
            QPoint p1 = QPoint(tree[i]->coords_xy.first, tree[i]->coords_xy.second + tree[i]->size.second * 0.5);
            Block* left = tree[i]->subtree[0];
            QPoint p2 = QPoint(left->coords_xy.first + left->size.first * 0.5, tree[i]->coords_xy.second + tree[i]->size.second * 0.5);
            QPoint p3 = QPoint(left->coords_xy.first + left->size.first * 0.5, left->coords_xy.second);
            painter.drawLine(p1, p2);
            painter.drawLine(p2, p3);

            // right
            if (tree[i]->elseBranch.size()){
                p1 = QPoint(tree[i]->coords_xy.first + tree[i]->size.first, tree[i]->coords_xy.second + tree[i]->size.second * 0.5);
                Block* right = tree[i]->elseBranch[0];
                p2 = QPoint(right->coords_xy.first + right->size.first * 0.5, tree[i]->coords_xy.second + tree[i]->size.second * 0.5);
                p3 = QPoint(right->coords_xy.first + right->size.first * 0.5, right->coords_xy.second);
                painter.drawLine(p1, p2);
                painter.drawLine(p2, p3);
            } else {
//                if (abs((tree[i]->coords_xy.first + tree[i]->size.first / 2) - (tree[i + 1]->coords_xy.first + tree[i + 1]->size.first / 2)) < 10){
//                    QPoint p1 = QPoint(tree[i]->coords_xy.first + tree[i]->size.first / 2, tree[i]->coords_xy.second + tree[i]->size.second);
//                    QPoint p2 = QPoint(tree[i + 1]->coords_xy.first + tree[i + 1]->size.first / 2, tree[i + 1]->coords_xy.second);
//                    painter.drawLine(p1, p2);
//                } else {
//                    QPoint p1 = QPoint(tree[i]->coords_xy.first + tree[i]->size.first / 2, tree[i]->coords_xy.second + tree[i]->size.second);
//                    QPoint p2 = QPoint(tree[i]->coords_xy.first + tree[i]->size.first / 2, tree[i + 1]->coords_xy.second - 15);
//                    QPoint p3 = QPoint(tree[i + 1]->coords_xy.first + tree[i + 1]->size.first / 2, tree[i + 1]->coords_xy.second - 15);
//                    QPoint p4 = QPoint(tree[i + 1]->coords_xy.first + tree[i + 1]->size.first / 2, tree[i + 1]->coords_xy.second);
//                    painter.drawLine(p1, p2);
//                    painter.drawLine(p2, p3);
//                    painter.drawLine(p3, p4);
//                }
            }

        } else if (tree[i]->shape == rect || tree[i]->shape == elipse || tree[i]->shape == paral){
            if (abs((tree[i]->coords_xy.first + tree[i]->size.first / 2) - (tree[i + 1]->coords_xy.first + tree[i + 1]->size.first / 2)) < 10){
                QPoint p1 = QPoint(tree[i]->coords_xy.first + tree[i]->size.first / 2, tree[i]->coords_xy.second + tree[i]->size.second);
                QPoint p2 = QPoint(tree[i + 1]->coords_xy.first + tree[i + 1]->size.first / 2, tree[i + 1]->coords_xy.second);
                painter.drawLine(p1, p2);
            } else {
                QPoint p1 = QPoint(tree[i]->coords_xy.first + tree[i]->size.first / 2, tree[i]->coords_xy.second + tree[i]->size.second);
                QPoint p2 = QPoint(tree[i]->coords_xy.first + tree[i]->size.first / 2, tree[i + 1]->coords_xy.second - 15);
                QPoint p3 = QPoint(tree[i + 1]->coords_xy.first + tree[i + 1]->size.first / 2, tree[i + 1]->coords_xy.second - 15);
                QPoint p4 = QPoint(tree[i + 1]->coords_xy.first + tree[i + 1]->size.first / 2, tree[i + 1]->coords_xy.second);
                painter.drawLine(p1, p2);
                painter.drawLine(p2, p3);
                painter.drawLine(p3, p4);
            }

            /*QPoint p1(tree[i]->coords_xy.first + tree[i]->size.first / 2, tree[i]->coords_xy.second + tree[i]->size.second);
            QPoint p2(tree[i + 1]->coords_xy.first + tree[i + 1]->size.first / 2, tree[i + 1]->coords_xy.second);
            painter.drawLine(p1, p2);*/
        }
    }
}

int Graphic::calcMaxWidth(std::vector<BaseOperator*> ops){
    QFont font("Arial", 25);
    QFontMetrics fontMetrics(font);
    int maxWidth = 0, tmp, tmp2;

    for (auto op : ops) {
        tmp = fontMetrics.horizontalAdvance(QString::fromStdString(op->getText()));
        switch (op->getType()) {
            case(start):
                if (maxWidth < tmp * 1.1){
                    maxWidth = tmp * 1.1;
                }
                break;
            case(end):
                if (maxWidth < tmp * 1.3){
                    maxWidth = tmp * 1.3;
                }
                break;
            case(input_op):
                if (maxWidth < tmp * 1.12){
                    maxWidth = tmp * 1.12;
                }
                break;
            case(output_op):
                if (maxWidth < tmp * 1.12){
                    maxWidth = tmp * 1.12;
                }
                break;
            case(if_op):
                tmp = calcMaxWidth(((IfOperator*)op)->getBodyBranch());
                tmp2 = calcMaxWidth(((IfOperator*)op)->getRightBranch());
                if (tmp < tmp2){
                    tmp = tmp2;
                }

                if (maxWidth < tmp * 2){
                    maxWidth = tmp * 2;
                }
                break;
            case(loop_op):
                tmp = calcMaxWidth(((LoopOperator*)op)->getBodyBranch());
                if (maxWidth < tmp){
                    maxWidth = tmp;
                }
                break;
            case(other_op):
                if (maxWidth < tmp * 1.13){
                    maxWidth = tmp * 1.13;
                }
                break;
            default:
                if (maxWidth < tmp * 1.13){
                    maxWidth = tmp * 1.13;
                }
        }
    }
    return maxWidth;
}


























