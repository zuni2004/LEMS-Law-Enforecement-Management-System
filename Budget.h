//
// Created by InnoSTARK on 4/21/2024.
//

#ifndef INC_2024_SPRING_SE102TA_PROJECT_SE102A_A_BUDGET_H
#define INC_2024_SPRING_SE102TA_PROJECT_SE102A_A_BUDGET_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "json.hpp"

class PoliceStation;

using namespace std;
using json = nlohmann::json;

//C=40000,HC=50000,ASI=60000,SI=70000,IP=100000,SHO=120000,AS=80000
//eg 1 crore allocated to policestation per year.
class Budget {
private:
    static double budgetAllocated;
    static double budgetRemaining;
    static Budget *instance;

    Budget();

public:
    static Budget *getInstance() {
        if (!instance) {
            instance = new Budget();
        }
        return instance;
    }

    static double getBudgetRemaining() {
        return budgetRemaining;
    }

    static void setBudgetRemaining(double remaining) {
        budgetRemaining = remaining;
    }

    static void deductFromBudget(double amount) {
        budgetRemaining -= amount;
        cout << "Price deducted from budget. Remaining budget: " << budgetRemaining << endl;
    }

    static double allocatingSalaries(string rank);
};


#endif //INC_2024_SPRING_SE102TA_PROJECT_SE102A_A_BUDGET_H
