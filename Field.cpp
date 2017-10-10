#include "Field.h"

Field::Field() {
    shown = true;
}

void Field::switchVisible() {
    shown = !shown;
}

void Field::show(sf::RenderWindow &window) {
    window.draw(field);
    if(shown){
        window.draw(number);
    }
}

void Field::setNum(int num) {
    _num = num;
    SanFran.loadFromFile("San Francisco.ttf");
    number.setFont(SanFran);

    std::stringstream boxContent;
    boxContent << num;

    number.setString(boxContent.str());
    number.setFillColor(sf::Color::Black);

}

void Field::setRect(double x, double y, int w) {
    _x = static_cast<int>(x);
    _y = static_cast<int>(y);
    _w = w;

    field.setSize(sf::Vector2f(w,w));
    field.setOutlineColor(sf::Color::Black);
    field.setOutlineThickness(2);
    field.setPosition(x, y);

    number.setPosition(x + w/3, y + w/8);
}


bool Field::collision(sf::Vector2i mouseCoords) {
    sf::IntRect collisionArea(_x,_y,_w,_w);
    return collisionArea.contains(mouseCoords);
}

int Field::getNum() const {
    return _num;
}
