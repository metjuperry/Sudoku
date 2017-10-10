#include "Table.h"
#include "vectorHelper.h"

void generateSudoku(Table Tables[]) {
    vectorHelper Vector(Tables);
    int itsDone = 0;

    std::vector<int> Possibilities = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Vector.saveList(Possibilities);
    float tableCol = 1.0f;
    float tableRow = 1.0f;

    while (itsDone != 9) {
        if (Possibilities.empty()) {
            Possibilities = Vector.RefreshList();

            if (tableCol == 1.0f) {
                tableCol = 9.0f;
                tableRow--;
            } else {
                tableCol--;
            }
        } else {
            int TryNumber = vectorHelper::pickRandomfromList(Possibilities);
            if (!Vector.IsValidNumber(tableRow,
                                      tableCol,
                                      Vector.GetFieldByCoords(tableRow, tableCol).first,
                                      TryNumber)) {
                Possibilities.erase(std::remove(Possibilities.begin(),
                                                Possibilities.end(),
                                                TryNumber), Possibilities.end());
            } else {
                std::pair<int, int> TableCoords = Vector.GetFieldByCoords(tableRow,tableCol);
                Tables[TableCoords.first].getFields()[TableCoords.second].setNum(TryNumber);

                if(tableCol == 9.0f){
                    tableCol = 1.0f;
                    tableRow++;
                } else {
                    tableCol++;
                }
            }
        }
        for (int DoneHelper = 0; DoneHelper != 9; DoneHelper++){
            if(Tables[DoneHelper].AllFieldsFilled()){
                itsDone++;
            }
        }
        if (itsDone < 9){
            itsDone = 0;
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
            table.checkFieldsCollision(mouseCoordinates);
        }
        window.display();
    }

    return 0;
}
