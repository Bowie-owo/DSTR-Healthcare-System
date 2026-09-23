#ifndef SORTING_HPP
#define SORTING_HPP

#include <iostream>
#include <vector>
#include <chrono>
#include "patient.hpp"
#include "quickSort.hpp"

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
            {
                cout << "\n---------- Sort (Quick Sort) ----------\n";

                cout << "Sort by which field?\n";
                cout << "1. Age\n";
                cout << "2. Visit Duration (Length of Stay)\n";
                cout << "Enter your choice: ";

                int fieldChoice;
                cin >> fieldChoice;

                if (fieldChoice != 1 && fieldChoice != 2)
                {
                    cout << "\nInvalid choice.\n";
                    break;
                }


                cout << "\nWhich dataset would you like to sort?\n";
                cout << "1. Facility A\n";
                cout << "2. Facility B\n";
                cout << "3. Facility C\n";
                cout << "4. Combined (All Facilities)\n";
                cout << "Enter your choice: ";

                int sortChoice;
                cin >> sortChoice;


                vector<Patient>* target = nullptr;
                string label;


                if (sortChoice == 1)
                {
                    target = &facilityA;
                    label = "FACILITY A";
                }
                else if (sortChoice == 2)
                {
                    target = &facilityB;
                    label = "FACILITY B";
                }
                else if (sortChoice == 3)
                {
                    target = &facilityC;
                    label = "FACILITY C";
                }
                else if (sortChoice == 4)
                {
                    combined.clear();

                    combined.insert(
                        combined.end(),
                        facilityA.begin(),
                        facilityA.end()
                    );

                    combined.insert(
                        combined.end(),
                        facilityB.begin(),
                        facilityB.end()
                    );

                    combined.insert(
                        combined.end(),
                        facilityC.begin(),
                        facilityC.end()
                    );

                    target = &combined;
                    label = "COMBINED (ALL FACILITIES)";
                }
                else
                {
                    cout << "\nInvalid choice.\n";
                    break;
                }


                if (target->empty())
                {
                    cout << "\nSelected dataset is empty.\n";
                    break;
                }


                // ==================================
                // PERFORM QUICK SORT
                // ==================================

                if (fieldChoice == 1)
                {
                    auto start = chrono::high_resolution_clock::now();

                    quickSortByAge(
                        *target,
                        0,
                        static_cast<int>(target->size()) - 1
                    );

                    auto end = chrono::high_resolution_clock::now();

                    double sortTime =
                        chrono::duration<double, milli>(end - start).count();

                    cout << "\n"
                        << label
                        << " sorted by Age (ascending).\n";

                    cout << "Sort time: "
                        << fixed
                        << setprecision(6)
                        << sortTime
                        << " ms\n";
                }
                else
                {
                    auto start = chrono::high_resolution_clock::now();

                    quickSortByVisitDuration(
                        *target,
                        0,
                        static_cast<int>(target->size()) - 1
                    );

                    auto end = chrono::high_resolution_clock::now();

                    double sortTime =
                        chrono::duration<double, milli>(end - start).count();

                    cout << "\n"
                        << label
                        << " sorted by Visit Duration (ascending).\n";

                    cout << "Sort time: "
                        << fixed
                        << setprecision(6)
                        << sortTime
                        << " ms\n";
                }

                cout << "\n";

                cout << left
                     << setw(12) << "Patient ID"
                     << setw(8) << "Age"
                     << setw(20) << "Care Type"
                     << setw(15) << "Stay(hr)"
                     << setw(15) << "Cost/hr"
                     << setw(12) << "Visits/Year"
                     << endl;

                cout << string(82, '-') << endl;


                for (const Patient& patient : *target)
                {
                    cout << left
                         << setw(12)
                         << patient.patientID

                         << setw(8)
                         << patient.age

                         << setw(20)
                         << patient.careType

                         << setw(15)
                         << fixed
                         << setprecision(2)
                         << patient.lengthOfStay

                         << setw(15)
                         << fixed
                         << setprecision(2)
                         << patient.baseCostPerHour

                         << setw(12)
                         << patient.daysVisitsPerYear

                         << endl;
                }


                cout << "\nTotal patients: "
                     << target->size()
                     << endl;

                break;
            }

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