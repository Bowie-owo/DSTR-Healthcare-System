#ifndef PATIENTARRAY_HPP
#define PATIENTARRAY_HPP

#include "patient.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

class PatientArray {

private:
    Patient* data;
    int size;
    int capacity;

    // Doubles capacity (or starts at 8) whenever the array is full.
    // Amortized O(1) per insertBack, same growth strategy as
    // std::vector, just self-written since STL containers aren't
    // allowed.
    void grow() {

        int newCapacity = (capacity == 0) ? 8 : capacity * 2;
        Patient* newData = new Patient[newCapacity];

        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:

    PatientArray() {
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    ~PatientArray() {
        clear();
    }

    void clear() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    void insertBack(Patient patient) {

        if (size >= capacity) {
            grow();
        }

        data[size] = patient;
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

        getline(file, line); // skip header row

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

    // Exposed mainly for the Performance Summary option (memory usage
    // comparisons need to know allocated capacity, not just used size).
    int getCapacity() const {
        return capacity;
    }

    // Read-only element access for analysis files (age group, billing,
    // care type, etc.) — mirrors how those files traverse LinkedList
    // via getHead().
    const Patient& at(int index) const {
        return data[index];
    }

    // Mutable element access for algorithm files (sorting) that need
    // to reorder or modify elements in place.
    Patient& operator[](int index) {
        return data[index];
    }

    // Appends copies of every patient from 'other' onto the end of
    // this array. Used to build a combined dataset across multiple
    // facility arrays (e.g. Facility A + B + C into one pool) —
    // matches LinkedList::appendAll.
    void appendAll(const PatientArray& other) {

        for (int i = 0; i < other.getSize(); i++) {
            insertBack(other.at(i));
        }
    }

    void display() {

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

        for (int i = 0; i < size; i++) {
            cout << left
                 << setw(12) << data[i].patientID
                 << setw(8)  << data[i].age
                 << setw(18) << data[i].careType
                 << setw(12) << data[i].lengthOfStay
                 << setw(12) << fixed << setprecision(2)
                 << data[i].baseCostPerHour
                 << setw(12) << data[i].daysVisitsPerYear
                 << endl;
        }

        cout << "================================================================================\n";
    }

};

#endif