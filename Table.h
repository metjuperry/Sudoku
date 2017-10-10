#ifndef SUDOKU_TABLE_H
#define SUDOKU_TABLE_H


#include "stdafx.h"
#include "Field.h"

class Table {
public:
    Table();
    void setRect(double x, double y);
    virtual void draw(sf::RenderWindow &window);

    Field *getFields();

    void setFields(double _x, double _y);
    void checkFieldsCollision(sf::Vector2i mousecoords);

    bool AllFieldsFilled();

    std::vector<int> GetRowCoords(int row);
    std::vector<int> GetColCoords(int col);
private:
    int w = 150;
    Field fields[9];
    sf::RectangleShape rectangle;
};


#endif //SUDOKU_TABLE_H
