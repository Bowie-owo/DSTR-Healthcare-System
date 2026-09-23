#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <vector>
#include "patient.hpp"

using namespace std;

// ==========================================
// QUICK SORT BY AGE
// ==========================================

int partitionByAge(vector<Patient>& data, int low, int high)
{
    int pivot = data[high].age;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (data[j].age <= pivot)
        {
            i++;

            Patient temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }

    Patient temp = data[i + 1];
    data[i + 1] = data[high];
    data[high] = temp;

    return i + 1;
}

void quickSortByAge(vector<Patient>& data, int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partitionByAge(data, low, high);

        quickSortByAge(data, low, pivotIndex - 1);
        quickSortByAge(data, pivotIndex + 1, high);
    }
}


// ==========================================
// QUICK SORT BY VISIT DURATION
// ==========================================

int partitionByVisitDuration(
    vector<Patient>& data,
    int low,
    int high
)
{
    double pivot = data[high].lengthOfStay;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (data[j].lengthOfStay <= pivot)
        {
            i++;

            Patient temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }

    Patient temp = data[i + 1];
    data[i + 1] = data[high];
    data[high] = temp;

    return i + 1;
}

void quickSortByVisitDuration(
    vector<Patient>& data,
    int low,
    int high
)
{
    if (low < high)
    {
        int pivotIndex =
            partitionByVisitDuration(data, low, high);

        quickSortByVisitDuration(
            data,
            low,
            pivotIndex - 1
        );

        quickSortByVisitDuration(
            data,
            pivotIndex + 1,
            high
        );
    }
}

#endif