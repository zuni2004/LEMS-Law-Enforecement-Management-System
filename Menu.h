//
// Created by InnoSTARK on 5/1/2024.
//

#ifndef TEMPLATE_MENU_H
#define TEMPLATE_MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "json.hpp"

#include "HR.h"
#include "PoliceStation.h"
#include "SHO.h"
#include "HeadConstable.h"
#include "IP.h"
#include "Forsenic Expert.h"
#include "Citizen.h"
#include "Complain.h"

using json = nlohmann::json;
using namespace std;

class Menu {
public:
    static void handleCitizenMenu() {
        int q1;
        do {
            ifstream read("citizenCount.json");
            json data2;
            read >> data2;
            read.close();
            int cnt = data2["Citizen Count"];
            Citizen::CitizenCount = cnt;
            cout << endl;
            cout << "Citizens Menu" << endl;
            cout << "1. File a complain" << endl;
            cout << "2. View complain status" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> q1;
            cout << endl;
            switch (q1) {
                case 1: {
                    string cnic;
                    cout << "Enter your CNIC: ";
                    cin.ignore();
                    cin >> cnic;
                    bool found;
                    for (int i = 1; i < cnt; i++) {
                        stringstream ss;
                        ss << i;
                        string count = ss.str();
                        string fileName = count + ".json";
                        ifstream file(fileName);
                        if (file.is_open()) {
                            json data;
                            file >> data;
                            file.close();
                            string cnic2 = data["Info"]["CNIC"];
                            if (cnic2 == cnic) {
                                int id;
                                cout << "Please enter your file ID: ";
                                cin >> id;
                                if (id == i) {
                                    found = true;
                                    Citizen obj(cnic);
                                    obj.fileComplain(found, i);
                                    break;
                                } else {
                                    cout << "Wrong ID entered" << endl;
                                    q1 = 3;
                                }
                            }
                        }
                    }
                    if (!found) {
                        ifstream inputFile("citizenCount.json");
                        if (!inputFile.is_open()) {
                            cerr << "Failed to open file." << endl;
                            return;
                        }
                        json data;
                        inputFile >> data;
                        inputFile.close();
                        Citizen::CitizenCount++;
                        int newCitizenCount = Citizen::CitizenCount;
                        data["Citizen Count"] = newCitizenCount;
                        ofstream outputFile("citizenCount.json");
                        if (!outputFile.is_open()) {
                            cerr << "Failed to open file for writing." << endl;
                            return;
                        }
                        outputFile << setw(4) << data << endl;
                        outputFile.close();
                        Citizen obj2(cnic);
                        obj2.fileComplain(found, Citizen::CitizenCount);
                        cout << "Your Citizen ID is :" << obj2.getCitizenCnt() << endl;
                        cout << endl;
                        cout << "Please keep a note of this , to keep up with the status of your complaint" << endl;
                    }
                    break;
                }
                case 2: {
                    int id;
                    int person;
                    cout << "Enter your Citizen ID: ";
                    cin >> person;
                    cout << "Enter your Complain ID: ";
                    cin >> id;
                    Citizen view;
                    stringstream ss;
                    ss << person;
                    string count = ss.str();
                    string fileName = count + ".json";
                    cout << "Your Complain Status is: ";
                    cout << view.viewComplainStatus(id, fileName) << endl;
                    break;
                }
                case 3: {
                    cout << "Exiting.........." << endl;
                    break;
                }
                default: {
                    cout << "Try Again" << endl;
                    break;
                }
            }
        } while (q1 != 3);
    }

