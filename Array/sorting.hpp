#ifndef SORTING_HPP
#define SORTING_HPP

#include <iostream>
#include <vector>
#include "patient.hpp"

using namespace std;

void sortingMenu(
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
        cout << "              SORTING MENU\n";
        cout << "================================================\n";
        cout << "1. Bubble Sort\n";
        cout << "2. Quick Sort\n";
        cout << "3. Insertion Sort\n";
        cout << "4. Back to Main Menu\n";
        cout << "================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "\nThis feature is not implemented yet.\n";
                break;

            case 2:
                cout << "\nThis feature is not implemented yet.\n";
            break;

            case 3:
                cout << "\nThis feature is not implemented yet.\n";
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

#endif