#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "patient.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

inline void display(const vector<Patient>& patients)
{
    cout << "\n";
    cout << "================================================================================\n";
    cout << left
         << setw(12) << "Patient ID"
         << setw(8)  << "Age"
         << setw(18) << "Care Type"
         << setw(12) << "Stay(hr)"
         << setw(12) << "Cost/hr"
         << setw(12) << "Visits/Year"
         << endl;
    cout << "================================================================================\n";

    for (const Patient& patient : patients)
    {
        cout << left
             << setw(12) << patient.patientID
             << setw(8)  << patient.age
             << setw(18) << patient.careType
             << setw(12) << patient.lengthOfStay
             << setw(12) << fixed << setprecision(2)
             << patient.baseCostPerHour
             << setw(12) << patient.daysVisitsPerYear
             << endl;
    }

    cout << "================================================================================\n";
}

#endif