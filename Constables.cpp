//
// Created by HP on 4/28/2024.
//
#include "HeadConstable.h"
#include "HR.h"
#include "Investigation.h"
#include "Patrolling.h"
#include "SHO.h"

void HeadConstable::getForensicExpert() {
    experts = HR::getInstance()->getPtr();
}

void HeadConstable::getConstables(Investigation *ptr) {
    vector<officer<string> *> ptr2 = ptr->getOfficers();
    for (int i = 0; i < ptr2.size(); i++) {
        if (ptr2[i]->getOfficerID() != getOfficerID()) {
            constables.push_back(ptr2[i]);
        }
    }
}

void HeadConstable::getConstables(Patrolling *ptr) {
    vector<officer<string> *> ptr2 = ptr->getOfficerPointers();
    for (int i = 0; i < ptr2.size(); i++) {
        if (ptr2[i]->getOfficerID() != getOfficerID()) {
            constables.push_back(ptr2[i]);
        }
    }
}

string getCurrentTaskID(const json &j, string task, const string &key2) {
    cout<<"task is "<<task<<endl;
    cout<<"key is "<<key2<<endl;
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

void HeadConstable::startInvestigation() {
    json j;
    string fileName = getOfficerID() + ".json";
    ifstream file(fileName);
    file >> j;
    file.close();
    string caseID = getCurrentTaskID(j, getCurrentTask(), "Case file ID");
    if (caseID == "") {
        cout << "This case id doesn't exist" << endl;
        return;
    }
    investigation = (SHO::InvestigationByid(caseID));
    getConstables(investigation);
    int choice;
    do {
        cout <<endl;
        cout << "Investigation Menu:" << endl;
        cout << "1. Get Investigation ID" << endl;
        cout << "2. Add Evidence" << endl;
        cout << "3. Add Forensic expert to evidences" << endl;
        cout << "4. Update Status" << endl;
        cout << "5. Display Investigation Details" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        switch (choice) {
            case 1:
                cout << "Case ID: " << investigation->getcaseID() << endl;
                break;
            case 2:
                investigation->addEvidence();
                break;
            case 3: {
                cout << endl;
                cout << "Displaying all evidences" << endl;
                investigation->displayEvidences();
                string idEvidence;
                cout << "Enter id of evidence you want to assign an expert to: ";
                cin.ignore();
                getline(cin, idEvidence);
                cout << "Displaying all experts" << endl;
                for (int i = 0; i < experts.size(); i++) {
                    experts[i]->displayDetails();
                }
                string id2;
                cout << "Enter id of expert you want to assign an expert to: ";
                getline(cin, id2);
                bool found = false;
                for (int i = 0; i < experts.size(); i++) {
                    if (experts[i]->getId() == id2) {
                        if (investigation->assignForensicExpert(experts[i], idEvidence)) {
                            experts[i]->addEvidence(investigation->getEvidenceByid(idEvidence));
                            found = true;
                        }
                    }
                }
                if (!found) {
                    cout << "This expert doesnt exist" << endl;
                }
                break;
            }
            case 4: {
                string status;
                cin.ignore();
                cout << "Enter new Status: ";
                getline(cin, status);
                investigation->updateStatus(status);
                break;
            }
            case 5: {
                investigation->display();
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 6);
}

void HeadConstable::startPatrolling() {
    json j;
    string fileName = getOfficerID() + ".json";
    ifstream file(fileName);
    file >> j;
    file.close();
    string caseID = getCurrentTaskID(j, getCurrentTask(), "Patrolling ID");
    if (caseID == "") {
        cout << "This case id doesn't exist" << endl;
        return;
    }
    patrolling = SHO::PatrollingByid(caseID);
    getConstables(patrolling);
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Get Patrol Information\n";
        cout << "2. Update Patrol Status\n";
        cout << "3. Add Log\n";
        cout << "4. Display Patrol Logs\n";
        cout << "5. Display Assigned Officers\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                patrolling->displayInfo();
                break;
            case 2:
                patrolling->updateStatus();
                break;
            case 3: {
                string logEntry;
                cout << "Enter log entry: ";
                cin.ignore();
                getline(cin, logEntry);
                patrolling->addLog(logEntry);
                break;
            }
            case 4: {
               patrolling->displayLogs();
                break;
            }
            case 5:
                patrolling->displayOfficers();
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}
