//
// Created by InnoSTARK on 4/4/2024.
//
#include "AdministrativeStaff.h"

int AdministrativeStaff::vehiclesAppointed = 0;
int AdministrativeStaff::equipmentAppointed = 0;

AdministrativeStaff::AdministrativeStaff() : nameA(""), idA(""), User("") {

}

AdministrativeStaff::AdministrativeStaff(const string &_nameA, const string &_idA, const User &idA) :
        nameA(_nameA), idA(_idA), User(idA) {

}

vector<Equipment<int, string, int, string, double, bool> *> AdministrativeStaff::equipment;

vector<Investigation *> AdministrativeStaff::investigation;

vector<Patrolling *> AdministrativeStaff::patrolling;

void AdministrativeStaff::getInvestigations() {
    SHO sho;
    vector<Investigation *> investigations = sho.getinvestigations();
    for (Investigation *ptr: investigations) {
        if (!ptr->getEquipment() || !ptr->getVehicles()) {
            cout << endl;
            ptr->display();
            cout << endl;
        }
    }
}

void AdministrativeStaff::getPatrolling() {
    SHO sho;
    vector<Patrolling *> patrolling = sho.getPatrollingWithUnassignedVehicles();
    for (Patrolling *ptr: patrolling) {
        if (!ptr->getVehicleStatus()) {
            cout << endl;
            ptr->displayInfo();
            cout << endl;
        }
    }
}

vector<int> AdministrativeStaff::getAvailableEquipmentIDs() {
    vector<int> availableEquipmentIDs;

    ifstream file("Equipment.json");
    if (!file.is_open()) {
        cout << "Failed to open file Equipment.json" << endl;
        return availableEquipmentIDs;
    }
    json j;
    file >> j;

    for (const auto &equipmentJson: j) {
        bool availabilityStatus = equipmentJson["AvailabilityStatus"];
        if (availabilityStatus == true) {
            int id = equipmentJson["Equipment ID"];
            availableEquipmentIDs.push_back(id);
        }
    }
    file.close();
    return availableEquipmentIDs;
}

vector<int> AdministrativeStaff::getAvailableVehicleIDs() {
    vector<int> availableVehicleIDs;

    ifstream file("Vehicles.json");
    if (!file.is_open()) {
        cout << "Failed to open file Vehicles.json" << endl;
        return availableVehicleIDs;
    }

    json j;
    file >> j;

    for (const auto &vehicleJson: j) {
        bool availabilityStatus = vehicleJson["AvailabilityStatus"];
        if (availabilityStatus) {
            int id = vehicleJson["Vehicle ID"];
            availableVehicleIDs.push_back(id);
        }
    }
    file.close();
    return availableVehicleIDs;
}


void AdministrativeStaff::assignEquipmentsToTeamAndLead() {

    for (Investigation *ptr: investigation) {
        getInvestigations();
        cout << "Investigation: " << ptr->getcaseID() << endl;
        json j;
        string filename = "Casefile " + ptr->getcaseID() + ".json";
        ifstream file(filename);
        if (file.is_open()) {
            file >> j;
            int assignedOfficersCount = j["Info"]["Count of assigned officers"];
            cout << "Count of assigned officers: " << assignedOfficersCount << endl;

            cout << "Assigning officers and equipment for this investigation..." << endl;

            vector<int> availableEquipmentIDs = getAvailableEquipmentIDs();
            cout << "Available Equipment IDs:" << endl;
            for (int id: availableEquipmentIDs) {
                cout << id << endl;
            }
            int eID;
            cout << "Assign an Equipment ID to Lead Officer: ";
            cin >> eID;
            json l;
            ifstream f11("Equipment.json");
            f11 >> l;
            ofstream f12("Equipment.json");
            l["AvailabilityStatus"] == false;
            f12 << setw(4) << l << endl;

            j["Info"]["Assigned Equipment ID to Lead"] = eID;

            vector<int> enteredIDs;
            for (int i = 0; i < assignedOfficersCount; i++) {
                cout << "Enter the Equipment ID to assign to Officer " << i << ": ";
                int ID;
                cin >> ID;
                enteredIDs.push_back(ID);
                ptr->setEquipment(true);
                json e;
                ifstream f1("Equipment.json");
                f1 >> e;
                ofstream f("Equipment.json");
                e["AvailabilityStatus"] == false;
                f << setw(4) << e << endl;
            }
            j["Info"]["Assigned equipment IDs"] = enteredIDs;
            ofstream outFile(filename);
            outFile << setw(4) << j << endl;
            outFile.close();

            cout << "Assigned equipment IDs have been written to the case file." << endl;

        } else {
            cout << "Unable to open File\n";
        }
    }
}

