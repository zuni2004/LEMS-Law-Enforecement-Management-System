//
// Created by HP on 4/6/2024.
//

#ifndef PROJECT_OOP_COMPLAIN_H
#define PROJECT_OOP_COMPLAIN_H

#include <sstream>
#include <iostream>
#include <string>

using namespace std;

class Complain {
public:
    string citizenFile;
    string incidentDate;
    string incidentTime;
    string incidentAddress;
    int policeStationID;
    string incidentDetail;
    bool emergency;
    string status;
    int id;

    Complain(const string &date = "", const string &time = "", const string &address = "",
             int stationID = 0, const string &detail = "", bool isEmergency = false, const string &citizenFile = "",
             int id = 0)
            : incidentDate(date), incidentTime(time), incidentAddress(address), policeStationID(stationID),
              incidentDetail(detail), emergency(isEmergency), citizenFile(citizenFile), id(id) {
        status = "Pending";
    }

    string getIncidentDate() const {
        return incidentDate;
    }

    string getIncidentTime() const {
        return incidentTime;
    }

    string getComplainAddress() const {
        return incidentAddress;
    }

    int getPoliceStationID() const {
        return policeStationID;
    }

    string getIncidentDetail() const {
        return incidentDetail;
    }

    bool isEmergency() const {
        return emergency;
    }

    string getStatus() const {
        return status;
    }

    void update_status(const string &newStatus) {
        status = newStatus;
        cout << "Status updated to: " << status << endl;
    }

    Complain &operator=(const Complain &other) {
        if (this != &other) {
            citizenFile = other.citizenFile;
            incidentDate = other.incidentDate;
            incidentTime = other.incidentTime;
            incidentAddress = other.incidentAddress;
            policeStationID = other.policeStationID;
            incidentDetail = other.incidentDetail;
            emergency = other.emergency;
            status = other.status;
            id = other.id;

        }
        return *this;
    }

    void displayDetail() {
        cout << "Citizen File: " << citizenFile << "\n"
             << "Incident Date: " << incidentDate << "\n"
             << "Incident Time: " << incidentTime << "\n"
             << "Incident Address: " << incidentAddress << "\n"
             << "Police Station ID: " << policeStationID << "\n"
             << "Incident Detail: " << incidentDetail << "\n"
             << "Emergency: " << (emergency ? "Yes" : "No") << "\n"
             << "Status: " << status << "\n"
             << "ID: " << id << "\n" << endl;
    }
};


#endif //PROJECT_OOP_COMPLAIN_H
