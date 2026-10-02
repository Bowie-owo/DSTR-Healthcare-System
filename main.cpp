#include <iostream>
#include <cstdlib>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

void displayMainMenu() {
    cout << "\n";
    cout << "============================================\n";
    cout << "           METROHEALTH SYSTEM\n";
    cout << "============================================\n";
    cout << "1. Array\n";
    cout << "2. Singly Linked List\n";
    cout << "3. Overall Performance Summary\n";
    cout << "4. Exit\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
}

bool loadPerformanceSnapshot(const string& filename, vector<double>& values) {
    ifstream file(filename);
    values.clear();

    double value;
    while (file >> value) {
        values.push_back(value);
    }

    return values.size() == 10;
}

void displayOverallPerformance() {
    const string labels[] = {
        "Sorting Method: Bubble Sort",
        "Sorting Method: Insertion Sort",
        "Sorting Method: Quick Sort",
        "Searching (Sorted): Bubble Sort + Linear Search",
        "Searching (Sorted): Insertion Sort + Linear Search",
        "Searching (Sorted): Quick Sort + Linear Search",
        "Searching (Sorted): Bubble Sort + Binary Search",
        "Searching (Sorted): Insertion Sort + Binary Search",
        "Searching (Sorted): Quick Sort + Binary Search",
        "Searching (Unsorted): Linear Search"
    };

    vector<double> arrayValues;
    vector<double> linkedListValues;
    bool hasArrayValues = loadPerformanceSnapshot(
        "array_performance_snapshot.txt", arrayValues);
    bool hasLinkedListValues = loadPerformanceSnapshot(
        "singly_linked_list_performance_snapshot.txt", linkedListValues);

    cout << "\n==============================================================\n";
    cout << "              OVERALL PERFORMANCE SUMMARY\n";
    cout << "==============================================================\n";
    cout << left << setw(58) << "Operation / Method"
         << right << setw(16) << "Array (ms)"
         << setw(24) << "Singly Linked List (ms)" << "\n";
    cout << string(98, '-') << "\n";

    for (int i = 0; i < 10; i++) {
        cout << left << setw(58) << labels[i]
             << right << setw(16) << fixed << setprecision(2);

        if (hasArrayValues) {
            cout << arrayValues[i];
        } else {
            cout << "N/A";
        }

        cout << setw(24);
        if (hasLinkedListValues) {
            cout << linkedListValues[i];
        } else {
            cout << "N/A";
        }
        cout << "\n";
    }

    cout << string(98, '=') << "\n";
    if (!hasArrayValues || !hasLinkedListValues) {
        cout << "Run both implementations first to populate all performance values.\n";
    }
}

int main() {

    int choice = 0;

    do {
        displayMainMenu();
        if (!(cin >> choice)) {
            cout << "\nInvalid input. Exiting MetroHealth System...\n";
            break;
        }

        switch (choice) {

        case 1:
            cout << "\nOpening Array...\n";
            {
                string executable = "%TEMP%\\MetroHealthArray_" +
                    to_string(chrono::steady_clock::now().time_since_epoch().count()) +
                    ".exe";
                string command = "cd Array && g++ -std=c++17 main.cpp -o \"" + executable +
                    "\" && \"" + executable + "\" && del \"" + executable + "\"";
                system(command.c_str());
            }
            break;

        case 2:
            cout << "\nOpening Singly Linked List...\n";
            {
                string executable = "%TEMP%\\MetroHealthSinglyLinkedList_" +
                    to_string(chrono::steady_clock::now().time_since_epoch().count()) +
                    ".exe";
                string command = "cd SinglyLinkedList && g++ -std=c++17 main.cpp -o \"" + executable +
                    "\" && \"" + executable + "\" && del \"" + executable + "\"";
                system(command.c_str());
            }
            break;

        case 3:
            displayOverallPerformance();
            break;

        case 4:
            cout << "\nExiting MetroHealth System...\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}