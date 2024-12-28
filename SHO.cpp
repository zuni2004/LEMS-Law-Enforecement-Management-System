//
// Created by HP on 4/7/2024
#include "SHO.h"
#include "Non-member Functs.h"

void SHO::displayAll() {
    for (int i = 0; i < officers.size(); i++) {
        officers[i]->displayInfo();
    }
}

Patrolling *write2Patrolling(Complain *ptr, const int &n, const vector<string> &assignedID, const string &area,
                             vector<officer<string> *> officers, const int &d, const int &m, const int &y,
                             const string &type) {
    json j;
    int id = getCount("Patrolling complain Count");
    id++;
    updateCount("Patrolling complain Count", id);
    stringstream ss;
    ss << id;
    string count = ss.str();
    string caseId = "Complain Patrolling" + count;
    Patrolling *invest = new Patrolling(caseId, type);
    json patrollingData = {
            {"Type",                       type},
            {"Date",                       d},
            {"Month",                      m},
            {"Year",                       y},
            {"Case ID",                    caseId},
            {"Complain file",              ptr->citizenFile},
            {"Complain ID",                ptr->id},
            {"Status",                     "Dispatched"},
            {"Area",                       area},
            {"Count of assigned officers", n},
            {"Assigned officer IDs",       assignedID}
    };
    ifstream inputFile("Complain Patrolling.json");
    json existingPatrollings;
    if (inputFile.is_open()) {
        inputFile >> existingPatrollings;
        inputFile.close();
    } else {
        existingPatrollings = {
                {"Patrollings", json::array()}
        };
    }
    existingPatrollings["Patrollings"].push_back(patrollingData);
    ofstream outputFile("Complain Patrolling.json");
    outputFile << setw(4) << existingPatrollings << endl;
    outputFile.close();
    for (int i = 0; i < officers.size(); i++) {
        officers[i]->addPatrolling(invest);
    }
    return invest;
}

Patrolling *
write2Patrolling(const int &n, const vector<string> &assignedID, const string &area, vector<officer<string> *>
officers, const int &d, const int &m, const int &y, const string &type) {
    json j;
    int id = getCount("Routine Patrolling Count");
    id++;
    updateCount("Routine Patrolling Count", id);
    stringstream ss;
    ss << id;
    string count = ss.str();
    string caseId = "Routine patrolling" + count;
    ifstream inputFile("Routine Patrolling.json");
    json existingPatrollings;
    if (inputFile.is_open()) {
        inputFile >> existingPatrollings;
        inputFile.close();
    } else {
        existingPatrollings = {
                {"Patrollings", json::array()}
        };
    }
    json newPatrollingData = {
            {"Type",                       type},
            {"Date",                       d},
            {"Month",                      m},
            {"Year",                       y},
            {"Area",                       area},
            {"Case ID",                    caseId},
            {"Status",                     "Dispatched"},
            {"Count of assigned officers", n},
            {"Assigned officer IDs",       assignedID}
    };
    existingPatrollings["Patrollings"].push_back(newPatrollingData);
    ofstream outputFile("Routine Patrolling.json");
    outputFile << setw(4) << existingPatrollings << endl;
    outputFile.close();
    Patrolling *invest = new Patrolling(caseId, type);
    for (int i = 0; i < officers.size(); i++) {
        officers[i]->addPatrolling(invest);
    }
    return invest;
}

