#ifndef LENGTH_OF_STAY_ANALYSIS_HPP
#define LENGTH_OF_STAY_ANALYSIS_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "patient.hpp"

using namespace std;

void lengthOfStayAnalysis(const vector<Patient>& patients,
                          const string& facilityName)
{
    cout << "\n" << facilityName << "\n\n";

    cout << "================================================================================\n";
    cout << "                       LENGTH OF STAY ANALYSIS\n";
    cout << "================================================================================\n";

    if (patients.empty())
    {
        cout << "No patient data available.\n";
        cout << "================================================================================\n";
        return;
    }

    double totalStay = 0.0;
    double minimumStay = patients[0].lengthOfStay;
    double maximumStay = patients[0].lengthOfStay;

    // Calculate total, minimum and maximum
    for (const Patient& patient : patients)
    {
        totalStay += patient.lengthOfStay;

        if (patient.lengthOfStay < minimumStay)
        {
            minimumStay = patient.lengthOfStay;
        }

        if (patient.lengthOfStay > maximumStay)
        {
            maximumStay = patient.lengthOfStay;
        }
    }

    // Calculate average
    double averageStay = totalStay / patients.size();

    cout << fixed << setprecision(2);

    cout << left
         << setw(45) << "Measurement"
         << setw(20) << "Value"
         << endl;

    cout << "--------------------------------------------------------------------------------\n";

    cout << left
         << setw(45) << "Total Patients"
         << setw(20) << patients.size()
         << endl;

    cout << left
         << setw(45) << "Total Length of Stay (hours)"
         << setw(20) << totalStay
         << endl;

    cout << left
         << setw(45) << "Average Length of Stay (hours)"
         << setw(20) << averageStay
         << endl;

    cout << left
         << setw(45) << "Minimum Length of Stay (hours)"
         << setw(20) << minimumStay
         << endl;

    cout << left
         << setw(45) << "Maximum Length of Stay (hours)"
         << setw(20) << maximumStay
         << endl;

    cout << "================================================================================\n";
}

#endif