#ifndef LINEAR_SEARCH_HPP
#define LINEAR_SEARCH_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>

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
// LINEAR SEARCH BY AGE
// ================================================================

void searchByAge(
    const vector<Patient>& patients,
    int targetAge
)
{
    bool found = false;

    cout << "\nSearching for patients with age: "
         << targetAge << endl;

    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].age == targetAge)
        {
            if (!found)
            {
                displaySearchHeader();
            }

            displaySearchResult(patients[i]);

            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNo patient found with age "
             << targetAge << ".\n";
    }
}


// ================================================================
// LINEAR SEARCH BY VISIT DURATION
// ================================================================

void searchByVisitDuration(
    const vector<Patient>& patients,
    double targetDuration
)
{
    bool found = false;

    cout << "\nSearching for patients with visit duration: "
         << fixed << setprecision(2)
         << targetDuration << endl;

    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].lengthOfStay == targetDuration)
        {
            if (!found)
            {
                displaySearchHeader();
            }

            displaySearchResult(patients[i]);

            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNo patient found with visit duration "
             << fixed << setprecision(2)
             << targetDuration << ".\n";
    }
}


// ================================================================
// LINEAR SEARCH BY CARE TYPE
// ================================================================

void searchByCareType(
    const vector<Patient>& patients,
    const string& targetCareType
)
{
    bool found = false;

    cout << "\nSearching for patients with care type: "
         << targetCareType << endl;

    for (int i = 0; i < patients.size(); i++)
    {
        if (patients[i].careType == targetCareType)
        {
            if (!found)
            {
                displaySearchHeader();
            }

            displaySearchResult(patients[i]);

            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNo patient found with care type: "
             << targetCareType << ".\n";
    }
}


// ================================================================
// SELECT DATASET
// ================================================================

void linearSearchDatasetMenu(
    const vector<Patient>& facilityA,
    const vector<Patient>& facilityB,
    const vector<Patient>& facilityC,
    const vector<Patient>& combined,
    int searchType
)
{
    int datasetChoice;

    do
    {
        cout << "\n";
        cout << "================================================\n";
        cout << "           SELECT DATASET TO SEARCH\n";
        cout << "================================================\n";
        cout << "1. Facility A\n";
        cout << "2. Facility B\n";
        cout << "3. Facility C\n";
        cout << "4. Combined (All Facilities)\n";
        cout << "5. Back to Linear Search Menu\n";
        cout << "================================================\n";
        cout << "Enter your choice: ";
        cin >> datasetChoice;


        // ========================================================
        // FACILITY A
        // ========================================================

        if (datasetChoice == 1)
        {
            cout << "\nFacility A selected.\n";

            if (searchType == 1)
            {
                int age;

                cout << "Enter age to search: ";
                cin >> age;

                searchByAge(facilityA, age);
            }

            else if (searchType == 2)
            {
                double duration;

                cout << "Enter visit duration to search: ";
                cin >> duration;

                searchByVisitDuration(facilityA, duration);
            }

            else if (searchType == 3)
            {
                string careType;

                cout << "Enter care type to search: ";

                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                getline(cin, careType);

                searchByCareType(facilityA, careType);
            }

            system("pause");
        }


        // ========================================================
        // FACILITY B
        // ========================================================

        else if (datasetChoice == 2)
        {
            cout << "\nFacility B selected.\n";

            if (searchType == 1)
            {
                int age;

                cout << "Enter age to search: ";
                cin >> age;

                searchByAge(facilityB, age);
            }

            else if (searchType == 2)
            {
                double duration;

                cout << "Enter visit duration to search: ";
                cin >> duration;

                searchByVisitDuration(facilityB, duration);
            }

            else if (searchType == 3)
            {
                string careType;

                cout << "Enter care type to search: ";

                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                getline(cin, careType);

                searchByCareType(facilityB, careType);
            }

            system("pause");
        }


        // ========================================================
        // FACILITY C
        // ========================================================

        else if (datasetChoice == 3)
        {
            cout << "\nFacility C selected.\n";

            if (searchType == 1)
            {
                int age;

                cout << "Enter age to search: ";
                cin >> age;

                searchByAge(facilityC, age);
            }

            else if (searchType == 2)
            {
                double duration;

                cout << "Enter visit duration to search: ";
                cin >> duration;

                searchByVisitDuration(facilityC, duration);
            }

            else if (searchType == 3)
            {
                string careType;

                cout << "Enter care type to search: ";

                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                getline(cin, careType);

                searchByCareType(facilityC, careType);
            }

            system("pause");
        }


        // ========================================================
        // COMBINED
        // ========================================================

        else if (datasetChoice == 4)
        {
            cout << "\nCombined (All Facilities) selected.\n";

            if (searchType == 1)
            {
                int age;

                cout << "Enter age to search: ";
                cin >> age;

                searchByAge(combined, age);
            }

            else if (searchType == 2)
            {
                double duration;

                cout << "Enter visit duration to search: ";
                cin >> duration;

                searchByVisitDuration(combined, duration);
            }

            else if (searchType == 3)
            {
                string careType;

                cout << "Enter care type to search: ";

                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                getline(cin, careType);

                searchByCareType(combined, careType);
            }

            system("pause");
        }


        // ========================================================
        // BACK
        // ========================================================

        else if (datasetChoice == 5)
        {
            cout << "\nReturning to Linear Search Menu...\n";
        }


        // ========================================================
        // INVALID
        // ========================================================

        else
        {
            cout << "\nInvalid choice. Please try again.\n";
            system("pause");
        }

    } while (datasetChoice != 5);
}


// ================================================================
// LINEAR SEARCH MENU
// ================================================================

void linearSearchMenu(
    const vector<Patient>& facilityA,
    const vector<Patient>& facilityB,
    const vector<Patient>& facilityC,
    const vector<Patient>& combined
)
{
    int choice;

    do
    {
        cout << "\n";
        cout << "================================================\n";
        cout << "              LINEAR SEARCH\n";
        cout << "================================================\n";
        cout << "1. Search by Age\n";
        cout << "2. Search by Visit Duration\n";
        cout << "3. Search by Care Type\n";
        cout << "4. Back to Searching Menu\n";
        cout << "================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                linearSearchDatasetMenu(
                    facilityA,
                    facilityB,
                    facilityC,
                    combined,
                    1
                );
                break;

            case 2:
                linearSearchDatasetMenu(
                    facilityA,
                    facilityB,
                    facilityC,
                    combined,
                    2
                );
                break;

            case 3:
                linearSearchDatasetMenu(
                    facilityA,
                    facilityB,
                    facilityC,
                    combined,
                    3
                );
                break;

            case 4:
                cout << "\nReturning to Searching Menu...\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
                system("pause");
        }

    } while (choice != 4);
}

#endif