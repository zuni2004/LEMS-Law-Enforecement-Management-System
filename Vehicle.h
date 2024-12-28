#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "json.hpp"
#include "Budget.h"

using namespace std;
using json = nlohmann::json;

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
class Vehicle {
private:
    T vehicleId;
    U make;
    V model;
    W year;
    X color;
    Y licensePlate;
    Z mileage;
    AA fuelType;
    BB engineSize;
    CC transmissionType;
    DD numSeats;
    EE vehicleClass;
    FF vehicleType;
    GG currentStatus;
    string MaintenanceHistory;
    bool AvailabilityStatus;
public:
    Vehicle() {}

    Vehicle(T id, const U mk, const V mdl, W yr, X col, Y lp, Z mlg, AA ft, BB es, CC tt, DD ns, EE vc, FF vt, GG cs,
            string MaintenanceHistory, bool AvailabilityStatus)
            :
            vehicleId(id), make(mk), model(mdl), year(yr), color(col), licensePlate(lp), mileage(mlg), fuelType(ft),
            engineSize(es), transmissionType(tt), numSeats(ns), vehicleClass(vc), vehicleType(vt),
            currentStatus(cs), MaintenanceHistory(MaintenanceHistory), AvailabilityStatus(AvailabilityStatus) {}

    int CalculatingId() {
        ifstream file("Vehicles.json", ios::in);
        if (!file.is_open()) {
            cout << "Cannot open file\n";
            return 109000;
        }

        json data;
        file >> data;

        int lastId = -1;
        for (const auto &finding: data) {
            lastId = finding["vehicleId"];
        }

        file.close();
        return lastId;
    }

    string AddVehicle() {
        string AvailabilityStatus;
        int price;
        vehicleId = 109000;
        json j;
        ifstream inFile("vehicles.json");
        if (inFile) {
            vehicleId = CalculatingId();
            ++vehicleId;
            inFile >> j;
        }
        inFile.close();
        cout << "Enter vehicle make: ";
        cin.ignore();
        getline(cin, make);
        cout << "Enter vehicle model: ";
        getline(cin, model);
        cout << "Enter vehicle year: ";
        cin >> year;
        cout << "Enter vehicle color: ";
        cin.ignore();
        getline(cin, color);
        cout << "Enter license plate: ";
        cin >> licensePlate;
        cout << "Enter vehicle mileage: ";
        cin >> mileage;
        cout << "Enter vehicle fuel type: ";
        cin.ignore();
        getline(cin, fuelType);
        cout << "Enter vehicle engine type: ";
        cin >> engineSize;
        cout << "Enter vehicle transmission type: ";
        cin >> transmissionType;
        cout << "Enter number of seats: ";
        cin >> numSeats;
        cout << "Enter vehicle class: ";
        cin.ignore();
        getline(cin, vehicleClass);
        cout << "Enter vehicle type: ";
        getline(cin, vehicleType);
        cout << "Enter vehicle current status(in use): ";
        getline(cin, currentStatus);
        cout << "Enter vehicle maintenance history: ";
        getline(cin, MaintenanceHistory);
        cout << "Enter Availability status(true or false): ";
        cin >> AvailabilityStatus;
        cout << "Enter price of vehicle: ";
        cin >> price;
        double remainingBudget = Budget::getInstance()->getBudgetRemaining();
        if (remainingBudget >= price) {
            Budget::getInstance()->deductFromBudget(price);
        } else {
            cout << "Insufficient budget to add the vehicle." << endl;
            return "Vehicle addition failed: Insufficient budget.";
        }
        json newVehicle;
        newVehicle["vehicleId"] = vehicleId;
        newVehicle["make"] = make;
        newVehicle["model"] = model;
        newVehicle["year"] = year;
        newVehicle["color"] = color;
        newVehicle["licensePlate"] = licensePlate;
        newVehicle["mileage"] = mileage;
        newVehicle["fuelType"] = fuelType;
        newVehicle["engineSize"] = engineSize;
        newVehicle["transmissionType"] = transmissionType;
        newVehicle["numSeats"] = numSeats;
        newVehicle["vehicleClass"] = vehicleClass;
        newVehicle["vehicleType"] = vehicleType;
        newVehicle["currentStatus"] = currentStatus;
        newVehicle["MaintenanceHistory"] = MaintenanceHistory;
        newVehicle["AvailabilityStatus"] = AvailabilityStatus;
        newVehicle["Price"] = price;
        j.push_back(newVehicle);

        ofstream outFile("vehicles.json");
        outFile << setw(4) << j << endl;
        outFile.close();
        cout << "Vehicle Id " << vehicleId << endl;
        return "Vehicle added successfully.";
    }

