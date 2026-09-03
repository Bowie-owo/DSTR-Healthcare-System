#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
using namespace std;

struct Patient {
    string patientID;
    int age;
    string careType;
    double lengthOfStay;
    double baseCostPerHour;
    int daysVisitsPerYear;
};

#endif