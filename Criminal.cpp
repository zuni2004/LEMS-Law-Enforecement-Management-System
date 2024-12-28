//
// Created by InnoSTARK on 4/27/2024.
//
#include "Criminal.h"

ostream &operator<<(ostream &os, const Criminal &criminal) {
    os << "criminalID: " << criminal.criminalID << " name: " << criminal.name
       << " description: " << criminal.description << " caseId: " << criminal.caseId << " crime: " << criminal.crime
       << " cell: " << criminal.cell;
    return os;
}

bool Criminal::operator==(const Criminal &rhs) const {
    return criminalID == rhs.criminalID &&
           name == rhs.name &&
           description == rhs.description &&
           caseId == rhs.caseId &&
           crime == rhs.crime &&
           cell == rhs.cell;
}

bool Criminal::operator!=(const Criminal &rhs) const {
    return !(rhs == *this);
}

void Criminal::setCriminalId1(int criminalId) {
    criminalID = criminalId;
}

const string &Criminal::getName() const {
    return name;
}

const string &Criminal::getDescription() const {
    return description;
}

const string &Criminal::getCaseId() const {
    return caseId;
}

Crime *Criminal::getCrime() const {
    return crime;
}

void Criminal::setCrime(Crime *crime) {
    Criminal::crime = crime;
}

void Criminal::setCaseId(const string &caseId) {
    Criminal::caseId = caseId;
}

void Criminal::setDescription(const string &description) {
    Criminal::description = description;
}


void Criminal::setName(const string &name) {
    Criminal::name = name;
}


Cells *Criminal::getCell() const {
    return cell;
}

void Criminal::setCell(Cells *cell) {
    Criminal::cell = cell;
}

int Criminal::getCriminalId() const {
    return criminalID;
}

void Criminal::setCriminalId(int criminalId) {
    criminalID = criminalId;
}
