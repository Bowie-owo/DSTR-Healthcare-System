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
    double averageCost = 0;
    const Node* current = list.getHead();
    int ageCounts[5] = {};
    int outOfRangeAges = 0;

    while (current != nullptr) {
        int age = current->data.age;
        if (age >= 0 && age <= 17) ageCounts[0]++;
        else if (age >= 18 && age <= 25) ageCounts[1]++;
        else if (age >= 26 && age <= 45) ageCounts[2]++;
        else if (age >= 46 && age <= 60) ageCounts[3]++;
        else if (age >= 61 && age <= 100) ageCounts[4]++;
        else outOfRangeAges++;

        totalStay += current->data.lengthOfStay;
        current = current->next;
    }

    if (list.getSize() > 0) {
        averageCost = totalCost / list.getSize();
    }

    const string ageGroupNames[5] = {
        "Pediatrics & Adolescents",
        "Young Adults / University Students",
        "Working Adults (Early Career)",
        "Working Adults (Late Career)",
        "Senior Citizens / Geriatric Care"
    };
    const string line(80, '=');

    cout << "\n" << line << "\n";
    cout << "                   DATASET SUMMARY - " << facilityName << "\n";
    cout << line << "\n";
    cout << left << setw(28) << "Total Patients" << ": " << list.getSize() << "\n";
    cout << left << setw(28) << "Total Stay Hours" << ": "
         << defaultfloat << setprecision(6) << totalStay << " hrs\n";
    cout << left << setw(28) << "Total Medical Cost" << ": RM "
         << fixed << setprecision(2) << totalCost << "\n";
    cout << left << setw(28) << "Average Cost Per Patient" << ": RM "
         << fixed << setprecision(2) << averageCost << "\n";
    cout << left << setw(28) << "Average Stay Duration" << ": "
         << defaultfloat << setprecision(6)
         << (list.getSize() > 0 ? totalStay / list.getSize() : 0.0) << " hrs\n";

    cout << "\nAge Groups Present:\n";
    bool anyAgeGroup = false;
    for (int i = 0; i < 5; i++) {
        if (ageCounts[i] > 0) {
            cout << "  - " << left << setw(38) << ageGroupNames[i]
                 << ageCounts[i] << " patients\n";
            anyAgeGroup = true;
        }
    }
    if (outOfRangeAges > 0) {
        cout << "  - " << left << setw(38) << "Unknown / Out of range"
             << outOfRangeAges << " patients\n";
        anyAgeGroup = true;
    }
    if (!anyAgeGroup) cout << "  (none)\n";

    cout << "\nCare Types Available:\n";
    bool anyCareType = false;
    for (const Node* first = list.getHead(); first != nullptr; first = first->next) {
        bool seenBefore = false;
        for (const Node* previous = list.getHead(); previous != first; previous = previous->next) {
            if (previous->data.careType == first->data.careType) {
                seenBefore = true;
                break;
            }
        }
        if (seenBefore) continue;

        int careTypeCount = 0;
        for (const Node* currentCare = first; currentCare != nullptr; currentCare = currentCare->next) {
            if (currentCare->data.careType == first->data.careType) {
                careTypeCount++;
            }
        }
        cout << "  - " << left << setw(38) << first->data.careType
             << careTypeCount << " patients\n";
        anyCareType = true;
    }
    if (!anyCareType) cout << "  (none)\n";

    cout << line << "\n";
}

#endif