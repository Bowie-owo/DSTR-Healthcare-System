#ifndef ARRAY_PERFORMANCE_METRICS_HPP
#define ARRAY_PERFORMANCE_METRICS_HPP

enum class ArraySortMethod
{
    None,
    Bubble,
    Insertion,
    Quick
};

struct ArrayPerformance
{
    double bubbleSort = 0.0;
    double insertionSort = 0.0;
    double quickSort = 0.0;
    double bubbleLinearSorted = 0.0;
    double insertionLinearSorted = 0.0;
    double quickLinearSorted = 0.0;
    double bubbleBinarySorted = 0.0;
    double insertionBinarySorted = 0.0;
    double quickBinarySorted = 0.0;
    double linearUnsorted = 0.0;
    ArraySortMethod sortedSortMethod = ArraySortMethod::None;
};

inline ArrayPerformance arrayPerformance;

inline void recordArraySortedLinearSearch(double searchTime)
{
    switch (arrayPerformance.sortedSortMethod)
    {
        case ArraySortMethod::Bubble:
            arrayPerformance.bubbleLinearSorted = searchTime;
            break;
        case ArraySortMethod::Insertion:
            arrayPerformance.insertionLinearSorted = searchTime;
            break;
        case ArraySortMethod::Quick:
            arrayPerformance.quickLinearSorted = searchTime;
            break;
        case ArraySortMethod::None:
            break;
    }
}

inline void recordArraySortedBinarySearch(double searchTime)
{
    switch (arrayPerformance.sortedSortMethod)
    {
        case ArraySortMethod::Bubble:
            arrayPerformance.bubbleBinarySorted = searchTime;
            break;
        case ArraySortMethod::Insertion:
            arrayPerformance.insertionBinarySorted = searchTime;
            break;
        case ArraySortMethod::Quick:
            arrayPerformance.quickBinarySorted = searchTime;
            break;
        case ArraySortMethod::None:
            break;
    }
}

inline void recordArrayUnsortedLinearSearch(double searchTime)
{
    arrayPerformance.linearUnsorted = searchTime;
}

#endif
