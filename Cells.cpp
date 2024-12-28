//
// Created by InnoSTARK on 4/27/2024.
//
#include "Cells.h"

const string &Cells::getLocation() const {
    return location;
}

int Cells::getCapacity() const {
    return capacity;
}

int Cells::getOccupancy() const {
    return occupancy;
}

bool Cells::operator<(const Cells &rhs) const {
    if (cellID < rhs.cellID)
        return true;
    if (rhs.cellID < cellID)
        return false;
    if (location < rhs.location)
        return true;
    if (rhs.location < location)
        return false;
    if (capacity < rhs.capacity)
        return true;
    if (rhs.capacity < capacity)
        return false;
    if (occupancy < rhs.occupancy)
        return true;
    if (rhs.occupancy < occupancy)
        return false;
    return criminal < rhs.criminal;
}

bool Cells::operator==(const Cells &rhs) const {
    return cellID == rhs.cellID &&
           location == rhs.location &&
           capacity == rhs.capacity &&
           occupancy == rhs.occupancy &&
           criminal == rhs.criminal;
}

bool Cells::operator!=(const Cells &rhs) const {
    return !(rhs == *this);
}

bool Cells::operator>(const Cells &rhs) const {
    return rhs < *this;
}

bool Cells::operator<=(const Cells &rhs) const {
    return !(rhs < *this);
}

bool Cells::operator>=(const Cells &rhs) const {
    return !(*this < rhs);
}

ostream &operator<<(ostream &os, const Cells &cells) {
    os << "cellID: " << cells.cellID << " location: " << cells.location << " capacity: " << cells.capacity
       << " occupancy: " << cells.occupancy << " criminal: " << cells.criminal;
    return os;
}

