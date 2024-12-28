//
// Created by InnoSTARK on 4/6/2024.
//

#include "User.h"

string User::login(const string &officerID, const string &enteredPassword, const string &enteredUsername) const {
    if (officerID == "HR") {
        json loginHR;
        ifstream hr("usernamesPasswords.json");
        if (hr.is_open()) {
            hr >> loginHR;
            hr.close();
            if (loginHR["HR"]["Username"] == enteredUsername &&
                loginHR["HR"]["Password"] == enteredPassword) {
                string portal = determinePortal(officerID);
                cout << "WELCOME TO " << portal << ": " << officerID << "!\n";
                return portal;
            } else {
                return "Invalid username or password";
            }
        } else {
            return "File not opening\n";
        }
    } else {
        json login;
        string officerFile = officerID + ".json";
        ifstream loginAttributes(officerFile);
        if (loginAttributes.is_open()) {
            loginAttributes >> login;
            loginAttributes.close();
            if (login["Login Info"]["Username"] == enteredUsername &&
                login["Login Info"]["Password"] == enteredPassword) {
                string portal = determinePortal(officerID);
                cout << "WELCOME TO " << portal << ": " << officerID << "!\n";
                return portal;
            } else {
                return "Invalid username or password";
            }
        } else {
            return "Failed to open";
        }
    }
}

void User::changePassword(const string &officerID, const string &username) {
    json changePassword;
    ifstream change("usernamesPasswords.json");
    if (change.is_open()) {
        change >> changePassword;
        change.close();
    } else {
        cout << "File not opening\n";
        return;
    }
    if (changePassword.contains(officerID)) {
        string oldPassword = changePassword[officerID]["Password"];
        string enteredPassword;
        cout << "Enter current password: ";
        cin >> enteredPassword;

        if (enteredPassword == oldPassword) {
            string newPassword;
            cout << "Enter a new password: ";
            cin >> newPassword;
            json newPassWord;
            string officerFile = officerID + ".json";
            ifstream readOfficerFile(officerFile);
            if (readOfficerFile.is_open()) {
                readOfficerFile >> newPassWord;
                readOfficerFile.close();
            } else {
                cout << "Officer File is not opening\n";
                return;
            }
            newPassWord["Login Info"] = {
                    {"Username", username},
                    {"Password", newPassword}
            };
            ofstream writePassword(officerFile);
            if (writePassword.is_open()) {
                writePassword << newPassWord.dump(4) << endl;
                writePassword.close();
                cout << "Password changed successfully for officer: " << officerID << endl;
            } else {
                cout << "Failed to open " << officerFile << endl;
            }
            json usernamesPasswordsJson;
            ifstream usernamesPasswordsFile("usernamesPasswords.json");
            if (usernamesPasswordsFile.is_open()) {
                usernamesPasswordsFile >> usernamesPasswordsJson;
                usernamesPasswordsFile.close();
                if (usernamesPasswordsJson.contains(officerID)) {
                    usernamesPasswordsJson.erase(officerID);
                    ofstream usernamesPasswordsOutFile("usernamesPasswords.json");
                    if (usernamesPasswordsOutFile.is_open()) {
                        usernamesPasswordsOutFile << setw(4) << usernamesPasswordsJson << endl;
                        usernamesPasswordsOutFile.close();
                        cout << "Old password removed\n";
                    } else {
                        cout << "Failed to open usernamesPasswords.json for writing" << endl;
                    }
                } else {
                    cout << "Failed to open usernamesPasswords.json for reading" << endl;
                }
            } else {
                cout << "Incorrect password.\n";
            }
        } else {
            cout << "Officer ID not found.\n";
        }
    }
}

string User::determinePortal(const string &officerID) const {
    if (officerID.substr(0, 2) == "HC") {
        return "Head Constable Portal";
    } else if (officerID.substr(0, 2) == "IP") {
        return "Inspector Police Portal";
    } else if (officerID.substr(0, 3) == "ASI") {
        return "Assistant Sub-Inspector Portal";
    } else if (officerID.substr(0, 2) == "SI") {
        return "Sub-Inspector Portal";
    } else if (officerID.substr(0, 2) == "AS") {
        return "Administrative Staff Portal";
    } else if (officerID.substr(0, 3) == "SHO") {
        return "SHO Portal";
    } else if (officerID.substr(0, 2) == "CO") {
        return "Correctional Officer Portal";
    } else if (officerID.substr(0, 1) == "C") {
        return "Constable Portal";
    } else if (officerID.substr(0, 3) == "DNA") {
        return "DNA Analyst Portal";
    } else if (officerID.substr(0, 5) == "TOXIC") {
        return "Toxicologist Portal";
    } else if (officerID.substr(0, 6) == "ANTHRO") {
        return "Anthropologist Portal";
    } else if (officerID.substr(0, 3) == "DOC") {
        return "Document Examiner Portal";
    } else if (officerID.substr(0, 5) == "PATHO") {
        return "Pathologist Portal";
    } else if (officerID.substr(0, 7) == "DIGITAL") {
        return "Digital Analyst Portal";
    } else if (officerID == "HR") {
        return "HR Portal";
    } else {
        return "Unknown Portal";
    }
}


