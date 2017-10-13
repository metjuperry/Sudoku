#include "Field.h"

Field::Field() {
    shown = true;
    _num = 0;
    Possibilities = {1, 2, 3, 4, 5, 6, 7, 8, 9};
}

void Field::switchVisible() {
    shown = !shown;
}

void Field::show(sf::RenderWindow &window) {
    window.draw(field);
    if (shown) {
        window.draw(number);
    } else {
        number.setFillColor(sf::Color(0, 0, 0, 100));
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

    field.setSize(sf::Vector2f(w, w));
    field.setOutlineColor(sf::Color::Black);
    field.setOutlineThickness(2);
    field.setPosition(x, y);

    number.setPosition(x + w / 3, y + w / 8);
}


bool Field::collision(sf::Vector2i mouseCoords) {
    sf::IntRect collisionArea(_x, _y, _w, _w);
    return collisionArea.contains(mouseCoords);
}

int Field::getNum() const {
    return _num;
}

const std::vector<int> &Field::getPossibilities() const {
    return Possibilities;
}

void Field::eraseFromPossibilities(int possibility) {
    Possibilities.erase(std::remove(Possibilities.begin(),
                                    Possibilities.end(),
                                    possibility), Possibilities.end());
}

void Field::setPossibilities(const std::vector<int> &Possibilities) {
    Field::Possibilities = Possibilities;
}

bool Field::isShown() const {
    return shown;
}
