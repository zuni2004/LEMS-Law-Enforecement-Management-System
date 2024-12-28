#include "Investigation.h"
#include "officer.h"
#include "HR.h"
#include "Non-member Functs.h"
#include "Person.h"

bool operator==(const Investigation &lhs, const Investigation &rhs) {
    return lhs.getCaseID() == rhs.getCaseID();
}

bool Investigation::assignForensicExpert(ForensicExpert *ptr, const string &id2) {
    bool found = false;
    for (int i = 0; i < evidences.size(); i++) {
        if (evidences[i]->id == id2) {
            evidences[i]->add2File(ptr);
            found = true;
        }
    }
    if (!found) {
        cout << "This evidence id doesnt exist" << endl;
    }
    return found;
}

vector<officer<string> *> getOfficers(vector<string> &ids, const string &lead) {
    vector<officer<string> *> officers;
    HR *hr = HR::getInstance();
    for (int i = 0; i < ids.size(); i++) {
        officers.push_back(hr->getOfficerByID(ids[i]));
    }
    officers.push_back(hr->getOfficerByID(lead));
    return officers;
}

vector<officer<string> *> Investigation::getOfficers() {
    getInfo();
    officers = ::getOfficers(officerIDs, LeadingOfficerID);
    return officers;
}

template<typename T>
void update(const string &key1, const string &key2, const T &change, const string &caseID) {
    json j;
    ifstream file3("Casefile " + caseID + ".json");
    file3 >> j;
    j[key1][key2] = change;
    ofstream file2("Casefile " + caseID + ".json");
    file2 << setw(4) << j << endl;
    file2.close();
}

void Investigation::updateStatus(const string &newStatus, const string &key) {
    ::editFile("Casefile " + caseID + ".json", "Info", "Status", newStatus);
    ::editFile(LeadingOfficerID + ".json", "Info", "Availability", true);
    ::editFile(LeadingOfficerID + ".json", "Task Count", "Current Assigned Investigation", "None");
    ::editFile(LeadingOfficerID + ".json", key, "Status", newStatus);
    for (const auto &officer: officerIDs) {
        ::editFile(officer + ".json", "Info", "Availability", true);
        ::editFile(officer + ".json", "Task Count", "Current Assigned Investigation", "None");
        ::editFile(officer + ".json", key, "Status", newStatus);
    }
}

void Investigation::getInfo() {
    json j;
    ifstream file3("Casefile " + caseID + ".json");
    if (!file3.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }
    file3 >> j;
    file3.close();
    LeadingOfficerID = j["Info"]["Leading officer ID"];
    complainFile = j["Info"]["Complain file"];
    complainID = j["Info"]["Complain ID"];
    this->assignedOfficers = j["Info"]["Count of assigned officers"];
    status = j["Info"]["Status"];
    officerIDs.clear();
    for (const auto &idofficer: j["Info"]["Assigned officer IDs"]) {
        officerIDs.push_back(idofficer);
    }
    bool foundTask = foundTask2(j);
    if (foundTask) {
        int ev = j["Task Count"]["Evidence count"];
        evidenceCnt = ev;
        int p = j["Task Count"]["Person under investigation count"];
        PersonCnt = p;
        if (j.contains("Evidences")) {
            for (const auto &evidenceJson: j["Evidences"]) {
                Evidence *evidence = new Evidence();
                evidence->id = evidenceJson["ID"];
                evidence->description = evidenceJson["Description"];
                evidence->locationFound = evidenceJson["Location Found"];
                evidence->dateAndTimeFound = evidenceJson["Date And Time Found"];
                evidence->chainOfCustody = evidenceJson["Chain of Custody"];
                evidence->type = evidenceJson["Type"];
                evidence->source = evidenceJson["Source"];
                evidence->associatedCaseID = evidenceJson["Associated Case ID"];
                evidence->status = evidenceJson["Status"];
                evidence->priority = evidenceJson["Priority"];
                evidence->remarks = evidenceJson["Remarks"];
                for (const auto &id2: evidenceJson["Discovered by officer IDs"]) {
                    evidence->officerIDs.push_back(id2);
                }
                if (evidenceJson.contains("Experts assigned")) {
                    for (const auto &expertJson: evidenceJson["Experts assigned"]) {
                        vector<ForensicExpert *> experts2 = HR::getInstance()->getPtr();
                        for (int i = 0; i < experts2.size(); i++) {
                            cout << expertJson["Expert ID"] << endl;
                            if (experts2[i]->getId() == expertJson["Expert ID"]) {
                                if (!PointerExists(experts2[i], evidence->experts)) {
                                    evidence->experts.push_back(experts2[i]);
                                    if (!PointerExists(experts2[i], experts)) {
                                        experts.push_back(experts2[i]);
                                    }
                                }
                            }
                        }
                    }
                }
                if (PointerExists(evidence, evidences)) {
                    delete evidence;
                } else {
                    evidences.push_back(evidence);
                }

            }
        }
        if (j.contains("Persons")) {
            for (const auto &personJson: j["Persons"]) {
                Person *person2 = new Person();
                person2->id = personJson["ID"];
                person2->name = personJson["Name"];
                person2->dateOfBirth = personJson["DateOfBirth"];
                person2->address = personJson["Address"];
                person2->occupation = personJson["Occupation"];
                person2->nationality = personJson["Nationality"];
                for (const auto &phoneNumber: personJson["PhoneNumbers"]) {
                    person2->phoneNumbers.push_back(phoneNumber);
                }
                for (const auto &email: personJson["EmailAddresses"]) {
                    person2->emailAddresses.push_back(email);
                }
                if (PointerExists(person2, person)) {
                    delete person2;
                } else {
                    person.push_back(person2);
                }
            }
        }
    }
}

