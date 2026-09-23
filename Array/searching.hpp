#ifndef SEARCHING_HPP
#define SEARCHING_HPP

#include <iostream>
#include <vector>
#include "patient.hpp"
#include "linearSearch.hpp"

using namespace std;

void searchingMenu(
    vector<Patient>& facilityA,
    vector<Patient>& facilityB,
    vector<Patient>& facilityC,
    vector<Patient>& combined
)
{
    int choice;

    do
    {
        cout << "\n";
        cout << "================================================\n";
        cout << "              SEARCHING ANALYSIS\n";
        cout << "================================================\n";
        cout << "1. Linear Search\n";
        cout << "2. Binary Search\n";
        cout << "3. Back to Main Menu\n";
        cout << "================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                linearSearchMenu(
                    facilityA,
                    facilityB,
                    facilityC,
                    combined
                );
                break;

            case 2:
                // Binary Search menu will be added later
                cout << "\nBinary Search selected.\n";
                system("pause");
                break;

            case 3:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
                system("pause");
        }

    } while (choice != 3);
}

#endif