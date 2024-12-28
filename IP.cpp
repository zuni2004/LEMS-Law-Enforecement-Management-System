//
// Created by InnoSTARK on 4/17/2024.
//

#include "IP.h"

IP::IP(const string &_rank, const string &_officerID, const string &_name, int _badgeNumber)
: officer<string>(_rank,_officerID,_name,_badgeNumber) {
    investigationStatus = false;
    asiCount = 0;
    siCount = 0;
}


bool IP::getInvestigationStatus() {
    return investigationStatus;
}

int IP::getASICount() {
    return asiCount;
}

int IP::getSICount() {
    return siCount;
}

void IP::getASI(Investigation *ptr) {

}

void IP::displayInfo()  {
    cout << "IP info\n";
    cout << "Rank: " << getRank() << "\nOfficer ID: " << getOfficerID() << "\nOfficer Name: " << getName()
         << "\nBadge Number: " << getBadgeNumber() << "\nInvestigationStatus: " << investigationStatus
         << "\nNumber of ASI: " << asiCount << "\nSI count: " << siCount << "\nASI Assigned: \n";
    for (const auto &asi: assitantSubInspector) {
        cout << "Name: " << asi->getName() << "\nID: " << asi->getOfficerID() << endl;
        cout << "---------------------------------------------" << endl;
        if (assitantSubInspector.empty()) {
            cout << "No ASI available\n";
        }
    }
    cout << "SI Assigned\n";
    for (const auto &si: subInspector) {
        cout << "Name: " << si->getName() << "\nID: " << si->getOfficerID() << endl;
        cout << "---------------------------------------------" << endl;
        if (subInspector.empty()) {
            cout << "No SI available\n";
        }
    }
    cout << "Current Task Assigned: " << endl;
    cout << getCurrentTask() << endl;
    displayInvestigations();
    displayPatrollings();
}

void IP::viewTask() {
    cout << getCurrentTask() << endl;
}

void IP::startPatrolling() {

}

void IP::startInvestigation() {

}

void IP::displayAssignedASIAndSI() {
    cout << "Assigned ASI\n";
    for (int i = 0; i < assitantSubInspector.size(); i++) {
        assitantSubInspector[i]->displayInfo();
    }
    cout << "Assigned SI\n";
    for (int i = 0; i < subInspector.size(); i++) {
        subInspector[i]->displayInfo();
    }
}

void IP::assignExpert2Evidence() {

}


