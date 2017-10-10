#include "Table.h"

Table::Table() = default;

void Table::setRect(double x, double y){
    rectangle.setSize(sf::Vector2f(w,w));
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(5);
    rectangle.setPosition(static_cast<float>(x), static_cast<float>(y));

    this->setFields(x, y);
}

void Table::draw(sf::RenderWindow &window){
    window.draw(rectangle);
    for(auto field:fields){
        field.show(window);
    }
}


void Table::setFields(double _x, double _y) {
    int num = 0;
    double x = _x;
    double y = _y;

    for (int rows = 0; rows != 3; rows++){
        for (int cols = 0; cols != 3; cols++){
            fields[num].setRect(x, y, w/3);
            num++;
            x += w/3;
        }
        x = _x;
        y += w/3;
    }
}

void Table::checkFieldsCollision(sf::Vector2i mousecoords) {
    for(auto collisionRectangle:fields){
        if(collisionRectangle.collision(mousecoords)){
            //TODO: It recognises collision, but doesn't do the function?
            collisionRectangle.setNum(2);
        }
    }
}

Field *Table::getFields() {
    return fields;
}

std::vector<int> Table::GetRowCoords(int row){
    std::vector<int> RowCoordsArray;
    switch(row){
        case 1:
            RowCoordsArray.emplace_back(0);
            RowCoordsArray.emplace_back(1);
            RowCoordsArray.emplace_back(2);
            break;
        case 2:
            RowCoordsArray.emplace_back(3);
            RowCoordsArray.emplace_back(4);
            RowCoordsArray.emplace_back(5);
            break;
        case 3:
            RowCoordsArray.emplace_back(6);
            RowCoordsArray.emplace_back(7);
            RowCoordsArray.emplace_back(8);
            break;
        default:
            std::cout << "Not a row number" << row << std::endl;
            break;
    }
    return RowCoordsArray;
}

std::vector<int> Table::GetColCoords(int col){
    std::vector<int> ColCoordsArray;
    switch(col){
        case 1:
            ColCoordsArray.emplace_back(0);
            ColCoordsArray.emplace_back(3);
            ColCoordsArray.emplace_back(6);
            break;
        case 2:
            ColCoordsArray.emplace_back(1);
            ColCoordsArray.emplace_back(4);
            ColCoordsArray.emplace_back(7);
            break;
        case 3:
            ColCoordsArray.emplace_back(2);
            ColCoordsArray.emplace_back(5);
            ColCoordsArray.emplace_back(8);
            break;
        default:
            std::cout << "Not a col number" << col << std::endl;
            break;
    }
    return ColCoordsArray;
}

bool Table::AllFieldsFilled() {
    for(auto field: fields){
        if(field.getNum() == 0){
            return false;
        }
    }
    return true;
}

