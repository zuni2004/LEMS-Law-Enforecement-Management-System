//
// Created by InnoSTARK on 4/17/2024.
//

#include "SI.h"

SI::SI(const string &_rank, const string &_officerID, const string &_name, int _badgeNumber) : officer(_rank,
                                                                                                       _officerID,
                                                                                                       _name,
                                                                                                       _badgeNumber) {
    investigationStatus = false;
}

bool SI::getInvestigationStatus() {
    return investigationStatus;
}

void SI::displayInfo()  {
    cout << "SI info\n";
    cout << "Rank: " << getRank() << "\nOfficer ID: " << getOfficerID() << "\nOfficer Name: " << getName()
         << "\nBadge Number: " << getBadgeNumber() << "\nInvestigationStatus: " << investigationStatus << endl;
}