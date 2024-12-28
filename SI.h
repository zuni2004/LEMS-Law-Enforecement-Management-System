//
// Created by InnoSTARK on 4/17/2024.
//

#ifndef OFFICERS_SI_H
#define OFFICERS_SI_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "json.hpp"
#include "officer.h"

using namespace std;
using json = nlohmann::json;

class SI : public officer<string> {
private:
    bool investigationStatus;
public:
    SI(const string &_rank, const string &_officerID = "", const string &_name = "", int _badgeNumber = 0);

    bool getInvestigationStatus();

    void displayInfo()  override;
};

#endif //OFFICERS_SI_H
