#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP

#include "patientArray.hpp"

// Contract: sorts 'arr' in place, ascending by age.
// Owner: bowie
void bubbleSortByAge(PatientArray& arr) {

    int n = arr.getSize();

    for (int i = 0; i < n - 1; i++) {

        bool swapped = false;

        for (int j = 0; j < n - 1 - i; j++) {

            if (arr[j].age > arr[j + 1].age) {
                Patient temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

// Contract: sorts 'arr' in place, ascending alphabetically by care type.
// Owner: bowie
void bubbleSortByCareType(PatientArray& arr) {

    int n = arr.getSize();

    for (int i = 0; i < n - 1; i++) {

        bool swapped = false;

        for (int j = 0; j < n - 1 - i; j++) {

            if (arr[j].careType > arr[j + 1].careType) {
                Patient temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

// Contract: sorts 'arr' in place, ascending by length of stay (visit duration).
// Owner: bowie
void bubbleSortByVisitDuration(PatientArray& arr) {

    int n = arr.getSize();

    for (int i = 0; i < n - 1; i++) {

        bool swapped = false;

        for (int j = 0; j < n - 1 - i; j++) {

            if (arr[j].lengthOfStay > arr[j + 1].lengthOfStay) {
                Patient temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

#endif