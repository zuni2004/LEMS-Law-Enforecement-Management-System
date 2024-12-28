//
// Created by HP on 4/6/2024.
#ifndef PROJECT_OOP_OFFICER_H
#define PROJECT_OOP_OFFICER_H
using namespace std;

#include <iostream>
#include <vector>
#include "json.hpp"
#include "Patrolling.h"

using json = nlohmann::json;

#include <fstream>
#include <sstream>

class Investigation;

template<typename T>
class officer {
private:
    T rank;
    string officerID;
    string name;
    int badgeNumber;
    bool available;
    int workYears;
    string currentTask;
    vector<Investigation *> investigations;
    vector<Patrolling *> patrollings;
    int investigationCnt;
    int patrollingCnt;
public:
    string getCurrentTask() const {
        return currentTask;
    }
    int getPatrollingsize(){
        return patrollings.size();
    }
    int getInvestigationsSize(){
        return investigations.size();
    }

    void addInvestigation(Investigation *ptr);

    void addPatrolling(Patrolling *patrolling);

    void getInvestigation(json &object);

    void readFromFile();

    void getPatrolling(json &object);

    void getTeam();

    officer(const string &id) {
        officerID = id;
        readFromFile();
    }

    officer() {

    }

    void setIDofficer(const string &id, string name, int badgeNumber) {
        rank = "SHO";
        officerID = id;
        this->name = name;
        this->badgeNumber = badgeNumber;
    }

    officer(T rank, string officerID, string name, int badgeNumber) {
        this->rank = rank;
        this->officerID = officerID;
        this->name = name;
        this->badgeNumber = badgeNumber;
        workYears = 0;
        available = true;
        investigationCnt = 0;
        patrollingCnt = 0;
    }

    bool operator==(const officer<T> &other) const {
        return rank == other.rank &&
               officerID == other.officerID &&
               name == other.name &&
               badgeNumber == other.badgeNumber &&
               available == other.available &&
               workYears == other.workYears;
    }

    ~officer() {}

    virtual void displayInfo() = 0;

    bool getAvailable() const {
        return available;
    }

    void displayInvestigations() ;

    void displayPatrollings() ;

    T getRank() const {
        return rank;
    }

    string getOfficerID() const {
        return officerID;
    }

    string getName() const {
        return name;
    }

    int getBadgeNumber() const {
        return badgeNumber;
    }

    int getWorkYears() const {
        return workYears;
    }

    void setAvailable(bool available) {
        this->available = available;
    }

    void setRank(T &rank) {
        this->rank = rank;
    }

    void setWorkYears(int workYears) {
        this->workYears = workYears;
    }

    void openFile() {

    }
};

template<typename T>
void editFile(string fileName, const string &key1, const string &key2, const T &update) {
    cout << "file name is" << fileName << endl;
    json j;
    ifstream file(fileName);
    file >> j;
    file.close();
    cout << "key 1 is " << key1;
    cout << "key 2 is " << key2;
    j[key1][key2] = update;
    ofstream file2(fileName);
    file2 << setw(4) << j << endl;
    file2.close();
    cout << "updated" << endl;
}

#endif //PROJECT_OOP_OFFICER_H
