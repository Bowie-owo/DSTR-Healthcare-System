#ifndef LIST_INSERTIONSORT_HPP
#define LIST_INSERTIONSORT_HPP

#include "linkedList.hpp"

// ============================================================
// WHAT IS INSERTION SORT? (explained like you're 9 years old)
// ============================================================
//
// Imagine you are holding a hand of playing cards, and you want
// to arrange them from smallest to biggest.
//
// You already have some cards sorted in your left hand.
// You pick up ONE new card with your right hand (let's call it
// the "key" card), and you slide it into the correct spot among
// the sorted cards — pushing the bigger cards one space to the
// right to make room for it.
//
// You repeat this — pick up the next card, slide it into place —
// until every card has been picked up once. That's it!
//
// In our linked list, we move the whole node into its new place.
// This is useful because a node already knows the next node after it.
// We do not need to make a second list or store extra node pointers.
// ============================================================

// Contract: sorts 'list' in place, ascending by age.
// Same const_cast rationale as bubbleSort.hpp — getHead() only
// hands back a const Node*, but the actual Node objects on the
// heap were never declared const, so this is safe.
void insertionSortByAge(LinkedList& list) {

    Node*& head = list.getHead();
    Node* sorted = nullptr;

    while (head != nullptr) {
        Node* current = head;
        head = head->next;

        if (sorted == nullptr || current->data.age < sorted->data.age) {
            current->next = sorted;
            sorted = current;
        }
        else {
            Node* place = sorted;

            while (place->next != nullptr &&
                   place->next->data.age <= current->data.age) {
                place = place->next;
            }

            current->next = place->next;
            place->next = current;
        }
    }

    head = sorted;
}

// Contract: sorts 'list' in place, ascending by visit duration
// (length of stay, in hours). Exact same idea as above, just
// comparing a different field.
void insertionSortByVisitDuration(LinkedList& list) {

    Node*& head = list.getHead();
    Node* sorted = nullptr;

    while (head != nullptr) {
        Node* current = head;
        head = head->next;

        if (sorted == nullptr ||
            current->data.lengthOfStay < sorted->data.lengthOfStay) {
            current->next = sorted;
            sorted = current;
        }
        else {
            Node* place = sorted;

            while (place->next != nullptr &&
                   place->next->data.lengthOfStay <= current->data.lengthOfStay) {
                place = place->next;
            }

            current->next = place->next;
            place->next = current;
        }
    }

    head = sorted;
}

#endif