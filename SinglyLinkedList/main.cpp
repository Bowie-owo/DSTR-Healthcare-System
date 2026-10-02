#include <iostream>
#include <chrono>
#include "linkedList.hpp"
#include "bubbleSort.hpp"
#include "insertionSort.hpp"
#include "quickSort.hpp"
#include "binarySearch.hpp"
#include "ageGroupAnalysis.hpp"
#include "careTypeAnalysis.hpp"
#include "billingAnalysis.hpp"
#include "linearSearch.hpp"
#include "performanceTest.hpp"

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
    cout << "5. Sorting\n";
    cout << "6. Linear Search\n";
    cout << "7. Analysis\n";
    cout << "8. Dataset Summary\n";
    cout << "9. Performance Summary\n";
    cout << "10. Exit\n";
    cout << "================================================\n";
    cout << "Enter your choice: ";
}

void searchList(LinkedList& target, int searchField) {
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

        matches = displayPatientsInAgeGroup(
            target, minimumAges[groupChoice - 1], maximumAges[groupChoice - 1]);
    }
    else if (searchField == 2) {
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

        matches = displayPatientsByCareType(target, careTypes[careChoice - 1]);
    }
    else {
        cout << "\nVisit duration ranges:\n"
               << "1. 1 to <6 hours (Quick observation / discharge)\n"
               << "2. 6 to <12 hours (Short-stay / extended observation)\n"
               << "3. 12 to <24 hours (Full day observation)\n"
               << "4. 24 to <48 hours (1 to 2 days admitted)\n"
               << "5. 48 to <72 hours (2 to 3 days admitted)\n"
               << "6. 72 to <120 hours (3 to 5 days)\n"
               << "7. >=120 hours\n"
             << "Enter your choice: ";

        int durationChoice;
        cin >> durationChoice;

        if (durationChoice < 1 || durationChoice > 7) {
            cout << "\nInvalid visit duration range.\n";
            return;
        }

        const double minimumLengths[] = {
            1.0, 6.0, 12.0, 24.0, 48.0, 72.0, 120.0
        };
        const double maximumLengths[] = {
            6.0, 12.0, 24.0, 48.0, 72.0, 120.0,
            numeric_limits<double>::infinity()
        };
        const bool maximumInclusive[] = {
            false, false, false, false, false, false, false
        };
        const bool minimumExclusive[] = {
            false, false, false, false, false, false, false
        };

        matches = displayPatientsByVisitDurationRange(
            target,
            minimumLengths[durationChoice - 1],
            maximumLengths[durationChoice - 1],
            maximumInclusive[durationChoice - 1],
            minimumExclusive[durationChoice - 1]);
    }

    auto searchEnd = chrono::high_resolution_clock::now();
    double searchMs = chrono::duration<double, milli>(searchEnd - searchStart).count();

    cout << "\nBinary search found " << matches << " matching patient(s).\n";
    cout << "Search time: " << searchMs << " ms  (n = " << target.getSize() << ")\n";

    recordSortedBinarySearch(searchMs);
}

void chooseSearchMethod(LinkedList& target,
                        int searchField,
                        PerformanceSortMethod sortedMethod) {
    cout << "\nSelect a search method:\n";
    cout << "1. Linear Search\n";
    cout << "2. Binary Search\n";
    cout << "Enter your choice: ";

    int searchMethod;
    cin >> searchMethod;

    getSessionPerformance().sortedSearchMethod = sortedMethod;

    if (searchMethod == 1) {
        linearSearchSortedFieldMenu(target, searchField);
    }
    else if (searchMethod == 2) {
        searchList(target, searchField);
    }
    else {
        cout << "\nInvalid choice.\n";
    }
}

