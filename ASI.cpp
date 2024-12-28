//
// Created by InnoSTARK on 4/17/2024.
//

#include "ASI.h"

ASI::ASI(const string &_rank, const string &_officerID, const string &_name, int _badgeNumber) :
        officer(_rank,

                _officerID,

                _name,

                _badgeNumber) {
    investigationStatus = false;
}

bool ASI::getInvestigationStatus() {
    return investigationStatus;
}

void ASI::displayInfo()  {
    cout << "ASI info\n";
    cout << "Rank: " << getRank() << "\nOfficer ID: " << getOfficerID() << "\nOfficer Name: " << getName()
         << "\nBadge Number: " << getBadgeNumber() << "\nInvestigationStatus: " << investigationStatus << endl;
}