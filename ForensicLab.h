#ifndef FORENSICLAB_H
#define FORENSICLAB_H

#include <iostream>
#include <string>
#include "Forsenic Expert.h"
#include "Evidence.h"
#include <vector>

class ForensicLab {
private:
    string location;
    string equipment;
    int expertCount;
    int capacity;
    vector<ForensicExpert *> forensicExperts;
    vector<Evidence *> evidence;

public:
    ForensicLab() {}

    ForensicLab(string location, string equipment, int cap, int count,
                const vector<ForensicExpert *> &forensicExpert)
            : location(location), equipment(equipment), capacity(cap), expertCount(count),
              forensicExperts(forensicExpert) {}

    string analyzeEvidence() {
        for (ForensicExpert *expert: forensicExperts) {
            if (expert->getTaskCapacity() > 0) {
                cout << "Evidence analyzed by " << expert->getName() << " at " << location << endl;
                expert->setTaskCapacity(expert->getTaskCapacity() - 1);
                return "Evidence analysis successful.";
            }
        }
        return "No available forensic experts to analyze evidence.";
    }

    const vector<ForensicExpert *> &getForensicExpert() const {
        return forensicExperts;
    }

    const vector<Evidence *> &getEvidence() const {
        return evidence;
    }

    void setEvidence(const vector<Evidence *> &evidence) {
        this->evidence = evidence;
    }

    int getCapacity() const {
        return capacity;
    }

    void setCapacity(int capacity) {
        ForensicLab::capacity = capacity;
    }

    void setForensicExpert(const vector<ForensicExpert *> &forensicExpert) {
        this->forensicExperts = forensicExpert;
    }

    const string &getLocation() const {
        return location;
    }

    void setLocation(const string &location) {
        ForensicLab::location = location;
    }

    const string &getEquipment() const {
        return equipment;
    }

    void setEquipment(const string &equipment) {
        ForensicLab::equipment = equipment;
    }

    const int &getExpertCount() const {
        return expertCount;
    }

    void setExpertCount(const int &expertCount) {
        ForensicLab::expertCount = expertCount;
    }

    void display() const {
        cout << "Location: " << location << endl;
        cout << "Equipment: " << equipment << endl;
        cout << "Expert Count: " << expertCount << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Forensic Experts:" << endl;
        for (const auto &expert: forensicExperts) {
            cout << "Id: " << expert->getId() << endl;
        }
    }

    friend ostream &operator<<(ostream &os, const ForensicLab &lab);

    void getExpert(ForensicExpert *expert){
        forensicExperts.push_back(expert);
        expert->getId();
        json LabData;
        json data;
        ifstream file("ForensicLab.json");
        if (file.is_open()) {
            file >> LabData;
            file.close();
        }
        for(auto &lab: LabData){
            lab["Experts"]=data;
            data.push_back(expert->getId());
            LabData["Experts"]=data;
        }
        ofstream outputfile("ForensicLab.json", ios::out);
        outputfile << setw(4) << LabData << endl;
        outputfile.close();
    }
};

#endif // FORENSICLAB_H
