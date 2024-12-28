//
// Created by HP on 4/7/2024.
//
#ifndef PROJECT_OOP_INVESTIGATION_H
#define PROJECT_OOP_INVESTIGATION_H
using namespace std;

#include <iostream>
#include "Evidence.h"
#include "Forsenic Expert.h"
#include <vector>
#include "json.hpp"
#include <fstream>
#include <string>

using json = nlohmann::json;

template<typename T>
class officer;

class Person;

//every investigation has a casefile assigned to it
const int MAX_MEMBERS = 10;

class Investigation {
private:
    int date;
    int month;
    int year;
    string caseID;
    string status;
    string complainFile;
    int complainID;
    int assignedOfficers;
    int evidenceCnt;
    int PersonCnt;
    bool equipmentAssignedStatus;
    bool vehicleAssignedStatus;
    vector<Evidence *> evidences;
    vector<Person *> person;
    vector<string> officerIDs;
    vector<officer<string> *> officers;
    string LeadingOfficerID;
    vector<ForensicExpert *> experts;
public:
    friend bool operator==(const Investigation &lhs, const Investigation &rhs);

    vector<officer<string> *> getOfficers();

    Investigation(const string &id = "") :
            caseID(id) {
        if (caseID == "") {
            status = "";
            complainFile = "";
            complainID = 0;
            assignedOfficers = 0;
            evidenceCnt = 0;
            PersonCnt = 0;
            LeadingOfficerID = "";
            date = 0;
            month = 0;
            year = 0;
            equipmentAssignedStatus= false;
            vehicleAssignedStatus= false;
        }
        ifstream file3("Casefile " + caseID + ".json");
        if (file3.is_open()) {
            file3.close();
            getInfo();
        }
    }

    void setEquipment(bool hasEquipment){
        equipmentAssignedStatus=hasEquipment;
    }

    void setVehicle(bool hasVehicle){
        vehicleAssignedStatus=hasVehicle;
    }

    const string &getCaseID() const {//first call the getInfo function to have values in getters
        return caseID;
    }

    const string &getStatus() const {
        return status;
    }

    const string &getComplainFile() const {
        return complainFile;
    }

    const int &getComplainID() const {
        return complainID;
    }

    string getcaseID() {
        return caseID;
    }

    bool getEquipment(){
        return equipmentAssignedStatus;
    }

    bool getVehicles(){
        return vehicleAssignedStatus;
    }

    vector<Evidence *> &getEvidences() {
        return evidences;
    }

    Evidence *getEvidenceByid(const string &id) {
        for (int i = 0; i < evidences.size(); i++) {
            if (evidences[i]->id == id) {
                return evidences[i];
            }
        }
        return nullptr;
    }

    void displayEvidences() {
        for (int i = 0; i < evidences.size(); i++) {
            cout << *evidences[i];
        }
    }

    const vector<string> &getOfficerIDs() const {
        return officerIDs;
    }

    const string &getLeadingOfficerID() const {
        return LeadingOfficerID;
    }

    const vector<ForensicExpert *> &getExperts() const {
        return experts;
    }

    void getInfo();

    void display();

    ~Investigation() {}

    void assignTeam(officer<string> *officers);

    void updateStatus(const string &newStatus);

    void addEvidence();

    void updateCaseFile();

    bool assignForensicExpert(ForensicExpert *ptr, const string &id);

    Investigation *returnInvestigationPtr();

    void updateStatus(const string& newStatus,const string&key);
};

//void Investigation::getInfo(){
//    json j;
//    ifstream file3("Casefile "+caseID+".json");
//    file3>>j;
//    file3.close();
//    j["Info"]["Case ID"] = caseID;
//    j["Info"]["Complain file"] = complainFile;
//    j["Info"]["Complain ID"] = complainID;
//    j["Info"]["Status"] = status;
//    j["Info"]["Leading officer ID"] = LeadingOfficerID;
//    j["Info"]["Count of assigned officers"] = assignedOfficers;
//    officerIDs.clear();
//    for (const auto& idofficer : j["Info"]["Assigned officer IDs"]) {
//        officerIDs.push_back(idofficer);
//    }
//    bool foundTask= foundTask2(j);
//    if(foundTask){
//        evidences.clear();
//        int ev= j["Task count"]["Evidence count"];
//        evidenceCnt=ev;
//      //working till here
//        int p=j["Task count"]["Person under investigation count"];
//        PersonCnt=p;
//        for(int i=0;i<evidenceCnt;i++) {
//            stringstream ss;
//            ss<<i;
//            string count = ss.str();
//            string key="Evidence"+count;
//            Evidence *evidence = new Evidence();
//            evidence->id=j[key]["ID"];
//            evidence->description = j[key]["Description"];
//            cout<<evidence->description<<endl;
//            evidence->locationFound = j[key]["Location Found"];
//            evidence->dateAndTimeFound = j[key]["Date And Time Found"];
//            evidence->chainOfCustody = j[key]["Chain of Custody"];
//            evidence->type = j[key]["Type"];
//            evidence->source = j[key]["Source"];
//            evidence->associatedCaseID = j[key]["Associated Case ID"];
//            evidence->status = j[key]["Status"];
//            evidence->priority = j[key]["Priority"];
//            evidence->remarks = j[key]["Remarks"];
//            for (const auto &id2: j[key]["Discovered by officer IDs"]) {
//                evidence->officerIDs.push_back(id2);
//            }
//            bool exists = false;
//            for (const auto& existingEvidence : evidences) {
//                if (existingEvidence == evidence) {
//                    exists = true;
//                    break;
//                }
//            }
//            if (!exists) {
//                evidences.push_back(evidence);
//                cout<<"pushed back"<<endl;
//            }else{
//                delete evidence;
//            }
//        }
//    }
//    }
#endif //PROJECT_OOP_INVESTIGATION_H