    friend ostream &operator<<(ostream &os, const Vehicle &vehicle) {
        os << "vehicleId: " << vehicle.vehicleId << " make: " << vehicle.make << " model: " << vehicle.model
           << " year: " << vehicle.year << " color: " << vehicle.color << " licensePlate: " << vehicle.licensePlate
           << " mileage: " << vehicle.mileage << " fuelType: " << vehicle.fuelType << " engineSize: "
           << vehicle.engineSize << " transmissionType: " << vehicle.transmissionType << " numSeats: "
           << vehicle.numSeats << " vehicleClass: " << vehicle.vehicleClass << " vehicleType: " << vehicle.vehicleType
           << " currentStatus: " << vehicle.currentStatus << " MaintenanceHistory: " << vehicle.MaintenanceHistory;
        return os;
    }

    void ViewVehicles() {
        json j;
        ifstream inFile("vehicles.json");
        if (inFile) {
            inFile >> j;
            cout << setw(4) << j << endl;
            inFile.close();
            return;
        } else {
            cout << "Cannot open file\n";
        }
    }

    void SearchVehicle() {
        bool found = false;
        int ID;
        json j, temp;
        ifstream file("Vehicles.json");
        if (!file.is_open()) {
            cout << "Cannot open file\n";
            return;
        } else {
            file >> j;
            cout << "Enter vehicle Id: ";
            cin >> ID;
            for (auto &temp: j) {
                int tempID = temp["vehicleId"];
                if (tempID == ID) {
                    cout << "Vehicle ID: " << temp["vehicleId"] << endl
                         << "Make: " << temp["make"] << endl
                         << "Model: " << temp["model"] << endl
                         << "Year: " << temp["year"] << endl
                         << "Color: " << temp["color"] << endl
                         << "License Plate: " << temp["licensePlate"] << endl
                         << "Mileage: " << temp["mileage"] << endl
                         << "Fuel Type: " << temp["fuelType"] << endl
                         << "Engine Size: " << temp["engineSize"] << endl
                         << "Transmission Type: " << temp["transmissionType"] << endl
                         << "Number of Seats: " << temp["numSeats"] << endl
                         << "Vehicle Class: " << temp["vehicleClass"] << endl
                         << "Vehicle Type: " << temp["vehicleType"] << endl
                         << "Current Status: " << temp["currentStatus"] << endl
                         << "Maintenance History: " << temp["MaintenanceHistory"] << endl;
                    found = true;
                    break;
                }
            }
            if (!found) { cout << "Id not found"; }
        }
    }

    bool CheackVehicle() {
        bool found = false;
        int ID;
        json j, temp;
        ifstream file("Vehicles.json");
        if (!file.is_open()) {
            cout << "Cannot open file\n";
            return false;
        } else {
            file >> j;
            cout << "Enter vehicle Id: ";
            cin >> ID;
            for (auto &temp: j) {
                int tempID = temp["vehicleId"];
                if (tempID == ID) {
                    found = true;
                    return true;
                    break;
                }
            }
            if (!found) { cout << "Id not found"; }
            return false;
        }
    }

