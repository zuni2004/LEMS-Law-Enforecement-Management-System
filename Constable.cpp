//
// Created by hp on 5/6/2024.
//
#include "Constable.h"
#include "SHO.h"

string getCurrentTaskID2(const json &j, string task, const string &key2) {
    if (j.contains(task)) {
        if (j[task].contains(key2)) {
            return j[task][key2];
        } else {
            cerr << "Error: Key 'Patrolling ID' not found in the current task." << endl;
            return "";
        }
    } else {
        cerr << "Error: Key 'Task count' not found in the JSON object." << endl;
        return "";
    }
}

void Constable::getLeadOfficer(Investigation *ptr) {
    vector<officer<string> *> ptr2 = ptr->getOfficers();
    for (int i = 0; i < ptr2.size(); i++) {
        if (ptr2[i]->getOfficerID() != getRank()) {
            HeadConstable = ptr2[i];
        }
    }
}

void Constable::getLeadOfficer(Patrolling *pr2) {
    vector<officer<string> *> ptr2 = pr2->getOfficerPointers();
    for (int i = 0; i < ptr2.size(); i++) {
        if (ptr2[i]->getOfficerID() != getRank()) {
            HeadConstable = ptr2[i];
        }
    }
}

void Constable::startInvestigation() {
    json j;
    string fileName = getOfficerID() + ".json";
    ifstream file(fileName);
    file >> j;
    file.close();
    string caseID = getCurrentTaskID2(j, getCurrentTask(), "Case file ID");
    if (caseID == "") {
        cout << "This case id doesn't exist" << endl;
        return;
    }
    investigation = (SHO::InvestigationByid(caseID));
    getLeadOfficer(investigation);
    int choice;
    do {
        cout << "Investigation Menu:" << endl;
        cout << "1. Get Investigation ID" << endl;
        cout << "2. Add Evidence" << endl;
        cout << "3. Display Investigation Details" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Case ID: " << investigation->getcaseID() << endl;
                break;
            case 2:
                investigation->addEvidence();
                break;
            case 3: {
                investigation->display();
            }
            case 4: {
                cout << "Exiting.." << endl;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 4);
}

void Constable::startPatrolling() {
    json j;
    string fileName = getOfficerID() + ".json";
    ifstream file(fileName);
    file >> j;
    file.close();
    string caseID = getCurrentTaskID2(j, getCurrentTask(), "Patrolling ID");
    if (caseID == "") {
        cout << "This case id doesn't exist" << endl;
        return;
    }
    patrolling = SHO::PatrollingByid(caseID);
    getLeadOfficer(patrolling);
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Get Patrol Information\n";
        cout << "2. Add Log\n";
        cout << "3. Display Assigned Officers\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                patrolling->displayInfo();
                break;
            case 2: {
                string logEntry;
                cout << "Enter log entry: ";
                cin.ignore();
                getline(cin, logEntry);
                patrolling->addLog(logEntry);
                break;
            }
            case 3:
                patrolling->displayOfficers();
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}