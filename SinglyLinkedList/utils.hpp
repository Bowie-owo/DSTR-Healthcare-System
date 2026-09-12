#ifndef UTILS_HPP
#define UTILS_HPP

#include "patient.hpp"
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Maps an age to its demographic category.
inline string getAgeGroup(int age) {
    if (age >= 0 && age <= 17)
        return "Pediatrics & Adolescents";
    else if (age >= 18 && age <= 25)
        return "Young Adults / University Students";
    else if (age >= 26 && age <= 45)
        return "Working Adults (Early Career)";
    else if (age >= 46 && age <= 60)
        return "Working Adults (Late Career)";
    else if (age >= 61 && age <= 100)
        return "Senior Citizens / Geriatric Care";
    else
        return "Unknown";
}

// Cost = Length of Stay x Base Cost Per Hour x Days Visits Per Year
inline double calculateCost(Patient patient) {
    return patient.lengthOfStay
         * patient.baseCostPerHour
         * patient.daysVisitsPerYear;
}

// Formats a number with thousand separators and 2 decimal places,
// e.g. 12000.5 -> "12,000.50"
inline string formatWithCommas(double value) {

    ostringstream oss;
    oss << fixed << setprecision(2) << value;
    string numStr = oss.str();

    size_t dotPos = numStr.find('.');
    string intPart = numStr.substr(0, dotPos);
    string decPart = numStr.substr(dotPos);

    bool negative = false;
    if (!intPart.empty() && intPart[0] == '-') {
        negative = true;
        intPart = intPart.substr(1);
    }

    string result;
    int count = 0;

    for (int i = (int)intPart.size() - 1; i >= 0; i--) {
        result = intPart[i] + result;
        count++;
        if (count % 3 == 0 && i != 0) {
            result = "," + result;
        }
    }

    if (negative) result = "-" + result;

    return result + decPart;
}

#endif