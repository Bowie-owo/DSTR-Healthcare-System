#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "patient.hpp"
#include "Utils.hpp"
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

    int getSize() const {
        return size;
    }

    // Appends copies of every patient from 'other' onto the end of
    // this list. Used to build a combined dataset across multiple
    // facility lists (e.g. Facility A + B + C into one pool).
    void appendAll(const LinkedList& other) {

        const Node* current = other.getHead();

        while (current != nullptr) {
            insertBack(current->data);
            current = current->next;
        }
    }

    // Read-only access to the head node so external modules
    // (analysis files) can traverse the list without needing
    // to be friends of / members of LinkedList.
    const Node* getHead() const {
        return head;
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

};

#endif