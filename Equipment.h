//
// Created by InnoSTARK on 4/6/2024.
//

#ifndef INC_2024_SPRING_SE102TA_PROJECT_SE102A_A_EQUIPMENT_H
#define INC_2024_SPRING_SE102TA_PROJECT_SE102A_A_EQUIPMENT_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "json.hpp"
#include "Budget.h"

using namespace std;
using json = nlohmann::json;

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
class Equipment {
private:
    IDType equipmentID;
    NameType equipmentName;
    QuantityType quantity;
    ModelType model;
    PriceType price;
    AvailabilityType availabilityStatus;
public:
    Equipment();

    Equipment(IDType _equipmentID, NameType _equipmentName, QuantityType _quantity, ModelType _model, PriceType _price,
              AvailabilityType _availabilityStatus);

    IDType getEquipmentID() const;

    NameType getName() const;

    QuantityType getQuantity() const;

    ModelType getModel() const;

    AvailabilityType getAvailabilityStatus();

    void setEquipmentID(IDType id);

    void setName(NameType n);

    void setQuantity(QuantityType q);

    void setModel(ModelType m);

    void setAvailabilityStatus(AvailabilityType s);

    void addEquipment();

    void updateEquipmentCount();

    void viewAllEquipment();

    void searchEquipmentIfAvailable();

    static vector<Equipment>* getEquipmentList();

};

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::Equipment() {
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::Equipment(IDType _equipmentID,
                                                                                             NameType _equipmentName,
                                                                                             QuantityType _quantity,
                                                                                             ModelType _model,
                                                                                             PriceType _price,
                                                                                             AvailabilityType _availabilityStatus)
        : equipmentID(_equipmentID),
          equipmentName(_equipmentName),
          quantity(_quantity),
          model(_model),
          price(_price),
          availabilityStatus(_availabilityStatus) {
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
IDType Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::getEquipmentID() const {
    return equipmentID;
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
NameType Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::getName() const {
    return equipmentName;
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
QuantityType Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::getQuantity() const {
    return quantity;
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
ModelType Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::getModel() const {
    return model;
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
AvailabilityType
Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::getAvailabilityStatus() {
    return availabilityStatus;
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
void Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::setEquipmentID(IDType id) {
    equipmentID = id;
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
void Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::setName(NameType n) {
    equipmentName = n;
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
void Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::setQuantity(QuantityType q) {
    quantity = q;
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
void Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::setModel(ModelType m) {
    model = m;
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
void Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::setAvailabilityStatus(
        AvailabilityType s) {
    availabilityStatus = s;
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
void Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::addEquipment() {

    json equipmentArray;
    ifstream equipmentFile("Equipment.json");
    if (equipmentFile.is_open()) {
        equipmentFile >> equipmentArray;
        equipmentFile.close();
    } else {
        cout << "Failed to open Equipment.json" << endl;
        return;
    }

    cout << "Enter equipment name: ";
    cin.ignore();
    getline(cin, equipmentName);
    cout << "Enter quantity: ";
    cin >> quantity;
    cin.ignore();
    cout << "Enter Model: ";
    getline(cin, model);
    availabilityStatus = true;
    cout << "Enter the price of the equipment: ";
    cin >> price;

    json newEquipment;
    for (int i = 0; i < quantity; i++) {
        int maxID = 0;
        for (const auto &entry: equipmentArray) {
            int id = entry["Equipment ID"];
            if (id > maxID) {
                maxID = id;
            }
        }
        equipmentID = maxID + 1;
        newEquipment["Equipment ID"] = equipmentID;
        newEquipment["Name"] = equipmentName;
        newEquipment["Model"] = model;
        newEquipment["AvailabilityStatus"] = availabilityStatus;
        equipmentArray.push_back(newEquipment);

        double remainingBudget = Budget::getInstance()->getBudgetRemaining();
        if (remainingBudget >= price) {
            Budget::getInstance()->deductFromBudget(price);
        } else {
            cout << "Insufficient budget to add the Equipment." << endl;
        }

        ofstream equipmentFileUpdate("Equipment.json");
        equipmentFileUpdate << setw(4) << equipmentArray << endl;
        equipmentFileUpdate.close();
    }
    cout << "Size:" << equipmentArray.size() << endl;
    cout << "Equipment Added Successfully\n";
    updateEquipmentCount();
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
void Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::updateEquipmentCount() {
    json equipmentCountArray;
    ifstream equipmentCountFile("EquipmentCount.json");
    if (equipmentCountFile.is_open()) {
        equipmentCountFile >> equipmentCountArray;
        equipmentCountFile.close();
    } else {
        cout << "Failed to open EquipmentCount.json" << endl;
        return;
    }

    bool found = false;
    for (auto &entry: equipmentCountArray) {
        if (entry["Name"] == equipmentName && entry["Model"] == model) {
            entry["Quantity"] = entry["Quantity"].get<int>() + quantity;
            found = true;
            break;
        }
    }

    if (!found) {
        json newEquipmentCount;
        newEquipmentCount["Name"] = equipmentName;
        newEquipmentCount["Quantity"] = quantity;
        newEquipmentCount["Model"] = model;
        equipmentCountArray.push_back(newEquipmentCount);
    }

    ofstream equipmentCountFileUpdate("EquipmentCount.json");
    if (equipmentCountFileUpdate.is_open()) {
        equipmentCountFileUpdate << setw(4) << equipmentCountArray << endl;
        equipmentCountFileUpdate.close();
    } else {
        cout << "Failed to update EquipmentCount.json" << endl;
    }
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
void Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::viewAllEquipment() {

    json Equipments;
    ifstream equipment("EquipmentCount.json");
    if (equipment.is_open()) {
        equipment >> Equipments;
        cout << setw(4) << Equipments << endl;
        equipment.close();
    } else {
        cout << "EquipmentCount.json not opened\n";
    }
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
vector<Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>> *
Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::getEquipmentList() {
    static vector<Equipment> equipmentList;
    return &equipmentList;
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
void Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType>::searchEquipmentIfAvailable() {
    int enteredID;
    cout << "Enter ID you want to check if is available: ";
    cin >> enteredID;
    ifstream findingEquipment("Equipment.json");
    if (findingEquipment.is_open()) {
        json find;
        findingEquipment >> find;
        findingEquipment.close();
        bool found = false;
        for (auto &entry: find) {
            if (entry["Equipment ID"] == enteredID) {
                cout << "Equipment found\nAvailability Status: " << entry["AvailabilityStatus"] << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Equipment not found." << endl;
        }
    } else {
        cout << "File not opened." << endl;
    }
}

template<typename IDType, typename NameType, typename QuantityType, typename ModelType, typename PriceType, typename AvailabilityType>
ostream &operator<<(ostream &os, const Equipment<IDType, NameType, QuantityType, ModelType, PriceType, AvailabilityType> &equipment) {
    os << "Equipment ID: " << equipment.getEquipmentID() << "\n"
       << "Name: " << equipment.getName() << "\n"
       << "Quantity: " << equipment.getQuantity() << "\n"
       << "Model: " << equipment.getModel() << "\n"
       << "Price: " << equipment.getPrice() << "\n"
       << "Availability Status: " << equipment.getAvailabilityStatus() << "\n";
    return os;
}

#endif // INC_2024_SPRING_SE102TA_PROJECT_SE102A_A_EQUIPMENT_H
