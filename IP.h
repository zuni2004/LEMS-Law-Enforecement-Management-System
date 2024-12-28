//
// Created by InnoSTARK on 4/17/2024.
//

#ifndef OFFICERS_IP_H
#define OFFICERS_IP_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "json.hpp"
#include "officer.h"
#include "SI.h"
#include "ASI.h"

using namespace std;
using json = nlohmann::json;

class IP : public officer<string> {
private:
    vector<ASI *> assitantSubInspector;
    vector<SI *> subInspector;
    bool investigationStatus; //tells if the officer is assigned an investigation
    int asiCount;
    int siCount;
    Investigation *investigation;
    Patrolling *patrolling;
public:
    IP(const string &_rank, const string &_officerID , const string &_name, int
    _badgeNumber );

    IP(const string&id):officer<string>(id){

    }

    IP(){

    }

    bool getInvestigationStatus();

    int getASICount();

    int getSICount();

    void displayInfo()  override;

    void getASI(Investigation *ptr);

    void getASI(Patrolling *ptr);

    void getSI(Investigation *ptr);

    void getSI(Patrolling *ptr);

    void viewTask();

    void startInvestigation();

    void startPatrolling();

    void displayAssignedASIAndSI();

    void assignExpert2Evidence();
};


#endif //OFFICERS_IP_H
