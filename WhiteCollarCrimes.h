#ifndef WHITECOLLARCRIME_H
#define WHITECOLLARCRIME_H

#include "Crime.h"
#include <iomanip>
#include <fstream>
#include <ostream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class WhiteCollarCrime : public Crime {
    double financialLoss;

public:
    WhiteCollarCrime(double financialLoss = 0, int crimeId = 0, string description = "", string date = "",
                     string location = "", string status = "", string motive = "");

    ~WhiteCollarCrime() {}

    void recordNewCrime() override;

    bool updateCrimeStatus() override;

    void viewListOfCrimes() const override;

    int CalculatingId();

    double getFinancialLoss() const;

    void setFinancialLoss(double financialLoss);

    friend ostream &operator<<(ostream &os, const WhiteCollarCrime &crime);
};


#endif // WHITECOLLARCRIME_H


