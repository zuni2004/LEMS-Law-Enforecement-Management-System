//
// Created by HP on 4/23/2024.
#include "HR.h"
#include "SHO.h"

template<typename T>
void updateFilee(const string &key, const T &newCnt) {
    json j;
    ifstream file("citizenCount.json");
    file >> j;
    file.close();
    j[key] = newCnt;
    ofstream file2("citizenCount.json");
    file2 << setw(4) << j << endl;
    file2.close();
}

string getPassword(int &pass) {
    string str;
    json j;
    ifstream file("citizenCount.json");
    file >> j;
    file.close();
    j["Password"] = str;
    for (char &c: str) {
        ++c;
        if (c > 'z') {
            c = 'a';
        }
    }
    stringstream ss;
    ss << pass;
    string count = ss.str() + str;
    updateFilee("Password", str);
    updateFilee("Password Cnt", pass);
    return str;
}

json Staff(string &username, string &password, User &user) {
    json j;
    if (user.getTaskCapacity() == 0) {
        j["Info"] = {
                {"ID",     user.getID()},
                {"Name",   user.getName()},
                {"CNIC",   user.getCNIC()},
                {"Status", "Hired"},
                {"Salary per Month", Budget::allocatingSalaries(user.getType())}
        };
    } else {
        j["Info"] = {
                {"ID",             user.getID()},
                {"Name",           user.getName()},
                {"Specialization", user.getType()},
                {"CNIC",           user.getCNIC()},
                {"Task Capacity",  user.getTaskCapacity()},
                {"Lab ID",         "UNDEFINED"},
                {"Status",         "Hired"},
                {"Evidence Count", 0},
                {"Salary per Month", Budget::allocatingSalaries(user.getType())}
        };
    }
    return j;
}

void HR::updateFile2() {
    json usernames;
    string fileName;
    ifstream readFile("usernamesPasswords.json");
    readFile >> usernames;
    readFile.close();
    for (int i = 0; i < users.size(); i++) {
        {
            pass++;
            string generatedUsername = "User" + users[i]->getID();
            string generatedPassword = "Pass" + getPassword(pass) + users[i]->getID();
            usernames[users[i]->getID()] = {
                    {"Username", generatedUsername},
                    {"Password", generatedPassword}
            };
            fileName = users[i]->getID() + ".json";
            ofstream outFile(fileName);
            if (outFile.is_open()) {
                json j;
                j = ::Staff(generatedUsername, generatedPassword, *(users[i]));
                outFile << setw(4) << j << endl;
                outFile.close();
            } else {
                cout << "File not open" << endl;
            }
        }
    }
    ofstream outFile("usernamesPasswords.json");
    if (outFile.is_open()) {
        outFile << setw(4) << usernames << endl;
        outFile.close();
        updateFilee("AS Count", AS);
        updateFilee("DNA analyst", DNA);
        updateFilee("Toxicologist", TOXIC);
        updateFilee("Anthropologist", ANTHRO);
        updateFilee("Document Examiner", DOC);
        updateFilee("Pathologist", PATHO);
        updateFilee("Digital Analyst", DIGITAL);
        updateFilee("SHO Count", SHO1);
        cout << "Usernames and passwords successfully written to usernamesPasswords.json" << endl;
    } else {
        cout << "Failed to open usernamesPasswords.json for writing" << endl;
    }
}

void HR::addStaff(const string &name, const string &CNIC, bool SHO) {
    if (!SHO) {
        stringstream ss;
        AS++;
        ss << AS;
        string cnt = ss.str();
        string ID = "AS" + cnt;
        AdministrativeStaff *ptr2 = new AdministrativeStaff(name, ID, ID);
        ptr2->setType("AS");
        ptr2->setName(name);
        ptr2->setCNIC(CNIC);
        users.push_back(ptr2);
    } else {
        if (SHO1 > 0) {
            cout << "Must fire previous SHO to replace" << endl;
        } else {
            stringstream ss;
            SHO1++;
            ss << SHO1;
            string cnt = ss.str();
            string ID = "SHO" + cnt;
            class SHO *ptr2 = new class SHO();
            ptr2->setType("SHO");
            ptr2->setName(name);
            ptr2->setCNIC(CNIC);
            ptr2->setID(ID);
            ptr2->setIDofficer(ID, name, SHO1);
            users.push_back(ptr2);
        }
    }
}

void HR::addStaff(const string &name, const string &cnic, const int &choice) {
    string specialization;
    string ID;
    stringstream ss;
    switch (choice) {
        case 1: {
            ss << DNA;
            ID = "DNA" + ss.str();
            DNA++;
            specialization = "DNA analyst";
            break;
        }
        case 2: {
            ss << TOXIC;
            ID = "TOXIC" + ss.str();
            TOXIC++;
            specialization = "Toxicologist";
            break;
        }
        case 3: {
            ss << ANTHRO;
            ID = "ANTHRO" + ss.str();
            ANTHRO++;
            specialization = "Anthropologist";
            break;
        }
        case 4: {
            ss << DOC;
            ID = "DOC" + ss.str();
            DOC++;
            specialization = "Document Examiner";
            break;
        }
        case 5: {
            ss << PATHO;
            ID = "PATHO" + ss.str();
            PATHO++;
            specialization = "Pathologist";
            break;
        }
        case 6: {
            ss << DIGITAL;
            ID = "DIGITAL" + ss.str();
            DIGITAL++;
            specialization = "Digital Analyst";
            break;
        }
        default: {
            cout << "invalid input" << endl;
            break;
        }
    }
    int n;
    cout << "Enter task capacity" << endl;
    cin >> n;
    ForensicExpert *pointer = new ForensicExpert(ID, name, cnic, specialization, n);
    pointer->setType(specialization);
    pointer->setName(name);
    pointer->setCNIC(cnic);
    users.push_back(pointer);
}

