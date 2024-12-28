//
// Created by InnoSTARK on 4/21/2024.
//
#include "PoliceStation.h"
#include "Budget.h"


Budget *Budget::instance = nullptr;

Budget::Budget() {

}

double Budget::allocatingSalaries(string rank) {
    double salary = 0.0;
    if (rank == "Constable") {
        salary = 40000;
    } else if (rank == "Head Constable") {
        salary = 50000;
    } else if (rank == "ASI") {
        salary = 60000;
    } else if (rank == "SI") {
        salary = 70000;
    } else if (rank == "IP") {
        salary = 100000;
    } else if (rank == "CO") {
        salary = 80000;
    } else if (rank == "DNA analyst") {
        salary = 100000;
    } else if (rank == "Toxicologist") {
        salary = 100000;
    } else if (rank == "Anthropologist") {
        salary = 120000;
    } else if (rank == "Document Examiner") {
        salary = 140000;
    } else if (rank == "Pathologist") {
        salary = 100000;
    } else if (rank == "Digital Analyst") {
        salary = 130000;
    } else if (rank == "AS") {
        salary = 120000;
    } else if (rank == "SHO") {
        salary = 200000;
    } else {
        cout << "No such rank exists" << endl;
    }
    double remainingBudget = Budget::getBudgetRemaining();
    if (remainingBudget >= salary) {
        budgetRemaining -= salary;
        cout << "Salary allocated successfully for " << rank << endl;
        cout << "Remaining budget: " << budgetRemaining << endl;
        return salary;
    } else {
        cout << "Insufficient budget to allocate salary for " << rank << endl;
        cout << "Allocating Budget by Police Station\n";
        return 0;
    }
    return remainingBudget;
}







double Budget::budgetAllocated = 10000000;

double Budget::budgetRemaining = 1000000;