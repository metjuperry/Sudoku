#ifndef SUDOKU_FIELD_H
#define SUDOKU_FIELD_H

#include "stdafx.h"

class Field {
public:
    Field();
    void switchVisible();
    virtual void show(sf::RenderWindow &window);

    void setRect(double x, double y, int w);
    void setNum(int num);
    int getNum() const;

    bool collision(sf::Vector2i mouseCoords);
private:
    int _x,_y,_w;
    bool shown;
    int _num;

    sf::Font SanFran;
    sf::Text number;
    sf::RectangleShape field;
};


#endif //SUDOKU_FIELD_H
