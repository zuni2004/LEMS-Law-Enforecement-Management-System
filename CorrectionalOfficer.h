#ifndef CORRECTIONALOFFICER_H
#define CORRECTIONALOFFICER_H

#include <iostream>
#include <string>
#include "Criminal.h"
#include "Cells.h"
#include "officer.h"
#include <vector>


const int MAX_crim = 100; // Maximum number of criminals
const int MAX_cell = 50;  // Maximum number of cells

class CorrectionalOfficer : public officer<string> {
private:
    vector<Criminal *> criminals;//association
    vector<Cells *> cells; //aggregation
    int cellCount;
    int crimeCount;

public:
    CorrectionalOfficer(const string &_rank, const string &_officerID = "", const string &_name = "",
                        int _badgeNumber = 0) : officer(_rank, _officerID, _name, _badgeNumber) {
        cells.resize(MAX_cell);
        for (int i = 0; i < MAX_cell; ++i) {
            cells[i] = nullptr;
        }
        cellCount = 0;
        crimeCount = 0;
    }

    int CalculatingId1() {
        ifstream file("Cells.json", ios::in);
        if (!file.is_open()) {
            cout << "Cannot open file\n";
            return 0;
        }

        json data;
        file >> data;

        int lastId = -1;
        for (const auto &finding: data) {
            lastId = finding["CellID"];
        }

        file.close();
        return lastId;
    }

    const vector<Criminal *> &getCriminals() const;

    void setCriminals(const vector<Criminal *> &criminals);

    const vector<Cells *> &getCells() const;

    void setCells(const vector<Cells *> &cells);

    int getCellCount() const;

    void setCellCount(int cellCount);

    int getCrimeCount() const;

    void setCrimeCount(int crimeCount);

    void updateCriminalInCell() {
        ifstream file("Cells.json", ios::in);
        if (!file.is_open()) {
            cout << "Cannot update\n";
            return;
        }

        json find;
        file >> find;
        file.close();

        int id;
        cout << "Enter Cell no: ";
        cin >> id;

        bool cellFound = false;
        int occupancy1 = 0, capacity1 = 0;
        for (auto &finding: find) {
            if (finding["CellID"] == id) {
                cellFound = true;
                occupancy1 = finding["Occupancy"];
                capacity1 = finding["Capacity"];

                int num;
                cout << "Enter number of criminals you want to add in the cell: ";
                cin >> num;

                if (capacity1 >= occupancy1 + num) {
                    for (int i = 0; i < num; ++i) {
                        int ids;
                        cout << "Enter criminal ID " << i + 1 << ": ";
                        cin >> ids;
                        finding["Criminal Ids"].push_back(ids);
                    }
                    finding["Occupancy"] = occupancy1 + num;
                    cout << "Criminals added successfully.\n";
                } else {
                    cout << "No space available. Cannot add criminals.\n";
                }
                break; // Stop searching after finding the cell
            }
        }

        if (!cellFound) {
            cout << "Cell with ID " << id << " not found.\n";
        } else {
            // Write updated JSON back to file
            ofstream outputfile("Cells.json", ios::out);
            outputfile << setw(4) << find << endl;
            outputfile.close();
        }
    }


    void removeCriminalFromCell() {
        ifstream file("Cells.json", ios::in);
        if (!file.is_open()) {
            cout << "Cannot update\n";
            return;
        }

        json find;
        file >> find;
        file.close();

        int id;
        cout << "Enter Cell no: ";
        cin >> id;

        for (auto &finding: find) {
            if (finding["CellID"] == id) {
                int criminalId;
                cout << "Enter the ID of the criminal you want to remove: ";
                cin >> criminalId;
                bool good = false;
                auto &criminalIds = finding["Criminal Ids"];
                for (auto it = criminalIds.begin(); it != criminalIds.end(); ++it) {
                    if (*it == criminalId) {
                        criminalIds.erase(it);
                        finding["Occupancy"] = finding["Occupancy"].get<int>() - 1; // Update occupancy
                        good = true;
                        break;
                    }
                }
                if (!good) {
                    cout << "Not found";
                    return;
                }

                // Write updated JSON back to file
                ofstream outFile("Cells.json", ios::out);
                outFile << setw(4) << find << endl;
                outFile.close();

                cout << "Criminal with ID " << criminalId << " removed from cell " << id << endl;
                return;
            }
        }

        cout << "Cell with ID " << id << " not found.\n";
    }


    void displayCellData() {
        json j;
        ifstream file("Cells.json");
        if (file.is_open()) {
            file >> j;
            cout << setw(4) << j << endl;
            file.close();
        } else
            cout << "Cannot display cells" << endl;
    }

    void displayInfo()  override {
        cout << "Correctional Officer info\n";
        cout << "Rank: " << getRank() << "\nOfficer ID: " << getOfficerID() << "\nOfficer Name: " << getName()
             << "\nBadge Number: " << getBadgeNumber() << endl;
    }
};

#endif