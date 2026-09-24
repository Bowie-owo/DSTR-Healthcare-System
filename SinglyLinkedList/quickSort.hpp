#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include "linkedList.hpp"

// Extracts the value we sort by from a patient
typedef double (*KeyFn)(const Patient&);

inline double ageKey(const Patient& p)      { return p.age; }
inline double stayKey(const Patient& p)     { return p.lengthOfStay; }

// Appends node to the end of a chain tracked by head/tail
inline void appendNode(Node*& head, Node*& tail, Node* node)
{
    node->next = nullptr;
    if (head == nullptr) head = tail = node;
    else { tail->next = node; tail = node; }
}

// Sorts the chain starting at 'head' and returns the new head.
// 'tailOut' receives the last node of the sorted chain.
inline Node* quickSortChain(Node* head, Node*& tailOut, KeyFn key)
{
    if (head == nullptr || head->next == nullptr)
    {
        tailOut = head;
        return head;
    }

    // Find the middle node (slow/fast pointers) and use its key as pivot
    Node* slow = head;
    Node* fast = head->next;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    double pivotKey = key(slow->data);

    // Three-way partition: less / equal / greater
    Node *lessHead = nullptr,  *lessTail = nullptr;
    Node *equalHead = nullptr, *equalTail = nullptr;
    Node *greatHead = nullptr, *greatTail = nullptr;

    Node* current = head;
    while (current != nullptr)
    {
        Node* nextNode = current->next;
        double k = key(current->data);

        if (k < pivotKey)       appendNode(lessHead, lessTail, current);
        else if (k > pivotKey)  appendNode(greatHead, greatTail, current);
        else                    appendNode(equalHead, equalTail, current);

        current = nextNode;
    }

    // Recursively sort the two outer partitions (equal is already "sorted")
    Node* sortedLessTail = nullptr;
    Node* sortedGreatTail = nullptr;
    lessHead  = quickSortChain(lessHead,  sortedLessTail,  key);
    greatHead = quickSortChain(greatHead, sortedGreatTail, key);

    // Join: less + equal + greater
    Node* resultHead = equalHead;
    if (lessHead != nullptr)
    {
        sortedLessTail->next = equalHead;
        resultHead = lessHead;
    }

    equalTail->next = greatHead;
    tailOut = (greatHead != nullptr) ? sortedGreatTail : equalTail;

    return resultHead;
}

inline void quickSortByAge(LinkedList& list)
{
    Node* tail = nullptr;
    list.getHead() = quickSortChain(list.getHead(), tail, ageKey);
}

inline void quickSortByVisitDuration(LinkedList& list)
{
    Node* tail = nullptr;
    list.getHead() = quickSortChain(list.getHead(), tail, stayKey);
}

#endif