#ifndef CYBERCRIMES_H
#define CYBERCRIMES_H

#include "Crime.h"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class CyberCrime : public Crime {
    string CyberAttackType;
    string targetSystem;

public:
    CyberCrime(string CyberAttackType = "", string targetSystem = "", int crimeId = 0, string description = "",
               string date = "", string location = "", string status = "", string motive = "");

    ~CyberCrime() {}

    void recordNewCrime() override;

    bool updateCrimeStatus() override;

    void viewListOfCrimes() const override;

    int CalculatingId();

    const string &getCyberAttackType() const;

    const string &getTargetSystem() const;

    void setTargetSystem(const string &targetSystem);

    void setCyberAttackType(const string &cyberAttackType);
};

#endif // CYBERCRIMES_H
