#include <iostream>
#include <chrono>
#include "linkedList.hpp"
#include "bubbleSort.hpp"
#include "insertionSort.hpp"
#include "binarySearch.hpp"
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
    cout << "5. Sort (Bubble Sort)\n";
    cout << "6. Age Group Analysis\n";
    cout << "7. Care Type Analysis (Per Facility)\n";
    cout << "8. Total Billing Cost (Per Facility)\n";
    cout << "9. Dataset Summary (Per Facility)\n";
    cout << "10. Combined Analysis (All Facilities)\n";
    cout << "11. Exit\n";
    cout << "================================================\n";
    cout << "Enter your choice: ";
}

void searchList(LinkedList& target) {
    cout << "\nSearch by which field?\n";
    cout << "1. Age Group\n";
    cout << "2. Care Type\n";
    cout << "Enter your choice: ";

    int searchField;
    cin >> searchField;

    if (searchField != 1 && searchField != 2) {
        cout << "\nInvalid choice.\n";
        return;
    }

    int matches = 0;
    auto searchStart = chrono::high_resolution_clock::now();

    if (searchField == 1) {
        cout << "\nAge groups:\n"
             << "1. 0-17: Pediatrics & Adolescents\n"
             << "2. 18-25: Young Adults / University Students\n"
             << "3. 26-45: Working Adults (Early Career)\n"
             << "4. 46-60: Working Adults (Late Career)\n"
             << "5. 61-100: Senior Citizens / Geriatric Care\n"
             << "Enter your choice: ";

        int groupChoice;
        cin >> groupChoice;
        const int minimumAges[] = {0, 18, 26, 46, 61};
        const int maximumAges[] = {17, 25, 45, 60, 100};

        if (groupChoice < 1 || groupChoice > 5) {
            cout << "\nInvalid age group.\n";
            return;
        }

        // Option 5 may already have sorted by age; sorting again is harmless.
        bubbleSortByAge(target);
        matches = displayPatientsInAgeGroup(
            target, minimumAges[groupChoice - 1], maximumAges[groupChoice - 1]);
    }
    else {
        cout << "\nCare types:\n"
             << "1. Emergency\n2. Inpatient\n3. Outpatient\n"
             << "4. Rehabilitation\n5. Routine checkup\n6. Vaccination\n"
             << "Enter your choice: ";

        int careChoice;
        cin >> careChoice;
        const string careTypes[] = {
            "Emergency", "Inpatient", "Outpatient",
            "Rehabilitation", "Routine Checkup", "Vaccination"
        };

        if (careChoice < 1 || careChoice > 6) {
            cout << "\nInvalid care type.\n";
            return;
        }

        bubbleSortByCareType(target);
        matches = displayPatientsByCareType(target, careTypes[careChoice - 1]);
    }

    auto searchEnd = chrono::high_resolution_clock::now();
    double searchMs = chrono::duration<double, milli>(searchEnd - searchStart).count();

    cout << "\nBinary search found " << matches << " matching patient(s).\n";
    cout << "Search time: " << searchMs << " ms  (n = " << target.getSize() << ")\n";
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

            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) {
                cout << "\nNo datasets could be loaded.\n";
                break;
            }

            // Rebuild combined so it reflects whatever facilities just loaded successfully
            combined.clear();
            if (facilityALoaded) combined.appendAll(facilityA);
            if (facilityBLoaded) combined.appendAll(facilityB);
            if (facilityCLoaded) combined.appendAll(facilityC);

            cout << "\n========== ALL DATASETS (COMBINED) ==========\n";
            cout << "Total patients combined: " << combined.getSize() << endl;
            combined.display();
            break;

        case 5: {

            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) {
                cout << "\nPlease load a dataset first.\n";
                break;
            }

            cout << "\n---------- Sort (Bubble Sort) ----------\n";
            cout << "Sort by which field?\n";
            cout << "1. Age\n";
            cout << "2. Visit Duration (Length of Stay)\n";
            cout << "Enter your choice: ";

            int fieldChoice;
            cin >> fieldChoice;

            if (fieldChoice != 1 && fieldChoice != 2) {
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

            LinkedList* target = nullptr;
            string label;

            if (sortChoice == 1) {
                if (!facilityALoaded) { cout << "\nFacility A is not loaded yet.\n"; break; }
                target = &facilityA;
                label = "FACILITY A";
            }
            else if (sortChoice == 2) {
                if (!facilityBLoaded) { cout << "\nFacility B is not loaded yet.\n"; break; }
                target = &facilityB;
                label = "FACILITY B";
            }
            else if (sortChoice == 3) {
                if (!facilityCLoaded) { cout << "\nFacility C is not loaded yet.\n"; break; }
                target = &facilityC;
                label = "FACILITY C";
            }
            else if (sortChoice == 4) {
                combined.clear();
                if (facilityALoaded) combined.appendAll(facilityA);
                if (facilityBLoaded) combined.appendAll(facilityB);
                if (facilityCLoaded) combined.appendAll(facilityC);
                target = &combined;
                label = "COMBINED (ALL FACILITIES)";
            }
            else {
                cout << "\nInvalid choice.\n";
                break;
            }

            string fieldLabel = (fieldChoice == 1) ? "Age" : "Visit Duration";

            auto start = chrono::high_resolution_clock::now();
            if (fieldChoice == 1) {
                bubbleSortByAge(*target);
            }
            else {
                bubbleSortByVisitDuration(*target);
            }
            auto end = chrono::high_resolution_clock::now();
            double ms = chrono::duration<double, milli>(end - start).count();

            cout << "\n" << label << " sorted by " << fieldLabel << " (ascending).\n";
            cout << "Sort time: " << ms << " ms  (n = " << target->getSize() << ")\n";
            target->display();

            cout << "\nWould you like to search this sorted dataset now? (y/n): ";
            char searchNow;
            cin >> searchNow;
            if (searchNow == 'y' || searchNow == 'Y') {
                searchList(*target);
            }

            break;
        }

        case 6: {
            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) {
                cout << "\nPlease load a dataset first.\n";
                break;
            }

            int loadedCount = (facilityALoaded ? 1 : 0)
                            + (facilityBLoaded ? 1 : 0)
                            + (facilityCLoaded ? 1 : 0);

            cout << "\n========== AGE GROUP ANALYSIS (PER FACILITY) ==========\n";
            if (facilityALoaded) { cout << "\nFACILITY A\n"; ageGroupAnalysis(facilityA); }
            if (facilityBLoaded) { cout << "\nFACILITY B\n"; ageGroupAnalysis(facilityB); }
            if (facilityCLoaded) { cout << "\nFACILITY C\n"; ageGroupAnalysis(facilityC); }

            if (loadedCount > 1) {
                combined.clear();
                if (facilityALoaded) combined.appendAll(facilityA);
                if (facilityBLoaded) combined.appendAll(facilityB);
                if (facilityCLoaded) combined.appendAll(facilityC);

                cout << "\nCOMBINED (ALL FACILITIES)\n";
                ageGroupAnalysis(combined);
            }

            break;
        }

        case 8:
            cout << "\n========== CARE TYPE ANALYSIS (PER FACILITY) ==========\n";
            if (facilityALoaded) { cout << "\nFACILITY A\n"; careTypeAnalysis(facilityA); }
            if (facilityBLoaded) { cout << "\nFACILITY B\n"; careTypeAnalysis(facilityB); }
            if (facilityCLoaded) { cout << "\nFACILITY C\n"; careTypeAnalysis(facilityC); }
            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) cout << "\nPlease load a dataset first.\n";
            break;

        case 9:
            cout << "\n========== TOTAL BILLING COST (PER FACILITY) ==========\n";
            if (facilityALoaded) displayTotalBillingCost(facilityA, "FACILITY A");
            if (facilityBLoaded) displayTotalBillingCost(facilityB, "FACILITY B");
            if (facilityCLoaded) displayTotalBillingCost(facilityC, "FACILITY C");
            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) cout << "\nPlease load a dataset first.\n";
            break;

        case 10:
            cout << "\n========== DATASET SUMMARY (PER FACILITY) ==========\n";
            if (facilityALoaded) displayDatasetSummary(facilityA, "FACILITY A");
            if (facilityBLoaded) displayDatasetSummary(facilityB, "FACILITY B");
            if (facilityCLoaded) displayDatasetSummary(facilityC, "FACILITY C");
            if (!facilityALoaded && !facilityBLoaded && !facilityCLoaded) cout << "\nPlease load a dataset first.\n";
            break;

        case 11:
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

        case 12:
            cout << "\nExiting MetroHealth System...\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

        cout << "\n\n\n\n\n";

    } while (choice != 12);

    return 0;
}