void ensureAllDatasetsLoaded(
    LinkedList& facilityA,
    LinkedList& facilityB,
    LinkedList& facilityC,
    bool& facilityALoaded,
    bool& facilityBLoaded,
    bool& facilityCLoaded)
{
    if (!facilityALoaded) {
        facilityALoaded = facilityA.loadCSV("datasets/dataset1_facility_a.csv");
    }

    if (!facilityBLoaded) {
        facilityBLoaded = facilityB.loadCSV("datasets/dataset2_facility_b.csv");
    }

    if (!facilityCLoaded) {
        facilityCLoaded = facilityC.loadCSV("datasets/dataset3_facility_c.csv");
    }
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

    dispatch:
        if (choice >= 5 && choice <= 20) {
            ensureAllDatasetsLoaded(
                facilityA,
                facilityB,
                facilityC,
                facilityALoaded,
                facilityBLoaded,
                facilityCLoaded
            );
        }

        switch (choice) {

        case 5: {
            cout << "\n---------- Sorting ----------\n";
            cout << "1. Bubble Sort\n";
            cout << "2. Insertion Sort\n";
            cout << "3. Quick Sort\n";
            cout << "Enter your choice: ";
            int sortMethod;
            cin >> sortMethod;
            if (sortMethod < 1 || sortMethod > 3) {
                cout << "\nInvalid choice.\n";
                break;
            }
            choice = 10 + sortMethod;
            goto dispatch;
        }

        case 6:
            choice = 14;
            goto dispatch;

        case 7: {
            cout << "\n---------- Analysis ----------\n";
            cout << "1. Age Group Analysis\n";
            cout << "2. Care Type Analysis\n";
            cout << "3. Total Billing Cost\n";
            cout << "4. Dataset Summary\n";
            cout << "5. Combined Analysis\n";
            cout << "Enter your choice: ";
            int analysisChoice;
            cin >> analysisChoice;
            if (analysisChoice < 1 || analysisChoice > 5) {
                cout << "\nInvalid choice.\n";
                break;
            }
            choice = 14 + analysisChoice;
            goto dispatch;
        }

        case 8:
            choice = 18;
            goto dispatch;

        case 9:
            choice = 20;
            goto dispatch;

        case 10:
            cout << "\nExiting MetroHealth System...\n";
            break;

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

        case 11: {
            cout << "\n---------- Sort (Bubble Sort) ----------\n";
            cout << "Sort by which field?\n";
            cout << "1. Age\n";
            cout << "2. Care Type\n";
            cout << "3. Visit Duration (Length of Stay)\n";
            cout << "Enter your choice: ";

            int fieldChoice;
            cin >> fieldChoice;

            if (fieldChoice < 1 || fieldChoice > 3) {
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

            string fieldLabel = (fieldChoice == 1) ? "Age" :
                                (fieldChoice == 2) ? "Care Type" : "Visit Duration";

            auto start = chrono::high_resolution_clock::now();
            if (fieldChoice == 1) {
                bubbleSortByAge(*target);
            }
            else if (fieldChoice == 2) {
                bubbleSortByCareType(*target);
            }
            else {
                bubbleSortByVisitDuration(*target);
            }
            auto end = chrono::high_resolution_clock::now();
            double ms = chrono::duration<double, milli>(end - start).count();
            getSessionPerformance().bubbleSort = ms;

            cout << "\n" << label << " sorted by " << fieldLabel << " (ascending).\n";
            cout << "Sort time: " << ms << " ms  (n = " << target->getSize() << ")\n";
            target->display();

            cout << "\nWould you like to search this sorted dataset now? (y/n): ";
            char searchNow;
            cin >> searchNow;
            if (searchNow == 'y' || searchNow == 'Y') {
                chooseSearchMethod(
                    *target,
                    fieldChoice,
                    PerformanceSortMethod::Bubble
                );
            }

            break;
        }

        case 12: {
            cout << "\n---------- Sort (Insertion Sort) ----------\n";
            cout << "Sort by which field?\n";
            cout << "1. Age\n";
            cout << "2. Care Type\n";
            cout << "3. Visit Duration (Length of Stay)\n";
            cout << "Enter your choice: ";

            int fieldChoice;
            cin >> fieldChoice;

            if (fieldChoice < 1 || fieldChoice > 3) {
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

            string fieldLabel = (fieldChoice == 1) ? "Age" :
                                (fieldChoice == 2) ? "Care Type" : "Visit Duration";

            auto start = chrono::high_resolution_clock::now();
            if (fieldChoice == 1) {
                insertionSortByAge(*target);
            }
            else if (fieldChoice == 2) {
                insertionSortByCareType(*target);
            }
            else {
                insertionSortByVisitDuration(*target);
            }

            auto end = chrono::high_resolution_clock::now();
            double ms = chrono::duration<double, milli>(end - start).count();
            getSessionPerformance().insertionSort = ms;

            cout << "\n========== DATASET: " << label << " ==========\n";
            cout << "\n" << label << " sorted by " << fieldLabel << " (ascending).\n";
            cout << "Sort time: " << ms << " ms  (n = " << target->getSize() << ")\n";
            target->display();

            cout << "\nWould you like to search this sorted dataset now? (y/n): ";
            char searchNow;
            cin >> searchNow;
            if (searchNow == 'y' || searchNow == 'Y') {
                chooseSearchMethod(
                    *target,
                    fieldChoice,
                    PerformanceSortMethod::Insertion
                );
            }
            break;
        }

        case 13: {
            cout << "\n---------- Sort (Quick Sort) ----------\n";
            cout << "Sort by which field?\n";
            cout << "1. Age\n";
            cout << "2. Care Type\n";
            cout << "3. Visit Duration (Length of Stay)\n";
            cout << "Enter your choice: ";

            int fieldChoice;
            cin >> fieldChoice;

            if (fieldChoice < 1 || fieldChoice > 3) {
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

            string fieldLabel = (fieldChoice == 1) ? "Age" :
                                (fieldChoice == 2) ? "Care Type" :
                                "Visit Duration";

            auto start = chrono::high_resolution_clock::now();
            if (fieldChoice == 1) {
                quickSortByAge(*target);
            }
            else if (fieldChoice == 2) {
                quickSortByCareType(*target);
            }
            else {
                quickSortByVisitDuration(*target);
            }
            auto end = chrono::high_resolution_clock::now();
            double ms = chrono::duration<double, milli>(end - start).count();
            getSessionPerformance().quickSort = ms;

            cout << "\n" << label << " sorted by " << fieldLabel << " (ascending).\n";
            cout << "Sort time: " << ms << " ms  (n = " << target->getSize() << ")\n";
            target->display();

            cout << "\nWould you like to search this sorted dataset now? (y/n): ";
            char searchNow;
            cin >> searchNow;
            if (searchNow == 'y' || searchNow == 'Y') {
                chooseSearchMethod(
                    *target,
                    fieldChoice == 1 ? 1 :
                    fieldChoice == 2 ? 2 : 3,
                    PerformanceSortMethod::Quick
                );
            }
            break;
        }

            case 14: {
            linearSearchMenu(
                facilityA,
                facilityB,
                facilityC,
                combined,
                facilityALoaded,
                facilityBLoaded,
                facilityCLoaded
            );
            break;
        }

        case 15: {
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

        case 16:
            cout << "\n========== CARE TYPE ANALYSIS (PER FACILITY) ==========\n";
            if (facilityALoaded) careTypeAnalysis(facilityA, "FACILITY A");
            if (facilityBLoaded) careTypeAnalysis(facilityB, "FACILITY B");
            if (facilityCLoaded) careTypeAnalysis(facilityC, "FACILITY C");

            combined.clear();
            if (facilityALoaded) combined.appendAll(facilityA);
            if (facilityBLoaded) combined.appendAll(facilityB);
            if (facilityCLoaded) combined.appendAll(facilityC);

            careTypeAnalysis(combined, "ALL FACILITIES");
            break;

        case 17:
            cout << "\n========== TOTAL BILLING COST (PER FACILITY) ==========\n";
            if (facilityALoaded) displayTotalBillingCost(facilityA, "FACILITY A");
            if (facilityBLoaded) displayTotalBillingCost(facilityB, "FACILITY B");
            if (facilityCLoaded) displayTotalBillingCost(facilityC, "FACILITY C");
            break;

        case 18:
            cout << "\n========== DATASET SUMMARY (PER FACILITY) ==========\n";
            if (facilityALoaded) displayDatasetSummary(facilityA, "FACILITY A");
            if (facilityBLoaded) displayDatasetSummary(facilityB, "FACILITY B");
            if (facilityCLoaded) displayDatasetSummary(facilityC, "FACILITY C");
            combined.clear();
            if (facilityALoaded) combined.appendAll(facilityA);
            if (facilityBLoaded) combined.appendAll(facilityB);
            if (facilityCLoaded) combined.appendAll(facilityC);
            displayDatasetSummary(combined, "COMBINED (A + B + C)");
            break;

        case 19:
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
            careTypeAnalysis(combined, "ALL FACILITIES");

            displayTotalBillingCost(combined, "COMBINED (ALL FACILITIES)");
            displayDatasetSummary(combined, "COMBINED (ALL FACILITIES)");
            break;
        
        case 20:
            displaySinglyLinkedListPerformance();
            break;

        case 21:
            cout << "\nExiting MetroHealth System...\n";
            choice = 10;
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

        cout << "\n\n\n\n\n";

    } while (choice != 10);

    saveSinglyLinkedListPerformanceSnapshot();
    return 0;
}