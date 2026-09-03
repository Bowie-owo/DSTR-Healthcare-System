#include <iostream>
#include "LinkedList.hpp"

using namespace std;

void displayMenu() {
    cout << "\n";
    cout << "==============================================\n";
    cout << "          METROHEALTH SYSTEM\n";
    cout << "     SINGLY LINKED LIST IMPLEMENTATION\n";
    cout << "==============================================\n";
    cout << "1. Load Facility A Dataset\n";
    cout << "2. Load Facility B Dataset\n";
    cout << "3. Load Facility C Dataset\n";
    cout << "4. Display Patients\n";
    cout << "5. Exit\n";
    cout << "==============================================\n";
    cout << "Enter your choice: ";
}

int main() {

    LinkedList patients;

    int choice;
    bool dataLoaded = false;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {

        case 1:
            patients = LinkedList();

            if (patients.loadCSV("datasets/dataset1.csv")) {
                cout << "\nFacility A dataset loaded successfully!\n";
                cout << "Number of patients: "
                     << patients.getSize() << endl;

                dataLoaded = true;
            }
            break;

        case 2:
            patients = LinkedList();

            if (patients.loadCSV("datasets/dataset2.csv")) {
                cout << "\nFacility B dataset loaded successfully!\n";
                cout << "Number of patients: "
                     << patients.getSize() << endl;

                dataLoaded = true;
            }
            break;

        case 3:
            patients = LinkedList();

            if (patients.loadCSV("datasets/dataset3.csv")) {
                cout << "\nFacility C dataset loaded successfully!\n";
                cout << "Number of patients: "
                     << patients.getSize() << endl;

                dataLoaded = true;
            }
            break;

        case 4:
            if (!dataLoaded) {
                cout << "\nPlease load a dataset first.\n";
            }
            else {
                patients.display();
            }
            break;

        case 5:
            cout << "\nExiting MetroHealth System...\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}