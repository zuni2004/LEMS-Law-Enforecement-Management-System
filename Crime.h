#ifndef CRIME_H
#define CRIME_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include"Evidence.h"

using json = nlohmann::json;
using namespace std;

class Crime {
protected:
    int totalCrimeReported;
    int crimeId;
    string description;
    string date;
    string location;
    string status;
    string motive;
    vector<Evidence *> evidence;//aggregation

public:
    Crime(int crimeId = 0, string description = "", string date = "",
          string location = "", string status = "", string motive = "");

    ~Crime();

    virtual void recordNewCrime() = 0;

    virtual bool updateCrimeStatus() = 0;

    virtual void viewListOfCrimes() const = 0;

    int getCrimeId() const;

    void setCrimeId(int crimeId);

    friend ostream &operator<<(ostream &os, const Crime &crime);

    bool operator<(const Crime &rhs) const;

    bool operator>(const Crime &rhs) const;

    bool operator<=(const Crime &rhs) const;

    bool operator>=(const Crime &rhs) const;

    bool operator==(const Crime &rhs) const;

    bool operator!=(const Crime &rhs) const;

    void addEvidence(Evidence *newEvidence);
};

#endif