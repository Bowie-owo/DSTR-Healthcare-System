#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Patient {
    string patientID;
    int age;
    string careType;
    double lengthOfStay;
    double baseCostPerHour;
    int daysVisitsPerYear;
};

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
	cout << "5.  Sorting (will further decide how to do)\n";
	cout << "6. Searching(will further decide how to do)\n";
	cout << "7. Length of Stay Analysis (per facility+combined) - jiahuey\n";
	cout << "8. Age Group Analysis(per facility+combined) - sinyi\n";
	cout << "9. Care Type Analysis(per facility+combined) - jiahuey\n";
	cout << "10. Total Billing Cost(per facility+combined) - sinyi\n";
    cout << "11. Dataset Summary - jiahuey \n";
    cout << "12. Performance Summary (Comparison View) - sinyi\n";
    cout << "13. Exit\n";
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

        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            cout << "\nThis feature is not implemented yet.\n";
            break;

        case 13:
            cout << "\nExiting Array implementation...\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 13);

    return 0;
}