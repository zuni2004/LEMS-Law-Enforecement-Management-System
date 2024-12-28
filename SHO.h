//
// Created by HP on 4/6/2024.
//
#ifndef PROJECT_OOP_SHO_H
#define PROJECT_OOP_SHO_H

#include "Citizen.h"
#include "Investigation.h"
#include "User.h"

class Patrolling;

class Complain;

#include "officer.h"

class SHO : public officer<string>, public User {
private:
    Patrolling *ptr1;
    static vector<Investigation *> investigations;
    static vector<Patrolling *> patrollings;
    vector<officer<string> *> officers;
    vector<Complain *> complains;
    int PC;//patrolling complain
    int RP;//rotuine patrolling
    int CFE;//case file emergency
    int CFN;//case file non emergeny
public:
    void displayAllinvestigations() {

    }

    static vector<Investigation *> getinvestigations();

    static vector<Investigation *> getInvestigationsWithUnassignedEquipmentAndVehicles();

    static vector<Patrolling *> getPatrollingWithUnassignedVehicles();

    static vector<Patrolling *> getpatrollings();

    static Investigation *InvestigationByid(const string &id) {
        getinvestigations();
        for (int i = 0; i < investigations.size(); i++) {
            if (investigations[i]->getcaseID() == id) {
                return investigations[i];
            }
        }
    }

    static Patrolling *PatrollingByid(const string &id) {
        getpatrollings();
        for (int i = 0; i < patrollings.size(); i++) {
            if (patrollings[i]->getID() == id) {
                return patrollings[i];
            }
        }
    }

    SHO() {

    }

    void displayInfo() override {
        cout << "Station House Officer Information:" << endl;
        cout << "Rank: " << getRank() << endl;
        cout << "Officer ID: " << getOfficerID() << endl;
        cout << "Name: " << officer<string>::getName() << endl;
        cout << "Badge Number: " << getBadgeNumber() << endl;
    }

    void displayAssignedInvestigations(){
        vector<Investigation*> investigation=getinvestigations();
        for(int i=0; i<investigation.size(); i++){
            investigation[i]->display();
        }
    }

    void displayAssignedPatrolls(){
        vector<Patrolling*> patrol=getpatrollings();
        for(int i=0; i<patrol.size(); i++){
            patrol[i]->displayInfo();
        }
    }

    void getComplain() {
        this->complains = Citizen::getPtr();
        for (int i = 0; i < complains.size(); i++) {
            complains[i]->displayDetail();
        }
    }

    void displayAll();

    void getOfficers();

    void recordLogs();

    void sortComplains();

    void discardComplaints(Complain *complain);

    void assignPatrolling(Complain *ptr);

    void createInvestigation(Complain *complain, bool emergency);

    void promoteOfficer() {

    }

    void demoteOfficer() {

    }
};

int getCount(const string &key);

#endif //PROJECT_OOP_SHO_H
