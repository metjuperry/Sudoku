#ifndef SUDOKU_FIELD_H
#define SUDOKU_FIELD_H

#include "stdafx.h"

class Field {
public:
    Field();

    void switchVisible();

    void switchGuessed();

    bool isShown() const;

    bool isGuessed() const;

    virtual void show(sf::RenderWindow &window);

    void setRect(double x, double y, int w);

    void setNum(int num);

    int getNum() const;

    bool collision(sf::Vector2i mouseCoords);

    const std::vector<int> &getPossibilities() const;

    void setPossibilities(const std::vector<int> &Possibilities);

    void eraseFromPossibilities(int possibility);

    void set_guessNum(int guessNum);

    bool checkCorrect();

    void validateGuessed();

private:
    int _x, _y, _w;
    bool shown, guessed;
    int _num, _guessNum;

    sf::Font SanFran;
    sf::Text number, Guessnumber;
    sf::RectangleShape field;

    std::vector<int> Possibilities;
};


#endif //SUDOKU_FIELD_H
