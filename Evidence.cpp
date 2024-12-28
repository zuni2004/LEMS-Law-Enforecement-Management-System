//
// Created by HP on 4/28/2024.
//
#include <fstream>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

#include "Evidence.h"
#include "Forsenic Expert.h"
#include "Person.h"
#include "Non-member Functs.h"

bool operator==(const Person &person1, const Person &person2) {
    return person1.id == person2.id &&
           person1.name == person2.name &&
           person1.dateOfBirth == person2.dateOfBirth &&
           person1.address == person2.address &&
           person1.occupation == person2.occupation &&
           person1.nationality == person2.nationality &&
           person1.phoneNumbers == person2.phoneNumbers &&
           person1.emailAddresses == person2.emailAddresses &&
           person1.notes == person2.notes;
}

istream &operator>>(istream &input, Person &person) {
    cout << "Enter Name: ";
    input.ignore();
    getline(input, person.name);
    cout << "Enter Date of Birth (YYYY-MM-DD): ";
    input >> person.dateOfBirth;
    cout << "Enter Address: ";
    input.ignore();
    getline(input, person.address);
    cout << "Enter Occupation: ";
    input.ignore();
    getline(input, person.occupation);
    cout << "Enter Nationality: ";
    input >> person.nationality;
    cout << "Enter Phone Numbers (end with 'end'): ";
    string phoneNumber;
    while (true) {
        input >> phoneNumber;
        if (phoneNumber == "end") break;
        person.phoneNumbers.push_back(phoneNumber);
    }
    cout << "Enter Email Addresses (end with 'end'): ";
    string emailAddress;
    while (true) {
        input >> emailAddress;
        if (emailAddress == "end") break;
        person.emailAddresses.push_back(emailAddress);
    }
    cout << "Enter Notes: ";
    input.ignore();
    getline(input, person.notes);
    return input;
}

ostream &operator<<(ostream &output, const Person &person) {
    output << "ID: " << person.id << endl;
    output << "Name: " << person.name << endl;
    output << "Date of Birth: " << person.dateOfBirth << endl;
    output << "Address: " << person.address << endl;
    output << "Occupation: " << person.occupation << endl;
    output << "Nationality: " << person.nationality << endl;
    output << "Phone Numbers:" << endl;
    for (const auto &phoneNumber: person.phoneNumbers) {
        output << "- " << phoneNumber << endl;
    }
    output << "Email Addresses:" << endl;
    for (const auto &emailAddress: person.emailAddresses) {
        output << "- " << emailAddress << endl;
    }
    output << "Notes: " << person.notes << endl;
    return output;
}

ostream &operator<<(ostream &os, const Evidence &evidence) {
    os << "ID: " << evidence.id << endl;
    os << "Description: " << evidence.description << endl;
    os << "Location Found: " << evidence.locationFound << endl;
    os << "Date and Time Found: " << evidence.dateAndTimeFound << endl;
    os << "Chain of Custody: " << evidence.chainOfCustody << endl;
    os << "Type: " << evidence.type << endl;
    os << "Source: " << evidence.source << endl;
    os << "Associated Case ID: " << evidence.associatedCaseID << endl;
    os << "Status: " << evidence.status << endl;
    os << "Priority: " << evidence.priority << endl;
    os << "Remarks: " << evidence.remarks << endl;
    os << "Officer IDs:" << endl;
    for (const auto &id: evidence.officerIDs) {
        os << "- " << id << endl;
    }
    return os;
}

istream &operator>>(istream &is, Evidence &evidence) {
    cout << "Enter Description: ";
    is.ignore();
    getline(is, evidence.description);

    cout << "Enter Location Found: ";
    getline(is, evidence.locationFound);

    cout << "Enter Date and Time Found (YYYY-MM-DD HH:MM:SS): ";
    getline(is, evidence.dateAndTimeFound);

    cout << "Enter Chain of Custody: ";
    getline(is, evidence.chainOfCustody);

    cout << "Enter Type: ";
    getline(is, evidence.type);

    cout << "Enter Source: ";
    getline(is, evidence.source);

    cout << "Enter Status: ";
    getline(is, evidence.status);

    cout << "Enter Priority: ";
    is >> evidence.priority;
    is.ignore();

    cout << "Enter Remarks: ";
    getline(is, evidence.remarks);

    cout << "Enter the number of officer IDs you want to add:" << endl;
    int numIDs;
    is >> numIDs;
    is.ignore();

    cout << "Enter officer IDs:" << endl;
    string id;
    for (int i = 0; i < numIDs; ++i) {
        cout << "> ";
        getline(is, id);
        evidence.officerIDs.push_back(id);
    }
    return is;
}

void Evidence::editEvidenceStatus(const string &key, const string &update, const string &id) {
    string caseFileName = "Casefile " + associatedCaseID + ".json";
    json j;
    ifstream file(caseFileName);
    file >> j;
    file.close();
    if (j.contains("Evidences")) {
        for (auto &evidence: j["Evidences"]) {
            if (evidence.contains("ID") && evidence["ID"] == this->id) {
                if (key == "Description") {
                    evidence[key] = evidence[key].get<string>() + " " + update;
                    if (evidence.contains("Experts assigned")) {
                        for (auto &expert: evidence["Experts assigned"]) {
                            if (expert.contains("Expert ID") && expert["Expert ID"] == id) {
                                if (expert.contains("Additions Made")) {
                                    if (expert["Additions Made"] != "N/A") {
                                        expert["Additions Made"] =
                                                expert["Additions Made"].get<string>() + " " + update;
                                    } else {
                                        expert["Additions Made"] = update;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    evidence[key] = update;
                }
                ofstream outFile(caseFileName);
                outFile << setw(4) << j << endl;
                outFile.close();
                cout << "Status of evidence with ID evidence.cpp" << id << " updated to " << update << "." << endl;
                return;
            }
        }
    } else {
        cout << "Evidences array not found in the JSON data." << endl;
    }
}

void Evidence::add2File(ForensicExpert *ptr) {
    string caseFileName = "Casefile " + associatedCaseID + ".json";
    json j;
    ifstream file(caseFileName);
    file >> j;
    file.close();
    if (j.contains("Evidences")) {
        for (auto &evidence: j["Evidences"]) {
            if (evidence.contains("ID") && evidence["ID"] == id) {
                if (!evidence.contains("Experts assigned")) {
                    evidence["Experts assigned"] = json::array();
                }
                json newExpert{
                        {"Expert ID",      ptr->getId()},
                        {"Additions Made", "N/A"}
                };
                evidence["Experts assigned"].push_back(newExpert);
            }
        }
        ofstream file2(caseFileName);
        file2 << setw(4) << j << endl;
        file2.close();
        experts.push_back(ptr);
    } else {
        cerr << "Evidences array not found in the JSON data." << endl;
    }
}


