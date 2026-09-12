#include <iostream>
#include "LinkedList.hpp"

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
    cout << "5. Age Group Analysis\n";
    cout << "6. Care Type Analysis\n";
    cout << "7. Total Billing Cost\n";
    cout << "8. Dataset Summary\n";
    cout << "9. Exit\n";
    cout << "================================================\n";
    cout << "Enter your choice: ";
}

int main() {

    LinkedList facilityA;
    LinkedList facilityB;
    LinkedList facilityC;

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
            if (facilityB.loadCSV("datasets/dataset1_facility_b.csv")) {
                cout << "\nFacility B dataset loaded successfully!\n";
                cout << "Number of patients: " << facilityB.getSize() << endl;
                facilityB.display();
                facilityBLoaded = true;
            }
            break;

        case 3:
            if (facilityC.loadCSV("datasets/dataset1_facility_c.csv")) {
                cout << "\nFacility C dataset loaded successfully!\n";
                cout << "Number of patients: " << facilityC.getSize() << endl;
                facilityC.display();
                facilityCLoaded = true;
            }
            break;

        case 4:
            if (facilityA.loadCSV("datasets/dataset1_facility_a.csv")) facilityALoaded = true;
            if (facilityB.loadCSV("datasets/dataset1_facility_b.csv")) facilityBLoaded = true;
            if (facilityC.loadCSV("datasets/dataset1_facility_c.csv")) facilityCLoaded = true;

            if (facilityALoaded) { cout << "\n========== FACILITY A ==========\n"; facilityA.display(); }
            if (facilityBLoaded) { cout << "\n========== FACILITY B ==========\n"; facilityB.display(); }
            if (facilityCLoaded) { cout << "\n========== FACILITY C ==========\n"; facilityC.display(); }
            break;

        case 5:
            cout << "\n========== AGE GROUP ANALYSIS ==========\n";
            if (facilityALoaded) { cout << "\nFACILITY A\n"; facilityA.ageGroupAnalysis(); }
            if (facilityBLoaded) { cout << "\nFACILITY B\n"; facilityB.ageGroupAnalysis(); }
            if (facilityCLoaded) { cout << "\nFACILITY C\n"; facilityC.ageGroupAnalysis(); }
            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) cout << "\nPlease load a dataset first.\n";
            break;

        case 6:
            cout << "\n========== CARE TYPE ANALYSIS ==========\n";
            if (facilityALoaded) { cout << "\nFACILITY A\n"; facilityA.careTypeAnalysis(); }
            if (facilityBLoaded) { cout << "\nFACILITY B\n"; facilityB.careTypeAnalysis(); }
            if (facilityCLoaded) { cout << "\nFACILITY C\n"; facilityC.careTypeAnalysis(); }
            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) cout << "\nPlease load a dataset first.\n";
            break;

        case 7:
            cout << "\n========== TOTAL BILLING COST ==========\n";
            if (facilityALoaded) facilityA.displayTotalBillingCost("FACILITY A");
            if (facilityBLoaded) facilityB.displayTotalBillingCost("FACILITY B");
            if (facilityCLoaded) facilityC.displayTotalBillingCost("FACILITY C");
            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) cout << "\nPlease load a dataset first.\n";
            break;

        case 8:
            cout << "\n========== DATASET SUMMARY ==========\n";
            if (facilityALoaded) facilityA.displayDatasetSummary("FACILITY A");
            if (facilityBLoaded) facilityB.displayDatasetSummary("FACILITY B");
            if (facilityCLoaded) facilityC.displayDatasetSummary("FACILITY C");
            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) cout << "\nPlease load a dataset first.\n";
            break;

        case 9:
            cout << "\nExiting MetroHealth System...\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}