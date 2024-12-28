#ifndef POLICESTATION_H
#define POLICESTATION_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "json.hpp"
#include <vector>
#include "Criminal.h"
#include "Crime.h"
#include "Vehicle.h"
#include "Equipment.h"
#include "CorrectionalOfficer.h"
#include "officer.h"
#include "ForensicLab.h"
#include "Forsenic Expert.h"

class Budget;

using json = nlohmann::json;
using namespace std;

class Complain;

const int Max = 20;
const int Max_E = 70;

class PoliceStation {
    static PoliceStation *instance;
    int stationId;
    string name;
    string location;
//    double allocatedBudget;
    int contactInfo;
    Complain *complain;
    vector<Criminal *> criminals;
    Criminal criminal;//association
    Crime *crime;//association
    officer<int> *Officer;
    vector<ForensicExpert *> forensicExperts;
    vector<Cells *> cells;
    CorrectionalOfficer *correctionalOfficer;//association
    vector<Equipment<int, string, int, string, double, bool> *> equipment;//composition
    string chiefOfficerInCharge;
    vector<ForensicLab *> forensicLab;
    vector<Vehicle<int, string, string, int, string, string, string, string, string, string, string, string, string, string> *> vehicles;//composition

    PoliceStation() {}

    PoliceStation(int stationId, string name, string location, int contactInfo, Crime *crime,
                  string chiefOfficerInCharge) {
        this->stationId = stationId;
        this->name = name;
        this->location = location;
        correctionalOfficer = nullptr;
        this->contactInfo = contactInfo;
        this->chiefOfficerInCharge = chiefOfficerInCharge;
        crime = nullptr;
        equipment.resize(Max_E);
        for (int i = 0; i < Max_E; ++i) {
            equipment[i] = nullptr;
        }
        vehicles.resize(Max);
        for (int i = 0; i < Max; ++i) {
            vehicles[i] = nullptr;
        }
    }

public:
    bool operator==(const PoliceStation &rhs) const;

    bool operator!=(const PoliceStation &rhs) const;

    static PoliceStation *getInstance() {
        if (!instance) {
            instance = new PoliceStation();
            return instance;
        }
        return instance;
    }

    const string &getName() const;

    ~PoliceStation() {
        for (auto equipments: equipment) {
            delete equipments;
        }
        for (auto vehicle: vehicles) {
            delete vehicle;
        }
        for (auto lab: forensicLab) {
            delete lab;
        }
    }

    void EquipmentCreationAndManagement() {
        int choice;
        do {
            cout << "\n1. Add equipment\n"
                    "2. View equipments\n"
                    "3. Search equipment\n"
                    "4. Exit\n"
                    "Enter your choice: ";
            cin >> choice;
            Equipment<int, string, int, string, double, bool> *newEquipment = new Equipment<int, string, int, string, double, bool>;
            if (choice == 1) {
                int count;
                cout << "Enter the number of equipment you want to add: ";
                cin >> count;
                for (int i = 0; i < count; ++i) {
                    newEquipment->addEquipment();
                }
            } else if (choice == 3) {
                newEquipment->searchEquipmentIfAvailable();
            } else if (choice == 2) {
                newEquipment->viewAllEquipment();
            } else if (choice == 4) {
                cout << "Exiting...\n";
                break;
            } else {
                cout << "Invalid choice.\n";
            }
        } while (choice != 4);
    }

    void viewListOfLabs() const {
        json j;
        ifstream file("ForensicLab.json");
        if (file.is_open()) {
            file >> j;
            cout << setw(4) << j << endl;
            file.close();
        } else
            cout << "Cannot display list of labs " << endl;
    }

