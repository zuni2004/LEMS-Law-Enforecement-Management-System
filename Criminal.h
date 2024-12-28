//
// Created by InnoSTARK on 4/27/2024.
//

#ifndef COMPILED_FOLDER_CRIMINAL_H
#define COMPILED_FOLDER_CRIMINAL_H

#include <iostream>
#include <string>

using namespace std;

#include "Crime.h"
#include "ViolentCrimes.h"
#include "WhiteCollarCrimes.h"
#include "CyberCrimes.h"
#include "Cells.h"
#include "Bail.h"

class BailInformation;

class Criminal {
    int criminalID;
    string name;
    string address;
    string phoneNumber;
    string job;
    string description;
    string caseId;
    string criminalHistory;
    string gender;
    Crime *crime; //aggregation
    Cells *cell;
    BailInformation bail; //association
public:
    Criminal()
            : criminalID(0), name(""), address(""), phoneNumber(""), job(""), description(""),
              caseId(""), criminalHistory(""), gender(""), crime(nullptr), cell(nullptr), bail() {}

    Criminal(int id, const string n, const string addr, const string phone, const string j,
             const string desc,
             const string caseId, const string history, const string gen, Crime *crime, Cells *cell,
             const BailInformation &bailInfo)
            : criminalID(id), name(n), address(addr), phoneNumber(phone), job(j), description(desc),
              caseId(caseId), criminalHistory(history), gender(gen), crime(crime), cell(cell), bail(bailInfo) {}

    ~Criminal() {}

    int CalculatingId() {
        ifstream file("Criminal.json", ios::in);
        if (!file.is_open()) {
            cout << "Cannot open file\n";
            return 101000;
        }

        json data;
        file >> data;

        int lastId = -1;
        for (const auto &finding: data) {
            lastId = finding["CriminalId"];
        }

        file.close();
        return lastId;
    }

    void viewListOfCriminal() {
        json j;
        ifstream file("Criminal.json");
        if (file.is_open()) {
            file >> j;
            cout << setw(4) << j << endl;
            file.close();
        } else
            cout << "Cannot display list of criminals. " << endl;
    }

    void EnterNewCriminal() {
        criminalID = 101000;
        float amount;
        int cellId;
        string conditions, status, dateIssued, datePaid, court;
        cout << "Entering new criminal\n";
        cout << "Enter name\n";
        cin.ignore();
        getline(cin, name);
        cout << "Enter criminal address\n";
        getline(cin, address);
        cout << "Enter criminal phone number\n";
        cin >> phoneNumber;
        cout << "Enter criminal job\n";
        cin.ignore();
        getline(cin, job);
        cout << "Enter criminal description\n";
        getline(cin, description);
        cout << "Enter criminal history\n";
        getline(cin, criminalHistory);
        cout << "Enter criminal gender\n";
        getline(cin, gender);
//        cout << "Enter cell id in which criminal is staying.";
//        cin >> cellId;
//        cell->setCellId(cellId);
        int choice;
        int Id;
        cout << "Type of crime committed\n";
        cout << "Press 1 for Violent Crime\nPress 2 for White Collar Crime\nPress 3 for Cyber Crime\n";
        cin >> choice;

        if (choice == 1) {
            crime = new VoilentCrime;
            crime->recordNewCrime();
        } else if (choice == 2) {
            crime = new WhiteCollarCrime;
            crime->recordNewCrime();
        } else if (choice == 3) {
            crime = new CyberCrime;
            crime->recordNewCrime();
        } else {
            cout << "Enter a valid number";
            return;
        }
        Id = crime->getCrimeId();

        ifstream file("Criminal.json");
        json criminalRecord;
        if (file.is_open()) {
            file >> criminalRecord;
            criminalID = CalculatingId();
            ++criminalID;
            file.close();
        }
        json recordCriminal{
                {"CriminalId",       criminalID},
                {"Criminal name",    name},
                {"Description",      description},
                {"Address",          address},
                //{"Cell Id", cell->getId()},
                {"Phone Number",     phoneNumber},
                {"Criminal History", criminalHistory},
                {"Gender",           gender},
                {"Job",              job},
                {"Crime ID num",     Id},
        };
        criminalRecord.push_back(recordCriminal);

        ofstream outFile("Criminal.json", ios::out);
        if (outFile.is_open()) {
            outFile << setw(4) << criminalRecord << endl;
            cout << "Criminal ID number is " << criminalID << endl;
        } else {
            cout << "Cannot write to file" << endl;
            return;
        }
    }

