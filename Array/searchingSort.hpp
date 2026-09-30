#ifndef SEARCHING_SORT_HPP
#define SEARCHING_SORT_HPP

#include <iostream>
#include "patient.hpp"
#include "array.hpp"
#include "sortedLinear.hpp"
#include "sortedBinary.hpp" 
using namespace std;


// ================================================================
// SEARCH METHOD MENU AFTER SORTING
//
// sortedBy:
// 1 = Age
// 2 = Care Type
// 3 = Visit Duration
// ================================================================
void sortedSearchMethodMenu(
    const DynamicArray<Patient>& patients,
    int sortedBy
)
{
    int choice;

    do
    {
        cout << "\n";
        cout << "================================================\n";
        cout << "              SEARCH METHOD\n";
        cout << "================================================\n";
        cout << "1. Linear Search\n";
        cout << "2. Binary Search\n";
        cout << "3. Back\n";
        cout << "================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            // ----------------------------------------------------
            // LINEAR SEARCH
            // ----------------------------------------------------
            case 1:
            {
                if (sortedBy == 1)
                {
                    cout << "\n---------- LINEAR SEARCH BY AGE ----------\n";
                    sortedLinearSearchByAge(patients);
                    return;
                }
                else if (sortedBy == 2)
                {
                    cout << "\n---------- LINEAR SEARCH BY CARE TYPE ----------\n";
                    sortedLinearSearchByCareType(patients);
                    return;
                }
                else if (sortedBy == 3)
                {
                    cout << "\n---------- LINEAR SEARCH BY VISIT DURATION ----------\n";
                    sortedLinearSearchByVisitDuration(patients);
                    return;
                }

                break;
            }

            // ----------------------------------------------------
            // BINARY SEARCH
            // ----------------------------------------------------
            case 2:
            {
                if (sortedBy == 1)
                {
                    cout << "\n---------- BINARY SEARCH BY AGE ----------\n";

                    sortedBinarySearchByAge(patients);
                    return;
                }
                else if (sortedBy == 2)
                {
                    cout << "\n---------- BINARY SEARCH BY CARE TYPE ----------\n";

                    sortedBinarySearchByCareType(patients);
                    return;
                }
                else if (sortedBy == 3)
                {
                    cout << "\n---------- BINARY SEARCH BY VISIT DURATION ----------\n";

                    sortedBinarySearchByVisitDuration(patients);
                    return;
                }

                break;
            }

            // ----------------------------------------------------
            // BACK
            // ----------------------------------------------------
            case 3:
                cout << "\nReturning...\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 3);
}

#endif