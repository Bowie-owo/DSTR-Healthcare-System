#include <iostream>
#include <cstdlib>
#include <chrono>
#include <string>

using namespace std;

void displayMainMenu() {
    cout << "\n";
    cout << "============================================\n";
    cout << "           METROHEALTH SYSTEM\n";
    cout << "============================================\n";
    cout << "1. Array\n";
    cout << "2. Singly Linked List\n";
    cout << "3. Exit\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
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
                string command = "cd Array && g++ main.cpp -o \"" + executable +
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
                string command = "cd SinglyLinkedList && g++ main.cpp -o \"" + executable +
                    "\" && \"" + executable + "\" && del \"" + executable + "\"";
                system(command.c_str());
            }
            break;

        case 3:
            cout << "\nExiting MetroHealth System...\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}