void AdministrativeStaff::assignVehiclesToTeamAndLead() {
    getInvestigations();
    for (Investigation *ptr: investigation) {
        cout << "Investigation: " << ptr->getcaseID() << endl;
        json j;
        string filename = "Casefile " + ptr->getcaseID() + ".json";
        ifstream file(filename);
        if (file.is_open()) {
            file >> j;
            int assignedOfficersCount = j["Info"]["Count of assigned officers"];
            cout << "Count of assigned officers: " << assignedOfficersCount << endl;

            cout << "Assigning vehicles for this investigation..." << endl;
            int vID;
            cout << "Assign an Vehicle ID to Lead Officer: ";
            cin >> vID;
            json l;
            ifstream f11("vehicles.json");
            f11 >> l;
            ofstream f12("vehicles.json");
            l["AvailabilityStatus"] == false;
            f12 << setw(4) << l << endl;

            j["Info"]["Assigned Vehicle ID to Lead"] = vID;

            vector<int> availableVehicleIDs = getAvailableVehicleIDs();
            cout << "Available Vehicle IDs:" << endl;
            for (int id: availableVehicleIDs) {
                cout << id << endl;
            }
            vector<int> enteredIDs;
            for (int i = 0; i < assignedOfficersCount; i++) {
                cout << "Enter the Vehicle ID to assign to Officer " << i << ": ";
                int ID;
                cin >> ID;
                enteredIDs.push_back(ID);
                json v;
                ifstream f1("vehicles.json");
                f1 >> v;
                ofstream f("vehicles.json");
                v["AvailabilityStatus"] == false;
                f << setw(4) << v << endl;
                ptr->setVehicle(true);
            }
            j["Info"]["Assigned vehicle IDs"] = enteredIDs;

            ofstream outFile(filename);
            outFile << setw(4) << j << endl;
            outFile.close();

            cout << "Assigned vehicle IDs have been written to the case file." << endl;
        } else {
            cout << "Unable to open File\n";
        }
    }
}

void AdministrativeStaff::assignVehiclesToPatrolling() {
    getPatrolling();
    for (Patrolling *ptr: patrolling) {
        cout << "Patrolling ID: " << ptr->getID() << endl;
        json j;
        ifstream file("Routine Patrolling.json");
        if (file.is_open()) {
            file >> j;
            vector<int> availableVehicleIDs = getAvailableVehicleIDs();
            cout << "Available Vehicle IDs:" << endl;
            for (int id: availableVehicleIDs) {
                cout << id << endl;
            }
            int assignedOfficersCount = j["Info"]["Count of assigned officers"];
            cout << "Count of assigned officers: " << assignedOfficersCount << endl;
            vector<int> enteredIDs;
            for (int i = 0; i < assignedOfficersCount; i++) {
                cout << "Enter the Vehicle ID to assign to Officer " << i << ": ";
                int ID;
                cin >> ID;
                enteredIDs.push_back(ID);
                json v;
                ifstream f1("vehicles.json");
                f1 >> v;
                ofstream f("vehicles.json");
                v["AvailabilityStatus"] == false;
                f << setw(4) << v << endl;
            }
            j["Info"]["Assigned vehicle IDs"] = enteredIDs;

            ofstream outFile("Routine Patrolling.json");
            outFile << setw(4) << j << endl;
            outFile.close();

            cout << "Assigned vehicle ID has been written to the patrolling file." << endl;
        } else {
            cout << "Vehicle already assigned to this patrolling." << endl;
        }
        cout << "Unable to open File\n";
    }
}

