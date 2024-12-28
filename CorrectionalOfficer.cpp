//
// Created by InnoSTARK on 4/27/2024.
//
#include "CorrectionalOfficer.h"

const vector<Criminal *> &CorrectionalOfficer::getCriminals() const {
    return criminals;
}

const vector<Cells *> &CorrectionalOfficer::getCells() const {
    return cells;
}

int CorrectionalOfficer::getCellCount() const {
    return cellCount;
}

int CorrectionalOfficer::getCrimeCount() const {
    return crimeCount;
}

void CorrectionalOfficer::setCrimeCount(int crimeCount) {
    CorrectionalOfficer::crimeCount = crimeCount;
}

void CorrectionalOfficer::setCellCount(int cellCount) {
    CorrectionalOfficer::cellCount = cellCount;
}

void CorrectionalOfficer::setCells(const vector<Cells *> &cells) {
    CorrectionalOfficer::cells = cells;
}

void CorrectionalOfficer::setCriminals(const vector<Criminal *> &criminals) {
    CorrectionalOfficer::criminals = criminals;
}
