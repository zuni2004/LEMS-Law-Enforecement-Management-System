//
// Created by HP on 4/28/2024.
//

#ifndef PEACE_PERSON_H
#define PEACE_PERSON_H

#include <iostream>
#include <vector>
#include "Investigation.h"

using namespace std;

class Person {
    string id;
    string name;
    string dateOfBirth;
    string address;
    string occupation;
    string nationality;
    vector<string> phoneNumbers;
    vector<string> emailAddresses;
    string notes;
public:
    Person() {

    }

    friend bool operator==(const Person &person1, const Person &person2);

    friend class Investigation;

    friend istream &operator>>(istream &input, Person &person);

    friend ostream &operator<<(ostream &output, const Person &person);
};

#endif //PEACE_PERSON_H
