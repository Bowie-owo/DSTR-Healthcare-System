#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "patient.hpp"
#include "ageGroupAnalysis.hpp"
#include "billingAnalysis.hpp"
#include "careTypeAnalysis.hpp"

using namespace std;

void displayMenu() {

	cout << "\n";
	cout << "================================================\n";
	cout << "              METROHEALTH SYSTEM\n";
    cout << "              ARRAY IMPLEMENTATION\n";
	cout << "================================================\n";
	cout << "1. Load and Display Facility A\n";
	cout << "2. Load and Display Facility B\n";
	cout << "3. Load and Display Facility C\n";
	cout << "4. Load and Display All Datasets\n";
	cout << "5. Sorting (will further decide how to do)\n";
	cout << "6. Searching(will further decide how to do)\n";
	cout << "7. Care Type Analysis (per facility+combined) - jiahuey\n";
	cout << "8. Age Group Analysis(per facility+combined) - sinyi\n";
	cout << "9. Total Billing Cost(per facility+combined) - sinyi\n";
    cout << "10. Dataset Summary - jiahuey \n";
    cout << "11. Performance Summary (Comparison View) - sinyi\n";
    cout << "12. Exit\n";
	cout << "================================================\n";
	cout << "Enter your choice: ";
}

bool loadDataset(const string& filename, vector<Patient>& patients) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file: " << filename << endl;
        return false;
    }

    patients.clear();

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream stream(line);
        string value;
        Patient patient;

        getline(stream, patient.patientID, ',');
        getline(stream, value, ',');
        patient.age = stoi(value);
        getline(stream, patient.careType, ',');
        getline(stream, value, ',');
        patient.lengthOfStay = stod(value);
        getline(stream, value, ',');
        patient.baseCostPerHour = stod(value);
        getline(stream, value, ',');
        patient.daysVisitsPerYear = stoi(value);

        patients.push_back(patient);
    }

    return true;
}

void displayDataset(const vector<Patient>& patients, const string& facilityName) {
    cout << "\n========== " << facilityName << " ==========\n";
    cout << left
         << setw(12) << "Patient ID"
         << setw(8) << "Age"
         << setw(20) << "Care Type"
         << setw(12) << "Stay(hr)"
         << setw(12) << "Cost/hr"
         << setw(12) << "Visits/Year" << endl;
    cout << string(76, '-') << endl;

    for (const Patient& patient : patients) {
        cout << left
             << setw(12) << patient.patientID
             << setw(8) << patient.age
             << setw(20) << patient.careType
             << setw(12) << patient.lengthOfStay
             << setw(12) << fixed << setprecision(2) << patient.baseCostPerHour
             << setw(12) << patient.daysVisitsPerYear << endl;
    }

    cout << "Total patients: " << patients.size() << endl;
}

void loadAndDisplayFacility(const string& filename, const string& facilityName) {
    vector<Patient> patients;
    if (loadDataset(filename, patients)) {
        displayDataset(patients, facilityName);
    }
}

int main() {

    int choice = 0;

    do {
        displayMenu();
        if (!(cin >> choice)) {
            cout << "\nInvalid input. Exiting Array implementation...\n";
            break;
        }

    switch (choice) {

        case 1:
            loadAndDisplayFacility("datasets/dataset1_facility_a.csv", "FACILITY A");
            break;

        case 2:
            loadAndDisplayFacility("datasets/dataset2_facility_b.csv", "FACILITY B");
            break;

        case 3:
            loadAndDisplayFacility("datasets/dataset3_facility_c.csv", "FACILITY C");
            break;

        case 4:
            loadAndDisplayFacility("datasets/dataset1_facility_a.csv", "FACILITY A");
            loadAndDisplayFacility("datasets/dataset2_facility_b.csv", "FACILITY B");
            loadAndDisplayFacility("datasets/dataset3_facility_c.csv", "FACILITY C");
            break;

        // Sorting
        case 5:
            cout << "\nThis feature is not implemented yet.\n";
            break;

        // Searching
        case 6:
            cout << "\nThis feature is not implemented yet.\n";
            break;

        // Care Type Analysis
        case 7:
        {
            vector<Patient> facilityA;
            vector<Patient> facilityB;
            vector<Patient> facilityC;

            loadDataset("datasets/dataset1_facility_a.csv", facilityA);
            loadDataset("datasets/dataset2_facility_b.csv", facilityB);
            loadDataset("datasets/dataset3_facility_c.csv", facilityC);

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

        // AGE GROUP ANALYSIS
        case 8:
        {
            vector<Patient> facilityA;
            vector<Patient> facilityB;
            vector<Patient> facilityC;

            loadDataset("datasets/dataset1_facility_a.csv", facilityA);
            loadDataset("datasets/dataset2_facility_b.csv", facilityB);
            loadDataset("datasets/dataset3_facility_c.csv", facilityC);

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


        // Total Billing Cost
        case 9:
        {
            vector<Patient> facilityA;
            vector<Patient> facilityB;
            vector<Patient> facilityC;

            loadDataset("datasets/dataset1_facility_a.csv", facilityA);
            loadDataset("datasets/dataset2_facility_b.csv", facilityB);
            loadDataset("datasets/dataset3_facility_c.csv", facilityC);

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

        // Dataset Summary
        case 10:
            cout << "\nThis feature is not implemented yet.\n";
            break;

        // Performance Summary
        case 11:
            cout << "\nThis feature is not implemented yet.\n";
            break;

        case 12:
            cout << "\nExiting Array implementation...\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
            } while (choice != 12);

            return 0;
        }