#ifndef UTILS_HPP
#define UTILS_HPP

#include "patient.hpp"
#include "array.hpp"


inline void buildCombined(const DynamicArray<Patient>& a,
                   const DynamicArray<Patient>& b,
                   const DynamicArray<Patient>& c,
                   DynamicArray<Patient>& combined) {
    combined.clear();
    combined.appendAll(a);
    combined.appendAll(b);
    combined.appendAll(c);
}

#endif