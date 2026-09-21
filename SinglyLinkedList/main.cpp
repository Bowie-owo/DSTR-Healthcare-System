#include <iostream>
#include "linkedList.hpp"
#include "ageGroupAnalysis.hpp"
#include "careTypeAnalysis.hpp"
#include "billingAnalysis.hpp"

using namespace std;

void displayMenu() {

    cout << "\n";
    cout << "================================================\n";
    cout << "              METROHEALTH SYSTEM\n";
    cout << "       SINGLY LINKED LIST IMPLEMENTATION\n";
    cout << "================================================\n";
    cout << "1. Load and Display Facility A\n";
    cout << "2. Load and Display Facility B\n";
    cout << "3. Load and Display Facility C\n";
    cout << "4. Load and Display All Datasets\n";
    cout << "5. Age Group Analysis (Per Facility)\n";
    cout << "6. Care Type Analysis (Per Facility)\n";
    cout << "7. Total Billing Cost (Per Facility)\n";
    cout << "8. Dataset Summary (Per Facility)\n";
    cout << "9. Combined Analysis (All Facilities)\n";
    cout << "10. Exit\n";
    cout << "================================================\n";
    cout << "Enter your choice: ";
}

int main() {

    LinkedList facilityA;
    LinkedList facilityB;
    LinkedList facilityC;
    LinkedList combined;

    bool facilityALoaded = false;
    bool facilityBLoaded = false;
    bool facilityCLoaded = false;

    int choice;

    do {

        displayMenu();
        cin >> choice;

        switch (choice) {

        case 1:
            if (facilityA.loadCSV("datasets/dataset1_facility_a.csv")) {
                cout << "\nFacility A dataset loaded successfully!\n";
                cout << "Number of patients: " << facilityA.getSize() << endl;
                facilityA.display();
                facilityALoaded = true;
            }
            break;

        case 2:
            if (facilityB.loadCSV("datasets/dataset2_facility_b.csv")) {
                cout << "\nFacility B dataset loaded successfully!\n";
                cout << "Number of patients: " << facilityB.getSize() << endl;
                facilityB.display();
                facilityBLoaded = true;
            }
            break;

        case 3:
            if (facilityC.loadCSV("datasets/dataset3_facility_c.csv")) {
                cout << "\nFacility C dataset loaded successfully!\n";
                cout << "Number of patients: " << facilityC.getSize() << endl;
                facilityC.display();
                facilityCLoaded = true;
            }
            break;

        case 4:
            if (facilityA.loadCSV("datasets/dataset1_facility_a.csv")) facilityALoaded = true;
            if (facilityB.loadCSV("datasets/dataset2_facility_b.csv")) facilityBLoaded = true;
            if (facilityC.loadCSV("datasets/dataset3_facility_c.csv")) facilityCLoaded = true;

            if (facilityALoaded) { cout << "\n========== FACILITY A ==========\n"; facilityA.display(); }
            if (facilityBLoaded) { cout << "\n========== FACILITY B ==========\n"; facilityB.display(); }
            if (facilityCLoaded) { cout << "\n========== FACILITY C ==========\n"; facilityC.display(); }
            break;

        case 5:
            cout << "\n========== AGE GROUP ANALYSIS (PER FACILITY) ==========\n";
            if (facilityALoaded) { cout << "\nFACILITY A\n"; ageGroupAnalysis(facilityA); }
            if (facilityBLoaded) { cout << "\nFACILITY B\n"; ageGroupAnalysis(facilityB); }
            if (facilityCLoaded) { cout << "\nFACILITY C\n"; ageGroupAnalysis(facilityC); }
            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) cout << "\nPlease load a dataset first.\n";
            break;

        case 6:
            cout << "\n========== CARE TYPE ANALYSIS (PER FACILITY) ==========\n";
            if (facilityALoaded) { cout << "\nFACILITY A\n"; careTypeAnalysis(facilityA); }
            if (facilityBLoaded) { cout << "\nFACILITY B\n"; careTypeAnalysis(facilityB); }
            if (facilityCLoaded) { cout << "\nFACILITY C\n"; careTypeAnalysis(facilityC); }
            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) cout << "\nPlease load a dataset first.\n";
            break;

        case 7:
            cout << "\n========== TOTAL BILLING COST (PER FACILITY) ==========\n";
            if (facilityALoaded) displayTotalBillingCost(facilityA, "FACILITY A");
            if (facilityBLoaded) displayTotalBillingCost(facilityB, "FACILITY B");
            if (facilityCLoaded) displayTotalBillingCost(facilityC, "FACILITY C");
            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) cout << "\nPlease load a dataset first.\n";
            break;

        case 8:
            cout << "\n========== DATASET SUMMARY (PER FACILITY) ==========\n";
            if (facilityALoaded) displayDatasetSummary(facilityA, "FACILITY A");
            if (facilityBLoaded) displayDatasetSummary(facilityB, "FACILITY B");
            if (facilityCLoaded) displayDatasetSummary(facilityC, "FACILITY C");
            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) cout << "\nPlease load a dataset first.\n";
            break;

        case 9:
            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) {
                cout << "\nPlease load at least one dataset first.\n";
                break;
            }

            // Rebuild the combined list from whichever facilities
            // are currently loaded, so it never goes stale if a
            // facility gets reloaded.
            combined.clear();
            if (facilityALoaded) combined.appendAll(facilityA);
            if (facilityBLoaded) combined.appendAll(facilityB);
            if (facilityCLoaded) combined.appendAll(facilityC);

            cout << "\n========== COMBINED ANALYSIS (ALL FACILITIES) ==========\n";
            cout << "Total patients combined: " << combined.getSize() << endl;

            cout << "\n---------- Age Group Analysis ----------\n";
            ageGroupAnalysis(combined);

            cout << "\n---------- Care Type Analysis ----------\n";
            careTypeAnalysis(combined);

            displayTotalBillingCost(combined, "COMBINED (ALL FACILITIES)");
            displayDatasetSummary(combined, "COMBINED (ALL FACILITIES)");
            break;

        case 10:
            cout << "\nExiting MetroHealth System...\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

        cout << "\n\n\n\n\n";

    } while (choice != 10);

    return 0;
}