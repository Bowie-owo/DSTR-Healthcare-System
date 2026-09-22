#ifndef LIST_BUBBLESORT_HPP
#define LIST_BUBBLESORT_HPP

#include "linkedList.hpp"

// Contract: sorts 'list' in place, ascending by patientID.
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
// restrictive than what we need. If LinkedList later adds a mutable
// accessor, this cast can be dropped.
// Owner: bowie
void bubbleSortById(LinkedList& list) {

    if (list.getHead() == nullptr) return;

    bool swapped;

    do {
        swapped = false;
        Node* current = const_cast<Node*>(list.getHead());

        while (current != nullptr && current->next != nullptr) {

            if (current->data.patientID > current->next->data.patientID) {
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