void SHO::assignPatrolling(Complain *ptr) {
    int n;
    vector<string> assignedID;
    vector<officer<string> *> assigned;
    Patrolling *ptr2;
    int countOfassigned;
    cout << "Choose" << endl;
    cout << "1. Singular patrolling" << endl;
    cout << "2. Team patrolling" << endl;
    cin >> n;
    if (n == 1) {
        int a;
        cout << "Choose rank of officer" << endl;
        cout << "1.Head constable" << endl;
        cout << "2.Constable" << endl;
        cout << "3.ASI" << endl;
        cout << "4.SI" << endl;
        cout << "5.IP" << endl;
        cin >> a;
        string rank;
        int cnt = 0;
        if (a == 1) {
            rank = "Head Constable";
        } else if (a == 2) {
            rank = "Constable";
        } else if (a == 3) {
            rank = "ASI";
        } else if (a == 4) {
            rank = "SI";
        } else if (a == 5) {
            rank = "IP";
        }
        for (int i = 0; i < officers.size(); ++i) {
            if (officers[i]->getAvailable()) {
                if (officers[i]->getRank() == rank && cnt < 1) {
                    assigned.push_back(officers[i]);
                    cnt++;
                    assignedID.push_back(officers[i]->getOfficerID());
                    cout << "Officer chosen: " << officers[i]->getOfficerID() << endl;
                }
            }
        }
        if (cnt < 1) {
            cout << "No available officers" << endl;
            return;
        }
        countOfassigned = 1;
    } else if (n == 2) {
        int a;
        cout << "Choose" << endl;
        cout << "1.High risk patrolling" << endl;
        cout << "2.Low risk patrolling" << endl;
        cin >> a;
        string leadingOfficerRank;
        int LO;
        if (a == 1) {
            leadingOfficerRank = "IP";
            int si, asi;
            cout << "Enter requirement of SI officers: ";
            cin >> si;
            cout << "Enter requirement of ASI officers: ";
            cin >> asi;
            int ASI = 0;
            int SI = 0;
            for (int i = 0; i < officers.size(); ++i) {
                if (officers[i]->getAvailable()) {
                    if (officers[i]->getRank() == "ASI" && ASI <= asi) {
                        assigned.push_back(officers[i]);
                        ASI++;
                        assignedID.push_back(officers[i]->getOfficerID());
                    }
                    if (officers[i]->getRank() == "SI" && SI <= si) {
                        assigned.push_back(officers[i]);
                        SI++;
                        assignedID.push_back(officers[i]->getOfficerID());
                    }
                }
            }
            if (SI < si || ASI < asi) {
                cout << "Not enough available officers" << endl;
                return;
            }
            countOfassigned = si + asi + 1;
        } else if (a == 2) {
            leadingOfficerRank = "Head Constable";
            int requirement;
            cout << "Enter requirement of team excluding the leader" << endl;
            cin >> requirement;
            int c = 0;
            for (int i = 0; i < officers.size(); ++i) {
                if (officers[i]->getAvailable()) {
                    if (officers[i]->getRank() == "Constable" && c <= requirement) {
                        assigned.push_back(officers[i]);
                        c++;
                        assignedID.push_back(officers[i]->getOfficerID());
                    }
                }
            }
            if (c < requirement) {
                cout << "Not enough available officers" << endl;
                return;
            }
            countOfassigned = requirement + 1;
        }
        for (int i = 0; i < officers.size(); ++i) {
            if (officers[i]->getAvailable()) {
                if (officers[i]->getRank() == leadingOfficerRank && LO < 1) {
                    assigned.push_back(officers[i]);
                    LO++;
                    assignedID.push_back(officers[i]->getOfficerID());
                }
            }
        }
        if (LO < 1) {
            cout << "No available officers" << endl;
            return;
        }
    } else {
        cout << "invalid option" << endl;
        return;
    }
    string area;
    cout << "Enter area of investigation: ";
    cin.ignore();
    getline(cin, area);
    int d, m, y;
    cout << "Enter D/M/Y of investigation" << endl;
    cout << "Input date: ";
    cin >> d;
    cout << "Input month: ";
    cin >> m;
    cout << "Input year: ";
    cin >> y;
    if (ptr != nullptr) {
        patrollings.push_back(
                write2Patrolling(ptr, countOfassigned, assignedID, area, assigned, d, m, y, "Complain Patrollings"));

        editComplaintStatus(ptr->id, "Patrolling Dispatched", ptr->citizenFile, "Complaints", "Status",
                            "Complain Count");

    } else {
        patrollings.push_back(
                write2Patrolling(countOfassigned, assignedID, area, assigned, d, m, y, "Routine Patrolling"));
    }
}

