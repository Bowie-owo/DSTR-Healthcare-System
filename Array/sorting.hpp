#ifndef SORTING_HPP
#define SORTING_HPP

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <string>
#include "patient.hpp"
#include "array.hpp"
#include "searching.hpp"
#include "bubbleSort.hpp"
#include "quickSort.hpp"
#include "insertionSort.hpp"


using namespace std;

void sortAndDisplayInsertionDataset(
    vector<Patient>& patients,
    const string& datasetName,
    int fieldChoice
)
{
    cout << "\n========== DATASET: " << datasetName << " ==========\n";

    if (patients.empty())
    {
        cout << "No patient data is available for this dataset.\n";
        cout << "Total patients: 0\n";
        return;
    }

    auto start = chrono::high_resolution_clock::now();
    if (fieldChoice == 1)
    {
        insertionSortByAge(patients);
    }
    else if (fieldChoice == 2)
    {
        insertionSortByCareType(patients);
    }
    else
    {
        insertionSortByVisitDuration(patients);
    }
    auto end = chrono::high_resolution_clock::now();
    double sortTime = chrono::duration<double, milli>(end - start).count();

    cout << "Sorted by "
         << (fieldChoice == 1 ? "Age" :
             fieldChoice == 2 ? "Care Type" : "Visit Duration")
         << " (ascending).\n";
    cout << "Sort time: " << fixed << setprecision(6)
         << sortTime << " ms\n";
    display(patients);
    cout << "Total patients: " << patients.size() << "\n";
}

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
            {
                cout << "\n---------- Sort (Bubble Sort) ----------\n";
                cout << "Sort by which field?\n";
                cout << "1. Age\n";
                cout << "2. Care Type\n";
                cout << "3. Visit Duration (Length of Stay)\n";
                cout << "Enter your choice: ";

                int fieldChoice;
                cin >> fieldChoice;

                if (fieldChoice < 1 || fieldChoice > 3)
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
                    combined.insert(combined.end(), facilityA.begin(), facilityA.end());
                    combined.insert(combined.end(), facilityB.begin(), facilityB.end());
                    combined.insert(combined.end(), facilityC.begin(), facilityC.end());
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

                PatientArray bubbleArray;
                for (const Patient& patient : *target)
                {
                    bubbleArray.insertBack(patient);
                }

                auto start = chrono::high_resolution_clock::now();
                if (fieldChoice == 1)
                {
                    bubbleSortByAge(bubbleArray);
                }
                else if (fieldChoice == 2)
                {
                    bubbleSortByCareType(bubbleArray);
                }
                else
                {
                    bubbleSortByVisitDuration(bubbleArray);
                }
                auto end = chrono::high_resolution_clock::now();
                double sortTime = chrono::duration<double, milli>(end - start).count();

                target->clear();
                for (int i = 0; i < bubbleArray.getSize(); i++)
                {
                    target->push_back(bubbleArray[i]);
                }

                cout << "\n" << label << " sorted by "
                     << (fieldChoice == 1 ? "Age" :
                         fieldChoice == 2 ? "Care Type" :
                         "Visit Duration")
                     << " (ascending).\n";
                cout << "Sort time: " << fixed << setprecision(6)
                     << sortTime << " ms\n";
                display(*target);
                break;
            }


            case 2:
            {
                cout << "\n---------- Sort (Quick Sort) ----------\n";
                cout << "Sort by which field?\n";
                cout << "1. Age\n";
                cout << "2. Care Type\n";
                cout << "3. Visit Duration (Length of Stay)\n";
                cout << "Enter your choice: ";

                int fieldChoice;
                cin >> fieldChoice;

                if (fieldChoice < 1 || fieldChoice > 3)
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
                    combined.insert(combined.end(), facilityA.begin(), facilityA.end());
                    combined.insert(combined.end(), facilityB.begin(), facilityB.end());
                    combined.insert(combined.end(), facilityC.begin(), facilityC.end());
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

                string fieldLabel = (fieldChoice == 1) ? "Age" : (fieldChoice == 2) ? "Care Type" : "Visit Duration";
                int last = static_cast<int>(target->size()) - 1;

                auto start = chrono::high_resolution_clock::now();
                if (fieldChoice == 1)
                {
                    quickSortByAge(*target, 0, last);
                }
                else if (fieldChoice == 2)
                {
                    quickSortByCareType(*target, 0, last);
                }
                else
                {
                    quickSortByVisitDuration(*target, 0, last);
                }
                auto end = chrono::high_resolution_clock::now();
                double sortTime = chrono::duration<double, milli>(end - start).count();


                cout << "\n" << label << " sorted by " << fieldLabel << " (ascending).\n";
                cout << "Sort time: " << fixed << setprecision(6) << sortTime
                     << " ms  (n = " << target->size() << ")\n";
                display(*target);

                cout << "\nWould you like to search this sorted dataset now? (y/n): ";
                char searchNow;
                cin >> searchNow;
                if (searchNow == 'y' || searchNow == 'Y')
                {
                    searchingMenu(facilityA, facilityB, facilityC, combined);
                }

                break;
            }

            case 3:
            {
                cout << "\n---------- Sort (Insertion Sort) ----------\n";
                cout << "Sort by which field?\n";
                cout << "1. Age\n";
                cout << "2. Care Type\n";
                cout << "3. Visit Duration (Length of Stay)\n";
                cout << "Enter your choice: ";

                int fieldChoice;
                cin >> fieldChoice;

                if (fieldChoice < 1 || fieldChoice > 3)
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
                string datasetName;

                if (sortChoice == 1)
                {
                    target = &facilityA;
                    datasetName = "FACILITY A";
                }
                else if (sortChoice == 2)
                {
                    target = &facilityB;
                    datasetName = "FACILITY B";
                }
                else if (sortChoice == 3)
                {
                    target = &facilityC;
                    datasetName = "FACILITY C";
                }
                else if (sortChoice == 4)
                {
                    combined.clear();
                    combined.insert(combined.end(), facilityA.begin(), facilityA.end());
                    combined.insert(combined.end(), facilityB.begin(), facilityB.end());
                    combined.insert(combined.end(), facilityC.begin(), facilityC.end());
                    target = &combined;
                    datasetName = "COMBINED (ALL FACILITIES)";
                }
                else
                {
                    cout << "\nInvalid choice.\n";
                    break;
                }

                sortAndDisplayInsertionDataset(*target, datasetName, fieldChoice);
                break;
            }

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