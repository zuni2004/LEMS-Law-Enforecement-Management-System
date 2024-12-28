//
// Created by HP on 4/5/2024.
//
#ifndef PROJECT_OOP_HR_H
#define PROJECT_OOP_HR_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

#include "HeadConstable.h"
#include "IP.h"
#include "ASI.h"
#include "SI.h"
#include "CorrectionalOfficer.h"
#include "AdministrativeStaff.h"
#include "Forsenic Expert.h"
#include "User.h"

class HR {
private:
    vector<officer<string> *> officers;
    vector<User *> users;
    static HR *ptr;
    int HC;
    int C;
    int IP;
    int ASI;
    int SI;
    int CO;
    int DNA;
    int TOXIC;
    int ANTHRO;
    int DOC;
    int PATHO;
    int DIGITAL;
    int AS;
    int date;
    int month;
    int year;
    int pass;
    int SHO1;

    HR() {
        json j;
        ifstream file("citizenCount.json");
        file >> j;
        file.close();
        this->C = j["Constable Count"];
        this->HC = j["Head Constable Count"];
        this->IP = j["IP Count"];
        this->ASI = j["ASI Count"];
        this->SI = j["SI Count"];
        this->CO = j["Correctional Officer"];
        this->AS = j["AS Count"];
        this->pass = j["Password Cnt"];
        this->DNA = j["DNA analyst"];
        this->TOXIC = j["Toxicologist"];
        this->ANTHRO = j["Anthropologist"];
        this->DOC = j["Document Examiner"];
        this->PATHO = j["Pathologist"];
        this->DIGITAL = j["Digital Analyst"];
        this->SHO1 = j["SHO Count"];
    }

public:
    void editRank(officer<string> *ptr, int &n);

    void FireStaff(officer<string> *ptr);

    void FireStaff(User *ptr);

    vector<ForensicExpert *> getPtr();

    void addStaff(const string &name, const string &CNIC, bool SHO);

    void addStaff(const string &name, const string &cnic, const int &choice);

    void addStaff();

//    ForsenicExpert* getPtr();
    vector<officer<string> *> getAllOfficers();

    void updateFile2();

    static HR *getInstance() {
        if (ptr == nullptr) {
            ptr = new HR;
        }
        return ptr;
    }

    void addUser();

    json toOFFICERJSON(officer<string> &officers) const {
        json j;
        j["Info"] = {
                {"Officer ID",       officers.getOfficerID()},
                {"Status",           "Hired"},
                {"Name",             officers.getName()},
                {"Badge Number",     officers.getBadgeNumber()},
                {"Work Years",       officers.getWorkYears()},
                {"Availability",     officers.getAvailable()},
                {"Rank",             officers.getRank()},
                {"Date Of Hiring",   date},
                {"Month",            month},
                {"Year",             year},
                {"Salary per Month", Budget::allocatingSalaries(officers.getRank())}
        };
        return j;
    }

    json toALLOFFICERJSON(officer<string> &officers) const {
        json j;
        j["Officer ID"] = officers.getOfficerID();
        j["Status"] = "Hired";
        j["Name"] = officers.getName();
        j["Badge Number"] = officers.getBadgeNumber();
        j["Work Years"] = officers.getWorkYears();
        j["Availability"] = officers.getAvailable();
        j["Rank"] = officers.getRank();
        return j;
    }

    void removeOfficers();

    void Add2File();

    vector<officer<string> *> getOfficers();

    void displayAddedOfficers();

    void addOFFICER(const string &name);

    officer<string> *getOfficerByID(const string &officerID);

};

#endif //PROJECT_OOP_HR_H