void SHO::createInvestigation(Complain *complain, bool emergency) {
    if (emergency) {
        vector<officer<string> *> team;
        string headOfficerId;
        vector<string> assignedID;
        vector<int> assignedEquipments;
        vector<int> assignedVehicles;
        int IP = 0;
        int ASI = 0;
        int SI = 0;
        int si, asi;
        cout << "Enter requirement of SI officers: ";
        cin >> si;
        cout << "Enter requirement of ASI officers: ";
        cin >> asi;
        for (int i = 0; i < officers.size(); ++i) {
            if (officers[i]->getAvailable()) {
                if (officers[i]->getRank() == "IP" && IP < 1) {
                    team.push_back(officers[i]);
                    headOfficerId = officers[i]->getOfficerID();
                    IP++;
                }
                if (officers[i]->getRank() == "ASI" && ASI <= asi) {
                    team.push_back(officers[i]);
                    ASI++;
                    assignedID.push_back(officers[i]->getOfficerID());
                }
                if (officers[i]->getRank() == "SI" && SI <= si) {//3-1=2
                    team.push_back(officers[i]);
                    SI++;
                    assignedID.push_back(officers[i]->getOfficerID());
                }
            }
        }
        if (ASI != asi && SI != si && IP == 0) {
            cout << "Not enough available officers" << endl;
            return;
        } else {
            int id = ::getCount("Case File Count Em");
            stringstream ss;
            id++;
            ::updateCount("Case File Count Em", id);
            ss << id;
            string count = ss.str();
            string caseId = "em" + count;//emergency
            cout << "This is the ID assigned to Case: " << caseId << endl;
            Investigation *invest = new Investigation(caseId);
            investigations.push_back(invest);
            invest->setEquipment(false);
            invest->setVehicle(false);
            ofstream file3("Casefile " + caseId + ".json");
            json j;
            int n = asi + si + 1;
            j["Info"] = {
                    {"Case ID",                    caseId},
                    {"Complain file",              complain->citizenFile},
                    {"Complain ID",                complain->id},
                    {"Status",                     "In progress"},
                    {"Leading officer ID",         headOfficerId},
                    {"Count of assigned officers", n},
                    {"Assigned officer IDs",       assignedID}
            };
            file3 << setw(4) << j << endl;
            file3.close();
            for (int i = 0; i < team.size(); i++) {
                team[i]->addInvestigation(invest);
            }
            cout << "Investigation team created" << endl;
        }
        cout << endl;
        editComplaintStatus(complain->id, "Investigation in progress", complain->citizenFile, "Complaints", "Status",
                            "Complain Count");
    } else {
        int n;
        cout << "Enter requirement of team: ";
        cin >> n;//3
        vector<officer<string> *> team;
        string headOfficerId;
        vector<string> assignedID;
        vector<int> assignedEquipments;
        vector<int> assignedVehicles;
        int HC = 0;
        int C = 0;
        for (int i = 0; i < officers.size(); ++i) {
            if (officers[i]->getAvailable()) {
                if (officers[i]->getRank() == "Head Constable" && HC < 1) {//2
                    team.push_back(officers[i]);
                    headOfficerId = officers[i]->getOfficerID();
                    HC++;
                }
                if (officers[i]->getRank() == "Constable" && C < n - 1) {//3-1=2
                    team.push_back(officers[i]);
                    C++;
                    assignedID.push_back(officers[i]->getOfficerID());
                }
            }
        }
        if (HC + C < n) {
            cout << "Not enough available officers" << endl;
            return;
        }
        int id = ::getCount("Case File Count non");
        stringstream ss;
        id++;
        ::updateCount("Case File Count non", id);
        ss << id;
        string count = ss.str();
        string caseId = "n" + count;//non emergency
        cout << "This is the ID assigned to Case: " << caseId << endl;
        Investigation *invest = new Investigation(caseId);
        investigations.push_back(invest);
        invest->setEquipment(false);
        invest->setVehicle(false);

        cout << "ID of investigation assigned: " << invest->getcaseID() << endl;
        ofstream file3("Casefile " + caseId + ".json");
        json j;
        n--;
        j["Info"] = {
                {"Case ID",                    caseId},
                {"Complain file",              complain->citizenFile},
                {"Complain ID",                complain->id},
                {"Status",                     "In progress"},
                {"Leading officer ID",         headOfficerId},
                {"Count of assigned officers", n},
                {"Assigned officer IDs",       assignedID}
        };
        file3 << setw(4) << j << endl;
        file3.close();
        for (int i = 0; i < team.size(); i++) {
            team[i]->addInvestigation(invest);
        }
        cout << "Investigation team created" << endl;
        editComplaintStatus(complain->id, "Investigation in progress", complain->citizenFile, "Complaints",
                            "Status", "Complain Count");
    }
}

void SHO::discardComplaints(Complain *complain) {
    cout << endl;
    cout << "Citizen file: " << complain->citizenFile << endl;
    editComplaintStatus(complain->id, "Discarded", complain->citizenFile, "Complaints", "Status", "Complain Count");
}

void SHO::sortComplains() {
    for (const auto &complaint: complains) {
        complaint->displayDetail();
        string ans;
        cout << "Would you like to start an investigation? (Y/N): ";
        cin >> ans;
        if (ans == "y" || ans == "Y") {
            if (complaint->isEmergency()) {
                createInvestigation(complaint, true);
            } else {
                createInvestigation(complaint, false);
            }
        } else {
            string ans2;
            cout << "Would you like to assign patrolling? (Y/N): ";
            cin >> ans2;
            if (ans2 == "y" || ans2 == "Y") {
                assignPatrolling(complaint);
            } else {
                string ans3;
                cout << "Would you like to discard this complaint? (Y/N): " ;
                cin >> ans3;
                if (ans3 == "y" || ans3 == "Y") {
                    discardComplaints(complaint);
                }
            }
        }
    }
}


