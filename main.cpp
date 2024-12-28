#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "json.hpp"
#include "User.h"
#include "AdministrativeStaff.h"
#include "ASI.h"
#include "SI.h"
#include "IP.h"
#include "officer.h"
#include "Citizen.h"
#include "HR.h"
#include "SHO.h"
#include "PoliceStation.h"
#include "Evidence.h"
#include "CorrectionalOfficer.h"
#include "Investigation.h"
#include "Menu.h"

using json = nlohmann::json;
using namespace std;

int Citizen::CitizenCount = 0;
int Citizen::TotalCount = 0;
HR *HR::ptr = nullptr;
vector<Complain *> Citizen::validComplaints;
vector<Investigation *> SHO::investigations;
vector<Patrolling *> SHO::patrollings;

int main() {
    User *user;
    Menu menu;
    cout << "\tWELCOME TO LEMS\t\n";
    cout << "\tGroup A\t\n";
    cout << "1. Report a Crime\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    int choice;
    cin >> choice;
    cout << endl;
    switch (choice) {
        case 1: {
            menu.handleCitizenMenu();
            break;
        }
        case 2: {
            string id, username, password;
            cout << "Please enter your officerID: ";
            cin >> id;
            if (id == "HR") {
                cout << "Enter your username: ";
                cin >> username;
                cout << "Enter your password: ";
                cin >> password;
                string portal = user->login(id, password, username);
                if (portal == "HR Portal") {
                    HR *hrInstance = HR::getInstance();
                    menu.handleHRMenu(*hrInstance);
                }
            } else {
                string passWord = "Pass" + id;
                json j;
                ifstream loggingIn("usernamesPasswords.json");
                if (loggingIn.is_open()) {
                    loggingIn >> j;
                    if (j[id]["Password"] == passWord) {
                        cout << "Change your Password\n";
                        cout << "Enter your username: ";
                        cin >> username;
                        user->changePassword(id, username);
                        cout << "Enter your password: ";
                        cin >> password;
                        string portal = user->login(id, password, username);
                        if (portal == "SHO Portal") {
                            SHO station;
                            menu.handleSHOMenu(station);
                        } else if (portal == "Correctional Officer Portal") {
                            CorrectionalOfficer *correctionalOfficer;
                            menu.handleCOMenu(*correctionalOfficer);
                        } else if (portal == "Head Constable Portal") {
                            HeadConstable hc(id);
                            menu.handleHCMenu(hc);
                        } else if (portal == "Inspector Police Portal") {
                            IP ip(id);
                            PoliceStation *policeStation = PoliceStation::getInstance();
                            menu.handleIPMenu(ip, *policeStation);
                        } else if(portal=="Administrative Staff Portal"){
                            AdministrativeStaff administrativeStaff;
                            menu.handleASMenu(administrativeStaff);
                        } else if (portal == "DNA Analyst Portal" || portal == "Toxicologist Portal" ||
                                   portal == "Document Examiner Portal" || portal == "Pathologist Portal" ||
                                   portal == "Digital Analyst Portal" || portal == "Anthropologist Portal") {
                            menu.handleForensicMenu();
                        }else if(portal == "Constable Portal"){
                            Constable constable(id);
                            menu.handleConstableMenu(constable);
                        }
                        loggingIn.close();
                    } else {
                        cout << "Enter your username: ";
                        cin >> username;
                        cout << "Enter your password: ";
                        cin >> password;
                        string portal = user->login(id, password, username);
                        if (portal == "SHO Portal") {
                            SHO station;
                            menu.handleSHOMenu(station);
                        } else if (portal == "Correctional Officer Portal") {
                            CorrectionalOfficer *correctionalOfficer;
                            menu.handleCOMenu(*correctionalOfficer);
                        } else if (portal == "Head Constable Portal") {
                            HeadConstable hc(id);
                            menu.handleHCMenu(hc);
                        } else if (portal == "Inspector Police Portal") {
                            IP ip(id);
                            PoliceStation *policeStation = PoliceStation::getInstance();
                            menu.handleIPMenu(ip, *policeStation);
                        } else if(portal=="Administrative Staff Portal"){
                                AdministrativeStaff administrativeStaff;
                                menu.handleASMenu(administrativeStaff);
                        } else if (portal == "DNA Analyst Portal" || portal == "Toxicologist Portal" ||
                                   portal == "Document Examiner Portal" || portal == "Pathologist Portal" ||
                                   portal == "Digital Analyst Portal" || portal == "Anthropologist Portal") {
                            menu.handleForensicMenu();
                        }
                        loggingIn.close();
                    }
                } else {
                    cout << "Failed to open usernamesPasswords.json\n";
                }
            }
            break;
        }
        case 3: {
            cout << "Exiting.......";
            break;
        }
        default: {
            cout << "Invalid Choice. Try again later\n";
            break;
        }
    }
    return 0;
}