    void SearchByCriminalID() {
        bool found = false;
        int ID;
        json j;
        ifstream file("Criminal.json");
        if (!file.is_open()) {
            cout << "Cannot open file\n";
            return;
        } else {
            file >> j;
            cout << "Enter Criminal Id: ";
            cin >> ID;
            for (auto &temp: j) {
                int tempID = temp["CriminalId"];
                if (tempID == ID) {
                    cout << "Name: " << temp["Criminal name"] << endl
                         << "Address: " << temp["Address"] << endl
                         << "Phone Number: " << temp["Phone Number"] << endl
                         << "Job: " << temp["Job"] << endl
                         << "Description: " << temp["Description"] << endl
                         << "Criminal History: " << temp["Criminal History"] << endl
                         << "Crime ID num: " << temp["Crime ID num"] << endl;
                    found = true;
                    break;
                }
            }
            if (!found) { cout << "Id not found"; }
        }
    }

    bool criminalExist() {
        bool found = false;
        int ID;
        json j;
        ifstream file("Criminal.json");
        if (!file.is_open()) {
            cout << "Cannot open file\n";
            return false;
        } else {
            file >> j;
            cout << "Enter Criminal Id: ";
            cin >> ID;
            for (auto &temp: j) {
                int tempID = temp["CriminalId"];
                if (tempID == ID) {
                    found = true;
                    break;
                    return true;
                }
            }
            if (!found)
                cout << "Id not found\n";
            return false;
        }
    }

    void SearchForCriminalInCell() {
        criminalExist();

    }

    void SearchByCrimeID() {
        bool found = false;
        int ID;
        json j;
        ifstream file("Criminal.json");
        if (!file.is_open()) {
            cout << "Cannot open file\n";
            return;
        } else {
            file >> j;
            cout << "Enter Crime Id: ";
            cin >> ID;
            for (auto &temp: j) {
                int tempID = temp["Crime ID num"];
                if (tempID == ID) { // Compare as integers
                    cout << "Name: " << temp["Criminal name"] << endl
                         << "Address: " << temp["Address"] << endl
                         << "Phone Number: " << temp["Phone Number"] << endl
                         << "Job: " << temp["Job"] << endl
                         << "Description: " << temp["Description"] << endl
                         << "Criminal History: " << temp["Criminal History"] << endl
                         << "Crime ID num: " << temp["Crime ID num"] << endl;
                    found = true;
                    break;
                }
            }
            if (!found) { cout << "Id not found"; }
        }
    }

    void AddBailInfo() {
        double amount;
        string court, dateIssued, datePaid, status, conditions;

        cout << "Entering new bail\n";
        cout << "Enter bail amount\n";
        cin >> amount;
        cin.ignore();
        cout << "Enter bail condition\n";
        getline(cin, conditions);
        cout << "Enter bail status\n";
        getline(cin, status);
        cout << "Enter bail date issued \n";
        getline(cin, dateIssued);
        cout << "Enter bail date paid\n";
        getline(cin, datePaid);
        cout << "Enter court information\n";
        getline(cin, court);
        cout << "Enter Criminal Id: \n";
        cin >> criminalID;

        ifstream file("Criminal.json", ios::in);
        if (!file.is_open()) {
            cout << "Error: Unable to open Criminal.json" << endl;
            return;
        }

        json find;
        file >> find;
        file.close();

        for (auto &finding: find) {
            if (finding["CriminalId"] == criminalID) {
                BailInformation newBail(amount, court, dateIssued, datePaid, status, conditions);
                json BailFile;

//                ifstream inFile("Bail.json");
//                if (!inFile.is_open()) {
//                    cout << "Error: Unable to open Bail.json" << endl;
//                } else {}
//                inFile >> BailFile;
//                inFile.close();

                json newBailJson = {
                        {"Criminal Id", criminalID},
                        {"Amount",      newBail.getAmount()},
                        {"Court",       newBail.getCourt()},
                        {"Date Issued", newBail.getDateIssued()},
                        {"Date Paid",   newBail.getDatePaid()},
                        {"Status",      newBail.getStatus()},
                        {"Conditions",  newBail.getConditions()}
                };

                BailFile.push_back(newBailJson);

                ofstream outFile("Bail.json", ios::out);
                if (!outFile.is_open()) {
                    cout << "Error: Unable to write to Bail.json" << endl;
                    return;
                }

                outFile << setw(4) << BailFile << endl;
                outFile.close();
                return;
            }
        }
        cout << "Error: Criminal ID not found" << endl;
    }

    bool operator==(const Criminal &rhs) const;

    bool operator!=(const Criminal &rhs) const;

    friend ostream &operator<<(ostream &os, const Criminal &criminal);

    int getCriminalId() const;

    void setCriminalId(int criminalId);

    const string &getName() const;

    void setName(const string &name);

    const string &getDescription() const;

    void setDescription(const string &description);

    const string &getCaseId() const;

    void setCaseId(const string &caseId);

    Crime *getCrime() const;

    void setCrime(Crime *crime);

    Cells *getCell() const;

    void setCell(Cells *cell);

    void setCriminalId1(int criminalId);

};

#endif //COMPILED_FOLDER_CRIMINAL_H


