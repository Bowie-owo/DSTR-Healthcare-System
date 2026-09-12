#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "patient.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

struct Node {
    Patient data;
    Node* next;

    Node(Patient patient) {
        data = patient;
        next = nullptr;
    }
};

class LinkedList {

private:
    Node* head;
    int size;

    string getAgeGroup(int age) {
        if (age >= 0 && age <= 17)
            return "Pediatrics & Adolescents";
        else if (age >= 18 && age <= 25)
            return "Young Adults / University Students";
        else if (age >= 26 && age <= 45)
            return "Working Adults (Early Career)";
        else if (age >= 46 && age <= 60)
            return "Working Adults (Late Career)";
        else if (age >= 61 && age <= 100)
            return "Senior Citizens / Geriatric Care";
        else
            return "Unknown";
    }

    double calculateCost(Patient patient) {
        return patient.lengthOfStay
             * patient.baseCostPerHour
             * patient.daysVisitsPerYear;
    }

    // Formats a number with thousand separators and 2 decimal places,
    // e.g. 12000.5 -> "12,000.50"
    string formatWithCommas(double value) {

        ostringstream oss;
        oss << fixed << setprecision(2) << value;
        string numStr = oss.str();

        size_t dotPos = numStr.find('.');
        string intPart = numStr.substr(0, dotPos);
        string decPart = numStr.substr(dotPos);

        bool negative = false;
        if (!intPart.empty() && intPart[0] == '-') {
            negative = true;
            intPart = intPart.substr(1);
        }

        string result;
        int count = 0;

        for (int i = (int)intPart.size() - 1; i >= 0; i--) {
            result = intPart[i] + result;
            count++;
            if (count % 3 == 0 && i != 0) {
                result = "," + result;
            }
        }

        if (negative) result = "-" + result;

        return result + decPart;
    }

public:

    LinkedList() {
        head = nullptr;
        size = 0;
    }

    ~LinkedList() {
        clear();
    }

    void clear() {
        Node* current = head;

        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }

