//
// Created by InnoSTARK on 5/5/2024.
//

#ifndef FULLY_COMPILATION_ASSISTENTSUPERINTENDENT_H
#define FULLY_COMPILATION_ASSISTENTSUPERINTENDENT_H


#include "Budget.h"
#include "officer.h"

class AssistentSuperIntendent : public officer<int> {
private:
    double allocatedBudget;
public:
    AssistentSuperIntendent() {}

    AssistentSuperIntendent(const int &_rank, const string &_officerID = "", const string &_name = "",
                            int _badgeNumber = 0) : officer(_rank, _officerID, _name, _badgeNumber) {}

    void displayInfo() {}
//    void allocateBudget() {
//        Budget *budgetInstance = Budget::getInstance();
//        double remainingBudget = budgetInstance->getBudgetRemaining();
//        double amountToAllocate = 1000000;
//
//        if (amountToAllocate <= remainingBudget) {
//            allocatedBudget += amountToAllocate;
//            budgetInstance->setBudgetRemaining(remainingBudget - amountToAllocate);
//        } else {
//            cout << "Insufficient budget remaining to allocate" << endl;
//        }
//    }
};


#endif //FULLY_COMPILATION_ASSISTENTSUPERINTENDENT_H
