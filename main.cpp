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

void hideNumbers(Table Tables[]) {
    int numOfHidden = 57;
    std::vector<std::pair<int, int>> CoordsOfFields;
    write_text_to_log_file("Starting the hiding process");

    for (int tables = 0; tables != 9; tables++) {
        for (int field = 0; field != 9; field++) {
            CoordsOfFields.emplace_back(std::make_pair(tables, field));
        }
    }

    for (int range = 0; range != numOfHidden; range++) {
        int randomPair = rand() % CoordsOfFields.size();
        std::pair<int, int> FieldToBeVisible = CoordsOfFields[randomPair];
        write_text_to_log_file("Hiding number at coords " + std::to_string(FieldToBeVisible.first) + " " +
                               std::to_string(FieldToBeVisible.second));

        Tables[FieldToBeVisible.first].getFields()[FieldToBeVisible.second].switchVisible();

        CoordsOfFields.erase(std::remove(CoordsOfFields.begin(),
                                         CoordsOfFields.end(),
                                         FieldToBeVisible), CoordsOfFields.end());
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sudoku");
    srand(time(NULL));

    Table Tables[9];
    vectorHelper Vector(Tables);
    sf::Uint8 opacity = 255;

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

    enum GameState {
        Generating, Transition, Playing
    };
    GameState CurrentGameState = Generating;

    sf::Font SanFran;
    sf::Text CurrentAction;
    sf::Time generatedIn;

    SanFran.loadFromFile("San Francisco.ttf");

    CurrentAction.setFont(SanFran);
    CurrentAction.setFillColor(sf::Color(0, 0, 0, opacity));
    CurrentAction.setPosition(window.getSize().x / 1.5,
                              window.getSize().y / 1.2);
    CurrentAction.setCharacterSize(45);
    CurrentAction.setString("Generating...");


    while (window.isOpen()) {
        sf::Vector2i mouseCoordinates = (sf::Mouse::getPosition(window));
        switch (CurrentGameState) {
            case Generating: {
                sf::Event MenuEvent;
                while (window.pollEvent(MenuEvent)) {
                    if (MenuEvent.type == sf::Event::Closed)
                        window.close();
                }

                window.clear(sf::Color::White);
                window.draw(CurrentAction);
                window.display();

                sf::Clock Timer;
                generateSudoku(Tables);
                generatedIn = Timer.getElapsedTime();

                hideNumbers(Tables);

                CurrentGameState = Transition;
                break;
            }
            case Transition: {
                window.clear(sf::Color::White);
                CurrentAction.setString("Generated. \n" + std::to_string(generatedIn.asSeconds()) + " sec");
                CurrentAction.setFillColor(sf::Color(0, 0, 0, opacity));
                opacity = opacity - sf::Uint8(1);

                if (opacity < 10) {
                    CurrentGameState = Playing;
                }
                window.draw(CurrentAction);
                window.display();
                break;
            }

            case Playing: {
                sf::Event PlayingEvent;
                while (window.pollEvent(PlayingEvent)) {
                    if (PlayingEvent.type == sf::Event::Closed)
                        window.close();
                    else if (PlayingEvent.type == sf::Event::EventType::MouseButtonPressed &&
                             sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        for (int table = 0; table != 9; table++) {
                            for (int field = 0; field != 9; field++) {
                                if (Tables[table].getFields()[field].collision(mouseCoordinates)) {
                                    Tables[table].getFields()[field].setNum(2);
                                }
                            }
                        }
                    }
                }

                window.clear(sf::Color::White);
                for (auto table: Tables) {
                    table.draw(window);
                }
                window.display();
                break;
            }
        }
    }

    return 0;
}
