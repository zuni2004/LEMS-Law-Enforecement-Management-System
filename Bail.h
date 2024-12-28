#ifndef BAIL_H
#define BAIL_H

#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Criminal;

class BailInformation {
private:
    float amount;
    string conditions;
    string status;
    string dateIssued;
    string datePaid;
    string court;
public:
    BailInformation() : amount(0.0), conditions(""), status(""), dateIssued(""), datePaid(""), court("") {}

    BailInformation(float amt, const string &cond, const string &stat, const string &issued, const string &paid,
                    const string &crt)


            : amount(amt), conditions(cond), status(stat), dateIssued(issued), datePaid(paid), court(crt) {}

    const string &getConditions() const;

    void setConditions(const string &conditions);

    const string &getStatus() const;

    void setStatus(const string &status);

    const string &getDateIssued() const;

    void setDateIssued(const string &dateIssued);

    float getAmount() const;

    void setAmount(float amount);

    const string &getDatePaid() const;

    void setDatePaid(const string &datePaid);

    const string &getCourt() const;

    void setCourt(const string &court);

    friend ostream &operator<<(ostream &os, const BailInformation &information);
};

#endif