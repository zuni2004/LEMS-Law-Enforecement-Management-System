//
// Created by HP on 4/8/2024.
//
#ifndef PROJECT_OOP_FORSENIC_EXPERT_H
#define PROJECT_OOP_FORSENIC_EXPERT_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

#include "User.h"

class Evidence;

class ForensicExpert : public User {
private:
    string id;
    string name;
    string CNIC;
    int taskCapacity;
    int evidenceCnt;
    string specialization;
    vector<Evidence *> ptr;
public:
    bool operator==(const ForensicExpert &other) const {
        return (id == other.id &&
                name == other.name &&
                CNIC == other.CNIC &&
                taskCapacity == other.taskCapacity &&
                evidenceCnt == other.evidenceCnt &&
                specialization == other.specialization);
    }

    bool capacity(json &j);

    void addEvidence(Evidence *ptr);

    void editEvidence();

    ForensicExpert(const string &id = "", const string &name = "", const string &CNIC = "",
                   const string &specialization = "", const int &taskCapacity = 0, const int &evidenceCnt = 0)
            : id(id), name(name), CNIC(CNIC),
              specialization(specialization), taskCapacity(taskCapacity), evidenceCnt(evidenceCnt), User(id) {

    }

    int getEvidenceCnt() {
        return evidenceCnt;
    }

    void displayAllEvidences();

    void completeExamination();

    void LoadEvidences();

    string getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    string getCNIC() const {
        return CNIC;
    }

    int getTaskCapacity() override {
        return taskCapacity;
    }

    void setTaskCapacity(int newTaskCapacity) {
        taskCapacity = newTaskCapacity;
    }

    string getSpecialization() const {
        return specialization;
    }

    void displayDetails() const {
        cout << "Forensic Expert Details:" << endl;
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "CNIC: " << CNIC << endl;
        cout << "Specialization: " << specialization << endl;
        cout << "Task Capacity: " << taskCapacity << endl;
    }
};

#endif //PROJECT_OOP_FORSENIC_EXPERT_H
