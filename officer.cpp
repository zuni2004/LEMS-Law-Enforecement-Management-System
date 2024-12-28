// Created by HP on 4/18/2024.
#include "Investigation.h"
#include "officer.h"
#include "Non-member Functs.h"

template<>
void officer<string>::addPatrolling(Patrolling *ptr) {
    string fileName = officerID + ".json";
    json object;
    ifstream file(fileName);
    file >> object;
    file.close();
    bool foundTask = ::foundTask2(object);
    int id;
    if (foundTask) {
        id = object["Task Count"]["Patrolling count"];
        patrollingCnt = id;
    } else {
        {
            object["Task Count"] = {
                    {"Investigation count",            0},
                    {"Patrolling count",               0},
                    {"Current Assigned Patrolling",    "None"},
                    {"Current Assigned Investigation", "None"}
            };
            patrollingCnt = 0;
            investigationCnt = 0;
        }
    }
    object["Info"]["Availability"] = false;
    stringstream ss;
    ss << patrollingCnt;
    string count = ss.str();
    string newKey = "Patrolling " + count;
    object[newKey] = {
            {"Status",           "In progress"},
            {"Patrolling count", patrollingCnt},
            {"Patrolling ID",    ptr->getID()}
    };
    patrollingCnt++;
    object["Task Count"]["Current Assigned Patrolling"] = newKey;
    object["Task Count"]["Patrolling count"] = patrollingCnt;
    ofstream file4(fileName);
    file4 << setw(4) << object << endl;
    file4.close();
    patrollings.push_back(ptr);
}

template<>
void officer<string>::addInvestigation(Investigation *ptr) {
    string fileName = officerID + ".json";
    json object;
    ifstream file(fileName);
    file >> object;
    file.close();
    bool foundTask = ::foundTask2(object);
    int id;
    if (foundTask) {
        id = object["Task Count"]["Investigation count"];
        investigationCnt = id;
    } else {
        {
            object["Task Count"] = {
                    {"Investigation count",            0},
                    {"Patrolling count",               0},
                    {"Current Assigned Patrolling",    "None"},
                    {"Current Assigned Investigation", "None"}
            };
            patrollingCnt = 0;
            investigationCnt = 0;
        }
    }
    object["Info"]["Availability"] = false;
    stringstream ss;
    ss << investigationCnt;
    string count = ss.str();
    string newKey = "Investigation " + count;
    object[newKey] = {
            {"Status",              "In progress"},
            {"Investigation count", investigationCnt},
            {"Case file ID",        ptr->getcaseID()}
    };
    investigationCnt++;
    object["Task Count"]["Investigation count"] = investigationCnt;
    object["Task Count"]["Current Assigned Investigation"] = newKey;
    ofstream file4(fileName);
    file4 << setw(4) << object << endl;
    file4.close();
    investigations.push_back(ptr);
}