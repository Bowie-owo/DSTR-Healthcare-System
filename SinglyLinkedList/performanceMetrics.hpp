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

inline SessionPerformance& getSessionPerformance()
{
    static SessionPerformance performance;
    return performance;
}

inline void recordSortedLinearSearch(double searchTime)
{
    switch (getSessionPerformance().sortedSearchMethod)
    {
        case PerformanceSortMethod::Bubble:
            getSessionPerformance().bubbleLinearSorted = searchTime;
            break;
        case PerformanceSortMethod::Insertion:
            getSessionPerformance().insertionLinearSorted = searchTime;
            break;
        case PerformanceSortMethod::Quick:
            getSessionPerformance().quickLinearSorted = searchTime;
            break;
        case PerformanceSortMethod::None:
            break;
    }
}

inline void recordSortedBinarySearch(double searchTime)
{
    switch (getSessionPerformance().sortedSearchMethod)
    {
        case PerformanceSortMethod::Bubble:
            getSessionPerformance().bubbleBinarySorted = searchTime;
            break;
        case PerformanceSortMethod::Insertion:
            getSessionPerformance().insertionBinarySorted = searchTime;
            break;
        case PerformanceSortMethod::Quick:
            getSessionPerformance().quickBinarySorted = searchTime;
            break;
        case PerformanceSortMethod::None:
            break;
    }
}

#endif
