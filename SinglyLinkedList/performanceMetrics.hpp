#ifndef LIST_PERFORMANCE_METRICS_HPP
#define LIST_PERFORMANCE_METRICS_HPP


enum class PerformanceSortMethod
{
    None,
    Bubble,
    Insertion,
    Quick
};

struct SessionPerformance
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
    PerformanceSortMethod sortedSearchMethod = PerformanceSortMethod::None;
};

inline SessionPerformance sessionPerformance;

inline void recordSortedLinearSearch(double searchTime)
{
    switch (sessionPerformance.sortedSearchMethod)
    {
        case PerformanceSortMethod::Bubble:
            sessionPerformance.bubbleLinearSorted = searchTime;
            break;
        case PerformanceSortMethod::Insertion:
            sessionPerformance.insertionLinearSorted = searchTime;
            break;
        case PerformanceSortMethod::Quick:
            sessionPerformance.quickLinearSorted = searchTime;
            break;
        case PerformanceSortMethod::None:
            break;
    }
}

inline void recordSortedBinarySearch(double searchTime)
{
    switch (sessionPerformance.sortedSearchMethod)
    {
        case PerformanceSortMethod::Bubble:
            sessionPerformance.bubbleBinarySorted = searchTime;
            break;
        case PerformanceSortMethod::Insertion:
            sessionPerformance.insertionBinarySorted = searchTime;
            break;
        case PerformanceSortMethod::Quick:
            sessionPerformance.quickBinarySorted = searchTime;
            break;
        case PerformanceSortMethod::None:
            break;
    }
}

#endif
