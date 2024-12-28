//
// Created by HP on 4/28/2024.
//
#include <fstream>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

#include "Forsenic Expert.h"
#include "Evidence.h"
#include "Investigation.h"
#include "SHO.h"

void ForensicExpert::LoadEvidences() {
    string fileName = getId() + ".json";
    json j;
    ifstream file3(fileName);
    if (!file3.is_open()) {
        cerr << "Failed to open file for reading: " << fileName << endl;
        return;
    }
    file3 >> j;
    file3.close();
    string case_id;
    string evidenceID;
    json &evidences = j["Evidences"];
    for (auto &evidence: evidences) {
        cout << "Evidence ID: " << evidence["Evidence ID"] << endl;
        cout << "Case File ID: " << evidence["Case File ID"] << endl;
        cout << "Status: " << evidence["Status"] << endl;
        cout << "Description: " << evidence["Description"] << endl;
        case_id = evidence["Case File ID"];
        evidenceID = evidence["Evidence ID"];
        cout << "case id is " << case_id << endl;
        cout << "evidence id is " << evidenceID << endl;
        Evidence *ptr = SHO::InvestigationByid(case_id)->getEvidenceByid(evidenceID);
        if (ptr != nullptr) {
            this->ptr.push_back(ptr);
        } else {
            cout << "this pointer was null ptr" << endl;
        }
    }
}

void ForensicExpert::displayAllEvidences() {
    for (int i = 0; i < ptr.size(); i++) {
        ptr[i]->displayInfo();
    }
}

bool ForensicExpert::capacity(json &j) {
    if (j["Info"]["Evidence Count"] >= j["Info"]["Task Capacity"]) {
        return false;
    }
    return true;
}

void ForensicExpert::addEvidence(Evidence *ptr) {
    string fileName = getId() + ".json";
    json j;
    ifstream file3(fileName);
    if (!file3.is_open()) {
        cerr << "Failed to open file for reading: " << fileName << endl;
        return;
    }
    file3 >> j;
    file3.close();
    if (j.empty()) {
        cerr << "JSON file is empty or failed to read data from file: " << fileName << endl;
        return;
    }
    int cnt2 = 1;
    cnt2 = j["Info"]["Evidence Count"];
    cnt2++;
    j["Info"]["Evidence Count"] = cnt2;
    if (!capacity(j)) {
        cout << "Unable to add more evidence. Capacity reached." << endl;
        return;
    }
    if (!j.contains("Evidences")) {
        j["Evidences"] = json::array();
    }
    json newEvidence = {
            {"Evidence ID",  ptr->getID()},
            {"Case File ID", ptr->getFile()},
            {"Status",       "Under examination"},
            {"Description",  ptr->getDesc()}
    };
    ptr->setStatus2("Under examination");
    j["Evidences"].push_back(newEvidence);
    ofstream file4(fileName);
    if (!file4.is_open()) {
        cerr << "Failed to open file for writing: " << fileName << endl;
        return;
    }
    file4 << setw(4) << j << endl;
    file4.close();
    this->ptr.push_back(ptr);
}

void ForensicExpert::editEvidence() {
    string id;
    cout << "Enter evidence ID you want to edit: ";
    cin.ignore();
    getline(cin, id);
    string fileName = this->id + ".json";
    json j;
    ifstream file3(fileName);
    file3 >> j;
    file3.close();
    if (j.contains("Evidences")) {
        string additionalDesc;
        json &evidences = j["Evidences"];
        for (auto &evidence: evidences) {
            if (evidence["Evidence ID"] == id) {
                cout << evidence["Status"] << endl;
                cout << "Enter additional description: ";
                getline(cin, additionalDesc);
                evidence["Description"] = evidence["Description"].get<string>() + " " + additionalDesc;
                ofstream file4(fileName);
                file4 << setw(4) << j << endl;
                file4.close();
                cout << "Evidence with ID '" << id << "' has been updated." << endl;
            }
        }
        for (int i = 0; i < ptr.size(); i++) {
            if (ptr[i]->getID() == id) {
                ptr[i]->setDesc(additionalDesc, this->id);
            } else {
                cout << "doesnt exist in vector" << endl;
            }
        }
    }
    cout << "Evidence with ID '" << id << "' not found." << endl;
}

void ForensicExpert::completeExamination() {
    string id;
    cout << "Enter evidence ID you want to edit: ";
    cin.ignore();
    getline(cin, id);
    string fileName = this->id + ".json";
    json j;
    ifstream file3(fileName);
    file3 >> j;
    file3.close();
    if (j.contains("Evidences")) {
        json &evidences = j["Evidences"];
        for (auto &evidence: evidences) {
            if (evidence["Evidence ID"] == id) {
                cout << evidence["Status"] << endl;
                evidence["Status"] = "Examination Completed";
                evidenceCnt--;
                evidence["Evidence Count"] = evidenceCnt;
                ofstream file4(fileName);
                file4 << setw(4) << j << endl;
                file4.close();
                for (auto it = ptr.begin(); it != ptr.end(); ++it) {
                    if ((*it)->getID() == id) {
                        (*it)->setStatus2("Examination Completed");
                        ptr.erase(it);
                        break;
                    }
                }
                return;
            } else {
                cout << "This evidence id doesn't exist" << endl;
            }
        }
    }
}
