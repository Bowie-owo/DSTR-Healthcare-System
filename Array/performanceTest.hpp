#ifndef ARRAY_PERFORMANCE_TEST_HPP
#define ARRAY_PERFORMANCE_TEST_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "performanceMetrics.hpp"

inline void displayArrayPerformanceSummary(
    const ArrayPerformance& performance
)
{
    const int operationWidth = 58;
    const int timeWidth = 18;
    const string separator(78, '=');

    cout << "\n" << separator << "\n";
    cout << "              PERFORMANCE SUMMARY IN ARRAY\n";
    cout << separator << "\n";
    cout << left << setw(operationWidth) << "Operation / Method"
         << right << setw(timeWidth) << "Time Taken (ms)\n";
    cout << string(78, '-') << "\n";

    cout << left << setw(operationWidth) << "Sorting Method: Bubble Sort"
         << right << setw(timeWidth) << fixed << setprecision(2)
         << performance.bubbleSort << " ms\n";
    cout << left << setw(operationWidth) << "Sorting Method: Insertion Sort"
         << right << setw(timeWidth)
         << performance.insertionSort << " ms\n";
    cout << left << setw(operationWidth) << "Sorting Method: Quick Sort"
         << right << setw(timeWidth)
         << performance.quickSort << " ms\n";
    cout << left << setw(operationWidth) << "Searching (Sorted): Bubble Sort + Linear Search"
         << right << setw(timeWidth)
         << performance.bubbleLinearSorted << " ms\n";
    cout << left << setw(operationWidth) << "Searching (Sorted): Insertion Sort + Linear Search"
         << right << setw(timeWidth)
         << performance.insertionLinearSorted << " ms\n";
    cout << left << setw(operationWidth) << "Searching (Sorted): Quick Sort + Linear Search"
         << right << setw(timeWidth)
         << performance.quickLinearSorted << " ms\n";
    cout << left << setw(operationWidth) << "Searching (Sorted): Bubble Sort + Binary Search"
         << right << setw(timeWidth)
         << performance.bubbleBinarySorted << " ms\n";
    cout << left << setw(operationWidth) << "Searching (Sorted): Insertion Sort + Binary Search"
         << right << setw(timeWidth)
         << performance.insertionBinarySorted << " ms\n";
    cout << left << setw(operationWidth) << "Searching (Sorted): Quick Sort + Binary Search"
         << right << setw(timeWidth)
         << performance.quickBinarySorted << " ms\n";
    cout << left << setw(operationWidth) << "Searching (Unsorted): Linear Search"
         << right << setw(timeWidth)
         << performance.linearUnsorted << " ms\n";

    cout << separator << "\n";
}

inline void displayArrayPerformance()
{
    cout << "\nReminder: complete the sorting and searching options first.\n";
    cout << "Only operations completed in this session have recorded times; others show 0.00 ms.\n";
    displayArrayPerformanceSummary(arrayPerformance);
}

#endif
