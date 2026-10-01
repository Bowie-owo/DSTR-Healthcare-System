#ifndef LIST_BUBBLESORT_HPP
#define LIST_BUBBLESORT_HPP

#include "linkedList.hpp"

// Helper: counts the nodes in 'list'.
// (If LinkedList already has a getSize(), use that instead.)
inline int countNodes(const LinkedList& list) {
    int count = 0;
    const Node* p = list.getHead();
    while (p != nullptr) {
        count++;
        p = p->next;
    }
    return count;
}

// Contract: sorts 'list' in place, ascending by age.
//
// Adapted for a singly linked list: instead of relinking pointers,
// each comparison swaps the *data* stored in adjacent nodes. The nodes
// themselves never move, only their contents do.
//
// NOTE ON const_cast: LinkedList::getHead() only exposes a
// `const Node*`, since it was originally written just for read-only
// traversal. The actual Node objects on the heap were never declared
// const, so stripping the const here is safe.
// Owner: bowie
void bubbleSortByAge(LinkedList& list) {

    int n = countNodes(list);

    for (int i = 0; i < n - 1; i++) {

        bool swapped = false;
        Node* current = const_cast<Node*>(list.getHead());

        for (int j = 0; j < n - 1 - i; j++) {

            if (current->data.age > current->next->data.age) {
                Patient temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }

            current = current->next;
        }

        if (!swapped) break;
    }
}

// Contract: sorts 'list' in place, ascending alphabetically by care type.
// Same const_cast rationale as bubbleSortByAge above.
// Owner: bowie
void bubbleSortByCareType(LinkedList& list) {

    int n = countNodes(list);

    for (int i = 0; i < n - 1; i++) {

        bool swapped = false;
        Node* current = const_cast<Node*>(list.getHead());

        for (int j = 0; j < n - 1 - i; j++) {

            if (current->data.careType > current->next->data.careType) {
                Patient temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }

            current = current->next;
        }

        if (!swapped) break;
    }
}

// Contract: sorts 'list' in place, ascending by length of stay (visit duration).
// Same const_cast rationale as bubbleSortByAge above.
// Owner: bowie
void bubbleSortByVisitDuration(LinkedList& list) {

    int n = countNodes(list);

    for (int i = 0; i < n - 1; i++) {

        bool swapped = false;
        Node* current = const_cast<Node*>(list.getHead());

        for (int j = 0; j < n - 1 - i; j++) {

            if (current->data.lengthOfStay > current->next->data.lengthOfStay) {
                Patient temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }

            current = current->next;
        }

        if (!swapped) break;
    }
}

#endif