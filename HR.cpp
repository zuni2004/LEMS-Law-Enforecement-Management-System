//
// Created by HP on 4/6/2024.
//
#include "HR.h"

vector<officer<string> *> HR::getAllOfficers() {
    vector<officer<string> *> loadedOfficers;
    Add2File();
    int count;
    string rank, name, RankID;
    int badgeNumber;
    json j;
    ifstream file("citizenCount.json");
    file >> j;
    file.close();
    count = j["Constable Count"];
    RankID = "C";
    rank = "Constable";
    string fileName;
    for (int i = 1; i <= count; i++) {
        stringstream ss;
        ss << i;
        fileName = RankID + ss.str() + ".json";
        ifstream inFile(fileName);
        if (inFile.is_open()) {
            json officerJson;
            inFile >> officerJson;
            inFile.close();
            if (officerJson["Info"]["Status"] == "Hired") {
                string officerID = officerJson["Info"]["Officer ID"];
                name = officerJson["Info"]["Name"];
                badgeNumber = officerJson["Info"]["Badge Number"];
                Constable *newOfficer = new Constable(rank, officerID, name, badgeNumber);
                bool available = officerJson["Info"]["Availability"];
                newOfficer->setAvailable(available);
                loadedOfficers.push_back(newOfficer);
            }
        }
    }
    count = j["Head Constable Count"];
    RankID = "HC";
    rank = "Head Constable";
    for (int i = 1; i <= count; i++) {
        stringstream ss;
        ss << i;
        fileName = RankID + ss.str() + ".json";
        ifstream inFile(fileName);
        if (inFile.is_open()) {
            json officerJson;
            inFile >> officerJson;
            inFile.close();
            if (officerJson["Info"]["Status"] == "Hired") {
                string officerID = officerJson["Info"]["Officer ID"];
                name = officerJson["Info"]["Name"];
                badgeNumber = officerJson["Info"]["Badge Number"];
                HeadConstable *newOfficer = new HeadConstable(rank, officerID, name, badgeNumber);
                bool available = officerJson["Info"]["Availability"];
                newOfficer->setAvailable(available);
                loadedOfficers.push_back(newOfficer);
            }
        }
    }

    count = j["IP Count"];
    RankID = "IP";
    rank = "IP";
    for (int i = 1; i <= count; i++) {
        stringstream ss;
        ss << i;
        fileName = RankID + ss.str() + ".json";
        ifstream inFile(fileName);
        if (inFile.is_open()) {
            json officerJson;
            inFile >> officerJson;
            inFile.close();
            if (officerJson["Info"]["Status"] == "Hired") {
                string officerID = officerJson["Info"]["Officer ID"];
                name = officerJson["Info"]["Name"];
                badgeNumber = officerJson["Info"]["Badge Number"];
                class IP *newOfficer = new class IP(rank, officerID, name, badgeNumber);
                bool available = officerJson["Info"]["Availability"];
                newOfficer->setAvailable(available);
                loadedOfficers.push_back(newOfficer);
            }
        }
    }

    count = j["ASI Count"];
    RankID = "ASI";
    rank = "ASI";
    for (int i = 1; i <= count; i++) {
        stringstream ss;
        ss << i;
        fileName = RankID + ss.str() + ".json";
        ifstream inFile(fileName);
        if (inFile.is_open()) {
            json officerJson;
            inFile >> officerJson;
            inFile.close();
            if (officerJson["Info"]["Status"] == "Hired") {
                string officerID = officerJson["Info"]["Officer ID"];
                name = officerJson["Info"]["Name"];
                badgeNumber = officerJson["Info"]["Badge Number"];
                class ASI *newOfficer = new class ASI(rank, officerID, name, badgeNumber);
                bool available = officerJson["Info"]["Availability"];
                newOfficer->setAvailable(available);
                loadedOfficers.push_back(newOfficer);
            }
        }
    }

    count = j["SI Count"];
    RankID = "SI";
    rank = "SI";
    for (int i = 1; i <= count; i++) {
        stringstream ss;
        ss << i;
        fileName = RankID + ss.str() + ".json";
        ifstream inFile(fileName);
        if (inFile.is_open()) {
            json officerJson;
            inFile >> officerJson;
            inFile.close();
            if (officerJson["Info"]["Status"] == "Hired") {
                string officerID = officerJson["Info"]["Officer ID"];
                name = officerJson["Info"]["Name"];
                badgeNumber = officerJson["Info"]["Badge Number"];
                class SI *newOfficer = new class SI(rank, officerID, name, badgeNumber);
                bool available = officerJson["Info"]["Availability"];
                newOfficer->setAvailable(available);
                loadedOfficers.push_back(newOfficer);
            }
        }
    }
//    count = j["Correctional Officer Count"];
//    RankID = "CO";
//    rank = "CO";
//    for (int i = 1; i <= count; i++) {
//        stringstream ss;
//        ss << i;
//        fileName = RankID + ss.str() + ".json";
//        ifstream inFile(fileName);
//        if (inFile.is_open()) {
//            json officerJson;
//            inFile >> officerJson;
//            inFile.close();
//            if (officerJson["Info"]["Status"] != "Hired") {
//                string officerID = officerJson["Info"]["Officer ID"];
//                name = officerJson["Info"]["Name"];
//                badgeNumber = officerJson["Info"]["Badge Number"];
//                loadedOfficers.push_back(new CorrectionalOfficer(rank, officerID, name, badgeNumber));
//            }
//        }
//    }
    return loadedOfficers;
}

