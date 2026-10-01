#ifndef LIST_PERFORMANCE_TEST_HPP
#define LIST_PERFORMANCE_TEST_HPP

#include <iomanip>
#include <iostream>

#include "performanceMetrics.hpp"

inline void displaySinglyLinkedListSummary(const SessionPerformance& performance)
{
	const int operationWidth = 58;
	const int timeWidth = 18;
	const string separator(78, '=');

	std::cout << "\n" << separator << "\n";
	std::cout << "          PERFORMANCE SUMMARY IN SINGLY LINKED LIST\n";
	std::cout << separator << "\n";
	std::cout << std::left << std::setw(operationWidth) << "Operation / Method"
			  << std::right << std::setw(timeWidth) << "Time Taken (ms)" << "\n";
	std::cout << string(78, '-') << "\n";

	std::cout << std::left << std::setw(operationWidth) << "Sorting Method: Bubble Sort"
			  << std::right << std::setw(timeWidth) << std::fixed
			  << std::setprecision(2) << performance.bubbleSort << " ms\n";
	std::cout << std::left << std::setw(operationWidth) << "Sorting Method: Insertion Sort"
			  << std::right << std::setw(timeWidth) << performance.insertionSort << " ms\n";
	std::cout << std::left << std::setw(operationWidth) << "Sorting Method: Quick Sort"
			  << std::right << std::setw(timeWidth) << performance.quickSort << " ms\n";
	std::cout << std::left << std::setw(operationWidth) << "Searching (Sorted): Bubble Sort + Linear Search"
			  << std::right << std::setw(timeWidth) << performance.bubbleLinearSorted << " ms\n";
	std::cout << std::left << std::setw(operationWidth) << "Searching (Sorted): Insertion Sort + Linear Search"
			  << std::right << std::setw(timeWidth) << performance.insertionLinearSorted << " ms\n";
	std::cout << std::left << std::setw(operationWidth) << "Searching (Sorted): Quick Sort + Linear Search"
			  << std::right << std::setw(timeWidth) << performance.quickLinearSorted << " ms\n";
	std::cout << std::left << std::setw(operationWidth) << "Searching (Sorted): Bubble Sort + Binary Search"
			  << std::right << std::setw(timeWidth) << performance.bubbleBinarySorted << " ms\n";
	std::cout << std::left << std::setw(operationWidth) << "Searching (Sorted): Insertion Sort + Binary Search"
			  << std::right << std::setw(timeWidth) << performance.insertionBinarySorted << " ms\n";
	std::cout << std::left << std::setw(operationWidth) << "Searching (Sorted): Quick Sort + Binary Search"
			  << std::right << std::setw(timeWidth) << performance.quickBinarySorted << " ms\n";
	std::cout << std::left << std::setw(operationWidth) << "Searching (Unsorted): Linear Search"
			  << std::right << std::setw(timeWidth) << performance.linearUnsorted << " ms\n";

	std::cout << separator << "\n";
}

inline void displaySinglyLinkedListPerformance()
{
	std::cout << "\nReminder: complete the sorting and searching options first.\n";
	std::cout << "Only operations completed in this session have recorded times; others show 0.00 ms.\n";
	displaySinglyLinkedListSummary(sessionPerformance);
}

#endif
