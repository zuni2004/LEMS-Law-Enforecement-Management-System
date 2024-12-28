#ifndef VIOLENTCRIMES_H
#define VIOLENTCRIMES_H

#include "Crime.h"

using namespace std;

class VoilentCrime : public Crime {
    string weaponsInvolved;
public:
    VoilentCrime(string weaponsInvolved = "", int crimeId = 0, string description = "", string date = "",
                 string location = "", string status = "", string motive = "");

    ~VoilentCrime();

    int CalculatingId();

    bool updateCrimeStatus() override;

    void recordNewCrime() override;

    void viewListOfCrimes() const override;

    const string getWeaponsInvolved() const;

    void setWeaponsInvolved(const string &weaponsInvolved);

};

#endif