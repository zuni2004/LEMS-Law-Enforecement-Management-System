#include "ForensicLab.h"

ostream &operator<<(ostream &os, const ForensicLab &lab) {
    os << "location: " << lab.location << " equipment: " << lab.equipment << " expertCount: " << lab.expertCount
       << " capacity: " << lab.capacity;
    return os;
}