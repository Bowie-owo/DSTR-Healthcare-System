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

inline void careTypeAnalysis(const LinkedList& list) {

    string careTypes[20];
    double careCosts[20];
    int careCounts[20];
    double careDuration[20];

    int careTypeCount = 0;

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

        if (position == -1) {

            careTypes[careTypeCount] = care;
            careCosts[careTypeCount] = cost;
            careCounts[careTypeCount] = 1;
            careDuration[careTypeCount] = current->data.lengthOfStay;

            careTypeCount++;
        }
        else {

            careCosts[position] += cost;
            careCounts[position]++;
            careDuration[position] += current->data.lengthOfStay;
        }

        current = current->next;
    }

    cout << "\n";
    cout << "================================================================================\n";
    cout << "                         CARE TYPE ANALYSIS\n";
    cout << "================================================================================\n";

    cout << left
         << setw(20) << "Care Type"
         << setw(15) << "Patients"
         << setw(20) << "Total Cost"
         << setw(20) << "Total Stay Hours"
         << endl;

    cout << "--------------------------------------------------------------------------------\n";

    for (int i = 0; i < careTypeCount; i++) {

        cout << left
             << setw(20) << careTypes[i]
             << setw(15) << careCounts[i]
             << setw(20) << fixed << setprecision(2)
             << careCosts[i]
             << setw(20) << careDuration[i]
             << endl;
    }

    cout << "================================================================================\n";
}

#endif