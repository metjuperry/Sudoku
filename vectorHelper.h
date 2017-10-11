#ifndef SUDOKU_VECTORHELPER_H
#define SUDOKU_VECTORHELPER_H

#include "Table.h"

class vectorHelper {
public:
    explicit vectorHelper(Table *tables);

    static int pickRandomfromList(std::vector<int> list);

    static std::vector<int> RemoveSame(std::vector<int> a, std::vector<int> b);
    static std::vector<int> GetCommon(std::vector<int> a, std::vector<int> b);

    std::pair<int, int> GetFieldCoordsByCoords(float row, float col);

    Field GetFieldByCoords(float row, float col);

    std::vector<std::pair<int, int>> GetWholeRow(float row);
    std::vector<std::pair<int, int>> GetWholeCol(float col);

    std::vector<int> GetRowNumbers(float row);
    std::vector<int> GetColNumbers(float col);

    std::vector<int> GetPossibleNumbersInRow(float row);
    std::vector<int> GetPossibleNumbersInCol(float col);
    std::vector<int> GetPossibleNumbersInTable(int table);

    int GetValidNumber(float row, float col, int table);

    bool IsValidNumber(float row, float col, int number);

    void saveList(std::vector<int> List);
    std::vector<int> RefreshList();

    const std::pair<int, int> &getBothFieldCoordinates() const;

    void setFieldCoordinates(float row, float col);

    const float &getRow() const;

    const float &getCol() const;

    void MoveForward();

    void MoveBackward();

private:
    Table *_tables;
    std::vector<int> OriginalList;
    std::pair<float, float> fieldCoordinates;
};


#endif //SUDOKU_VECTORHELPER_H
