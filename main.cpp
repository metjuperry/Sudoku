#include "Table.h"
#include "vectorHelper.h"

void generateSudoku(Table Tables[]) {
    vectorHelper Vector(Tables);
    bool itsDone = false;

    std::vector<int> OriginalList = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Vector.saveList(OriginalList);
    int counter = 0;
    Vector.setFieldCoordinates(1.0f, 1.0f);

    while (!itsDone) {
        counter++;
        std::cout << counter << ": Working on " << Vector.getRow() << " " << Vector.getCol() << std::endl;

        std::pair<int, int> WorkedOnCoords = Vector.GetFieldCoordsByCoords(Vector.getRow(), Vector.getCol());
        Field *WorkedOn = &Tables[WorkedOnCoords.first].getFields()[WorkedOnCoords.second];

        if (WorkedOn->getPossibilities().empty()) {
            WorkedOn->setPossibilities(Vector.RefreshList());

            //Move back one square
            Vector.MoveBackward();
            WorkedOn->setNum(0);
            std::cout << counter << ": All possibilities empty. Refreshing and moving to " << Vector.getRow() << " "
                      << Vector.getCol() << std::endl;
        } else {
            int TryNumber = vectorHelper::pickRandomfromList(WorkedOn->getPossibilities());
            std::cout << counter << ": Trying " << TryNumber << std::endl;
            if (!Vector.IsValidNumber(Vector.getRow(),
                                      Vector.getCol(),
                                      TryNumber)) {
                WorkedOn->eraseFromPossibilities(TryNumber);
                std::cout << counter << ": Not possible, removing " << TryNumber << " from possibilities" << std::endl;
                std::cout << counter << ": Remaining: ";

                for (auto number:WorkedOn->getPossibilities()) {
                    std::cout << number;
                }
                std::cout << std::endl;

            } else {
                WorkedOn->setNum(TryNumber);

                std::cout << counter << ": " << TryNumber << " works, writing " << std::endl;

                // Move forward one square
                Vector.MoveForward();
                std::cout << counter << ": Moving on to " << Vector.getRow() << " " << Vector.getCol() << std::endl;
            }
        }
        if (Vector.getRow() == 10.0f && Vector.getCol() == 1.0f) {
            std::cout << counter << ": Final field" << std::endl;
            itsDone = true;
        }
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sudoku");
    srand(time(NULL));

    Table Tables[9];
    vectorHelper Vector(Tables);

    int num = 0;
    double x = window.getSize().x / 2 - 1.5 * 150;
    double y = window.getSize().y / 2 - 1.5 * 150;

    for (int rows = 0; rows != 3; rows++) {
        for (int cols = 0; cols != 3; cols++) {
            Tables[num].setRect(x, y);
            num++;
            x += 150;
        }
        x = window.getSize().x / 2 - 1.5 * 150;
        y += 150;
    }

    /**
    Code to set a row/col in one big table to a certain number
    std::vector<int> coords = Tables[0].GetRowCoords(1);
    for(auto coord: coords){
        Tables[0].getFields()[coord].setNum(1);
    }

    for (int f = 1; f != 10; f++) {
        //Code to set a whole row in the sudoku to a number
        std::vector<std::pair<int, int>> PairsOfCoordsRow = Vector.GetWholeRow(f);
        for (auto field:PairsOfCoordsRow) {
            Tables[field.first].getFields()[field.second].setNum(1);
        }
    }

    std::vector<std::pair<int, int>> PairOfCoordsCol = Vector.GetWholeCol(5.0f);
    for(auto field:PairOfCoordsCol){
        Tables[field.first].getFields()[field.second].setNum(1);
    }

    int tableCol = 1;
    for (int tableRow = 1; tableRow != 10; tableRow++){
        std::vector<std::pair<int, int>> PairsOfCoordsRow = Vector.GetWholeRow(tableRow);
        for (auto field:PairsOfCoordsRow) {
            Tables[field.first].getFields()[field.second].setNum(Vector.GetValidNumber(tableRow, tableCol, field.first));
            tableCol++;
        }
        tableCol = 1;
    }
    **/

    generateSudoku(Tables);

    while (window.isOpen()) {

        sf::Vector2i mouseCoordinates = (sf::Mouse::getPosition(window));

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        for (auto table: Tables) {
            table.draw(window);
            //table.checkFieldsCollision(mouseCoordinates);
        }
        window.display();
    }

    return 0;
}
