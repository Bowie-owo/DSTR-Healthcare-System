#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "patient.hpp"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Self-made resizable array (replaces std::vector).
// Doubles its capacity when full.
template <typename T>
class DynamicArray {

private:
    T* data;
    int count;
    int capacity;

    void grow() {
        int newCap = (capacity == 0) ? 4 : capacity * 2;
        T* newData = new T[newCap];

        for (int i = 0; i < count; i++)
            newData[i] = data[i];

        delete[] data;
        data = newData;
        capacity = newCap;
    }

public:

    DynamicArray() : data(nullptr), count(0), capacity(0) {}

    DynamicArray(const DynamicArray& other)
        : data(nullptr), count(0), capacity(0) {
        for (int i = 0; i < other.count; i++)
            push_back(other.data[i]);
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            data = nullptr;
            count = 0;
            capacity = 0;

            for (int i = 0; i < other.count; i++)
                push_back(other.data[i]);
        }
        return *this;
    }

    ~DynamicArray() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (count == capacity)
            grow();
        data[count++] = value;
    }

    // Appends copies of every element of 'other' to the end
    // (same idea as LinkedList::appendAll). Replaces vector::insert.
    void appendAll(const DynamicArray& other) {
        for (int i = 0; i < other.count; i++)
            push_back(other.data[i]);
    }

    void removeAt(int index) {
        if (index < 0 || index >= count)
            return;

        for (int i = index; i < count - 1; i++)
            data[i] = data[i + 1];

        count--;
    }

    void clear() {
        count = 0;
    }

    int size() const { return count; }
    bool empty() const { return count == 0; }

    T& operator[](int index) { return data[index]; }
    const T& operator[](int index) const { return data[index]; }
};


// Display a DynamicArray of patients
inline void display(const DynamicArray<Patient>& patients)
{
    cout << "\n";
    cout << "================================================================================\n";
    cout << left
         << setw(12) << "Patient ID"
         << setw(8)  << "Age"
         << setw(18) << "Care Type"
         << setw(12) << "Stay(hour)"
         << setw(12) << "Cost/hr(RM)"
         << setw(12) << "Visits/Year"
         << endl;
    cout << "================================================================================\n";

    for (int i = 0; i < patients.size(); i++)
    {
        const Patient& patient = patients[i];

        cout << left
             << setw(12) << patient.patientID
             << setw(8)  << patient.age
             << setw(18) << patient.careType;
        cout << defaultfloat << setprecision(6) << setw(12) << patient.lengthOfStay;
        cout << setw(12) << fixed << setprecision(2) << patient.baseCostPerHour;
        cout << defaultfloat << setw(12) << patient.daysVisitsPerYear
             << endl;
    }

    cout << "================================================================================\n";
}

#endif