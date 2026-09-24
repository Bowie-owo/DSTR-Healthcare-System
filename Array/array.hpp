#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "patient.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

const int NUM_AGE_GROUPS = 5;

inline void display(const vector<Patient>& patients)
{
    cout << "\n";
    cout << "================================================================================\n";
    cout << left
         << setw(12) << "Patient ID"
         << setw(8)  << "Age"
         << setw(18) << "Care Type"
         << setw(12) << "Stay(hour)"
         << setw(12) << "Cost/hr(RM)"
         << setw(12) << "Visits/Year"
         << endl;
    cout << "================================================================================\n";

    for (const Patient& patient : patients)
    {
        cout << left
             << setw(12) << patient.patientID
             << setw(8)  << patient.age
             << setw(18) << patient.careType;
        cout << defaultfloat << setprecision(6) << setw(12) << patient.lengthOfStay;
        cout << setw(12) << fixed << setprecision(2) << patient.baseCostPerHour;
        cout << defaultfloat << setw(12) << patient.daysVisitsPerYear
             << endl;
    }

    cout << "================================================================================\n";
}

// ---------------------------------------------------------------------------
// AGE GROUP HELPERS (shared by Dataset Summary, Age Group Analysis, etc.)
// Index: 0 = Pediatrics, 1 = Young Adults, 2 = Early Career,
//        3 = Late Career, 4 = Senior Citizens
// ---------------------------------------------------------------------------

// Returns the group index (0-4) for an age, or -1 if the age is out of range
inline int getAgeGroupIndex(int age)
{
    if (age >= 0  && age <= 17)  return 0;
    if (age >= 18 && age <= 25)  return 1;
    if (age >= 26 && age <= 45)  return 2;
    if (age >= 46 && age <= 60)  return 3;
    if (age >= 61 && age <= 100) return 4;
    return -1;
}

// Returns the group name for a group index
inline string getAgeGroupName(int index)
{
    static const string names[NUM_AGE_GROUPS] =
    {
        "Pediatrics & Adolescents",
        "Young Adults / University Students",
        "Working Adults (Early Career)",
        "Working Adults (Late Career)",
        "Senior Citizens / Geriatric Care"
    };
    return (index >= 0 && index < NUM_AGE_GROUPS) ? names[index] : "Unknown";
}

// Returns the age range text for a group index
inline string getAgeGroupRange(int index)
{
    static const string ranges[NUM_AGE_GROUPS] =
    {
        "0-17", "18-25", "26-45", "46-60", "61-100"
    };
    return (index >= 0 && index < NUM_AGE_GROUPS) ? ranges[index] : "-";
}

// Convenience: age -> group name
inline string getAgeGroup(int age)
{
    return getAgeGroupName(getAgeGroupIndex(age));
}

// Counts patients per age group into counts[NUM_AGE_GROUPS].
// Returns the number of patients whose age was out of range.
inline int countAgeGroups(const vector<Patient>& patients, int counts[NUM_AGE_GROUPS])
{
    for (int i = 0; i < NUM_AGE_GROUPS; i++)
        counts[i] = 0;

    int outOfRange = 0;
    for (const Patient& patient : patients)
    {
        int idx = getAgeGroupIndex(patient.age);
        if (idx >= 0)
            counts[idx]++;
        else
            outOfRange++;
    }
    return outOfRange;
}

// Splits patients into groups[NUM_AGE_GROUPS] (use when you need the actual records)
inline void categorizeAgeGroups(const vector<Patient>& patients,
                                vector<Patient> groups[NUM_AGE_GROUPS])
{
    for (int i = 0; i < NUM_AGE_GROUPS; i++)
        groups[i].clear();

    for (const Patient& patient : patients)
    {
        int idx = getAgeGroupIndex(patient.age);
        if (idx >= 0)
            groups[idx].push_back(patient);
    }
}

// ---------------------------------------------------------------------------
// DATASET SUMMARY: which age groups exist in each facility
// ---------------------------------------------------------------------------
inline void displayAgeGroupsPerFacility(const vector<Patient>& facilityA,
                                        const vector<Patient>& facilityB,
                                        const vector<Patient>& facilityC)
{
    int countA[NUM_AGE_GROUPS], countB[NUM_AGE_GROUPS], countC[NUM_AGE_GROUPS];
    countAgeGroups(facilityA, countA);
    countAgeGroups(facilityB, countB);
    countAgeGroups(facilityC, countC);

    const string line(90, '=');

    cout << "\n" << line << "\n";
    cout << "                    AGE GROUPS PRESENT IN EACH FACILITY\n";
    cout << line << "\n";
    cout << left
         << setw(8)  << "Range"
         << setw(38) << "Age Group"
         << setw(14) << "Facility A"
         << setw(14) << "Facility B"
         << setw(14) << "Facility C" << endl;
    cout << string(90, '-') << "\n";

    for (int i = 0; i < NUM_AGE_GROUPS; i++)
    {
        cout << left
             << setw(8)  << getAgeGroupRange(i)
             << setw(38) << getAgeGroupName(i);

        // Show the patient count if the group exists, otherwise "-"
        const int* counts[3] = { countA, countB, countC };
        for (int f = 0; f < 3; f++)
        {
            if (counts[f][i] > 0)
                cout << setw(14) << counts[f][i];
            else
                cout << setw(14) << "-";
        }
        cout << "\n";
    }
    cout << line << "\n";

    // Per-facility list of groups that exist
    const string facilityNames[3] = { "Facility A", "Facility B", "Facility C" };
    const int* counts[3] = { countA, countB, countC };

    for (int f = 0; f < 3; f++)
    {
        cout << facilityNames[f] << ": ";
        bool first = true;
        for (int i = 0; i < NUM_AGE_GROUPS; i++)
        {
            if (counts[f][i] > 0)
            {
                if (!first) cout << ", ";
                cout << getAgeGroupName(i);
                first = false;
            }
        }
        if (first) cout << "No valid age groups found";
        cout << "\n";
    }
    cout << line << "\n";
}

#endif