void Investigation::updateStatus(const string &newStatus) {
    ::editFile("Casefile " + caseID + ".json", "Info", "Status", "Completed");
    for (const auto &officer: officerIDs) {
        ::editFile(officer + ".json", "Info", "Availability", true);
        ::editFile(officer + ".json", "Task Count", "Current Assigned Investigation", "None");
    }
}

void Investigation::addEvidence() {
    json j;
    ifstream file3("Casefile " + caseID + ".json");
    file3 >> j;
    file3.close();
    bool foundTask = ::foundTask2(j);
    if (!foundTask) {
        j["Task Count"] = {
                {"Evidence count",                   0},
                {"Person under investigation count", 0}
        };
        evidenceCnt = 0;
        PersonCnt = 0;
    }
    int choice;
    cout << "1.Add evidence" << endl;
    cout << "2.Add Person" << endl;
    cin >> choice;
    if (choice == 1) {
        Evidence *evidence = new Evidence();
        cin >> *evidence;
        evidences.push_back(evidence);
        stringstream ss;
        ss << evidenceCnt;
        string count = ss.str();
        string newID = caseID + " " + count;
        if (j.find("Evidences") == j.end()) {
            j["Evidences"] = json::array();
        }
        json evidenceObj = {
                {"ID",                        newID},
                {"Description",               evidence->description},
                {"Location Found",            evidence->locationFound},
                {"Date And Time Found",       evidence->dateAndTimeFound},
                {"Chain of Custody",          evidence->chainOfCustody},
                {"Type",                      evidence->type},
                {"Source",                    evidence->source},
                {"Associated Case ID",        caseID},
                {"Status",                    evidence->status},
                {"Priority",                  evidence->priority},
                {"Remarks",                   evidence->remarks},
                {"Discovered by officer IDs", evidence->officerIDs}
        };
        evidence->id = newID;
        evidence->associatedCaseID = caseID;
        j["Evidences"].push_back(evidenceObj);
        evidenceCnt++;
    } else {
        Person *person2 = new Person();
        cin >> *person2;
        person.push_back(person2);
        stringstream ss;
        ss << PersonCnt;
        string count = ss.str();
        string newID = caseID + count;
        if (j.find("Persons") == j.end()) {
            j["Persons"] = json::array();
        }
        json personObj = {
                {"ID",             newID},
                {"Name",           person2->name},
                {"DateOfBirth",    person2->dateOfBirth},
                {"Address",        person2->address},
                {"Occupation",     person2->occupation},
                {"Nationality",    person2->nationality},
                {"PhoneNumbers",   person2->phoneNumbers},
                {"EmailAddresses", person2->emailAddresses},
                {"Notes",          person2->notes}
        };
        person2->id = newID;
        j["Persons"].push_back(personObj);
        PersonCnt++;
    }
    ofstream file2("Casefile " + caseID + ".json");
    file2 << setw(4) << j << endl;
    file2.close();
    update("Task Count", "Evidence count", evidenceCnt, caseID);
    update("Task Count", "Person under investigation count", PersonCnt, caseID);
}

void Investigation::display() {
    cout << "Case ID: " << caseID << endl;
    cout << "Status: " << status << endl;
    cout << "Complain File: " << complainFile << endl;
    cout << "Complain ID: " << complainID << endl;
    cout << "Assigned Officers: " << assignedOfficers << endl;
    cout << "Evidence Count: " << evidenceCnt << endl;
    cout << "Person Count: " << PersonCnt << endl;
    cout << "Leading Officer ID: " << LeadingOfficerID << endl;
    cout << "Officer IDs:" << endl;
    for (const auto &officerID: officerIDs) {
        cout << officerID << endl;
    }
    cout << "Evidences:" << endl;
    for (const auto &evidence: evidences) {
        cout << *evidence << endl;
    }
    cout << "People under investigation:" << endl;
    for (const auto &person2: person) {
        cout << *person2 << endl;
    }
    cout << "Forensic Experts:" << endl;
    for (const auto &expert: experts) {
        cout << expert->getId() << endl;
    }
}