//
// Created by HP on 4/6/2024.
//
#ifndef PROJECT_OOP_CITIZEN_H
#define PROJECT_OOP_CITIZEN_H
using namespace std;

#include <fstream>
#include "json.hpp"
#include <iostream>
#include <vector>
#include "Complain.h"

using json = nlohmann::json;

class Citizen {
private:
    string citizenName;
    long int contactNo;
    string address;
    string CNIC;
    string email;
    int complainCnt;
    static vector<Complain *> validComplaints;
public:
    int citizenCount;
    static int CitizenCount;
    static int TotalCount;

    Citizen(const string &CNIC = "") {
        this->CNIC = CNIC;
        complainCnt = 0;
    }

    void fileComplain(bool exist, int count);

    string viewComplainStatus(int complainCount, string fileName) const;

    static int getComplainCount();

    static vector<Complain *> getPtr();

    void SetcitizenCnt() {
        CitizenCount++;
    }

    int getCitizenCnt() {
        return CitizenCount;
    }

    static void CalculateTotalCnt();
};

bool checkCNIC(const string &enteredCNIC, const string &fileName);

#endif //PROJECT_OOP_CITIZEN_H