        head = nullptr;
        size = 0;
    }

    void insertBack(Patient patient) {

        Node* newNode = new Node(patient);

        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* current = head;

            while (current->next != nullptr) {
                current = current->next;
            }

            current->next = newNode;
        }

        size++;
    }

    bool loadCSV(string filename) {

        clear();

        ifstream file(filename);

        if (!file.is_open()) {
            cout << "Error: Unable to open file: "
                 << filename << endl;
            return false;
        }

        string line;

        getline(file, line);

        while (getline(file, line)) {

            if (line.empty())
                continue;

            stringstream ss(line);
            string value;

            Patient patient;

            getline(ss, patient.patientID, ',');

            getline(ss, value, ',');
            patient.age = stoi(value);

            getline(ss, patient.careType, ',');

            getline(ss, value, ',');
            patient.lengthOfStay = stod(value);

            getline(ss, value, ',');
            patient.baseCostPerHour = stod(value);

            getline(ss, value, ',');
            patient.daysVisitsPerYear = stoi(value);

            insertBack(patient);
        }

        file.close();

        return true;
    }

    int getSize() {
        return size;
    }

    void display() {

        Node* current = head;

        cout << "\n";
        cout << "================================================================================\n";
        cout << left
             << setw(12) << "Patient ID"
             << setw(8)  << "Age"
             << setw(18) << "Care Type"
             << setw(12) << "Stay(hr)"
             << setw(12) << "Cost/hr"
             << setw(12) << "Visits/Year"
             << endl;
        cout << "================================================================================\n";

        while (current != nullptr) {

            cout << left
                 << setw(12) << current->data.patientID
                 << setw(8)  << current->data.age
                 << setw(18) << current->data.careType
                 << setw(12) << current->data.lengthOfStay
                 << setw(12) << fixed << setprecision(2)
                 << current->data.baseCostPerHour
                 << setw(12) << current->data.daysVisitsPerYear
                 << endl;

            current = current->next;
        }

        cout << "================================================================================\n";
    }

    // ==========================================
    // AGE GROUP ANALYSIS
    // For each age group: a Care-Type breakdown table
    // (Patient Count, Total Cost, Average Cost per Patient),
    // sorted by Patient Count descending, plus a total
    // billing figure for the age group.
    // ==========================================

    void ageGroupAnalysis() {

        string ageGroups[5] = {
            "Pediatrics & Adolescents",
            "Young Adults / University Students",
            "Working Adults (Early Career)",
            "Working Adults (Late Career)",
            "Senior Citizens / Geriatric Care"
        };

        string ageRanges[5] = {
            "0-17", "18-25", "26-45", "46-60", "61-100"
        };

        int minAge[5] = {0, 18, 26, 46, 61};
        int maxAge[5] = {17, 25, 45, 60, 100};

        for (int i = 0; i < 5; i++) {

            string careTypes[20];
            double careCosts[20];
            int careCounts[20];
            int careTypeCount = 0;

            int patientCount = 0;
            double ageGroupTotal = 0;

            Node* current = head;

            while (current != nullptr) {

                int age = current->data.age;

                if (age >= minAge[i] && age <= maxAge[i]) {

                    patientCount++;

                    double cost = calculateCost(current->data);
                    ageGroupTotal += cost;

                    string care = current->data.careType;
                    int position = -1;

                    for (int j = 0; j < careTypeCount; j++) {
                        if (careTypes[j] == care) {
                            position = j;
                            break;
                        }
                    }

                    if (position == -1) {
                        careTypes[careTypeCount] = care;
                        careCosts[careTypeCount] = cost;
                        careCounts[careTypeCount] = 1;
                        careTypeCount++;
                    }
                    else {
                        careCosts[position] += cost;
                        careCounts[position]++;
                    }
                }

                current = current->next;
            }

            // Sort care types by patient count, descending
            // (selection sort — keeps the "most preferred" care
            // type as the first row, matching the sample output)
            for (int a = 0; a < careTypeCount - 1; a++) {

                int maxIdx = a;

                for (int b = a + 1; b < careTypeCount; b++) {
                    if (careCounts[b] > careCounts[maxIdx]) {
                        maxIdx = b;
                    }
                }

                if (maxIdx != a) {
                    string tmpCare = careTypes[a];
                    careTypes[a] = careTypes[maxIdx];
                    careTypes[maxIdx] = tmpCare;

                    int tmpCount = careCounts[a];
                    careCounts[a] = careCounts[maxIdx];
                    careCounts[maxIdx] = tmpCount;

                    double tmpCost = careCosts[a];
                    careCosts[a] = careCosts[maxIdx];
                    careCosts[maxIdx] = tmpCost;
                }
            }

            cout << "\n";
            cout << "Age Group: " << ageRanges[i]
                 << " (" << ageGroups[i] << ")\n";
            cout << "--------------------------------------------------------------------------------\n";

            cout << left
                 << setw(16) << "Care Type"
                 << setw(16) << "Patient Count"
                 << setw(18) << "Total Cost ($)"
                 << setw(30) << "Average Cost per Patient ($)"
                 << endl;

            cout << "--------------------------------------------------------------------------------\n";

            if (patientCount == 0) {

                cout << "No patients in this age group.\n";
            }
            else {

                for (int j = 0; j < careTypeCount; j++) {

                    double avgCost = careCosts[j] / careCounts[j];

                    cout << left
                         << setw(16) << careTypes[j]
                         << setw(16) << careCounts[j]
                         << setw(18) << formatWithCommas(careCosts[j])
                         << setw(30) << formatWithCommas(avgCost)
                         << endl;
                }
            }

            cout << "--------------------------------------------------------------------------------\n";
            cout << "Total Billing for Age Group: $"
                 << formatWithCommas(ageGroupTotal) << "\n";
        }
    }

    // ==========================================
    // TOTAL BILLING COST
    // ==========================================

    double getTotalBillingCost() {

        double total = 0;

        Node* current = head;

        while (current != nullptr) {

            total += calculateCost(current->data);

            current = current->next;
        }

        return total;
    }

    void displayTotalBillingCost(string facilityName) {

        double total = getTotalBillingCost();

        cout << "\n";
        cout << "==============================================\n";
        cout << "        " << facilityName << "\n";
        cout << "        TOTAL MEDICAL BILLING\n";
        cout << "==============================================\n";
        cout << fixed << setprecision(2);
        cout << "Total Patients : " << size << endl;
        cout << "Total Cost     : RM " << total << endl;
        cout << "==============================================\n";
    }

    // ==========================================
    // COST BY CARE TYPE
    // ==========================================

    void careTypeAnalysis() {

        string careTypes[20];
        double careCosts[20];
        int careCounts[20];
        double careDuration[20];

        int careTypeCount = 0;

        Node* current = head;

        while (current != nullptr) {

            string care = current->data.careType;

            int position = -1;

            for (int i = 0; i < careTypeCount; i++) {

                if (careTypes[i] == care) {
                    position = i;
                    break;
                }
            }

            double cost = calculateCost(current->data);

            if (position == -1) {

                careTypes[careTypeCount] = care;
                careCosts[careTypeCount] = cost;
                careCounts[careTypeCount] = 1;
                careDuration[careTypeCount] = current->data.lengthOfStay;

                careTypeCount++;
            }
            else {

                careCosts[position] += cost;
                careCounts[position]++;
                careDuration[position] += current->data.lengthOfStay;
            }

            current = current->next;
        }

        cout << "\n";
        cout << "================================================================================\n";
        cout << "                         CARE TYPE ANALYSIS\n";
        cout << "================================================================================\n";

        cout << left
             << setw(20) << "Care Type"
             << setw(15) << "Patients"
             << setw(20) << "Total Cost"
             << setw(20) << "Total Stay Hours"
             << endl;

        cout << "--------------------------------------------------------------------------------\n";

        for (int i = 0; i < careTypeCount; i++) {

            cout << left
                 << setw(20) << careTypes[i]
                 << setw(15) << careCounts[i]
                 << setw(20) << fixed << setprecision(2)
                 << careCosts[i]
                 << setw(20) << careDuration[i]
                 << endl;
        }

        cout << "================================================================================\n";
    }

    // ==========================================
    // DATASET SUMMARY
    // ==========================================

    void displayDatasetSummary(string facilityName) {

        double totalCost = getTotalBillingCost();

        double totalStay = 0;

        Node* current = head;

        while (current != nullptr) {

            totalStay += current->data.lengthOfStay;

            current = current->next;
        }

        double averageStay = 0;

        if (size > 0) {
            averageStay = totalStay / size;
        }

        cout << "\n";
        cout << "============================================================\n";
        cout << "              " << facilityName << " SUMMARY\n";
        cout << "============================================================\n";

        cout << fixed << setprecision(2);

        cout << "Number of Patients       : " << size << endl;
        cout << "Total Medical Cost       : RM " << totalCost << endl;
        cout << "Total Stay Duration      : " << totalStay << " hours" << endl;
        cout << "Average Stay Duration    : " << averageStay << " hours" << endl;

        cout << "============================================================\n";
    }

};

#endif