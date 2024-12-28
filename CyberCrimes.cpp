#include "CyberCrimes.h"

CyberCrime::CyberCrime(string CyberAttackType, string targetSystem, int crimeId, string description,
                       string date, string location, string status, string motive)
        : CyberAttackType(CyberAttackType), targetSystem(targetSystem),
          Crime(crimeId, description, date, location, status, motive) {
    for (int i = 0; i < evidence.size(); ++i) {
        evidence[i] = nullptr;
    }
}

void CyberCrime::recordNewCrime() {
    crimeId = 31000;
    cout << "Entering new crime\n";
    cout << "Enter Cyber Attack Type\n";
    cin.ignore();
    getline(cin, CyberAttackType);
    cout << "Enter Target Time\n";
    getline(cin, targetSystem);
    cout << "Enter crime date\n";
    cin >> date;
    cout << "Enter crime location\n";
    cin.ignore();
    getline(cin, location);
    cout << "Enter crime status solved or unsolved\n";
    cin >> status;
    cout << "Enter crime motive\n";
    cin.ignore();
    getline(cin, motive);
    cout << "Enter crime description\n";
    getline(cin, description);
    cin.ignore();
    string evidenceID, evidenceDescription, evidenceLocation, evidenceDateTime, chainOfCustody;
    string evidenceType, evidenceSource, associatedCaseID, evidenceStatus, evidenceRemarks;
    int evidencePriority;
    int number;
    cout << "Enter number of evidence you want to store";
    cin >> number;
    cin.ignore();
    for (int i = 0; i < number; ++i) {
        Evidence evidence1;
        cout << "Enter Evidence ID: ";
        getline(cin, evidenceID);
        evidence1.setId(evidenceID);

        cout << "Enter Evidence Description: ";
        getline(cin, evidenceDescription);
        evidence1.setDescription(evidenceDescription);

        cout << "Enter Evidence Location: ";
        getline(cin, evidenceLocation);
        evidence1.setLocationFound(evidenceLocation);

        cout << "Enter Evidence Date and Time: ";
        getline(cin, evidenceDateTime);
        evidence1.setDateAndTimeFound(evidenceDateTime);

        cout << "Enter Chain of Custody: ";
        getline(cin, chainOfCustody);
        evidence1.setChainOfCustody(chainOfCustody);

        cout << "Enter Evidence Type: ";
        getline(cin, evidenceType);
        evidence1.setType(evidenceType);

        cout << "Enter Evidence Source: ";
        getline(cin, evidenceSource);
        evidence1.setSource(evidenceSource);

        cout << "Enter Associated Case ID: ";
        getline(cin, associatedCaseID);
        evidence1.setAssociatedCaseID(associatedCaseID);

        cout << "Enter Evidence Status: ";
        getline(cin, evidenceStatus);
        evidence1.setStatus(evidenceStatus);

        cout << "Enter Evidence Priority: ";
        cin >> evidencePriority;
        evidence1.setPriority(evidencePriority);
        cin.ignore();

        cout << "Enter Evidence Remarks: ";
        getline(cin, evidenceRemarks);
        evidence1.setRemarks(evidenceRemarks);
        addEvidence(&evidence1);
    }

    ifstream file("CyberCrime.json");
    json crimeRecords;
    if (file.is_open()) {
        file >> crimeRecords;
        crimeId = CalculatingId();
        ++crimeId;
        file.close();
    } else {
        // cout << "Nothing exist in file to read" << endl;
    }
    json allEvidence;
    for (const auto &e: evidence) {
        json evidenceData{
                {"ID",               e->getId()},
                {"Description",      e->getDescription()},
                {"Location",         e->getLocationFound()},
                {"DateAndTime",      e->getDateAndTimeFound()},
                {"ChainOfCustody",   e->getChainOfCustody()},
                {"Type",             e->getType()},
                {"Source",           e->getSource()},
                {"AssociatedCaseID", e->getAssociatedCaseID()},
                {"Status",           e->getStatus()},
                {"Priority",         e->getPriority()},
                {"Remarks",          e->getRemarks()}
        };
        allEvidence.push_back(evidenceData);
    }
    json recordCrime{
            {"Crime Id",          crimeId},
            {"Description",       description},
            {"Date",              date},
            {"Target System",     targetSystem},
            {"Cyber Attack Type", CyberAttackType},
            {"Location",          location},
            {"Status",            status},
            {"Motive",            motive},
            {"Evidence",          {allEvidence}}
    };
    crimeRecords.push_back(recordCrime);

    ofstream outFile("CyberCrime.json", ios::out);
    if (outFile.is_open()) {
        outFile << setw(4) << crimeRecords << endl;
        cout << "Crime ID number is " << crimeId << endl;
    } else {
        cout << "Cannot write to file" << endl;
        return;
    }
}

bool CyberCrime::updateCrimeStatus() {
    ifstream file("CyberCrime.json", ios::in);
    if (!file.is_open()) {
        cout << "Cannot update\n";
        return false;
    }
    json find;
    file >> find;
    int id;
    cout << "Enter Crime Id\n";
    cin >> id;
    for (auto &finding: find) {
        if (finding["Crime Id"] == id) {
            cout << "Enter new status";
            string updatedStatus;
            cin >> updatedStatus;
            finding["Status"] = updatedStatus;
            break;
        }
    }
    ofstream outputfile("CyberCrimes.json", ios::out);
    outputfile << setw(4) << find << endl;
    outputfile.close();
    return true;
}

void CyberCrime::viewListOfCrimes() const {
    json j;
    ifstream file("CyberCrime.json");
    if (file.is_open()) {
        file >> j;
        cout << setw(4) << j << endl;
        file.close();
    } else
        cout << "Cannot display list of Cyber Crime " << endl;
}

int CyberCrime::CalculatingId() {
    ifstream file("CyberCrime.json", ios::in);
    if (!file.is_open()) {
        cout << "Cannot open file\n";
        return 31000;
    }

    json data;
    file >> data;

    int lastId = -1;
    for (const auto &finding: data) {
        lastId = finding["Crime Id"];
    }

    file.close();
    return lastId;
}

const string &CyberCrime::getCyberAttackType() const {
    return CyberAttackType;
}

const string &CyberCrime::getTargetSystem() const {
    return targetSystem;
}

void CyberCrime::setTargetSystem(const string &targetSystem) {
    CyberCrime::targetSystem = targetSystem;
}

void CyberCrime::setCyberAttackType(const string &cyberAttackType) {
    CyberAttackType = cyberAttackType;
}
