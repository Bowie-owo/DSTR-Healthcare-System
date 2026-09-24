#ifndef LINEAR_SEARCH_HPP
#define LINEAR_SEARCH_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <chrono>

#include "patient.hpp"

using namespace std;


// ================================================================
// DISPLAY PATIENT RECORD
// ================================================================

void displaySearchResult(const Patient& patient)
{
    cout << left
         << setw(12) << patient.patientID
         << setw(8)  << patient.age
         << setw(22) << patient.careType
         << setw(18) << fixed << setprecision(2) << patient.lengthOfStay
         << setw(18) << patient.baseCostPerHour
         << setw(15) << patient.daysVisitsPerYear
         << endl;
}


// ================================================================
// DISPLAY TABLE HEADER
// ================================================================

void displaySearchHeader()
{
    cout << "\n";

    cout << left
         << setw(12) << "Patient ID"
         << setw(8)  << "Age"
         << setw(22) << "Care Type"
         << setw(18) << "Visit Duration"
         << setw(18) << "Cost/Hour"
         << setw(15) << "Visits/Year"
         << endl;

    cout << string(93, '-') << endl;
}


// ================================================================
// LINEAR SEARCH BY AGE GROUP
// ================================================================

void searchByAgeGroup(const vector<Patient>& patients)
{
    int choice;

    cout << "\n";
    cout << "================================================\n";
    cout << "                 AGE GROUPS\n";
    cout << "================================================\n";
    cout << "1. 0-17   : Pediatrics & Adolescents\n";
    cout << "2. 18-25  : Young Adults / University Students\n";
    cout << "3. 26-45  : Working Adults (Early Career)\n";
    cout << "4. 46-60  : Working Adults (Late Career)\n";
    cout << "5. 61-100 : Senior Citizens / Geriatric Care\n";
    cout << "================================================\n";
    cout << "Enter your choice: ";
    cin >> choice;


    // ------------------------------------------------------------
    // SET AGE RANGE
    // ------------------------------------------------------------

    int minimumAge;
    int maximumAge;
    string ageGroupName;


    switch (choice)
    {
        case 1:
            minimumAge = 0;
            maximumAge = 17;
            ageGroupName = "Pediatrics & Adolescents";
            break;

        case 2:
            minimumAge = 18;
            maximumAge = 25;
            ageGroupName = "Young Adults / University Students";
            break;

        case 3:
            minimumAge = 26;
            maximumAge = 45;
            ageGroupName = "Working Adults (Early Career)";
            break;

        case 4:
            minimumAge = 46;
            maximumAge = 60;
            ageGroupName = "Working Adults (Late Career)";
            break;

        case 5:
            minimumAge = 61;
            maximumAge = 100;
            ageGroupName = "Senior Citizens / Geriatric Care";
            break;

        default:
            cout << "\nInvalid choice.\n";
            return;
    }


    // ------------------------------------------------------------
    // START LINEAR SEARCH TIMER
    // ------------------------------------------------------------

    auto start = chrono::high_resolution_clock::now();


    int foundCount = 0;


    // ------------------------------------------------------------
    // LINEAR SEARCH
    // ------------------------------------------------------------

    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].age >= minimumAge &&
            patients[i].age <= maximumAge)
        {
            foundCount++;
        }
    }


    // ------------------------------------------------------------
    // END SEARCH TIMER
    // ------------------------------------------------------------

    auto end = chrono::high_resolution_clock::now();


    double searchTime =
        chrono::duration<double, milli>(end - start).count();


    // ------------------------------------------------------------
    // DISPLAY RESULT
    // ------------------------------------------------------------

    cout << "\n";
    cout << "================================================\n";
    cout << "             LINEAR SEARCH RESULT\n";
    cout << "================================================\n";

    cout << "Search Field : Age Group\n";
    cout << "Category     : " << ageGroupName << endl;
    cout << "Age Range    : " << minimumAge
         << " - " << maximumAge << endl;


    if (foundCount > 0)
    {
        cout << "\n";

        displaySearchHeader();


        // --------------------------------------------------------
        // SEARCH AGAIN TO DISPLAY MATCHING RECORDS
        // --------------------------------------------------------

        for (int i = 0; i < patients.size(); i++)
        {
            if (patients[i].age >= minimumAge &&
                patients[i].age <= maximumAge)
            {
                displaySearchResult(patients[i]);
            }
        }
    }
    else
    {
        cout << "\nNo matching patients found.\n";
    }


    cout << "\n";
    cout << "------------------------------------------------\n";
    cout << "Linear search found "
         << foundCount
         << " matching patient(s).\n";

    cout << "Search time: "
         << fixed << setprecision(3)
         << searchTime
         << " ms\n";

    cout << "------------------------------------------------\n";
}