    void VehicleCreationAndManagement() {
        int choice;
        do {
            cout << "\n1. Add Vehicle\n"
                    "2. View Vehicles\n"
                    "3. Search Vehicle\n"
                    "4. Update Vehicle Status\n"
                    "5. Update Vehicle Maintenance History\n"
                    "6. Exit\n"
                    "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                int count;
                cout << "Enter the number of vehicles you want to add\n";
                cin >> count;
                for (int i = 0; i < count; ++i) {
                    Vehicle<int, string, string, int, string, string, string, string, string, string, string, string, string, string> *newVehicle = new Vehicle<int, string, string, int, string, string, string, string, string, string, string, string, string, string>;
                    newVehicle->AddVehicle();
                    vehicles.push_back(newVehicle);
                }
            } else if (choice == 2) {
                for (auto &vehicle: vehicles) {
                    vehicle->ViewVehicles();
                }
            } else if (choice == 3) {
                Vehicle<int, string, string, int, string, string, string, string, string, string, string, string, string, string> *vehicles = new Vehicle<int, string, string, int, string, string, string, string, string, string, string, string, string, string>;
                vehicles->SearchVehicle();
            } else if (choice == 4) {
                Vehicle<int, string, string, int, string, string, string, string, string, string, string, string, string, string> *vehicles = new Vehicle<int, string, string, int, string, string, string, string, string, string, string, string, string, string>;
                vehicles->UpdateVehicleStatus();
            } else if (choice == 5) {
                Vehicle<int, string, string, int, string, string, string, string, string, string, string, string, string, string> *vehicles = new Vehicle<int, string, string, int, string, string, string, string, string, string, string, string, string, string>;
                vehicles->UpdateVehicleMaintainanceHistory();
            } else if (choice == 6) {
                cout << "Exiting...\n";
                break;
            } else {
                cout << "Invalid choice.\n";
            }
        } while (choice != 6);
    }

    void displayCriminaldata() {
        int choice;
        while (true) {
            cout << "\nMenu:\n";
            cout << "1. Enter new criminal\n";
            cout << "2. View list of criminals\n";
            cout << "3. Search by criminal ID\n";
            cout << "4. Search by crime ID\n";
            cout << "5. Add bail information\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                criminal.EnterNewCriminal();
            } else if (choice == 2) {
                criminal.viewListOfCriminal();
            } else if (choice == 3) {
                criminal.SearchByCriminalID();
            } else if (choice == 4) {
                criminal.SearchByCrimeID();
            } else if (choice == 5) {
                criminal.AddBailInfo();
            } else if (choice == 6) {
                cout << "Exiting program.\n";
                break;
            } else {
                cout << "Invalid choice. Please enter a number from 1 to 6.\n";
            }
        }
        return;
    }

    vector<ForensicLab *> getPtr() {
        int count = 0;
        json LabData;

        ifstream file("ForensicLab.json");
        if (!file.is_open()) {
            cout << "Failed to open ForensicLab.json" << endl;
            return forensicLab;
        }

        file >> LabData;
        file.close();

        for (const auto &lab: LabData) {
            string location, equipment;
            int capacity = 0, noOfExperts = 0;
            location = lab["Location"];
            equipment = lab["Equipment"];
            if (lab.contains("Capacity of experts")) {
                capacity = lab["Capacity of experts"];
            }
            if (lab.contains("Number of expert")) {
                noOfExperts = lab["Number of expert"];
            }
            for (const auto &expert: lab["Experts"]) {
                string expertId;
                expertId = expert["ID"];
                ForensicExpert *forensicExpert = new ForensicExpert();
                forensicExpert->setID(expertId);
                forensicExperts.push_back(forensicExpert);
            }
            ForensicLab *forensicLab1 = new ForensicLab(location, equipment, capacity, noOfExperts, forensicExperts);
            forensicLab.push_back(forensicLab1);
            count++;
        }
        return forensicLab;
    }

    void setName(string newName) {
        name = newName;
    }

    int getContactInfo() const {
        return contactInfo;
    }

    void setContactInfo(int info) {
        contactInfo = info;
    }

    string getLocation() const {
        return location;
    }

    void addForensicLab() {
        int choice;
        cout << "Enter the number of forensic lab to enter: ";
        cin >> choice;
        cin.ignore(); // Clear newline character from input buffer
        for (int i = 0; i < choice; ++i) {
            ForensicLab *forensicLab1 = new ForensicLab;
            string location, equipment;
            cout << "Enter location of lab: ";
            getline(cin, location);
            cout << "Enter the details of equipment: ";
            getline(cin, equipment);
            int nomOfExpert, capacityExpert;
            cout << "Enter number of experts in lab: ";
            cin >> nomOfExpert;
            cout << "Enter capacity of expert in lab: ";
            cin >> capacityExpert;
            cin.ignore();
            if (nomOfExpert > capacityExpert) {
                cout << "Cannot hold this much experts: ";
                return;
            }
            forensicLab1->setLocation(location);
            forensicLab1->setEquipment(equipment);
            forensicLab1->setExpertCount(nomOfExpert);
            forensicLab1->setCapacity(capacityExpert);
            json LabData;
            ifstream file("ForensicLab.json");
            if (file.is_open()) {
                file >> LabData;
                file.close();
            } else {
                // cout << "Nothing exist in file to read" << endl;
            }

            json NewLab{
                    {"Location",            forensicLab1->getLocation()},
                    {"Equipment",           forensicLab1->getEquipment()},
                    {"Number of expert",    forensicLab1->getExpertCount()},
                    {"Capacity of experts", forensicLab1->getCapacity()},
                    {"Experts",             json::array()} // Array to hold expert data
            };

            LabData.push_back(NewLab);

            ofstream outFile("ForensicLab.json", ios::out);
            if (outFile.is_open()) {
                outFile << setw(4) << LabData << endl;
            } else {
                cout << "Cannot write to file" << endl;
                return;
            }
        }
    }

    void addCell() {
        string location;
        int capacity;
        int occupancy = 0;

        cout << "Entering new cell\n";
        cout << "Enter location: ";
        cin.ignore();
        getline(cin, location);

        cout << "Enter capacity of criminals it can hold: ";
        cin >> capacity;

        int numofcriminals;
        cout << "Enter number of criminals to add: ";
        cin >> numofcriminals;

        if (capacity < numofcriminals) {
            cout << "Cannot add this many criminals. Capacity exceeded.\n";
            return;
        }

        vector<int> criminalIDS;
        for (int i = 0; i < numofcriminals; ++i) {
            int temp;
            cout << "Enter ID of criminal " << i + 1 << ": ";
            cin >> temp;
            criminalIDS.push_back(temp);
        }

        occupancy = numofcriminals;
        for (int i = 0; i < criminals.size(); i++) {
            if (occupancy <= capacity) {
                if (criminals[i]->criminalExist()) {
                    criminalIDS.push_back(criminals[i]->getCriminalId());
                } else {
                    cout << "Criminal with ID " << criminals[i]->getCriminalId() << " does not exist.\n";
                    return;
                }
            } else {
                cout << "Cannot hold this many criminals. Capacity exceeded.\n";
                return;
            }
        }
        int cellID = cells.size() + 1;
        Cells *newCell = new Cells(cellID, location, capacity, occupancy);
        cells.push_back(newCell);
        json cellData = {
                {"CellID",       newCell->getCellId()},
                {"Location",     newCell->getLocation()},
                {"Capacity",     newCell->getCapacity()},
                {"Occupancy",    newCell->getOccupancy()},
                {"Criminal Ids", criminalIDS}
        };
        ifstream file("Cells.json");
        json find;
        if (file.is_open()) {
            file >> find;
            file.close();
        }
        find.push_back(cellData);
        ofstream outFile("Cells.json");
        if (!outFile.is_open()) {
            cout << "Error: Unable to write to Cells.json" << endl;
            return;
        }
        outFile << setw(4) << find << endl;
        outFile.close();
        cout << "New cell added successfully.\n";
    }

    void displayCrime() {
        int choice;
        do {
            cout << "Enter the type of crime: " << endl
                 << " 1. Violent crime " << endl
                 << " 2. White collar crimes " << endl
                 << " 3. Cyber crimes " << endl
                 << " 4. Exit " << endl;
            cin >> choice;

            switch (choice) {
                case 1: {
                    int violentChoice;
                    do {
                        cout << "Violent Crime Options: " << endl
                             << " 1. Record new violent crime " << endl
                             << " 2. Update status of a violent crime " << endl
                             << " 3. Display violent crimes " << endl
                             << " 4. Back to main menu " << endl;
                        cin >> violentChoice;

                        switch (violentChoice) {
                            case 1: {
                                crime = new VoilentCrime;
                                crime->recordNewCrime();
                                break;
                            }
                            case 2: {
                                crime = new VoilentCrime;
                                crime->updateCrimeStatus();
                                break;
                            }
                            case 3: {
                                crime = new VoilentCrime;
                                crime->viewListOfCrimes();
                                break;
                            }
                            case 4: {
                                cout << "Returning to main menu..." << endl;
                                break;
                            }
                            default: {
                                cout << "Please enter a valid option." << endl;
                                break;
                            }
                        }
                    } while (violentChoice != 4);
                    break;
                }
                case 2: {
                    int whiteCollarChoice;
                    do {
                        cout << "White Collar Crime Options: " << endl
                             << " 1. Record new white collar crime " << endl
                             << " 2. Update status of a white collar crime " << endl
                             << " 3. Display white collar crimes " << endl
                             << " 4. Back to main menu " << endl;
                        cin >> whiteCollarChoice;

                        switch (whiteCollarChoice) {
                            case 1: {
                                crime = new WhiteCollarCrime;
                                crime->recordNewCrime();
                                break;
                            }
                            case 2: {
                                crime = new WhiteCollarCrime;
                                crime->updateCrimeStatus();
                                break;
                            }
                            case 3: {
                                crime = new WhiteCollarCrime;
                                crime->viewListOfCrimes();
                                break;
                            }
                            case 4: {
                                cout << "Returning to main menu..." << endl;
                                break;
                            }
                            default: {
                                cout << "Please enter a valid option." << endl;
                                break;
                            }
                        }
                    } while (whiteCollarChoice != 4);
                    break;
                }
                case 3: {
                    int cyberChoice;
                    do {
                        cout << "Cyber Crime Options: " << endl
                             << " 1. Record new cyber crime " << endl
                             << " 2. Update status of a cyber crime " << endl
                             << " 3. Display cyber crimes " << endl
                             << " 4. Back to main menu " << endl;
                        cin >> cyberChoice;

                        switch (cyberChoice) {
                            case 1: {
                                crime = new CyberCrime;
                                crime->recordNewCrime();
                                break;
                            }
                            case 2: {
                                crime = new CyberCrime;
                                crime->updateCrimeStatus();
                                break;
                            }
                            case 3: {
                                crime = new CyberCrime;
                                crime->viewListOfCrimes();
                                break;
                            }
                            case 4: {
                                cout << "Returning to main menu..." << endl;
                                break;
                            }
                            default: {
                                cout << "Please enter a valid option." << endl;
                                break;
                            }
                        }
                    } while (cyberChoice != 4);
                    break;
                }
                case 4: {
                    cout << "Exiting..." << endl;
                    break;
                }
                default: {
                    cout << "Please enter a valid option." << endl;
                    break;
                }
            }
        } while (choice != 4);
    }

    void setLocation(string newLocation) {
        location = newLocation;
    }

    string getChiefOfficerInCharge() const {
        return chiefOfficerInCharge;
    }

    void setChiefOfficerInCharge(string newChief) {
        chiefOfficerInCharge = newChief;
    }

    void viewComplain() {}

    Complain *getComplain() const;

    void setComplain(Complain *complain);

    static void setInstance(PoliceStation *instance);

    int getStationId() const;

    void setStationId(int stationId);

    Crime *getCrime() const;

    void setCrime(Crime *crime);

    const vector<Vehicle<int, string, string, int, string, string, string, string, string, string, string, string, string, string> *> &
    getVehicles() const;

    void setVehicles(
            const vector<Vehicle<int, string, string, int, string, string, string, string, string, string, string, string, string, string> *> &vehicles);

    void setEquipment1(const vector<Equipment<int, string, int, string, double, bool> *> &equipment);

};

#endif








