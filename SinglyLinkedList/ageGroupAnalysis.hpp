#ifndef AGEGROUPANALYSIS_HPP
#define AGEGROUPANALYSIS_HPP

#include "linkedList.hpp"
#include "utils.hpp"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// ==========================================
// PATIENTS BY AGE GROUP
// ==========================================
void ageGroupAnalysis(const LinkedList& list) {

    string ageGroups[20];
    int ageCounts[20] = {}; 

    int ageGroupCount = 0;

    const Node* current = list.getHead();

    while (current != nullptr) {

        string ageGroup = getAgeGroup(current->data.age);

        int position = -1;

        for (int i = 0; i < ageGroupCount; i++) {

            if (ageGroups[i] == ageGroup) {
                position = i;
                break;
            }
        }

        if (position == -1) {

            ageGroups[ageGroupCount] = ageGroup;
            ageCounts[ageGroupCount] = 1;
            ageGroupCount++;
        }
        else {

            ageCounts[position]++;
        }

        current = current->next;
    }

    cout << "\n";
    cout << "================================================================================\n";
    cout << "                         AGE GROUP ANALYSIS\n";
    cout << "================================================================================\n";

    cout << left
         << setw(45) << "Age Group"
         << setw(15) << "Patients"
         << endl;

    cout << "--------------------------------------------------------------------------------\n";

    for (int i = 0; i < ageGroupCount; i++) {

        cout << left
             << setw(45) << ageGroups[i]
             << setw(15) << ageCounts[i]
             << endl;
    }

    cout << "--------------------------------------------------------------------------------\n";

    int totalPatients = 0;
    for (int i = 0; i < ageGroupCount; i++) {
        totalPatients += ageCounts[i];
    }

    cout << left
         << setw(45) << "TOTAL"
         << setw(15) << totalPatients
         << endl;

    cout << "================================================================================\n";
}

#endif