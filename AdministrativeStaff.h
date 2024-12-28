//
// Created by InnoSTARK on 4/4/2024.
//

#ifndef INC_2024_SPRING_SE102TA_PROJECT_SE102A_A_ADMINISTRATIVESTAFF_H
#define INC_2024_SPRING_SE102TA_PROJECT_SE102A_A_ADMINISTRATIVESTAFF_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "json.hpp"
#include "Equipment.h"
#include "officer.h"
#include "Vehicle.h"
#include "User.h"
#include "SHO.h"

using json = nlohmann::json;
using namespace std;

class AdministrativeStaff : public User {
private:
    string nameA;
    string idA;
    static int vehiclesAppointed;
    static int equipmentAppointed;
    static vector<Equipment<int, string, int, string, double, bool> *> equipment;
    vector<Vehicle<int, string, string, int, string, string, string, string, string, string, string, string, string, string> *> vehicle;
    vector<officer<string> *> officer;
    static vector<Investigation *> investigation;
    static vector<Patrolling *> patrolling;
public:
    AdministrativeStaff(); // default constructor

    AdministrativeStaff(const string &_nameA, const string &_idA, const User &idA); // Parametrized Constructor

    vector<int> getAvailableEquipmentIDs();

    vector<int> getAvailableVehicleIDs();

    void assignEquipmentsToTeamAndLead();

    void assignVehiclesToTeamAndLead();

    void getInvestigations();

    void getPatrolling();

    void assignVehiclesToPatrolling();
};

#endif // INC_2024_SPRING_SE102TA_PROJECT_SE102A_A_ADMINISTRATIVESTAFF_H
