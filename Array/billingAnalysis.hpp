#ifndef BILLING_ANALYSIS_HPP
#define BILLING_ANALYSIS_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "patient.hpp"

using namespace std;

void billingAnalysis(const vector<Patient>& patients,
                     const string& facilityName)
{
    int numberOfPatients = patients.size();

    // Array to store billing cost for each patient
    double* billingCost = new double[numberOfPatients];

    double totalCost = 0;

    // Calculate billing cost for each patient
    for (int i = 0; i < numberOfPatients; i++)
    {
        billingCost[i] =
            patients[i].lengthOfStay *
            patients[i].baseCostPerHour;

        totalCost += billingCost[i];
    }

    cout << "\n==============================================\n";
    cout << "        " << facilityName << "\n";
    cout << "        TOTAL MEDICAL BILLING\n";
    cout << "==============================================\n";

    cout << fixed << setprecision(2);

    cout << "Total Patients : " << numberOfPatients << endl;
    cout << "Total Cost     : RM " << totalCost << endl;

    cout << "==============================================\n";

    delete[] billingCost;
}

#endif