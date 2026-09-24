#ifndef ARRAY_INSERTIONSORT_HPP
#define ARRAY_INSERTIONSORT_HPP

#include <vector>
#include "patient.hpp"

// Put patients in order from the youngest age to the oldest age.
void insertionSortByAge(std::vector<Patient>& patients) {
	for (int currentIndex = 1; currentIndex < static_cast<int>(patients.size()); currentIndex++) {
		Patient currentPatient = patients[currentIndex];
		int position = currentIndex - 1;

		// Move older patients one place to the right.
		while (position >= 0 && patients[position].age > currentPatient.age) {
			patients[position + 1] = patients[position];
			position--;
		}

		// Put the patient in the empty place.
		patients[position + 1] = currentPatient;
	}
}

// Put patients in order from the shortest stay to the longest stay.
void insertionSortByVisitDuration(std::vector<Patient>& patients) {
	for (int currentIndex = 1; currentIndex < static_cast<int>(patients.size()); currentIndex++) {
		Patient currentPatient = patients[currentIndex];
		int position = currentIndex - 1;

		// Move patients with longer stays one place to the right.
		while (position >= 0 &&
			   patients[position].lengthOfStay > currentPatient.lengthOfStay) {
			patients[position + 1] = patients[position];
			position--;
		}

		// Put the patient in the empty place.
		patients[position + 1] = currentPatient;
	}
}

#endif
