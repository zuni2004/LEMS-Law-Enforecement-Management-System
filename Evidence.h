//
// Created by HP on 4/8/2024.
//
#ifndef PROJECT_OOP_EVIDENCE_H
#define PROJECT_OOP_EVIDENCE_H

class ForensicExpert; // Forward declaration
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

#include "User.h"

using namespace std;

class Evidence {
    string id;
    string description;
    string locationFound;
    string dateAndTimeFound;
    string chainOfCustody;
    string type;
    string source;
    string associatedCaseID;
    string status;
    int priority;
    string remarks;
    vector<string> officerIDs;
    vector<ForensicExpert *> experts;
public:
    void displayInfo() const {
        cout << "ID: " << id << endl;
        cout << "Description: " << description << endl;
        cout << "Location Found: " << locationFound << endl;
        cout << "Date and Time Found: " << dateAndTimeFound << endl;
        cout << "Chain of Custody: " << chainOfCustody << endl;
        cout << "Type: " << type << endl;
        cout << "Source: " << source << endl;
        cout << "Associated Case ID: " << associatedCaseID << endl;
        cout << "Status: " << status << endl;
        cout << "Priority: " << priority << endl;
        cout << "Remarks: " << remarks << endl;

        cout << "Officer IDs:" << endl;
        for (const auto &officerID: officerIDs) {
            cout << "- " << officerID << endl;
        }

        cout << "Forensic Experts:" << endl;
        for (const auto &expert: experts) {
//            cout << "- " << expert->getID() << endl;
        }
    }

    Evidence() {
        associatedCaseID = "id";
        id = "ID";
    }

    void setStatus(const string &status) {
        this->status = status;
//        editEvidenceStatus("Status", status, "N/A");
    }

    void setStatus2(const string &status) {
        this->status = status;
        editEvidenceStatus("Status", status, "N/A");
    }

    void setDesc(const string &desc, const string &id) {
        this->description = desc;
        editEvidenceStatus("Description", desc, id);
    }

    string getFile() {
        return associatedCaseID;
    }

    void editEvidenceStatus(const string &key, const string &update, const string &id);

    Evidence(string &id, const string &caseID) {
        this->id = id;
    }

    void updateFile();

    bool operator==(const Evidence &other) const {
        return id == other.id &&
               description == other.description &&
               locationFound == other.locationFound &&
               dateAndTimeFound == other.dateAndTimeFound &&
               chainOfCustody == other.chainOfCustody &&
               type == other.type &&
               source == other.source &&
               associatedCaseID == other.associatedCaseID &&
               status == other.status &&
               priority == other.priority &&
               remarks == other.remarks &&
               officerIDs == other.officerIDs;
    }

    string getID() {
        return id;
    }

    string Getremarks() {
        return remarks;
    }

    string getDesc() {
        return description;
    }

    void setId(const string &id) { this->id = id; }

    const string &getId() const { return id; }

    void setDescription(const string &description) { this->description = description; }

    const string &getDescription() const { return description; }

    void setLocationFound(const string &locationFound) { this->locationFound = locationFound; }

    const string &getLocationFound() const { return locationFound; }

    void setDateAndTimeFound(const string &dateAndTimeFound) { this->dateAndTimeFound = dateAndTimeFound; }

    const string &getDateAndTimeFound() const { return dateAndTimeFound; }

    void setChainOfCustody(const string &chainOfCustody) { this->chainOfCustody = chainOfCustody; }

    const string &getChainOfCustody() const { return chainOfCustody; }

    void setType(const string &type) { this->type = type; }

    const string &getType() const { return type; }

    void setSource(const string &source) { this->source = source; }

    const string &getSource() const { return source; }

    void setAssociatedCaseID(const string &associatedCaseID) { this->associatedCaseID = associatedCaseID; }

    const string &getAssociatedCaseID() const { return associatedCaseID; }

    const string &getStatus() const { return status; }

    void setPriority(int priority) { this->priority = priority; }

    int getPriority() const { return priority; }

    void setRemarks(const string &remarks) { this->remarks = remarks; }

    const string &getRemarks() const { return remarks; }

    void setOfficerIDs(const vector<string> &officerIDs) { this->officerIDs = officerIDs; }

    const vector<string> &getOfficerIDs() const { return officerIDs; }

    void GetAllexperts();

    void add2File(ForensicExpert *ptr);

    friend ostream &operator<<(ostream &os, const Evidence &evidence);

    friend istream &operator>>(istream &is, Evidence &evidence);

    friend class Investigation;
};

#endif //PROJECT_OOP_EVIDENCE_H
