//
// Created by HP on 5/3/2024.
//
#include "Non-member Functs.h"

bool foundTask2(json object) {
    bool foundTask = false;
    if (object.find("Task Count") != object.end()) {
        foundTask = true;
    }
    if (!foundTask) {
    }
    return foundTask;
}

void updateCount(const string &key, int n) {
    json j;
    ifstream file("citizenCount.json");
    file >> j;
    file.close();
    j[key] = n;
    ofstream file2("citizenCount.json");
    file2 << setw(4) << j << endl;
}

int getCount(const string &key) {
    json obj;
    ifstream file("citizenCount.json");
    file >> obj;
    file.close();
    int id = obj[key];
    return id;
}