    static void handleHRMenu(HR &hrInstance) {
        int choice1;
        do {
            cout << endl;
            cout << "HR Management Menu:" << endl;
            cout << "1. Display added officers" << endl;
            cout << "2. Add Officer" << endl;
            cout << "3. Remove Officer" << endl;
            cout << "4. Display all Officers by Type" << endl;
            cout << "5. Add Staff (Administrative Staff, SHO, Forensic Experts)" << endl;
            cout << "6. Display Forensic Experts \n";
            cout << "7. Promote/Demote\n";
            cout << "8. Fire Staff ((Administrative Staff, SHO, Forensic Experts)\n";
            cout << "9. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice1;
            cout << endl;
            switch (choice1) {
                case 1:
                    hrInstance.displayAddedOfficers();
                    break;
                case 2: {
                    string name;
                    cout << "Enter Name of Officer to add: ";
                    cin.ignore();
                    getline(cin, name);
                    hrInstance.addOFFICER(name);
                    break;
                }
                case 3:
                    hrInstance.removeOfficers();
                    break;
                case 4: {
                    vector<officer<string> *> officeres;
                    officeres = hrInstance.getOfficers();
                    for (const auto &officerPtr: officeres) {
                        officerPtr->displayInfo();
                    }
                    break;
                }
                case 5:
                    hrInstance.addUser();
                    break;
                case 6: {
                    vector<ForensicExpert *> vec = hrInstance.getPtr();
                    for (const auto &phoneNumber: vec) {
                        phoneNumber->displayDetails();
                        if (phoneNumber->getEvidenceCnt() > 0) {
                            cout << "loading evidences" << endl;
                            phoneNumber->LoadEvidences();
                        }
                    }
                    break;
                }
                case 7: {
                    cin.ignore();
                    string id;
                    cout << "Enter officer id: ";
                    getline(cin, id);
                    int answer;
                    cout << "Chose" << endl;
                    cout << "1.Promote" << endl;
                    cout << "2.Demote" << endl;
                    cin >> answer;
                    hrInstance.editRank(hrInstance.getOfficerByID(id), answer);
                    break;
                }
                case 8: {
                    cin.ignore();
                    string id;
                    cout << "Enter officer id: ";
                    getline(cin, id);
                    int answer;
                    cout << "Chose" << endl;
                    cout << "1.Promote" << endl;
                    cout << "2.Demote" << endl;
                    cin >> answer;
                    hrInstance.FireStaff(hrInstance.getOfficerByID(id));
                    break;
                }
                case 9: {
                    hrInstance.Add2File();
                    hrInstance.updateFile2();
                    break;
                }
                default: {
                    cout << "Invalid choice! Please try again." << endl;
                    break;
                }
            }

        } while (choice1 != 9);
    }

