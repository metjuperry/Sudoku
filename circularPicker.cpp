#include "circularPicker.h"
#include "vectorHelper.h"

#define PI 3.14159265

circularPicker::circularPicker() {
    radius = 80.0f;

    _OuterCircle.setRadius(radius);
    _OuterCircle.setPointCount(9);
    _OuterCircle.setFillColor(sf::Color::White);
    _OuterCircle.setOutlineThickness(2);
    _OuterCircle.setOutlineColor(sf::Color::Black);

    _InnerCircle.setRadius(radius / 2);
    _InnerCircle.setPointCount(9);
    _InnerCircle.setFillColor(sf::Color::Transparent);
    _InnerCircle.setOutlineThickness(2);
    _InnerCircle.setOutlineColor(sf::Color::Black);

    _visible = false;

    breakingPoints.emplace_back(std::make_pair(50.0f, 90.0f)); // 1
    breakingPoints.emplace_back(std::make_pair(90.0f, 130.0f)); // 2
    breakingPoints.emplace_back(std::make_pair(130.0f, 170.0f)); // 3
    breakingPoints.emplace_back(std::make_pair(170.0f, 210.0f)); // 4
    breakingPoints.emplace_back(std::make_pair(210.0f, 250.0f)); // 5
    breakingPoints.emplace_back(std::make_pair(250.0f, 290.0f)); // 6
    breakingPoints.emplace_back(std::make_pair(290.0f, 330.0f)); // 7
    breakingPoints.emplace_back(std::make_pair(330.0f, 360.0f)); // 8
    breakingPoints.emplace_back(std::make_pair(10.0f, 50.0f)); // 9
}

void circularPicker::show(sf::RenderWindow &window) {
    _OuterCircle.setPosition(_mouseXOuter, _mouseYOuter);
    _InnerCircle.setPosition(_mouseXInner, _mouseYInner);

    if (_visible) {
        window.draw(_OuterCircle);
        window.draw(_InnerCircle);
    }
}

void circularPicker::setPosition(sf::Vector2i mouseCoords) {
    _mouseXOuter = mouseCoords.x - radius;
    _mouseYOuter = mouseCoords.y - radius;

    _mouseXInner = mouseCoords.x - radius / 2;
    _mouseYInner = mouseCoords.y - radius / 2;
}

void circularPicker::switchVisible() {
    _visible = !_visible;
}

bool circularPicker::isBetween(float firstNumber, float secondNumber, float betweenNumber) {
    if (firstNumber > secondNumber) {
        return firstNumber > betweenNumber && betweenNumber > secondNumber;
    } else {
        return firstNumber < betweenNumber && betweenNumber < secondNumber;
    }
}

int circularPicker::getNumberOnRadial(sf::Vector2f numbers) {
    float currentAngle = vectorHelper::getFullCircleAngle(
            atan2(vectorHelper::Normalize(numbers).y, vectorHelper::Normalize(numbers).x) * (180.0f / PI));

    for (int i = 0; i != breakingPoints.size(); i++) {
        if (isBetween(breakingPoints[i].first, breakingPoints[i].second, currentAngle)) {
            return i + 1;
        }
    }
    return 8;
}

bool circularPicker::is_visible() const {
    return _visible;
}