// ================================================================
// LINEAR SEARCH BY CARE TYPE
// ================================================================

void searchByCareType(const vector<Patient>& patients)
{
    int choice;

    cout << "\n";
    cout << "================================================\n";
    cout << "                CARE TYPE\n";
    cout << "================================================\n";
    cout << "1. Emergency\n";
    cout << "2. Inpatient\n";
    cout << "3. Outpatient\n";
    cout << "4. Rehabilitation\n";
    cout << "5. Routine Checkup\n";
    cout << "6. Vaccination\n";
    cout << "================================================\n";
    cout << "Enter your choice: ";
    cin >> choice;


    string targetCareType;


    // ------------------------------------------------------------
    // SELECT CARE TYPE
    // ------------------------------------------------------------

    switch (choice)
    {
        case 1:
            targetCareType = "Emergency";
            break;

        case 2:
            targetCareType = "Inpatient";
            break;

        case 3:
            targetCareType = "Outpatient";
            break;

        case 4:
            targetCareType = "Rehabilitation";
            break;

        case 5:
            targetCareType = "Routine Checkup";
            break;

        case 6:
            targetCareType = "Vaccination";
            break;

        default:
            cout << "\nInvalid choice.\n";
            return;
    }


    // ------------------------------------------------------------
    // START LINEAR SEARCH TIMER
    // ------------------------------------------------------------

    auto start = chrono::high_resolution_clock::now();


    int foundCount = 0;


    // ------------------------------------------------------------
    // LINEAR SEARCH
    // ------------------------------------------------------------

    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].careType == targetCareType)
        {
            foundCount++;
        }
    }


    // ------------------------------------------------------------
    // END SEARCH TIMER
    // ------------------------------------------------------------

    auto end = chrono::high_resolution_clock::now();


    double searchTime =
        chrono::duration<double, milli>(end - start).count();


    // ------------------------------------------------------------
    // DISPLAY RESULT
    // ------------------------------------------------------------

    cout << "\n";
    cout << "================================================\n";
    cout << "             LINEAR SEARCH RESULT\n";
    cout << "================================================\n";

    cout << "Search Field : Care Type\n";
    cout << "Selected Type: " << targetCareType << endl;


    if (foundCount > 0)
    {
        cout << "\n";

        displaySearchHeader();


        // --------------------------------------------------------
        // DISPLAY MATCHING RECORDS
        // --------------------------------------------------------

        for (int i = 0; i < patients.size(); i++)
        {
            if (patients[i].careType == targetCareType)
            {
                displaySearchResult(patients[i]);
            }
        }
    }
    else
    {
        cout << "\nNo matching patients found.\n";
    }


    cout << "\n";
    cout << "------------------------------------------------\n";
    cout << "Linear search found "
         << foundCount
         << " matching patient(s).\n";

    cout << "Search time: "
         << fixed << setprecision(3)
         << searchTime
         << " ms\n";

    cout << "------------------------------------------------\n";
}


// ================================================================
// LINEAR SEARCH BY VISITS PER YEAR
// ================================================================

