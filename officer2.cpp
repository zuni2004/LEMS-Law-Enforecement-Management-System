//
// Created by HP on 4/25/2024.
#include "Investigation.h"
#include "officer.h"
#include "Non-member Functs.h"
#include "SHO.h"

template<>
void officer<string>::displayInvestigations() {
    cout << "Investigations:" << endl;

    for (const auto &investigation: investigations) {
        investigation->display();
    }
}

template<>
void officer<string>::displayPatrollings() {
    cout << "Patrollings: " << endl;
    for (const auto &patrolling: patrollings) {
        patrolling->displayOfficers();
    }
}

template<>
void officer<string>::readFromFile() {
    string fileName = officerID + ".json";
    json object;
    ifstream file(fileName);
    file >> object;
    file.close();
    bool foundTask = ::foundTask2(object);
    if (foundTask) {
        getPatrolling(object);
        getInvestigation(object);
    }
    name = object["Info"]["Name"];
    badgeNumber = object["Info"]["Badge Number"];
    rank = object["Info"]["Rank"];
    available = object["Info"]["Availability"];
    workYears = object["Info"]["Work Years"];
    if (object["Task Count"]["Current Assigned Patrolling"] == "None") {
        currentTask = object["Task Count"]["Current Assigned Investigation"];
    } else {
        currentTask = object["Task Count"]["Current Assigned Patrolling"];
        cout << "Current task is " << currentTask << endl;
    }
}

template<typename T>
void officer<T>::getPatrolling(json &object) {
    patrollings.clear();
    bool foundTask = ::foundTask2(object);
    if (foundTask) {
        patrollingCnt = object["Task Count"]["Patrolling count"];
        for (int i = 0; i <= patrollingCnt; i++) {
            stringstream ss;
            ss << i;
            string count = ss.str();
            string newKey = "Patrolling " + count;
            if (object.contains(newKey)) {
                patrollings.push_back(SHO::PatrollingByid(object[newKey]["Patrolling ID"]));
            }
        }
    } else {
        cout << "No Tasks assigned" << endl;
    }
}

template<typename T>
void officer<T>::getInvestigation(json &object) {
    investigations.clear();
    bool foundTask = ::foundTask2(object);
    if (foundTask) {
        investigationCnt = object["Task Count"]["Investigation count"];
        cout << investigationCnt << endl;
        for (int i = 0; i < investigationCnt; i++) {
            stringstream ss;
            string count = ss.str();
            string newKey = "Investigation " + count;
            if (object.contains(newKey)) {
                cout << "ID of Investigation: " << object[newKey]["Case file ID"] << endl;
                investigations.push_back(SHO::InvestigationByid(object[newKey]["Case file ID"]));
            }
        }
    } else {
        cout << "No tasks assigned" << endl;
    }
}