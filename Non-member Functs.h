//
// Created by HP on 5/3/2024.
//

#ifndef PEACE_NON_MEMBER_FUNCTS_H
#define PEACE_NON_MEMBER_FUNCTS_H

#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

#include <iostream>
#include <vector>

using namespace std;

bool foundTask2(json object);

template<typename T>
bool PointerExists(T *ptr, vector<T *> vctor) {
    bool exists = false;
    for (const auto &existingEvidence: vctor) {
        if (*existingEvidence == *ptr) {
            exists = true;
            return exists;
        }
    }
    return exists;
}

void updateCount(const string &key, int n);

int getCount(const string &key);

template<typename T>
void editComplaintStatus(T id, const string &newStatus, const string &fileName, const string &arrayName,
                         const string &keyName, const string &key2) {
    cout << endl;
    cout << "Complain Id: " << id << endl;
    cout << "Investigation Status: " << newStatus << endl;
    cout << "Citizen File name: " << fileName << endl;

    json object;
    ifstream fileInput(fileName);
    if (fileInput.is_open()) {
        fileInput >> object;
        fileInput.close();
        bool found = false;
        for (auto &complaint: object[arrayName]) {
            if (complaint[key2] == id) {
                complaint[keyName] = newStatus;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Complaint with ID " << id << " does not exist." << endl;
            return;
        }
        ofstream fileOutput(fileName);
        if (fileOutput.is_open()) {
            fileOutput << object.dump(4);
            fileOutput.close();
            cout << "Status of Complaint ID: " << id << " updated successfully." << endl;
            cout << endl;
        } else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    } else {
        cout << "Error: Unable to open file for reading." << endl;
    }
}

#endif //PEACE_NON_MEMBER_FUNCTS_H