void searchByVisitDuration(const vector<Patient>& patients)
{
    int targetVisits;

    cout << "\n";
    cout << "================================================\n";
    cout << "          SEARCH BY VISITS PER YEAR\n";
    cout << "================================================\n";
    cout << "Enter number of visits per year: ";
    cin >> targetVisits;


    if (targetVisits < 0)
    {
        cout << "\nInvalid number of visits.\n";
        return;
    }


    // ------------------------------------------------------------
    // START LINEAR SEARCH TIMER
    // ------------------------------------------------------------

    auto start = chrono::high_resolution_clock::now();


    int foundCount = 0;


    // ------------------------------------------------------------
    // LINEAR SEARCH
    // ------------------------------------------------------------

    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].daysVisitsPerYear == targetVisits)
        {
            foundCount++;
        }
    }


    // ------------------------------------------------------------
    // END SEARCH TIMER
    // ------------------------------------------------------------

    auto end = chrono::high_resolution_clock::now();


    double searchTime =
        chrono::duration<double, milli>(end - start).count();


    // ------------------------------------------------------------
    // DISPLAY RESULT
    // ------------------------------------------------------------

    cout << "\n";
    cout << "================================================\n";
    cout << "             LINEAR SEARCH RESULT\n";
    cout << "================================================\n";

    cout << "Search Field : Visits Per Year\n";
    cout << "Target Visits: " << targetVisits << endl;


    if (foundCount > 0)
    {
        cout << "\n";

        displaySearchHeader();


        // --------------------------------------------------------
        // DISPLAY MATCHING RECORDS
        // --------------------------------------------------------

        for (int i = 0; i < patients.size(); i++)
        {
            if (patients[i].daysVisitsPerYear == targetVisits)
            {
                displaySearchResult(patients[i]);
            }
        }
    }
    else
    {
        cout << "\nNo matching patients found.\n";
    }


    cout << "\n";
    cout << "------------------------------------------------\n";
    cout << "Linear search found "
         << foundCount
         << " matching patient(s).\n";

    cout << "Search time: "
         << fixed << setprecision(3)
         << searchTime
         << " ms\n";

    cout << "------------------------------------------------\n";
}


// ================================================================
// SEARCH FIELD MENU
// ================================================================

void linearSearchFieldMenu(const vector<Patient>& patients)
{
    int choice;

    do
    {
        cout << "\n";
        cout << "================================================\n";
        cout << "             SEARCH BY WHICH FIELD?\n";
        cout << "================================================\n";
        cout << "1. Age Group\n";
        cout << "2. Care Type\n";
        cout << "3. Search by Visit Duration\n";
        cout << "4. Back to Main Menu\n";
        cout << "================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;


        switch (choice)
        {
            case 1:
                searchByAgeGroup(patients);
                system("pause");
                break;

            case 2:
                searchByCareType(patients);
                system("pause");
                break;

            case 3:
                searchByVisitDuration(patients);
                system("pause");
                break;

            case 4:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
                system("pause");
        }

    } while (choice != 4);
}


// ================================================================
// DATASET SELECTION MENU
// ================================================================

void linearSearchDatasetMenu(
    const vector<Patient>& facilityA,
    const vector<Patient>& facilityB,
    const vector<Patient>& facilityC,
    const vector<Patient>& combined
)
{
    int datasetChoice;

    do
    {
        cout << "\n";
        cout << "================================================\n";
        cout << "          SELECT DATASET TO SEARCH\n";
        cout << "================================================\n";
        cout << "1. Facility A\n";
        cout << "2. Facility B\n";
        cout << "3. Facility C\n";
        cout << "4. Combined (All Facilities)\n";
        cout << "5. Back to Main Menu\n";
        cout << "================================================\n";
        cout << "Enter your choice: ";
        cin >> datasetChoice;


        switch (datasetChoice)
        {
            case 1:
                cout << "\nFacility A selected.\n";
                linearSearchFieldMenu(facilityA);
                break;

            case 2:
                cout << "\nFacility B selected.\n";
                linearSearchFieldMenu(facilityB);
                break;

            case 3:
                cout << "\nFacility C selected.\n";
                linearSearchFieldMenu(facilityC);
                break;

            case 4:
                cout << "\nCombined (All Facilities) selected.\n";
                linearSearchFieldMenu(combined);
                break;

            case 5:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
                system("pause");
        }

    } while (datasetChoice != 5);
}


// ================================================================
// LINEAR SEARCH MAIN MENU
// ================================================================

void linearSearchMenu(
    const vector<Patient>& facilityA,
    const vector<Patient>& facilityB,
    const vector<Patient>& facilityC,
    const vector<Patient>& combined
)
{
    linearSearchDatasetMenu(
        facilityA,
        facilityB,
        facilityC,
        combined
    );
}


#endif