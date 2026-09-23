#ifndef LIST_BINARYSEARCH_HPP
#define LIST_BINARYSEARCH_HPP

#include "linkedList.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

// Binary search on a linked list uses a node at a calculated position as its
// midpoint. The list must already be sorted by the searched field.
inline const Node* nodeAt(const LinkedList& list, int index) {
	const Node* current = list.getHead();

	for (int position = 0; current != nullptr && position < index; position++) {
		current = current->next;
	}

	return current;
}

inline int firstAgeAtLeast(const LinkedList& list, int minimumAge) {
	int low = 0;
	int high = list.getSize();

	while (low < high) {
		int middle = low + (high - low) / 2;
		const Node* middleNode = nodeAt(list, middle);

		if (middleNode->data.age < minimumAge)
			low = middle + 1;
		else
			high = middle;
	}

	return low;
}

inline int firstCareTypeAtLeast(const LinkedList& list, const string& careType) {
	int low = 0;
	int high = list.getSize();

	while (low < high) {
		int middle = low + (high - low) / 2;
		const Node* middleNode = nodeAt(list, middle);

		if (middleNode->data.careType < careType)
			low = middle + 1;
		else
			high = middle;
	}

	return low;
}

inline int displayPatientsInAgeGroup(const LinkedList& list,
									 int minimumAge,
									 int maximumAge) {
	int first = firstAgeAtLeast(list, minimumAge);
	int afterLast = firstAgeAtLeast(list, maximumAge + 1);
	int matches = 0;

	for (int index = first; index < afterLast; index++) {
		const Node* patient = nodeAt(list, index);
		cout << patient->data.patientID << " | Age: " << patient->data.age
			 << " | Care Type: " << patient->data.careType << endl;
		matches++;
	}

	return matches;
}

inline int displayPatientsByCareType(const LinkedList& list,
									 const string& careType) {
	int first = firstCareTypeAtLeast(list, careType);
	int matches = 0;

	for (int index = first; index < list.getSize(); index++) {
		const Node* patient = nodeAt(list, index);

		if (patient->data.careType != careType)
			break;

		cout << patient->data.patientID << " | Age: " << patient->data.age
			 << " | Care Type: " << patient->data.careType << endl;
		matches++;
	}

	return matches;
}

#endif
