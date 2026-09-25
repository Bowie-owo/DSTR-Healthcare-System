#ifndef LIST_LINEARSEARCH_HPP
#define LIST_LINEARSEARCH_HPP

#include "linkedList.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

using namespace std;


// ================================================================
// DISPLAY SEARCH RESULT
// ================================================================

inline void displayLinearSearchHeader()
{
    cout << "\n";
    cout << "==========================================================================\n";
    cout << left
         << setw(12) << "Patient ID"
         << setw(8)  << "Age"
         << setw(22) << "Care Type"
         << setw(12) << "Stay(hr)"
         << setw(12) << "Cost/hr"
         << setw(12) << "Visits/Year"
         << "\n";
    cout << "--------------------------------------------------------------------------\n";
}


// ================================================================
// DISPLAY ONE PATIENT
// ================================================================

inline void displayLinearSearchPatient(const Node* patient)
{
    cout << left
         << setw(12) << patient->data.patientID
         << setw(8)  << patient->data.age
         << setw(22) << patient->data.careType
         << setw(12) << fixed << setprecision(2)
         << patient->data.lengthOfStay
         << setw(12) << patient->data.baseCostPerHour
         << setw(12) << patient->data.daysVisitsPerYear
         << "\n";
}


// ================================================================
// LINEAR SEARCH BY AGE GROUP
// ================================================================

inline int linearSearchByAgeGroup(const LinkedList& list,
                                  int minimumAge,
                                  int maximumAge)
{
    int matches = 0;

    const Node* current = list.getHead();

    while (current != nullptr)
    {
        int age = current->data.age;

        if (age >= minimumAge && age <= maximumAge)
        {
            if (matches == 0)
            {
                displayLinearSearchHeader();
            }

            displayLinearSearchPatient(current);
            matches++;
        }

        current = current->next;
    }

    return matches;
}


// ================================================================
// LINEAR SEARCH BY CARE TYPE
// ================================================================

inline int linearSearchByCareType(const LinkedList& list,
                                  const string& careType)
{
    int matches = 0;

    const Node* current = list.getHead();

    while (current != nullptr)
    {
        if (current->data.careType == careType)
        {
            if (matches == 0)
            {
                displayLinearSearchHeader();
            }

            displayLinearSearchPatient(current);
            matches++;
        }

        current = current->next;
    }

    return matches;
}


// ================================================================
// LINEAR SEARCH BY VISITS PER YEAR
// ================================================================

inline int linearSearchByVisitsPerYear(const LinkedList& list,
                                       int visitsPerYear)
{
    int matches = 0;

    const Node* current = list.getHead();

    while (current != nullptr)
    {
        if (current->data.daysVisitsPerYear == visitsPerYear)
        {
            if (matches == 0)
            {
                displayLinearSearchHeader();
            }

            displayLinearSearchPatient(current);
            matches++;
        }

        current = current->next;
    }

    return matches;
}


// ================================================================
// AGE GROUP MENU
// ================================================================

inline int linearSearchAgeGroupMenu(const LinkedList& list)
{
    cout << "\n";
    cout << "Age groups:\n";
    cout << "1. 0-17: Pediatrics & Adolescents\n";
    cout << "2. 18-25: Young Adults / University Students\n";
    cout << "3. 26-45: Working Adults (Early Career)\n";
    cout << "4. 46-60: Working Adults (Late Career)\n";
    cout << "5. 61-100: Senior Citizens / Geriatric Care\n";
    cout << "Enter your choice: ";

    int groupChoice;
    cin >> groupChoice;

    const int minimumAges[] = {0, 18, 26, 46, 61};
    const int maximumAges[] = {17, 25, 45, 60, 100};

    if (groupChoice < 1 || groupChoice > 5)
    {
        cout << "\nInvalid age group.\n";
        return -1;
    }

    return linearSearchByAgeGroup(
        list,
        minimumAges[groupChoice - 1],
        maximumAges[groupChoice - 1]
    );
}


// ================================================================
// CARE TYPE MENU
// ================================================================

inline int linearSearchCareTypeMenu(const LinkedList& list)
{
    cout << "\n";
    cout << "Care types:\n";
    cout << "1. Emergency\n";
    cout << "2. Inpatient\n";
    cout << "3. Outpatient\n";
    cout << "4. Rehabilitation\n";
    cout << "5. Routine Checkup\n";
    cout << "6. Vaccination\n";
    cout << "Enter your choice: ";

    int careChoice;
    cin >> careChoice;

    const string careTypes[] =
    {
        "Emergency",
        "Inpatient",
        "Outpatient",
        "Rehabilitation",
        "Routine Checkup",
        "Vaccination"
    };

    if (careChoice < 1 || careChoice > 6)
    {
        cout << "\nInvalid care type.\n";
        return -1;
    }

    return linearSearchByCareType(
        list,
        careTypes[careChoice - 1]
    );
}


