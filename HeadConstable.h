// Created by HP on 4/7/2024.
#ifndef PEACE_HEADCONSTABLE_H
#define PEACE_HEADCONSTABLE_H

#include "officer.h"
#include "Constable.h"
#include "Forsenic Expert.h"

class Investigation;

class Patrolling;

class HeadConstable : public officer<string> {
    vector<ForensicExpert *> experts;
    vector<officer<string> *> constables;
    int constableCnt;
    Investigation *investigation;
    Patrolling *patrolling;
public:
    void getConstables(Investigation *ptr);

    void getConstables(Patrolling *ptr);

    HeadConstable(const string &id) : officer(id) {
        getForensicExpert();
    }

    HeadConstable(string rank, string officerID, string name, int badgeNumber)
            : officer(rank, officerID, name, badgeNumber) {
        constableCnt = 0;
    }

    void getForensicExpert();

    void displayForensicExperts();

    void displayInfo() override {
        cout << "HeadConstable Information:" << endl;
        cout << "Rank: " << getRank() << endl;
        cout << "Officer ID: " << getOfficerID() << endl;
        cout << "Name: " << getName() << endl;
        cout << "Badge Number: " << getBadgeNumber() << endl;
        cout << "Number of Constables: " << constableCnt << endl;
        cout << "Constables Assigned:" << endl;
        for (const auto &constable: constables) {
            cout << "- " << constable->getName() << " (ID: " << constable->getOfficerID() << ")" << endl;
            if (constables.empty()) {
                cout << "Start your task to get Info about the constables assigned" << endl;
            }
        }
        if (getCurrentTask() != "") {
            cout << "Current Task Assigned: " << endl;
            cout << getCurrentTask() << endl;
        }
        if (getPatrollingsize() != 0) {
            displayPatrollings();
        }
        if (getInvestigationsSize() != 0) {
            displayInvestigations();
        }
    }

    void viewTask() {
        cout << getCurrentTask() << endl;
    }

    void startInvestigation();

    void startPatrolling();

    void displayAssignedConstables() {
        for (int i = 0; i < constables.size(); i++) {
            constables[i]->displayInfo();
        }
    }

    void assignLocationSecurity() {

    }
};

#endif //PEACE_HEADCONSTABLE_H
