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
    // ==========================================

    void ageGroupAnalysis() {

        string ageGroups[5] = {
            "Pediatrics & Adolescents",
            "Young Adults / University Students",
            "Working Adults (Early Career)",
            "Working Adults (Late Career)",
            "Senior Citizens / Geriatric Care"
        };

        int minAge[5] = {0, 18, 26, 46, 61};
        int maxAge[5] = {17, 25, 45, 60, 100};

        cout << "\n";
        cout << "==============================================================================================================\n";
        cout << "                              AGE GROUP ANALYSIS\n";
        cout << "==============================================================================================================\n";

        cout << left
             << setw(38) << "Age Group"
             << setw(10) << "Patients"
             << setw(18) << "Total Cost"
             << setw(18) << "Average Cost"
             << setw(30) << "Most Preferred Care"
             << endl;

        cout << "--------------------------------------------------------------------------------------------------------------\n";

        for (int i = 0; i < 5; i++) {

            int patientCount = 0;
            double totalCost = 0;

            string careTypes[10];
            int careCounts[10];
            int careTypeCount = 0;

            Node* current = head;

            while (current != nullptr) {

                int age = current->data.age;

                if (age >= minAge[i] && age <= maxAge[i]) {

                    patientCount++;

                    totalCost += calculateCost(current->data);

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
                        careCounts[careTypeCount] = 1;
                        careTypeCount++;

                    }
                    else {
                        careCounts[position]++;
                    }
                }

                current = current->next;
            }

            string mostPreferred = "None";
            int highestCount = 0;

            for (int j = 0; j < careTypeCount; j++) {

                if (careCounts[j] > highestCount) {
                    highestCount = careCounts[j];
                    mostPreferred = careTypes[j];
                }
            }

            double averageCost = 0;

            if (patientCount > 0) {
                averageCost = totalCost / patientCount;
            }

            cout << left
                 << setw(38) << ageGroups[i]
                 << setw(10) << patientCount
                 << setw(18) << fixed << setprecision(2) << totalCost
                 << setw(18) << averageCost
                 << setw(30) << mostPreferred
                 << endl;
        }

        cout << "==============================================================================================================\n";
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