// ================================================================
// VISITS PER YEAR MENU
// ================================================================

inline int linearSearchVisitsMenu(const LinkedList& list)
{
    cout << "\n";
    cout << "Enter number of visits per year: ";

    int visitsPerYear;
    cin >> visitsPerYear;

    if (visitsPerYear < 0)
    {
        cout << "\nInvalid number of visits.\n";
        return -1;
    }

    return linearSearchByVisitsPerYear(
        list,
        visitsPerYear
    );
}


// ================================================================
// SEARCH FIELD MENU
// ================================================================

inline void linearSearchFieldMenu(const LinkedList& list)
{
    while (true)
    {
        cout << "\n";
        cout << "Search by which field?\n";
        cout << "1. Age Group\n";
        cout << "2. Care Type\n";
        cout << "3. Search by Visit Duration / Visits Per Year\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";

        int searchField;
        cin >> searchField;

        if (searchField == 4)
        {
            return;
        }

        if (searchField < 1 || searchField > 4)
        {
            cout << "\nInvalid choice.\n";
            continue;
        }

        int matches = 0;

        // Start timing only when the actual search begins
        auto searchStart = chrono::high_resolution_clock::now();

        if (searchField == 1)
        {
            matches = linearSearchAgeGroupMenu(list);
        }
        else if (searchField == 2)
        {
            matches = linearSearchCareTypeMenu(list);
        }
        else if (searchField == 3)
        {
            matches = linearSearchVisitsMenu(list);
        }

        auto searchEnd = chrono::high_resolution_clock::now();

        // If invalid input was returned from a search menu
        if (matches == -1)
        {
            continue;
        }

        double searchMs =
            chrono::duration<double, milli>(
                searchEnd - searchStart
            ).count();

        cout << "\n";

        if (matches == 0)
        {
            cout << "No matching patient(s) found.\n";
        }
        else
        {
            cout << "==========================================================================\n";
            cout << "Linear search found "
                 << matches
                 << " matching patient(s).\n";
        }

        cout << "Search time: "
             << fixed << setprecision(6)
             << searchMs
             << " ms"
             << "  (n = "
             << list.getSize()
             << ")\n";
    }
}


// ================================================================
// MAIN LINEAR SEARCH MENU
// ================================================================

inline void linearSearchMenu(
    LinkedList& facilityA,
    LinkedList& facilityB,
    LinkedList& facilityC,
    LinkedList& combined,
    bool facilityALoaded,
    bool facilityBLoaded,
    bool facilityCLoaded)
{
    cout << "\n";
    cout << "================================================\n";
    cout << "              LINEAR SEARCH\n";
    cout << "       SINGLY LINKED LIST IMPLEMENTATION\n";
    cout << "================================================\n";

    if (!facilityALoaded &&
        !facilityBLoaded &&
        !facilityCLoaded)
    {
        cout << "\nPlease load a dataset first.\n";
        return;
    }

    while (true)
    {
        cout << "\n";
        cout << "Which dataset would you like to search?\n";
        cout << "1. Facility A\n";
        cout << "2. Facility B\n";
        cout << "3. Facility C\n";
        cout << "4. Combined (All Facilities)\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter your choice: ";

        int searchChoice;
        cin >> searchChoice;

        LinkedList* target = nullptr;

        if (searchChoice == 1)
        {
            if (!facilityALoaded)
            {
                cout << "\nFacility A is not loaded yet.\n";
                continue;
            }

            target = &facilityA;
        }
        else if (searchChoice == 2)
        {
            if (!facilityBLoaded)
            {
                cout << "\nFacility B is not loaded yet.\n";
                continue;
            }

            target = &facilityB;
        }
        else if (searchChoice == 3)
        {
            if (!facilityCLoaded)
            {
                cout << "\nFacility C is not loaded yet.\n";
                continue;
            }

            target = &facilityC;
        }
        else if (searchChoice == 4)
        {
            // Rebuild combined dataset
            combined.clear();

            if (facilityALoaded)
            {
                combined.appendAll(facilityA);
            }

            if (facilityBLoaded)
            {
                combined.appendAll(facilityB);
            }

            if (facilityCLoaded)
            {
                combined.appendAll(facilityC);
            }

            target = &combined;
        }
        else if (searchChoice == 5)
        {
            return;
        }
        else
        {
            cout << "\nInvalid choice.\n";
            continue;
        }

        linearSearchFieldMenu(*target);
    }
}


#endif