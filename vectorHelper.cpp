#include "vectorHelper.h"

#include <utility>

vectorHelper::vectorHelper(Table *tables) {
    _tables = tables;
}

int vectorHelper::pickRandomfromList(std::vector<int> list) {
    int index = rand() % list.size();
    return list[index];
}

std::vector<int> vectorHelper::RemoveSame(std::vector<int> a, std::vector<int> b) {
    std::vector<int> difference;

    if (a.size() == b.size()) {
        return a;
    } else {

        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());

        std::set_difference(
                a.begin(), a.end(),
                b.begin(), b.end(),
                std::back_inserter(difference)
        );
    }
    return difference;
}

std::vector<int> vectorHelper::GetCommon(std::vector<int> a, std::vector<int> b) {
    std::vector<int> Common;

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    std::set_intersection(
            a.begin(), a.end(),
            b.begin(), b.end(),
            std::back_inserter(Common)
    );
    return Common;
}

std::pair<int, int> vectorHelper::GetFieldCoordsByCoords(float row, float col) {
    std::vector<std::pair<int, int>> Row = GetWholeRow(row);
    std::vector<std::pair<int, int>> Col = GetWholeCol(col);

    for (auto RowField : Row) {
        for (auto ColField : Col) {
            if (RowField == ColField) {
                return RowField;
            }
        }
    }
}

Field vectorHelper::GetFieldByCoords(float row, float col) {
    std::vector<std::pair<int, int>> Row = GetWholeRow(row);
    std::vector<std::pair<int, int>> Col = GetWholeCol(col);

    for (auto RowField : Row) {
        for (auto ColField : Col) {
            if (RowField == ColField) {
                return _tables[RowField.first].getFields()[RowField.second];
            }
        }
    }
}

std::vector<std::pair<int, int>> vectorHelper::GetWholeRow(float row) {
    int start, finish;
    std::vector<std::pair<int, int>> RowCoords;

    if (row / 3 <= 1) {
        start = 0;
        finish = 3;
    } else if (row / 3 > 1 && row / 3 <= 2) {
        start = 3;
        finish = 6;
    } else {
        start = 6;
        finish = 9;
    }

    if (row > 6.0f) {
        row -= 6.0f;
    } else if (row > 3.0f) {
        row -= 3.0f;
    }

    for (int TableCoords = start; TableCoords != finish; TableCoords++) {
        std::vector<int> RowInCoords = _tables[TableCoords].GetRowCoords(static_cast<int>(row));
        for (auto coord: RowInCoords) {
            RowCoords.emplace_back(std::make_pair(TableCoords, coord));
        }
    }
    return RowCoords;
}

std::vector<std::pair<int, int>> vectorHelper::GetWholeCol(float col) {
    std::vector<std::pair<int, int>> ColCoords;

    int columnTables[] = {0, 3, 6};

    if (col / 3 > 1 && col / 3 <= 2) {
        for (int i = 0; i != 3; i++) {
            columnTables[i] = columnTables[i] + 1;
        }
    } else if (col / 3 > 2) {
        for (int i = 0; i != 3; i++) {
            columnTables[i] = columnTables[i] + 2;
        }
    }

    if (col > 6.0f) {
        col -= 6.0f;
    } else if (col > 3.0f) {
        col -= 3.0f;
    }

    for (int tableReference:columnTables) {
        std::vector<int> ColInCoords = _tables[tableReference].GetColCoords(static_cast<int>(col));
        for (auto field:ColInCoords) {
            ColCoords.emplace_back(std::make_pair(tableReference, field));
        }
    }

    return ColCoords;
}

std::vector<int> vectorHelper::GetRowNumbers(float row) {
    std::vector<int> RowPossibilities;

    for (auto field : GetWholeRow(row)) {
        RowPossibilities.emplace_back(_tables[field.first].getFields()[field.second].getNum());
    }

    return RowPossibilities;
}

std::vector<int> vectorHelper::GetColNumbers(float col) {
    std::vector<int> ColPossibilities;

    for (auto field : GetWholeCol(col)) {
        ColPossibilities.emplace_back(_tables[field.first].getFields()[field.second].getNum());
    }

    return ColPossibilities;
}

std::vector<int> vectorHelper::GetPossibleNumbersInRow(float row) {
    std::vector<int> AllNumbers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::vector<int> PossibleNumbers = RemoveSame(AllNumbers, GetRowNumbers(row));

    return PossibleNumbers;
}

std::vector<int> vectorHelper::GetPossibleNumbersInCol(float col) {
    std::vector<int> AllNumbers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::vector<int> PossibleNumbers = RemoveSame(AllNumbers, GetColNumbers(col));

    return PossibleNumbers;
}

std::vector<int> vectorHelper::GetPossibleNumbersInTable(int table) {
    std::vector<int> AllNumbers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::vector<int> NumbersInTable;

    for (int field = 0; field != 9; field++) {
        NumbersInTable.emplace_back(_tables[table].getFields()[field].getNum());
    }

    return RemoveSame(AllNumbers, NumbersInTable);
}

int vectorHelper::GetValidNumber(float row, float col, int table) {
    std::vector<int> NumberInRow = GetPossibleNumbersInRow(row);
    std::vector<int> NumberInCol = GetPossibleNumbersInCol(col);
    std::vector<int> NumberInTable = GetPossibleNumbersInTable(table);

    return pickRandomfromList(GetCommon(GetCommon(NumberInRow, NumberInCol), NumberInTable));
}

bool vectorHelper::IsValidNumber(float row, float col, int number) {
    int table = GetFieldCoordsByCoords(row, col).first;

    std::vector<int> NumberInRow = GetPossibleNumbersInRow(row);
    std::vector<int> NumberInCol = GetPossibleNumbersInCol(col);
    std::vector<int> NumberInTable = GetPossibleNumbersInTable(table);

    std::vector<int> AllPossible = GetCommon(GetCommon(NumberInRow, NumberInCol), NumberInTable);

    return std::find(AllPossible.begin(), AllPossible.end(), number) != AllPossible.end();
}

void vectorHelper::saveList(std::vector<int> List) {
    OriginalList = std::move(List);
}

std::vector<int> vectorHelper::RefreshList() {
    return OriginalList;
}

const std::pair<int, int> &vectorHelper::getBothFieldCoordinates() const {
    return fieldCoordinates;
}

const float &vectorHelper::getRow() const {
    return fieldCoordinates.first;
}

const float &vectorHelper::getCol() const {
    return fieldCoordinates.second;
}

void vectorHelper::setFieldCoordinates(float row, float col) {
    vectorHelper::fieldCoordinates = {row, col};
}

void vectorHelper::MoveForward() {
    if (getCol() == 9.0f) {
        fieldCoordinates.first++;
        fieldCoordinates.second = 1.0f;
    } else {
        fieldCoordinates.second++;
    }
}

void vectorHelper::MoveBackward() {
    if (getCol() == 1.0f) {
        fieldCoordinates.first--;
        fieldCoordinates.second = 9.0f;
    } else {
        fieldCoordinates.second--;
    }
}
