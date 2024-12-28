
#ifndef PEACE_CONSTABLE_H
#define PEACE_CONSTABLE_H

#include "officer.h"

class Constable : public officer<string> {
    string locationSecurity;
    officer<string> *HeadConstable;
    Investigation *investigation;
    Patrolling *patrolling;
public:
    Constable(const string &id) : officer(id) {
    }

    Constable(string rank, string officerID, string name, int badgeNumber)
            : officer(rank, officerID, name, badgeNumber) {
        locationSecurity = "Unassigned";
    }

    void startPatrolling();

    void startInvestigation();

    void getLeadOfficer(Investigation *ptr);

    void getLeadOfficer(Patrolling *pr2);

    void displayInfo() override {
        cout << "Constable Information:" << endl;
        cout << "Rank: " << getRank() << endl;
        cout << "Officer ID: " << getOfficerID() << endl;
        cout << "Name: " << getName() << endl;
        cout << "Badge Number: " << getBadgeNumber() << endl;
        cout << "Location Security: " << locationSecurity << endl;
        cout << "Current Task Assigned" << getCurrentTask() << endl;
        if (getCurrentTask() != "None") {
            cout << getCurrentTask() << endl;
        }
    }

    void assignLocationSecurity(string &location) {
        locationSecurity = location;
    }

};

#endif //PEACE_CONSTABLE_H