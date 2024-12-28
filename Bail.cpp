//
// Created by InnoSTARK on 4/27/2024.
//
#include "Bail.h"

const string &BailInformation::getConditions() const {
    return conditions;
}

void BailInformation::setConditions(const string &conditions) {
    BailInformation::conditions = conditions;
}

const string &BailInformation::getStatus() const {
    return status;
}

const string &BailInformation::getDateIssued() const {
    return dateIssued;
}

const string &BailInformation::getDatePaid() const {
    return datePaid;
}

const string &BailInformation::getCourt() const {
    return court;
}

void BailInformation::setCourt(const string &court) {
    BailInformation::court = court;
}

void BailInformation::setDatePaid(const string &datePaid) {
    BailInformation::datePaid = datePaid;
}

void BailInformation::setDateIssued(const string &dateIssued) {
    BailInformation::dateIssued = dateIssued;
}

void BailInformation::setStatus(const string &status) {
    BailInformation::status = status;
}

float BailInformation::getAmount() const {
    return amount;
}

ostream &operator<<(ostream &os, const BailInformation &information) {
    os << "amount: " << information.amount << " conditions: " << information.conditions << " status: "
       << information.status << " dateIssued: " << information.dateIssued << " datePaid: " << information.datePaid
       << " court: " << information.court;
    return os;
}

void BailInformation::setAmount(float amount) {
    BailInformation::amount = amount;
}