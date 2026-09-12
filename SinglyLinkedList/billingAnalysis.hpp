#ifndef BILLINGANALYSIS_HPP
#define BILLINGANALYSIS_HPP

#include "linkedList.hpp"
#include "utils.hpp"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// ==========================================
// TOTAL BILLING COST
// ==========================================

inline double getTotalBillingCost(const LinkedList& list) {

    double total = 0;

    const Node* current = list.getHead();

    while (current != nullptr) {

        total += calculateCost(current->data);

        current = current->next;
    }

    return total;
}

inline void displayTotalBillingCost(const LinkedList& list, string facilityName) {

    double total = getTotalBillingCost(list);

    cout << "\n";
    cout << "==============================================\n";
    cout << "        " << facilityName << "\n";
    cout << "        TOTAL MEDICAL BILLING\n";
    cout << "==============================================\n";
    cout << fixed << setprecision(2);
    cout << "Total Patients : " << list.getSize() << endl;
    cout << "Total Cost     : RM " << total << endl;
    cout << "==============================================\n";
}

// ==========================================
// DATASET SUMMARY
// ==========================================

inline void displayDatasetSummary(const LinkedList& list, string facilityName) {

    double totalCost = getTotalBillingCost(list);

    double totalStay = 0;

    const Node* current = list.getHead();

    while (current != nullptr) {

        totalStay += current->data.lengthOfStay;

        current = current->next;
    }

    double averageStay = 0;

    if (list.getSize() > 0) {
        averageStay = totalStay / list.getSize();
    }

    cout << "\n";
    cout << "============================================================\n";
    cout << "              " << facilityName << " SUMMARY\n";
    cout << "============================================================\n";

    cout << fixed << setprecision(2);

    cout << "Number of Patients       : " << list.getSize() << endl;
    cout << "Total Medical Cost       : RM " << totalCost << endl;
    cout << "Total Stay Duration      : " << totalStay << " hours" << endl;
    cout << "Average Stay Duration    : " << averageStay << " hours" << endl;

    cout << "============================================================\n";
}

#endif