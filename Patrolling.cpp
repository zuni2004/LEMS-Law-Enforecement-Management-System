//
// Created by HP on 4/20/2024.
#include "officer.h"
#include "Patrolling.h"
#include "HR.h"
#include "Non-member Functs.h"

void Patrolling::displayOfficers() {
    cout << endl;
    cout << "Displaying Patrolling " << endl;
    cout << "Date: " << date << endl;
    cout << "Month: " << month << endl;
    cout << "Year: " << year << endl;
    cout << "Status: " << status << endl;
    cout << "Case ID: " << id << endl;
    cout << "Area: " << area << endl;
    cout << "Complain ID: " << complainID << endl;
    cout << "Complain File: " << complainFile << endl;
    cout << "Assigned Officers IDs: " << endl;
    for (const auto &officer: officers) {
        cout << officer << " ";
    }
    cout << "Assigned Officers Info: " << endl;
    for (int i = 0; i < officersPtr.size(); i++) {
        cout<<"Officer number "<<i<<endl;
        officersPtr[i]->displayInfo();
        cout<<"----"<<endl;
    }


}

void Patrolling::updateStatus() {
    if (complainFile != "N/A") {
        editComplaintStatus(complainID, "Patrolling Completed", complainFile, "Complaints", "Status", "Complain Count");
    }
    for (const auto &officer: officers) {
        ::editFile(officer + ".json", "Info", "Availability", true);
        ::editFile(officer + ".json", "Task Count", "Current Assigned Patrolling", "None");
        editComplaintStatus(id, "Completed", type + ".json", "Patrollings", "Status", "Case ID");
    }
}

vector<officer<string> *> Patrolling::getOfficerPointers() {
    return officersPtr;
}

void Patrolling::getInfo() {
    json j;
    ifstream file(type + ".json");
    if (!file.is_open()) {
        cerr << "Error: Unable to open Patrolling.json" << endl;
        return;
    }
    file >> j;
    file.close();
    auto patrollingsArray = j["Patrollings"];
    bool found = false;
    for (size_t i = 0; i < patrollingsArray.size(); ++i) {
        if (patrollingsArray[i]["Case ID"] == id) {
            complainID = patrollingsArray[i].value("Complain ID", 0);
            complainFile = patrollingsArray[i].value("Complain file", "N/A");
            date = patrollingsArray[i]["Date"];
            month = patrollingsArray[i]["Month"];
            year = patrollingsArray[i]["Year"];
            status = patrollingsArray[i]["Status"];
            area = patrollingsArray[i]["Area"];
            auto officersArray = patrollingsArray[i]["Assigned officer IDs"];
            for (auto &officer: officersArray) {
                officers.push_back(officer);
            }
            for (int k = 0; k < officers.size(); ++k) {
                cout << officers[i] << endl;
                officersPtr.push_back(HR::getInstance()->getOfficerByID(officers[i]));
            }
            found = true;
            break;
        }
    }
    if (!found) {
        return;
    }
}

bool operator==(const Patrolling &lhs, const Patrolling &rhs) {
    return lhs.date == rhs.date &&
           lhs.month == rhs.month &&
           lhs.year == rhs.year &&
           lhs.status == rhs.status &&
           lhs.id == rhs.id &&
           lhs.area == rhs.area &&
           lhs.complainID == rhs.complainID &&
           lhs.complainFile == rhs.complainFile &&
           lhs.type == rhs.type &&
           lhs.logs == rhs.logs &&
           lhs.officers == rhs.officers &&
           lhs.officersPtr == rhs.officersPtr;
}