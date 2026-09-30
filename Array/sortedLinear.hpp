#ifndef SORTED_LINEAR_HPP
#define SORTED_LINEAR_HPP

#include <iostream>
#include <chrono>
#include <iomanip>
#include "patient.hpp"
#include "array.hpp"

using namespace std;


inline void displayLinearSearchResult(const Patient& patient)
{
    cout << "Patient ID: " << patient.patientID
         << " | Age: " << patient.age
         << " | Care Type: " << patient.careType
         << " | Length of Stay: " << patient.lengthOfStay
         << "\n";
}

inline void printLinearSearchSummary(
    int count,
    double searchTime,
    const string& description
)
{
    cout << "\n--------------------------------------------------\n";

    if (count == 0)
    {
        cout << "No patient found with " << description << ".\n";
    }
    else
    {
        cout << "Total patients found: " << count << "\n";
    }

    cout << "Linear Search time: "
         << fixed << setprecision(6)
         << searchTime << " ms\n";
}

inline void sortedLinearSearchByAge(
    const DynamicArray<Patient>& patients
)
{
    cout << "\n================================================\n"
         << "                 AGE GROUPS\n"
         << "================================================\n"
         << "1. 0-17   : Pediatrics & Adolescents\n"
         << "2. 18-25  : Young Adults / University Students\n"
         << "3. 26-45  : Working Adults (Early Career)\n"
         << "4. 46-60  : Working Adults (Late Career)\n"
         << "5. 61-100 : Senior Citizens / Geriatric Care\n"
         << "================================================\n"
         << "Enter your choice: ";

    int choice;
    cin >> choice;

    int minimumAge;
    int maximumAge;
    string description;

    switch (choice)
    {
        case 1: minimumAge = 0; maximumAge = 17; description = "age group 0-17"; break;
        case 2: minimumAge = 18; maximumAge = 25; description = "age group 18-25"; break;
        case 3: minimumAge = 26; maximumAge = 45; description = "age group 26-45"; break;
        case 4: minimumAge = 46; maximumAge = 60; description = "age group 46-60"; break;
        case 5: minimumAge = 61; maximumAge = 100; description = "age group 61-100"; break;
        default:
            cout << "\nInvalid choice.\n";
            return;
    }

    auto start = chrono::high_resolution_clock::now();
    int count = 0;

    cout << "\nPatients found:\n";
    cout << "--------------------------------------------------\n";
    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].age >= minimumAge && patients[i].age <= maximumAge)
        {
            displayLinearSearchResult(patients[i]);
            count++;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    double searchTime = chrono::duration<double, milli>(end - start).count();
    printLinearSearchSummary(count, searchTime, description);
}

inline void sortedLinearSearchByCareType(
    const DynamicArray<Patient>& patients
)
{
    cout << "\n================================================\n"
         << "                CARE TYPE\n"
         << "================================================\n"
         << "1. Emergency\n"
         << "2. Inpatient\n"
         << "3. Outpatient\n"
         << "4. Rehabilitation\n"
         << "5. Routine Checkup\n"
         << "6. Vaccination\n"
         << "================================================\n"
         << "Enter your choice: ";

    int choice;
    cin >> choice;

    const string careTypes[] = {
        "Emergency",
        "Inpatient",
        "Outpatient",
        "Rehabilitation",
        "Routine Checkup",
        "Vaccination"
    };

    if (choice < 1 || choice > 6)
    {
        cout << "\nInvalid choice.\n";
        return;
    }

    string target = careTypes[choice - 1];
    auto start = chrono::high_resolution_clock::now();
    int count = 0;

    cout << "\nPatients found:\n";
    cout << "--------------------------------------------------\n";
    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].careType == target)
        {
            displayLinearSearchResult(patients[i]);
            count++;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    double searchTime = chrono::duration<double, milli>(end - start).count();
    printLinearSearchSummary(count, searchTime, "care type \"" + target + "\"");
}

inline void sortedLinearSearchByVisitDuration(
    const DynamicArray<Patient>& patients
)
{
    cout << "\n================================================\n"
         << "       SEARCH BY VISIT DURATION (HOURS)\n"
         << "================================================\n"
         << "1. <20\n"
         << "2. 20 - 60\n"
         << "3. 61-100\n"
         << "4. >101\n"
         << "Choice: ";

    int choice;
    cin >> choice;

    double minimumDuration;
    double maximumDuration;
    string description;

    switch (choice)
    {
        case 1: minimumDuration = 0; maximumDuration = 19.999999; description = "visit duration below 20 hours"; break;
        case 2: minimumDuration = 20; maximumDuration = 60; description = "visit duration 20-60 hours"; break;
        case 3: minimumDuration = 61; maximumDuration = 100; description = "visit duration 61-100 hours"; break;
        case 4: minimumDuration = 101; maximumDuration = 1.0e100; description = "visit duration above 101 hours"; break;
        default:
            cout << "\nInvalid choice.\n";
            return;
    }

    auto start = chrono::high_resolution_clock::now();
    int count = 0;

    cout << "\nPatients found:\n";
    cout << "--------------------------------------------------\n";
    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].lengthOfStay >= minimumDuration &&
            patients[i].lengthOfStay <= maximumDuration)
        {
            displayLinearSearchResult(patients[i]);
            count++;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    double searchTime = chrono::duration<double, milli>(end - start).count();
    printLinearSearchSummary(count, searchTime, description);
}

#endif