void HR::addOFFICER(const string &name) {
    string rank, officerID;
    int badgeNumber;
    int n;
    cout << "Choose rank" << endl;
    cout << "1. Head constable" << endl;
    cout << "2. Constable" << endl;
    cout << "3. IP" << endl;
    cout << "4. ASI" << endl;
    cout << "5. SI" << endl;
    cout << "6. Correctional Officer" << endl;
    cin >> n;
    cout << "Enter date of Hiring (DD): ";
    cin >> date;
    cout << "Enter month of Hiring (MM): ";
    cin >> month;
    cout << "Enter year of Hiring (YY): ";
    cin >> year;
    if (n == 1) {
        HC++;
        rank = "Head Constable";
        stringstream ss;
        ss << HC;
        officerID = "HC" + ss.str();
        badgeNumber = HC;
        HeadConstable *newOFFICER = new HeadConstable(rank, officerID, name, badgeNumber);
        officers.push_back(newOFFICER);
    }
    if (n == 2) {
        C++;
        rank = "Constable";
        stringstream ss;
        ss << C;
        officerID = "C" + ss.str();
        badgeNumber = C;
        Constable *newOFFICER = new Constable(rank, officerID, name, badgeNumber);
        officers.push_back(newOFFICER);
    }
    if (n == 3) {
        IP++;
        rank = "IP";
        stringstream ss;
        ss << IP;
        officerID = "IP" + ss.str();
        badgeNumber = IP;
        officers.push_back(new class IP(rank, officerID, name, badgeNumber));
    }
    if (n == 4) {
        ASI++;
        rank = "ASI";
        stringstream ss;
        ss << ASI;
        officerID = "ASI" + ss.str();
        badgeNumber = ASI;
        officers.push_back(new class ASI(rank, officerID, name, badgeNumber));
    }
    if (n == 5) {
        SI++;
        rank = "SI";
        stringstream ss;
        ss << SI;
        officerID = "SI" + ss.str();
        badgeNumber = SI;
        officers.push_back(new class SI(rank, officerID, name, badgeNumber));
    }
    if (n == 6) {
        CO++;
        rank = "CO";
        stringstream ss;
        ss << CO;
        officerID = "CO" + ss.str();
        badgeNumber = CO;
        officers.push_back(new CorrectionalOfficer(rank, officerID, name, badgeNumber));
    }
    cout << "The Size of vector is " << officers.size() << endl;
}

