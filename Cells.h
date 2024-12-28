#ifndef CELLS_H
#define CELLS_H

#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Criminal;

const int MAX = 100;

class Cells {
private:
    int cellID;
    string location;
    int capacity;
    int occupancy;

    Criminal *criminal[MAX]; // Array of pointers to criminals

public:
    Cells(int cellID, string location, int capacity, int occupancy) {
        this->cellID = cellID;
        this->location = location;
        this->capacity = capacity;
        this->occupancy = occupancy;
    }

    int getId() {
        return cellID;
    }

    int viewCellsAvailable() {
        json j;
        ifstream file("Cells.json");
        if (file.is_open()) {
            file >> j;
            cout << setw(4) << j << endl;
            file.close();
        } else
            cout << "Cannot display " << endl;
        return 0;
    }

    friend ostream &operator<<(ostream &os, const Cells &cells);

    void assignCellToCriminal() {}

    int getCellId() const {
        return cellID;
    }

    Criminal *const *getCriminal() const {
        return criminal;
    }

    void setOccupancy(int occupancy) {
        Cells::occupancy = occupancy;
    }

    void setCapacity(int capacity) {
        Cells::capacity = capacity;
    }

    void setLocation(const string &location) {
        Cells::location = location;
    }

    void setCellId(int cellId) {
        cellID = cellId;
    }

    const string &getLocation() const;

    int getCapacity() const;

    int getOccupancy() const;

    bool operator<(const Cells &rhs) const;

    bool operator>(const Cells &rhs) const;

    bool operator<=(const Cells &rhs) const;

    bool operator>=(const Cells &rhs) const;

    bool operator==(const Cells &rhs) const;

    bool operator!=(const Cells &rhs) const;
};

#endif
