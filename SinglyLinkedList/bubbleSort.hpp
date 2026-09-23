#ifndef LIST_BUBBLESORT_HPP
#define LIST_BUBBLESORT_HPP

#include "linkedList.hpp"

// Contract: sorts 'list' in place, ascending by age.
//
// Adapted for a singly linked list: instead of relinking pointers,
// each pass swaps the *data* stored in adjacent nodes. The nodes
// themselves never move — only their contents do.
//
// NOTE ON const_cast: LinkedList::getHead() only exposes a
// `const Node*`, since it was originally written just for read-only
// traversal (see analysis files). The actual Node objects on the
// heap were never declared const, so stripping the const here is
// safe — we're not mutating something the compiler thinks is
// genuinely immutable, just working around an interface that's more
// restrictive than what we need.
// Owner: bowie
void bubbleSortByAge(LinkedList& list) {

    if (list.getHead() == nullptr) return;

    bool swapped;

    do {
        swapped = false;
        Node* current = const_cast<Node*>(list.getHead());

        while (current != nullptr && current->next != nullptr) {

            if (current->data.age > current->next->data.age) {
                Patient temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }

            current = current->next;
        }

    } while (swapped);
}

// Contract: sorts 'list' in place, ascending by visit duration (length of stay, in hours).
// Same const_cast rationale as bubbleSortByAge above.
// Owner: bowie
void bubbleSortByVisitDuration(LinkedList& list) {

    if (list.getHead() == nullptr) return;

    bool swapped;

    do {
        swapped = false;
        Node* current = const_cast<Node*>(list.getHead());

        while (current != nullptr && current->next != nullptr) {

            if (current->data.lengthOfStay > current->next->data.lengthOfStay) {
                Patient temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }

            current = current->next;
        }

    } while (swapped);
}

// Contract: sorts 'list' in place, ascending by care type.
void bubbleSortByCareType(LinkedList& list) {

    if (list.getHead() == nullptr) return;

    bool swapped;

    do {
        swapped = false;
        Node* current = const_cast<Node*>(list.getHead());

        while (current != nullptr && current->next != nullptr) {

            if (current->data.careType > current->next->data.careType) {
                Patient temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }

            current = current->next;
        }

    } while (swapped);
}

#endif