    void UpdateVehicleStatus() {
        json j;
        ifstream inFile("vehicles.json");
        if (!inFile) {
            cout << "Error: Cannot open file.\n";
            return;
        }
        inFile >> j;
        inFile.close();

        int selectedId;
        cout << "Enter the Vehicle ID you want to update: ";
        cin >> selectedId;

        bool found = false;
        for (auto &vehicle: j) {
            if (vehicle["vehicleId"] == selectedId) {
                string currentStatus;
                cout << "Enter new current status: ";
                cin.ignore();
                getline(cin, currentStatus);
                vehicle["currentStatus"] = currentStatus;

                ofstream outFile("vehicles.json");
                outFile << setw(4) << j << endl;
                outFile.close();

                cout << "Vehicle information updated." << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Vehicle not found." << endl;
        }
    }

    void UpdateVehicleMaintainanceHistory() {
        json j;
        ifstream inFile("vehicles.json");
        if (!inFile) {
            cout << "Error: Cannot open file.\n";
            return;
        }
        inFile >> j;
        inFile.close();

        int selectedId;
        cout << "Enter the Vehicle ID you want to update: ";
        cin >> selectedId;

        bool found = false;
        for (auto &vehicle: j) {
            if (vehicle["vehicleId"] == selectedId) {
                string history;
                cout << "Enter new current history: ";
                cin.ignore();
                getline(cin, history);
                vehicle["MaintenanceHistory"] = history;

                ofstream outFile("vehicles.json");
                outFile << setw(4) << j << endl;
                outFile.close();

                cout << "Vehicle information updated." << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Vehicle not found." << endl;
        }
    }

    bool vehicleExist(int ID) {
        bool found = false;
        json j;

        ifstream file("vehicles.json");
        if (!file.is_open()) {
            cout << "Cannot open file\n";
            return false;
        } else {
            file >> j;
            cout << "Enter vehicle  Id: ";
            cin >> ID;
            for (auto &temp: j) {
                int tempID = temp["vehicleId"];
                if (tempID == ID) {
                    found = true;
                    cout << "found";
                    return true;
                    break;
                }
            }
            if (!found)
                cout << "Id not found\n";
            return false;
        }
    }

    void assignVehicleToOfficer() {
        json j;
        ifstream inFile("vehicles.json");
        if (!inFile) {
            cout << "Error: Cannot open file.\n";
            return;
        }
        inFile >> j;
        inFile.close();

        int selectedId;
        cout << "Enter the Vehicle ID: ";
        cin >> selectedId;

        bool found = false;
        for (auto &vehicle: j) {
            if (vehicle["vehicleId"] == selectedId) {
                int officerID;
                cout << "Enter Officer Id: ";
                cin >> officerID;
                if (vehicle["AvailabilityStatus"] == "True") {
                    vehicle["AvailabilityStatus"] = "False";
                    ofstream outFile("vehicles.json");
                    outFile << setw(4) << j << endl;
                    outFile.close();

                    cout << "Vehicle assigned." << endl;
                    found = true;
                    break;
                } else
                    cout << "Not avaliable\n";
            }
        }
        if (!found) {
            cout << "Vehicle not found." << endl;
        }
    }

    bool operator==(const Vehicle &rhs) const;

    bool operator!=(const Vehicle &rhs) const;

    T getVehicleId() const;

    void setVehicleId(T vehicleId);

    U getMake() const;

    void setMake(U make);

    V getModel() const;

    void setModel(V model);

    W getYear() const;

    void setYear(W year);

    X getColor() const;

    void setColor(X color);

    Y getLicensePlate() const;

    void setLicensePlate(Y licensePlate);

    Z getMileage() const;

    void setMileage(Z mileage);

    AA getFuelType() const;

    void setFuelType(AA fuelType);

    BB getEngineSize() const;

    void setEngineSize(BB engineSize);

    CC getTransmissionType() const;

    void setTransmissionType(CC transmissionType);

    DD getNumSeats() const;

    void setNumSeats(DD numSeats);

    EE getVehicleClass() const;

    void setVehicleClass(EE vehicleClass);

    FF getVehicleType() const;

    void setVehicleType(FF vehicleType);

    GG getCurrentStatus() const;

    void setCurrentStatus(GG currentStatus);

    const string &getMaintenanceHistory() const;

    void setMaintenanceHistory(const string &maintenanceHistory);
};

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
bool Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::operator==(const Vehicle &rhs) const {
    return vehicleId == rhs.vehicleId &&
           make == rhs.make &&
           model == rhs.model &&
           year == rhs.year &&
           color == rhs.color &&
           licensePlate == rhs.licensePlate &&
           mileage == rhs.mileage &&
           fuelType == rhs.fuelType &&
           engineSize == rhs.engineSize &&
           transmissionType == rhs.transmissionType &&
           numSeats == rhs.numSeats &&
           vehicleClass == rhs.vehicleClass &&
           vehicleType == rhs.vehicleType &&
           currentStatus == rhs.currentStatus;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
bool Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::operator!=(const Vehicle &rhs) const {
    return !(rhs == *this);
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
T Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getVehicleId() const {
    return vehicleId;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setVehicleId(T vehicleId) {
    Vehicle::vehicleId = vehicleId;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
U Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getMake() const {
    return make;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
V Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getModel() const {
    return model;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
W Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getYear() const {
    return year;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
X Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getColor() const {
    return color;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
Y Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getLicensePlate() const {
    return licensePlate;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
Z Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getMileage() const {
    return mileage;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
AA Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getFuelType() const {
    return fuelType;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
BB Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getEngineSize() const {
    return engineSize;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
CC Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getTransmissionType() const {
    return transmissionType;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
DD Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getNumSeats() const {
    return numSeats;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
EE Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getVehicleClass() const {
    return vehicleClass;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
FF Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getVehicleType() const {
    return vehicleType;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
GG Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getCurrentStatus() const {
    return currentStatus;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
const string &Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::getMaintenanceHistory() const {
    return MaintenanceHistory;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setMaintenanceHistory(const string &maintenanceHistory) {
    MaintenanceHistory = maintenanceHistory;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setCurrentStatus(GG currentStatus) {
    Vehicle::currentStatus = currentStatus;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setVehicleType(FF vehicleType) {
    Vehicle::vehicleType = vehicleType;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setVehicleClass(EE vehicleClass) {
    Vehicle::vehicleClass = vehicleClass;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setNumSeats(DD numSeats) {
    Vehicle::numSeats = numSeats;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setTransmissionType(CC transmissionType) {
    Vehicle::transmissionType = transmissionType;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setEngineSize(BB engineSize) {
    Vehicle::engineSize = engineSize;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setFuelType(AA fuelType) {
    Vehicle::fuelType = fuelType;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setMileage(Z mileage) {
    Vehicle::mileage = mileage;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setLicensePlate(Y licensePlate) {
    Vehicle::licensePlate = licensePlate;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setColor(X color) {
    Vehicle::color = color;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setYear(W year) {
    Vehicle::year = year;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setModel(V model) {
    Vehicle::model = model;
}

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Z, typename AA, typename BB, typename CC, typename DD, typename EE, typename FF, typename GG>
void Vehicle<T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG>::setMake(U make) {
    Vehicle::make = make;
}

#endif