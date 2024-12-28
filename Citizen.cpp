//
// Created by HP on 4/6/2024.
//
#include "Citizen.h"

bool checkCNIC(const string &enteredCNIC, const string &fileName) {
    json object;
    ifstream fileInput(fileName);
    if (fileInput.is_open()) {
        fileInput >> object;
        fileInput.close();

        string storedCNIC = object["Info"]["CNIC"];
        return (enteredCNIC == storedCNIC);
    } else {
        cout << "Error: Unable to open file for reading." << endl;
        return false;
    }
}

void Citizen::fileComplain(bool exist, int count) {
    json object;
    stringstream ss;
    ss << count;
    string citizenName, address, contactNo, email;
    string cnt = ss.str();
    string fileName = cnt + ".json";
    if (!exist) {
        json object2;
        cin.ignore();
        cout << "Enter your Name: ";
        getline(cin, citizenName);
        cout << "Enter your address: ";
        getline(cin, address);
        cout << "Enter your contact No.: ";
        cin >> contactNo;
        cin.ignore();
        cout << "Enter your email: ";
        cin.ignore();
        cin >> email;
        {
            object2["Info"] = {
                    {"CNIC",         CNIC},
                    {"Name",         citizenName},
                    {"Address",      address},
                    {"Contact info", contactNo},
                    {"Email",        email}};
        }
        ofstream file(fileName);
        file << object2;
        file.close();
        ifstream file2(fileName);
        file2 >> object;
        file.close();
    } else {
        ifstream file(fileName);
        file >> object;
        file.close();
    }

    string incidentDate;
    string incidentTime;
    string incidentAddress;
    int policeStationID;
    string incidentDetail;
    bool emergency;
    cin.ignore();
    cout << "Enter incident date (YYYY-MM-DD): ";
    getline(cin, incidentDate);

    cout << "Enter incident time (HH:MM): ";
    getline(cin, incidentTime);

    cout << "Enter incident address: ";
    getline(cin, incidentAddress);

    cout << "Enter police station ID: ";
    cin >> policeStationID;
    cin.ignore();
    cout << "Enter incident detail: ";
    getline(cin, incidentDetail);

    char emergencyInput;
    cout << "Is it an emergency? (Y/N): ";
    cin >> emergencyInput;
    cin.ignore();
    emergency = (emergencyInput == 'Y' || emergencyInput == 'y');

    int complainCnt = object["Complaints"].size();
    int id = count * 10 + complainCnt;
    ss.str("");
    ss << id;
    string ID = ss.str();
    string complain = "Complaint " + ID;
    json newComplaint = {
            {"Complain Count",    id},
            {"Incident Date",     incidentDate},
            {"Incident Time",     incidentTime},
            {"Incident Address",  incidentAddress},
            {"Police Station ID", policeStationID},
            {"Incident Detail",   incidentDetail},
            {"Emergency",         emergency},
            {"Status",            "Pending"}
    };

    object["Complaints"].push_back(newComplaint);
    ofstream outFile(fileName);
    outFile << setw(4) << object << endl;
    outFile.close();
    cout << endl;
    cout << "Your Complain ID is: " << id << endl;
}

string Citizen::viewComplainStatus(int complainCount, string fileName) const {
    string complainStatus;
    json object;
    ifstream file(fileName);
    if (file.is_open()) {
        file >> object;
        file.close();
        bool found = false;
        for (const auto &complaint: object["Complaints"]) {
            if (complaint["Complain Count"] == complainCount) {
                complainStatus = complaint["Status"];
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Complaint with ID " << complainCount << " does not exist." << endl;
            return "Error: Complaint not found";
        }

        return complainStatus;
    } else {
        cout << "Unable to open file, file ID provided does not exist" << endl;
        return "Error: Unable to open file";
    }
}

vector<Complain *> Citizen::getPtr() {
    json j;
    ifstream file("citizenCount.json");
    file >> j;
    file.close();
    int cnt = j["Citizen Count"];
    for (int i = 1; i <= cnt; i++) {
        stringstream ss;
        ss << i;
        string count = ss.str();
        string fileName = count + ".json";
        json object;
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Failed to open file: " << fileName << endl;
            continue;
        }
        file >> object;
        file.close();
        for (const auto &complaint: object["Complaints"]) {
            if (complaint["Status"] == "Pending") {
                Complain *newComplaint = new Complain(
                        complaint["Incident Date"],
                        complaint["Incident Time"],
                        complaint["Incident Address"],
                        complaint["Police Station ID"],
                        complaint["Incident Detail"],
                        complaint["Emergency"],
                        fileName, complaint["Complain Count"]
                );
                validComplaints.push_back(newComplaint);
            }
        }
    }
    return validComplaints;
}
