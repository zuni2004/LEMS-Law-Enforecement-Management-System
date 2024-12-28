//
// Created by InnoSTARK on 4/6/2024.
//

#ifndef INC_2024_SPRING_SE102TA_PROJECT_SE102A_A_USER_H
#define INC_2024_SPRING_SE102TA_PROJECT_SE102A_A_USER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class User {
protected:
    string id;
    string cnic;
    string type;
    string name;
public:
    User() : id(""), cnic(""), type(""), name("") {

    }

    virtual int getTaskCapacity() {
        return 0;
    }

    User(const string &id) {
        this->id = id;
    }

    void setType(const string &type) {
        this->type = type;
    }

    void setName(const string &name) {
        this->name = name;
    }

    void setCNIC(const string &cnic) {
        this->cnic = cnic;
    }

    string getCNIC() {
        return cnic;
    }

    string getID() {
        return id;
    }

    string getName() {
        return name;
    }

    string getType() {
        return type;
    }

    void setID(const string &id) {
        this->id = id;
    }

    string login(const string &officerID, const string &enteredPassword, const string &enteredUsername) const;

    void changePassword(const string &officerID, const string &username);

    string determinePortal(const string &officerID) const;
};

#endif //INC_2024_SPRING_SE102TA_PROJECT_SE102A_A_USER_H
