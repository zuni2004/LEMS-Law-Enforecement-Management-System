//
// Created by InnoSTARK on 4/17/2024.
//

#ifndef OFFICERS_ASI_H
#define OFFICERS_ASI_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "json.hpp"
#include "officer.h"

using namespace std;
using json = nlohmann::json;

class ASI : public officer<string> {
private:
    bool investigationStatus;
public:
    ASI(const string &_rank, const string &_officerID = "", const string &_name = "", int _badgeNumber = 0);

    bool getInvestigationStatus();

    void displayInfo() override;
};


#endif //OFFICERS_ASI_H
