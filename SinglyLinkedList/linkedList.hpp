#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Patient.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
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

public:
    // Constructor
    LinkedList() {
        head = nullptr;
        size = 0;
    }

    // Destructor
    ~LinkedList() {
        Node* current = head;

        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Insert patient at the end
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

    // Load CSV file
    bool loadCSV(string filename) {
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "Error: Unable to open file: " << filename << endl;
            return false;
        }

        string line;

        // Skip header
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string value;

            Patient patient;

            // Patient ID
            getline(ss, patient.patientID, ',');

            // Age
            getline(ss, value, ',');
            patient.age = stoi(value);

            // Care Type
            getline(ss, patient.careType, ',');

            // Length of Stay
            getline(ss, value, ',');
            patient.lengthOfStay = stod(value);

            // Base Cost Per Hour
            getline(ss, value, ',');
            patient.baseCostPerHour = stod(value);

            // Days Visits Per Year
            getline(ss, value, ',');
            patient.daysVisitsPerYear = stoi(value);

            insertBack(patient);
        }

        file.close();

        return true;
    }

    // Display patients
    void display() {
        Node* current = head;

        cout << "\n";
        cout << "====================================================================\n";
        cout << "Patient ID   Age   Care Type       Stay(hr)   Cost/hr   Visits/Year\n";
        cout << "====================================================================\n";

        while (current != nullptr) {
            cout << current->data.patientID << "\t"
                 << current->data.age << "\t"
                 << current->data.careType << "\t\t"
                 << current->data.lengthOfStay << "\t"
                 << current->data.baseCostPerHour << "\t"
                 << current->data.daysVisitsPerYear << endl;

            current = current->next;
        }

        cout << "====================================================================\n";
    }

    // Get number of patients
    int getSize() {
        return size;
    }
};

#endif