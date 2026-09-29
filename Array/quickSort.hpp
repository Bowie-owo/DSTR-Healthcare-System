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

// ==========================================
// QUICK SORT BY CARE TYPE (3-way partition)
// ==========================================

void quickSortByCareType(vector<Patient>& data, int low, int high)
{
    while (low < high)
    {
        // Middle element as pivot avoids worst case on already-sorted data
        string pivot = data[low + (high - low) / 2].careType;

        int lt = low;    // data[low..lt-1]   <  pivot
        int i  = low;    // data[lt..i-1]     == pivot
        int gt = high;   // data[gt+1..high]  >  pivot

        while (i <= gt)
        {
            int cmp = data[i].careType.compare(pivot);

            if (cmp < 0)
            {
                swap(data[lt], data[i]);
                lt++;
                i++;
            }
            else if (cmp > 0)
            {
                swap(data[i], data[gt]);
                gt--;
            }
            else
            {
                i++;
            }
        }

        // Recurse on the smaller side, loop on the larger (bounds stack depth to O(log n))
        if (lt - low < high - gt)
        {
            quickSortByCareType(data, low, lt - 1);
            low = gt + 1;
        }
        else
        {
            quickSortByCareType(data, gt + 1, high);
            high = lt - 1;
        }
    }
}

#endif