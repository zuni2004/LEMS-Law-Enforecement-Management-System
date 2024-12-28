//
// Created by InnoSTARK on 4/27/2024.
//
#include "PoliceStation.h"
#include "Budget.h"

PoliceStation *PoliceStation::instance = nullptr;

Complain *PoliceStation::getComplain() const {
    return complain;
}

void PoliceStation::setComplain(Complain *complain) {
    PoliceStation::complain = complain;
}


void PoliceStation::setInstance(PoliceStation *instance) {
    PoliceStation::instance = instance;
}

int PoliceStation::getStationId() const {
    return stationId;
}

Crime *PoliceStation::getCrime() const {
    return crime;
}

const vector<Vehicle<int, string, string, int, string, string, string, string, string, string, string, string, string, string> *> &
PoliceStation::getVehicles() const {
    return vehicles;
}

void PoliceStation::setVehicles(
        const vector<Vehicle<int, string, string, int, string, string, string, string, string, string, string, string, string, string> *> &vehicles) {
    PoliceStation::vehicles = vehicles;
}

void PoliceStation::setEquipment1(const vector<Equipment<int, string, int, string, double, bool> *> &equipment) {
    PoliceStation::equipment = equipment;
}

void PoliceStation::setCrime(Crime *crime) {
    PoliceStation::crime = crime;
}

void PoliceStation::setStationId(int stationId) {
    PoliceStation::stationId = stationId;
}

const string &PoliceStation::getName() const {
    return name;
}

bool PoliceStation::operator==(const PoliceStation &rhs) const {
    return stationId == rhs.stationId &&
           name == rhs.name &&
           location == rhs.location &&
           contactInfo == rhs.contactInfo &&
           complain == rhs.complain &&
           criminal == rhs.criminal &&
           crime == rhs.crime &&
           Officer == rhs.Officer &&
           correctionalOfficer == rhs.correctionalOfficer &&
           equipment == rhs.equipment &&
           chiefOfficerInCharge == rhs.chiefOfficerInCharge &&
           forensicLab == rhs.forensicLab &&
           vehicles == rhs.vehicles;
}

bool PoliceStation::operator!=(const PoliceStation &rhs) const {
    return !(rhs == *this);
}