ForensicExpert *ReadFromFile(string &fileName, const json &j) {
    string id = j["Info"]["ID"];
    string name = j["Info"]["Name"];
    string CNIC = j["Info"]["CNIC"];
    string specialization = j["Info"]["Specialization"];
    int taskCapacity = j["Info"]["Task Capacity"];
    int evidenceCnt = j["Info"]["Evidence Count"];
    ForensicExpert *expert = new ForensicExpert(id, name, CNIC, specialization, taskCapacity, evidenceCnt);
    return expert;
}

vector<ForensicExpert *> HR::getPtr() {
    vector<ForensicExpert *> expertise;
    string fileName;
    for (int i = 0; i < DNA; i++) {
        fileName = "DNA" + to_string(i) + ".json";
        ifstream file(fileName);
        if (!file.is_open()) {
            break;
        }
        json j;
        file >> j;
        file.close();
        if (j["Info"]["Status"] == "Hired") {
            expertise.push_back(::ReadFromFile(fileName, j));
        }
    }
    for (int i = 0; i < ANTHRO; i++) {
        fileName = "ANTHRO" + to_string(i) + ".json";
        ifstream file(fileName);
        if (!file.is_open()) {
            break;
        }
        json j;
        file >> j;
        file.close();
        if (j["Info"]["Status"] == "Hired") {
            expertise.push_back(::ReadFromFile(fileName, j));
        }
    }
    for (int i = 0; i < DIGITAL; i++) {
        fileName = "DIGITAL" + to_string(i) + ".json";
        ifstream file(fileName);
        if (!file.is_open()) {
            break;
        }
        json j;
        file >> j;
        file.close();
        if (j["Info"]["Status"] == "Hired") {
            expertise.push_back(::ReadFromFile(fileName, j));
        }
    }
    for (int i = 0; i < TOXIC; i++) {
        fileName = "DIGITAL" + to_string(i) + ".json";
        ifstream file(fileName);
        if (!file.is_open()) {
            break;
        }
        json j;
        file >> j;
        file.close();
        if (j["Info"]["Status"] == "Hired") {
            expertise.push_back(::ReadFromFile(fileName, j));
        }
    }
    for (int i = 0; i < PATHO; i++) {
        fileName = "PATHO" + to_string(i) + ".json";
        ifstream file(fileName);
        if (!file.is_open()) {
            break;
        }
        json j;
        file >> j;
        file.close();
        if (j["Info"]["Status"] == "Hired") {
            expertise.push_back(::ReadFromFile(fileName, j));
        }
    }
    for (int i = 0; i < DOC; i++) {
        fileName = "DOC" + to_string(i) + ".json";
        ifstream file(fileName);
        if (!file.is_open()) {
            break;
        }
        json j;
        file >> j;
        file.close();
        if (j["Info"]["Status"] == "Hired") {
            expertise.push_back(::ReadFromFile(fileName, j));
        }
    }
    return expertise;
}

void HR::addUser() {
    int n;
    cout << "Choose" << endl;
    cout << "1.Administrative staff" << endl;
    cout << "2.Forensic Expert" << endl;
    cout << "3.SHO" << endl;
    cin >> n;
    string name;
    cout << "Enter name: ";
    getline(cin, name);
    string cnic;
    cin.ignore();
    cout << "Enter CNIC: ";
    cin >> cnic;
    cin.ignore();
    cout << "Enter date of Hiring (DD): ";
    cin >> date;
    cout << "Enter month of Hiring (MM): ";
    cin >> month;
    cout << "Enter year of Hiring (YY): ";
    cin >> year;
    if (n == 1) {
        addStaff(name, cnic, false);
    }
    if (n == 2) {
        int n2;
        cout << "Choose specialization" << endl;
        cout << "1. DNA analyst" << endl;
        cout << "2. Toxicologist" << endl;//for presence of drugs
        cout << "3. Anthropologist" << endl;//for checking skeletal stuff innit
        cout << "4. Document Examiners" << endl;//for checking of forgery of signatures and allat
        cout << "5. Pathologist" << endl;//for performing autopsies
        cout << "6. Digital Analysts" << endl;//check for digital background
        cin >> n2;
        addStaff(name, cnic, n2);
    }
    if (n == 3) {
        addStaff(name, cnic, true);
    } else {
        cout << "Invalid input" << endl;
    }
}

void HR::editRank(officer<string> *ptr, int &n) {
    if (ptr == nullptr) {
        cout << "this officer doesnt exist" << endl;
        return;
    }
    string newStatus;
    if (n == 1) {
        newStatus = "Promoted";
    } else {
        newStatus = "Demoted";
    }
    ::editFile(ptr->getOfficerID() + ".json", "Info", "Status", newStatus);
    cout << ptr->getOfficerID();
    addOFFICER(ptr->getName());
    Add2File();

}//ADD BOOL EDITED rank so i can store previous id
void HR::FireStaff(officer<string> *ptr) {
    if (ptr == nullptr) {
        cout << "this officer doesnt exist" << endl;
        return;
    }
    ::editFile(ptr->getOfficerID() + ".json", "Info", "Status", "Fired");
}