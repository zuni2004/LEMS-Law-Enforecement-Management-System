//
// Created by HP on 4/27/2024.
//
#include "SHO.h"
#include "HR.h"
#include "Investigation.h"
#include "Non-member Functs.h"

void SHO::getOfficers() {
    officers = HR::getInstance()->getAllOfficers();
}

vector<Patrolling *> SHO::getpatrollings() {
    int CC = getCount("Patrolling complain Count");
    for (int i = 1; i <= CC; i++) {
        stringstream ss;
        ss << i;
        string count = ss.str();
        string caseId = "Complain Patrolling" + count;
        Patrolling *ptr = new Patrolling(caseId, "Complain Patrolling");
        if (PointerExists(ptr, patrollings)) {
            delete ptr;
        } else {
            patrollings.push_back(ptr);
        }
    }
    int id = getCount("Routine Patrolling Count");
    for (int i = 1; i <= id; i++) {
        stringstream ss;
        ss << i;
        string count = ss.str();
        string caseId = "Routine patrolling" + count;
        Patrolling *ptr = new Patrolling(caseId, "Routine Patrolling");
        if (PointerExists(ptr, patrollings)) {
            delete ptr;
        } else {
            patrollings.push_back(ptr);
        }
    }
    return patrollings;
}

vector<Patrolling *> SHO::getPatrollingWithUnassignedVehicles() {
    vector<Patrolling *> patrollingWithUnassignedVehicles;
    int complainCount = getCount("Patrolling complain Count");
    for (int i = 1; i <= complainCount; i++) {
        stringstream ss;
        ss << i;
        string count = ss.str();
        string caseId = "Complain Patrolling" + count;
        Patrolling *ptr = new Patrolling(caseId, "Complain Patrolling");
        if (!PointerExists(ptr, patrollings)) {
            patrollings.push_back(ptr);
            if (!ptr->getVehicleStatus()) {
                patrollingWithUnassignedVehicles.push_back(ptr);
            }
        } else {
            delete ptr;
        }
    }
    int routineCount = getCount("Routine Patrolling Count");
    for (int i = 1; i <= routineCount; i++) {
        stringstream ss;
        ss << i;
        string count = ss.str();
        string caseId = "Routine patrolling" + count;
        Patrolling *ptr = new Patrolling(caseId, "Routine Patrolling");
        if (!PointerExists(ptr, patrollings)) {
            patrollings.push_back(ptr);
            if (!ptr->getVehicleStatus()) {
                patrollingWithUnassignedVehicles.push_back(ptr);
            }
        } else {
            delete ptr;
        }
    }
    return patrollingWithUnassignedVehicles;
}

vector<Investigation *> SHO::getinvestigations() {
    int ECF = getCount("Case File Count Em");
    for (int i = 1; i <= ECF; i++) {
        stringstream ss;
        ss << i;
        string count = ss.str();
        string caseId = "em" + count;
        Investigation *ptr = new Investigation(caseId);
        if (PointerExists(ptr, investigations)) {
            delete ptr;
        } else {
            investigations.push_back(ptr);
        }
    }
    int NCF = getCount("Case File Count non");
    for (int i = 1; i <= NCF; i++) {
        stringstream ss;
        ss << i;
        string count = ss.str();
        string caseId = "n" + count;
        Investigation *ptr = new Investigation(caseId);
        if (PointerExists(ptr, investigations)) {
            delete ptr;
        } else {
            investigations.push_back(ptr);
        }
    }
    return investigations;
}

vector<Investigation *> SHO::getInvestigationsWithUnassignedEquipmentAndVehicles() {
    vector<Investigation *> investigationsWithUnassigned;
    int ECF = getCount("Case File Count Em");
    for (int i = 1; i <= ECF; i++) {
        stringstream ss;
        ss << i;
        string count = ss.str();
        string caseId = "em" + count;
        Investigation *ptr = new Investigation(caseId);
        if (!PointerExists(ptr, investigations)) {
            investigations.push_back(ptr);
            if (!ptr->getEquipment() || !ptr->getVehicles()) {
                investigationsWithUnassigned.push_back(ptr);
            }
        } else {
            delete ptr;
        }
    }
    int NCF = getCount("Case File Count non");
    for (int i = 1; i <= NCF; i++) {
        stringstream ss;
        ss << i;
        string count = ss.str();
        string caseId = "n" + count;
        Investigation *ptr = new Investigation(caseId);
        if (!PointerExists(ptr, investigations)) {
            investigations.push_back(ptr);
            if (!ptr->getEquipment() || !ptr->getVehicles()) {
                investigationsWithUnassigned.push_back(ptr);
            }
        } else {
            delete ptr;
        }
    }
    return investigationsWithUnassigned;
}
