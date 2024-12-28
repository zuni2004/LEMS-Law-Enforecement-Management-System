//
// Created by HP on 4/7/2024.
//
#ifndef PROJECT_PATROLLING_H
#define PROJECT_PATROLLING_H

#include "Complain.h"
#include <vector>
#include <fstream>

template<typename T>
class officer;

class Patrolling {
private:
    int date;
    int month;
    int year;
    string status;
    string id;
    string area;
    int complainID;
    string complainFile;
    string type;
    bool vehicleAssigned;
    vector<string> logs;
    vector<string> officers;
    vector<officer<string> *> officersPtr;
public:
    Patrolling(const string &id, const string &type)
            : id(id) {
        this->type = type;
        string fileName = type + ".json";
        ifstream file(fileName);
        if (file.is_open()) {
            file.close();
            getInfo();
        }
    }

    vector<officer<string> *> getOfficerPointers();

    void getInfo();

    void getComplainingInfo();

    void updateStatus();

    void addLog(string logEntry) {
        logs.push_back(logEntry);
    }

    string getID() {
        return id;
    }

    bool getVehicleStatus(){
        return vehicleAssigned;
    }

    void setVehicleStatus(bool assigned){
        vehicleAssigned=assigned;
    }

    void displayLogs() {
        cout << "Patrol Logs for " << area << ":\n";
        for (const auto &log: logs) {
            cout << log << "\n";
        }
    }

    void displayInfo() const {
        cout << "Patrolling ID: " << id << endl;
        cout << "Type: " << type << endl;
        cout << "Date: " << date << "/" << month << "/" << year << endl;
        cout << "Status: " << status << endl;
        cout << "Area: " << area << endl;
        cout << "Complain ID: " << complainID << endl;
        cout << "Complain File: " << complainFile << endl;
        cout << "Assigned Officers:\n";
        for (const auto &officer: officers) {
            cout << "- " << officer << endl;
        }
    }

    string getArea() const {
        return area;
    }

    void setArea(string newArea) {
        area = newArea;
    }

    void displayOfficers();

    friend bool operator==(const Patrolling &lhs, const Patrolling &rhs);
};

#endif //PROJECT_PATROLLING_H