    static void handleSHOMenu(SHO &station) {
        int choice;
        cout << endl;
        station.getinvestigations();
        station.getComplain();
        station.getOfficers();
        do {
            cout << "1. Sort Complains" << endl;
            cout << "2. Assign Routine Patrolling" << endl;
            cout << "3. View officer logs" << endl;
            cout << "4. View all Investigations\n";
            cout << "5. View all patrollings\n";
            cout << "6. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cout << endl;
            switch (choice) {
                case 1:
                    station.sortComplains();
                    break;
                case 2:
                    station.assignPatrolling(nullptr);
                    break;
                case 3:
                    station.displayAll();
                    break;
                case 4:
                    station.displayAssignedInvestigations();
                    break;
                case 5:
                    station.displayAssignedPatrolls();
                    break;
                case 6:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        } while (choice != 6);
    }

    static void handleCOMenu(CorrectionalOfficer &correctionalOfficer) {
        int choice3;
        do {
            cout << "\nCorrectional Officer Menu\n";
            cout << "1. Add Criminal in Cell\n";
            cout << "2. Remove Criminal in Cell\n";
            cout << "3. Display Cell Data\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice3;
            cout << endl;
            cin.ignore();
            switch (choice3) {
                case 1:
                    correctionalOfficer.updateCriminalInCell();
                    break;
                case 2:
                    correctionalOfficer.removeCriminalFromCell();
                case 3:
                    correctionalOfficer.displayCellData();
                    break;
                case 4:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice! Please enter a valid option.\n";
                    break;
            }
        } while (choice3 != 4);
    }

    static void handleHCMenu(HeadConstable &hc) {
        int choice4;
        do {
            cout << "HeadConstable Menu:" << endl;
            cout << "1. Display Information" << endl;
            cout << "2. View Task" << endl;
            cout << "3. Start Investigation" << endl;
            cout << "4. Start Patrolling" << endl;
            cout << "5. Display Assigned Constables" << endl;
            cout << "6. Assign Location Security" << endl;
            cout << "7. Exit" << endl;
            cout << "Enter your choice: ";
            cout << endl;
            cin >> choice4;
            switch (choice4) {
                case 1:
                    hc.displayInfo();
                    break;
                case 2:
                    hc.viewTask();
                    break;
                case 3:
                    hc.startInvestigation();
                    break;
                case 4:
                    hc.startPatrolling();
                    break;
                case 5:
                    hc.displayAssignedConstables();
                    break;
                case 6:
                    hc.assignLocationSecurity();
                    break;
                case 7:
                    cout << "Exiting program.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        } while (choice4 != 7);
    }

    static void handleIPMenu(IP &ip, PoliceStation &policeStation) {
        int choice4;
        do {
            cout << endl;
            cout << "1. Add Forensic Lab\n";
            cout << "2. Vehicle Creation and Management\n";
            cout << "3. Equipment Creation and Management\n";
            cout << "4. Display Criminal Data\n";
            cout << "5. Display Crime Data\n";
            cout << "6. View list of Labs\n";
            cout << "7. Add cell\n";
            cout << "8. Exit\n";
            cout << "Choose: ";
            cin >> choice4;
            cout << endl;
            switch (choice4) {
                case 1: {
                    policeStation.addForensicLab();
                    break;
                }
                case 2: {
                    policeStation.VehicleCreationAndManagement();
                    break;
                }
                case 3: {
                    policeStation.EquipmentCreationAndManagement();
                    break;
                }
                case 4: {
                    policeStation.displayCriminaldata();
                    break;
                }
                case 5: {
                    policeStation.displayCrime();
                    break;
                }
                case 6: {
                    policeStation.viewListOfLabs();
                    break;
                }
                case 7: {
                    policeStation.addCell();
                    break;
                }
                case 8: {
                    cout << "Exiting.....\n";
                    break;
                }
                default:
                    cout << "Invalid\n";
                    break;
            }
        } while (choice4 != 8);
    }

    static void handleASMenu(AdministrativeStaff &administrativeStaff) {
        int choice;
        cout << endl;
        do {
            cout << "1. Assign Vehicles to Patrolling\n";
            cout << "2. Assign Vehicles and Equipment to Lead Officer and Team in Investigation\n";
            cout << "3. Exit\n";
            cout << "Choose: ";
            cin >> choice;
            cout << endl;
            switch (choice) {
                case 1: {
                    administrativeStaff.assignVehiclesToPatrolling();
                    break;
                }
                case 2: {
                    administrativeStaff.assignEquipmentsToTeamAndLead();
                    administrativeStaff.assignVehiclesToTeamAndLead();
                    break;
                }
                case 3: {
                    cout << "Exiting\n";
                    break;
                }
            }
        } while (choice != 3);
    }

    static void handleForensicMenu() {
        int choice;
        vector<ForensicExpert *> experts = HR::getInstance()->getPtr();
        string id;
        cout << "Enter id of expert u wanna log into" << endl;
        cin.ignore();
        getline(cin, id);
        ForensicExpert *ptr;
        bool exists=false;
        for (int i = 0; i < experts.size(); i++) {
            cout<<experts[i]->getId()<<endl;
            if (experts[i]->getId() == id) {
                ptr = experts[i];
                exists=true;
            }
        }
        if(!exists){
            cout<<"LOOOSERRR"<<endl;
            return;
        }
        if (ptr->getEvidenceCnt() > 0) {
            cout << "loading evidences" << endl;
            ptr->LoadEvidences();
            cout << "loading evidences" << endl;
        }
        do {
            cout << "Forensic Expert Menu\n";
            cout << "1. Edit Evidence\n";
            cout << "2. Display All Evidences\n";
            cout << "3. Complete Examination\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    ptr->editEvidence();
                    break;
                case 2:
                    ptr->displayAllEvidences();
                    break;
                case 3:
                    ptr->completeExamination();
                    break;
                case 4:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 4);
    }

    static void handleConstableMenu(Constable &constable) {
        int choice;
        cout << "1. Start Patrolling" << endl;
        cout << "2. Start Investigation" << endl;
        cout << "3. Display Constable Information" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;
        cout << endl;
        switch (choice) {
            case 1:
                constable.startPatrolling();
                break;
            case 2:
                constable.startInvestigation();
                break;
            case 3:
                constable.displayInfo();
                break;
            case 4:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
        while (choice != 4);
    }

};

#endif //TEMPLATE_MENU_H
