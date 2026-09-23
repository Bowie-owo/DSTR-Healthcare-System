#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include <iostream>
#include <vector>
#include "patient.hpp"
#include "careTypeAnalysis.hpp"
#include "ageGroupAnalysis.hpp"
#include "billingAnalysis.hpp"

using namespace std;


void analysisMenu(
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
        cout << "              ANALYSIS MENU\n";
        cout << "================================================\n";
        cout << "1. Care Type Analysis\n";
        cout << "2. Age Group Analysis\n";
        cout << "3. Total Billing Cost\n";
        cout << "4. Back to Main Menu\n";
        cout << "================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                cout << "\n========== CARE TYPE ANALYSIS (PER FACILITY) ==========\n";

                // Facility A
                careTypeAnalysis(facilityA, "FACILITY A");

                // Facility B
                careTypeAnalysis(facilityB, "FACILITY B");

                // Facility C
                careTypeAnalysis(facilityC, "FACILITY C");

                // Combine all facilities
                vector<Patient> combined = facilityA;

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

                // Combined analysis
                careTypeAnalysis(combined, "ALL FACILITIES");

                break;
            }

            case 2:
            {
                cout << "\n========== AGE GROUP ANALYSIS (PER FACILITY) ==========\n";

                ageGroupAnalysis(facilityA, "FACILITY A");

                ageGroupAnalysis(facilityB, "FACILITY B");

                ageGroupAnalysis(facilityC, "FACILITY C");

                // Combine all three datasets
                vector<Patient> combined = facilityA;

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

                ageGroupAnalysis(combined, "COMBINED (ALL FACILITIES)");

                break;
            }

            case 3:
            {
                cout << "\n========== TOTAL BILLING COST (PER FACILITY) ==========\n";

                // Facility A
                billingAnalysis(facilityA, "FACILITY A");

                // Facility B
                billingAnalysis(facilityB, "FACILITY B");

                // Facility C
                billingAnalysis(facilityC, "FACILITY C");

                // Combine all facilities
                vector<Patient> combined = facilityA;

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

                // Combined total
                billingAnalysis(combined, "ALL FACILITIES");

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