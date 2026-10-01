#ifndef CARETYPEANALYSIS_HPP
#define CARETYPEANALYSIS_HPP

#include "linkedList.hpp"
#include "utils.hpp"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// ==========================================
// COST BY CARE TYPE
// ==========================================

inline void careTypeAnalysis(const LinkedList& list, const string& facilityName) {

    string careTypes[20];
    double careCosts[20];
    int careCounts[20];
    double careDuration[20];
    double hourlyCosts[20];

    int careTypeCount = 0;
    double totalBilling = 0;
    double totalStayHours = 0;
    bool showHourlyCost = facilityName != "ALL FACILITIES";

    const Node* current = list.getHead();

    while (current != nullptr) {

        string care = current->data.careType;

        int position = -1;

        for (int i = 0; i < careTypeCount; i++) {

            if (careTypes[i] == care) {
                position = i;
                break;
            }
        }

        double cost = calculateCost(current->data);
        totalBilling += cost;
        totalStayHours += current->data.lengthOfStay;

        if (position == -1) {

            careTypes[careTypeCount] = care;
            careCosts[careTypeCount] = cost;
            careCounts[careTypeCount] = 1;
            careDuration[careTypeCount] = current->data.lengthOfStay;
            hourlyCosts[careTypeCount] = current->data.baseCostPerHour;

            careTypeCount++;
        }
        else {

            careCosts[position] += cost;
            careCounts[position]++;
            careDuration[position] += current->data.lengthOfStay;
        }

        current = current->next;
    }

        cout << "\n" << facilityName << "\n\n";
        cout << "=====================================================================================================================================\n";
        cout << "                                                        CARE TYPE ANALYSIS\n";
        cout << "=====================================================================================================================================\n";

        if (list.getSize() == 0) {
           cout << "No patient data available.\n";
           cout << "=====================================================================================================================================\n";
           return;
        }

        cout << fixed << setprecision(2);
    cout << left
         << setw(20) << "Care Type"
            << setw(20) << "Total Patients"
            << setw(20) << "Total Stay Hours";

        if (showHourlyCost) {
           cout << setw(20) << "Cost/hr (RM)";
        }

        cout << setw(20) << "Total Cost (RM)"
            << setw(20) << "Average Cost Per Patient (RM)"
            << endl;

        cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < careTypeCount; i++) {
           double averageCost = careCosts[i] / careCounts[i];

        cout << left
             << setw(20) << careTypes[i]
               << setw(20) << careCounts[i]
               << setw(20) << setprecision(0) << careDuration[i];

           cout << setprecision(2);
           if (showHourlyCost) {
              cout << setw(20) << hourlyCosts[i];
           }

           cout << setw(20) << careCosts[i]
               << setw(20) << averageCost
               << endl;
    }

        cout << "=====================================================================================================================================\n";
        cout << "                                                        FACILITY SUMMARY\n";
        cout << "=====================================================================================================================================\n";
    cout << fixed << setprecision(2);
        cout << left << setw(30) << "Total Patients" << ": " << list.getSize() << endl;
        cout << left << setw(30) << "Total Stay Hours" << setprecision(0)
            << ": " << totalStayHours << " hours" << endl;
        cout << left << setw(30) << "Total Billing Cost (RM)" << setprecision(2)
            << ": RM " << totalBilling << endl;
        cout << left << setw(30) << "Average Cost Per Patient (RM)" << setprecision(2)
            << ": RM " << totalBilling / list.getSize() << endl;
        cout << "=====================================================================================================================================\n";
}

#endif