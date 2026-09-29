#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "patient.hpp"
#include "ageGroupAnalysis.hpp"
#include "billingAnalysis.hpp"
#include "careTypeAnalysis.hpp"
#include "searching.hpp"
#include "sorting.hpp"
#include "analysis.hpp"
#include "array.hpp"
#include "helpers.hpp"
#include "utils.hpp"

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
	cout << "5. Sorting\n";
	cout << "6. Searching\n";
	cout << "7. Analysis\n";
    cout << "8. Dataset Summary - jiahuey \n";
    cout << "9. Performance Summary (Comparison View) - sinyi\n";
    cout << "10. Exit\n";
	cout << "================================================\n";
	cout << "Enter your choice: ";
}

bool loadDataset(const string& filename, DynamicArray<Patient>& patients) {
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

void displayDataset(const DynamicArray<Patient>& patients, const string& facilityName) {
    cout << "\n========== " << facilityName << " ==========\n";
    cout << left
         << setw(12) << "Patient ID"
         << setw(8) << "Age"
         << setw(20) << "Care Type"
         << setw(12) << "Stay(hr)"
         << setw(12) << "Cost/hr"
         << setw(12) << "Visits/Year" << endl;
    cout << string(76, '-') << endl;

    for (int i = 0; i < patients.size(); i++) {
        const Patient& patient = patients[i];
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
    DynamicArray<Patient> patients;
    if (loadDataset(filename, patients)) {
        displayDataset(patients, facilityName);
    }
}

void displayFacilitySummary(const DynamicArray<Patient>& patients, const string& facilityName) {
    const string line(80, '=');

    double totalStayHours = 0.0;
    double totalMedicalCost = 0.0;
    double avgCostPerPatient = 0.0;

    // Care types found in this facility, with a patient count for each
    DynamicArray<string> careTypes;
    DynamicArray<int> careTypeCounts;

    for (int p = 0; p < patients.size(); p++) {
        const Patient& patient = patients[p];
        totalStayHours += patient.lengthOfStay;
        totalMedicalCost += patient.lengthOfStay * patient.baseCostPerHour * patient.daysVisitsPerYear;

        bool found = false;
        for (int i = 0; i < careTypes.size(); i++) {
            if (careTypes[i] == patient.careType) {
                careTypeCounts[i]++;
                found = true;
                break;
            }
        }
        if (!found) {
            careTypes.push_back(patient.careType);
            careTypeCounts.push_back(1);
        }
    }

    if (!patients.empty()) {
        avgCostPerPatient = totalMedicalCost / patients.size();
    }

    int ageCounts[NUM_AGE_GROUPS];
    int outOfRange = countAgeGroups(patients, ageCounts);

    cout << "\n" << line << "\n";
    cout << "                   DATASET SUMMARY - " << facilityName << "\n";
    cout << line << "\n";

    cout << left << setw(28) << "Total Patients"
         << ": " << patients.size() << "\n";
    cout << left << setw(28) << "Total Stay Hours"
         << ": " << defaultfloat << setprecision(6) << totalStayHours << " hrs\n";
    cout << left << setw(28) << "Total Medical Cost"
         << ": RM " << fixed << setprecision(2) << totalMedicalCost << "\n";
    cout << left << setw(28) << "Average Cost Per Patient"
         << ": RM " << fixed << setprecision(2) << avgCostPerPatient << "\n";

    cout << "\nAge Groups Present:\n";
    bool anyAgeGroup = false;
    for (int i = 0; i < NUM_AGE_GROUPS; i++) {
        if (ageCounts[i] > 0) {
            cout << "  - " << left << setw(38)
                 << getAgeGroupName(i) << ageCounts[i] << " patients\n";
            anyAgeGroup = true;
        }
    }
    if (outOfRange > 0) {
        cout << "  - " << left << setw(38) << "Unknown / Out of range"
             << outOfRange << " patients\n";
        anyAgeGroup = true;
    }
    if (!anyAgeGroup) {
        cout << "  (none)\n";
    }

    cout << "\nCare Types Available:\n";
    if (careTypes.empty()) {
        cout << "  (none)\n";
    }
    for (size_t i = 0; i < careTypes.size(); i++) {
        cout << "  - " << left << setw(38) << careTypes[i]
             << careTypeCounts[i] << " patients\n";
    }

    cout << line << "\n";
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
        {
            DynamicArray<Patient> facilityA;
            DynamicArray<Patient> facilityB;
            DynamicArray<Patient> facilityC;
            DynamicArray<Patient> combined;

            loadDataset("datasets/dataset1_facility_a.csv", facilityA);
            loadDataset("datasets/dataset2_facility_b.csv", facilityB);
            loadDataset("datasets/dataset3_facility_c.csv", facilityC);

            buildCombined(facilityA, facilityB, facilityC, combined);

            sortingMenu(facilityA, facilityB, facilityC, combined);

            break;
        }

        // Searching
        case 6:
        {
            DynamicArray<Patient> facilityA;
            DynamicArray<Patient> facilityB;
            DynamicArray<Patient> facilityC;
            DynamicArray<Patient> combined;

            loadDataset("datasets/dataset1_facility_a.csv", facilityA);
            loadDataset("datasets/dataset2_facility_b.csv", facilityB);
            loadDataset("datasets/dataset3_facility_c.csv", facilityC);

            buildCombined(facilityA, facilityB, facilityC, combined);

            searchingMenu(facilityA, facilityB, facilityC, combined);

            break;
        }

        // Analysis
        case 7:
        {
            DynamicArray<Patient> facilityA;
            DynamicArray<Patient> facilityB;
            DynamicArray<Patient> facilityC;
            DynamicArray<Patient> combined;

            loadDataset("datasets/dataset1_facility_a.csv", facilityA);
            loadDataset("datasets/dataset2_facility_b.csv", facilityB);
            loadDataset("datasets/dataset3_facility_c.csv", facilityC);

            buildCombined(facilityA, facilityB, facilityC, combined);

            analysisMenu(facilityA, facilityB, facilityC, combined);

            break;
        }

        // Dataset Summary
        case 8:
        {
            DynamicArray<Patient> facilityA;
            DynamicArray<Patient> facilityB;
            DynamicArray<Patient> facilityC;
            DynamicArray<Patient> combined;

            bool okA = loadDataset("datasets/dataset1_facility_a.csv", facilityA);
            bool okB = loadDataset("datasets/dataset2_facility_b.csv", facilityB);
            bool okC = loadDataset("datasets/dataset3_facility_c.csv", facilityC);

            if (!okA || !okB || !okC) {
                cout << "\nSummary cancelled: one or more datasets failed to load.\n";
                break;
            }

            buildCombined(facilityA, facilityB, facilityC, combined);
       
            displayFacilitySummary(facilityA, "FACILITY A");
            displayFacilitySummary(facilityB, "FACILITY B");
            displayFacilitySummary(facilityC, "FACILITY C");
            displayFacilitySummary(combined, "COMBINED (A + B + C)");

            break;
        }

        // Performance Summary
        case 9:
            cout << "\nThis feature is not implemented yet.\n";
            break;

        case 10:
            cout << "\nExiting Array implementation...\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
            } while (choice != 10);

            return 0;
            
        }