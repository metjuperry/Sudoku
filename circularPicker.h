#ifndef SUDOKU_CIRCULARPICKER_H
#define SUDOKU_CIRCULARPICKER_H

#include "stdafx.h"

class circularPicker {
public:
    circularPicker();

    void setPosition(sf::Vector2i mouseCoords);

    void show(sf::RenderWindow &window);

    static bool isBetween(float firstNumber, float secondNumber, float betweenNumber);

    int getNumberOnRadial(sf::Vector2f numbers);

    void switchVisible();

private:
    float radius;
    float _mouseXOuter, _mouseYOuter, _mouseXInner, _mouseYInner;
    bool _visible;
    sf::CircleShape _OuterCircle;
    sf::CircleShape _InnerCircle;

    std::vector<std::pair<float, float>> breakingPoints;
};


#endif //SUDOKU_CIRCULARPICKER_H