void HR::Add2File() {
    string fileName;
    for (const auto &officerPtr: officers) {
        json j = toOFFICERJSON(*officerPtr);
        fileName = officerPtr->getOfficerID() + ".json";
        ofstream outFile(fileName);
        if (outFile.is_open()) {
            outFile << setw(4) << j << endl;
            outFile.close();
        } else {
            cout << "File not open" << endl;
        }
    }

    json count;
    ifstream file("citizenCount.json");
    file >> count;
    file.close();
    count["Constable Count"] = C;
    count["Head Constable Count"] = HC;
    count["IP Count"] = IP;
    count["ASI Count"] = ASI;
    count["SI Count"] = SI;
    count["Correctional Officer"] = CO;
    ofstream out("citizenCount.json");
    out << setw(4) << count << endl;

    json allOfficers;
    ifstream officerFile2("allOfficers.json");
    if (officerFile2.is_open()) {
        officerFile2 >> allOfficers;
        officerFile2.close();

        for (const auto &officerPtr: officers) {
            json j = toALLOFFICERJSON(*officerPtr);
            allOfficers[officerPtr->getOfficerID()] = j;
        }

        ofstream officerFile("allOfficers.json");
        if (officerFile.is_open()) {
            officerFile << setw(4) << allOfficers << endl;
            officerFile.close();
        } else {
            cout << "Failed to open allOfficers.json for writing" << endl;
        }
    } else {
        cout << "Failed to open allOfficers.json for reading" << endl;
    }

    json usernamesPasswordsJson;
    ifstream f("usernamesPasswords.json");
    if (f.is_open()) {
        f >> usernamesPasswordsJson;
        f.close();
    } else {
        cout << "File username not opening\n";
    }

    for (const auto &officerPtr: officers) {
        if (!usernamesPasswordsJson.contains(officerPtr->getOfficerID())) {
            string generatedUsername = "officer" + officerPtr->getOfficerID();
            string generatedPassword = "Pass" + officerPtr->getOfficerID();
            usernamesPasswordsJson[officerPtr->getOfficerID()] = {
                    {"Username", generatedUsername},
                    {"Password", generatedPassword}
            };
        }
    }

    ofstream outFile("usernamesPasswords.json");
    if (outFile.is_open()) {
        outFile << setw(4) << usernamesPasswordsJson << endl;
        outFile.close();
    } else {
        cout << "Failed to open usernamesPasswords.json for writing" << endl;
    }
    officers.clear();
}

vector<officer<string> *> HR::getOfficers() {
    vector<officer<string> *> loadedOfficers;
    int count;
    string rank, name, RankID;
    int badgeNumber;
    int n;
    cout << "Choose rank" << endl;
    cout << "1. Head constable" << endl;
    cout << "2. Constable" << endl;
    cout << "3. IP" << endl;
    cout << "4. ASI" << endl;
    cout << "5. SI" << endl;
    cout << "6. Correctional Officer" << endl;
    cin >> n;
    json j;
    ifstream file("citizenCount.json");
    file >> j;
    file.close();
    if (n == 1) {
        count = j["Head Constable Count"];
        RankID = "HC";
        rank = "Head Constable";
    }
    if (n == 2) {
        count = j["Constable Count"];
        RankID = "C";
        rank = "Constable";
    }
    if (n == 3) {
        count = j["IP Count"];
        RankID = "IP";
        rank = "IP";
    }
    if (n == 4) {
        count = j["ASI Count"];
        RankID = "ASI";
        rank = "ASI";
    }
    if (n == 5) {
        count = j["SI Count"];
        RankID = "SI";
        rank = "SI";
    }
    if (n == 6) {
        count = j["Correctional Officer Count"];
        RankID = "CO";
        rank = "CO";
    }
    string fileName;
    for (int i = 1; i <= count; i++) {
        stringstream ss;
        ss << i;
        fileName = RankID + ss.str() + ".json";
        ifstream inFile(fileName);
        if (inFile.is_open()) {
            json officerJson;
            inFile >> officerJson;
            inFile.close();
            if (officerJson["Info"]["Status"] != "Fired") {
                string officerID = officerJson["Info"]["Officer ID"];
                name = officerJson["Info"]["Name"];
                badgeNumber = officerJson["Info"]["Badge Number"];
                if (RankID == "HC") {
                    HeadConstable *newOfficer = new HeadConstable(rank, officerID, name, badgeNumber);
                    loadedOfficers.push_back(newOfficer);
                } else if (RankID == "C") {
                    Constable *newOfficer = new Constable(rank, officerID, name, badgeNumber);
                    loadedOfficers.push_back(newOfficer);
                } else if (RankID == "IP") {
                    loadedOfficers.push_back(new class IP(rank, officerID, name, badgeNumber));
                } else if (RankID == "ASI") {
                    loadedOfficers.push_back(new class ASI(rank, officerID, name, badgeNumber));
                } else if (RankID == "SI") {
                    loadedOfficers.push_back(new class SI(rank, officerID, name, badgeNumber));
                } else if (RankID == "CO") {
                    loadedOfficers.push_back(new CorrectionalOfficer(rank, officerID, name, badgeNumber));
                } else {
                    cout << "No such Rank exists\n";
                }
            }
        }
    }
    return loadedOfficers;
}

