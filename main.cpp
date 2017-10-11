#include "Table.h"
#include "vectorHelper.h"

void write_text_to_log_file(const std::string &text) {
    std::ofstream log_file(
            "log_text.txt", std::ios_base::out | std::ios_base::app);
    log_file << text << std::endl;
    log_file.close();
}

void clear_text_in_log_file() {
    std::ofstream ofs;
    ofs.open("log_text.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void read_text() {
    std::string line;
    std::ifstream myfile("log_text.txt");
    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            std::cout << line << '\n';
        }
        myfile.close();
    } else std::cout << "Unable to open file";

}

void generateSudoku(Table Tables[]) {
    vectorHelper Vector(Tables);
    bool itsDone = false;
    clear_text_in_log_file();

    std::vector<int> OriginalList = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Vector.saveList(OriginalList);
    int counter = 0;
    Vector.setFieldCoordinates(1.0f, 1.0f);

    while (!itsDone) {
        counter++;
        write_text_to_log_file(std::to_string(counter) + ": Working on " + std::to_string(
                static_cast<int>(Vector.getRow())) + " " + std::to_string(static_cast<int>(Vector.getCol())) + "\n");

        std::pair<int, int> WorkedOnCoords = Vector.GetFieldCoordsByCoords(Vector.getRow(), Vector.getCol());
        Field *WorkedOn = &Tables[WorkedOnCoords.first].getFields()[WorkedOnCoords.second];

        if (WorkedOn->getPossibilities().empty()) {
            WorkedOn->setPossibilities(Vector.RefreshList());

            //Move back one square
            Vector.MoveBackward();
            WorkedOn->setNum(0);
            write_text_to_log_file(std::to_string(counter) + ": All possibilities empty. Refreshing and moving to " +
                                   std::to_string(static_cast<int>(Vector.getRow())) + " "
                                   + std::to_string(static_cast<int>(Vector.getCol())) + "\n");
        } else {
            int TryNumber = vectorHelper::pickRandomfromList(WorkedOn->getPossibilities());
            write_text_to_log_file(std::to_string(counter) + ": Trying " + std::to_string(TryNumber) + "\n");
            if (!Vector.IsValidNumber(Vector.getRow(),
                                      Vector.getCol(),
                                      TryNumber)) {
                WorkedOn->eraseFromPossibilities(TryNumber);
                write_text_to_log_file(
                        std::to_string(counter) + ": Not possible, removing " + std::to_string(TryNumber) +
                        " from possibilities" + "\n");;
                write_text_to_log_file(std::to_string(counter) + ": Remaining: ");

                for (auto number:WorkedOn->getPossibilities()) {
                    write_text_to_log_file(std::to_string(number));
                }
                write_text_to_log_file("\n");

            } else {
                WorkedOn->setNum(TryNumber);

                write_text_to_log_file(
                        std::to_string(counter) + ": " + std::to_string(TryNumber) + " works, writing " + "\n");

                // Move forward one square
                Vector.MoveForward();
                write_text_to_log_file(std::to_string(counter) + ": Moving on to " +
                                       std::to_string(static_cast<int>(Vector.getRow())) + " " +
                                       std::to_string(static_cast<int>(Vector.getCol())) + "\n");
            }
        }
        if (Vector.getRow() == 10.0f && Vector.getCol() == 1.0f) {
            write_text_to_log_file(std::to_string(counter) + ": Final field " + "\n");
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
