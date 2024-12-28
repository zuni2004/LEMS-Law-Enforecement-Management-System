#include "Crime.h"

Crime::Crime(int crimeId, string description, string date,
             string location, string status, string motive) {
    this->crimeId = crimeId;
    this->description = description;
    this->date = date;
    this->location = location;
    this->status = status;
    this->motive = motive;
    for (int i = 0; i < evidence.size(); ++i) {
        evidence[i] = nullptr;
    }
}


Crime::~Crime() {

}

ostream &operator<<(ostream &os, const Crime &crime) {
    os << "totalCrimeReported: " << crime.totalCrimeReported << " crimeId: " << crime.crimeId << " description: "
       << crime.description << " date: " << crime.date << " location: " << crime.location << " status: " << crime.status
       << " motive: " << crime.motive;
    return os;
}


bool Crime::operator==(const Crime &rhs) const {
    return totalCrimeReported == rhs.totalCrimeReported &&
           crimeId == rhs.crimeId &&
           description == rhs.description &&
           date == rhs.date &&
           location == rhs.location &&
           status == rhs.status &&
           motive == rhs.motive &&
           evidence == rhs.evidence;
}

bool Crime::operator!=(const Crime &rhs) const {
    return !(rhs == *this);
}

bool Crime::operator<(const Crime &rhs) const {
    return crimeId < rhs.crimeId;
}

bool Crime::operator>(const Crime &rhs) const {
    return rhs < *this;
}

bool Crime::operator<=(const Crime &rhs) const {
    return !(rhs < *this);
}

bool Crime::operator>=(const Crime &rhs) const {
    return !(*this < rhs);
}

int Crime::getCrimeId() const {
    return crimeId;
}

void Crime::setCrimeId(int crimeId) {
    this->crimeId = crimeId;
}

void Crime::addEvidence(Evidence *newEvidence) {
    evidence.push_back(newEvidence);
}