void HR::displayAddedOfficers() {
    cout << "Officer Count: " << officers.size() << endl;
    for (const auto &officerPtr: officers) {
        cout << endl;
        officerPtr->displayInfo();
        cout << endl;
    }
}

void HR::removeOfficers() {
    vector<officer<string> *> officers = getOfficers();
    cout << "Displaying all officers" << endl;
    for (const auto &officerPtr: officers) {
        cout << endl;
        officerPtr->displayInfo();
        cout << endl;
    }
    string id;
    cout << "Enter ID you want to fire: ";
    cin >> id;
    cout << "Enter date of Firing : ";
    cin >> date;
    cout << "Enter month of Firing : ";
    cin >> month;
    cout << "Enter year of Firing : ";
    cin >> year;
    bool officerFound = false;
    for (const auto &officerPtr: officers) {
        if (officerPtr->getOfficerID() == id) {
            officerFound = true;
            string fileName = id + ".json";
            json find;
            ifstream file(fileName);
            file >> find;
            file.close();
            find["Info"]["Status"] = "Fired";
            ofstream out(fileName);
            out << setw(4) << find << endl;
            out.close();

            json allOfficersJ;
            ifstream fileAllOfficers("allOfficers.json");
            fileAllOfficers >> allOfficersJ;
            fileAllOfficers.close();
            allOfficersJ[id]["Status"] = "Fired";
            ofstream allOfficersFile("allOfficers.json");
            allOfficersFile << setw(4) << allOfficersJ << endl;
            allOfficersFile.close();

            json usernamesPasswordsJson;
            ifstream usernamesPasswordsFile("usernamesPasswords.json");
            if (usernamesPasswordsFile.is_open()) {
                usernamesPasswordsFile >> usernamesPasswordsJson;
                usernamesPasswordsFile.close();
                cout << "Attempting to remove username and password entry for officer: " << id << endl;
                if (usernamesPasswordsJson.contains(id)) {
                    cout << "Entry found for officer: " << id << endl;
                    usernamesPasswordsJson.erase(id);
                    ofstream usernamesPasswordsOutFile("usernamesPasswords.json");
                    if (usernamesPasswordsOutFile.is_open()) {
                        usernamesPasswordsOutFile << setw(4) << usernamesPasswordsJson << endl;
                        usernamesPasswordsOutFile.close();
                        cout << "Username and password entry removed for officer: " << id << endl;
                    } else {
                        cout << "Failed to open usernamesPasswords.json for writing" << endl;
                    }
                } else {
                    cout << "Username and password entry not found for officer: " << id << endl;
                }
            } else {
                cout << "Failed to open usernamesPasswords.json for reading" << endl;
            }
        }
    }

    if (!officerFound) {
        cout << "Officer with ID " << id << " not found." << endl;
    }
}

officer<string> *HR::getOfficerByID(const string &officerID) {
    vector<officer<string> *> ptr2 = getAllOfficers();
    for (const auto &officerPtr: ptr2) {
        if (officerPtr->getOfficerID() == officerID) {
            return officerPtr;
        }
    }
    return nullptr;
}
