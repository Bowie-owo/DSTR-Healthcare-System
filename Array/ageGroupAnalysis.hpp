#ifndef AGE_GROUP_ANALYSIS_HPP
#define AGE_GROUP_ANALYSIS_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "patient.hpp"

using namespace std;

void ageGroupAnalysis(const vector<Patient>& patients,
                      const string& facilityName)
{
    // Array to store the number of patients in each age group
    int ageGroupCount[5] = {0};

    // Count patients according to their age
    for (const Patient& patient : patients)
    {
        if (patient.age >= 0 && patient.age <= 17)
        {
            ageGroupCount[0]++;
        }
        else if (patient.age >= 18 && patient.age <= 25)
        {
            ageGroupCount[1]++;
        }
        else if (patient.age >= 26 && patient.age <= 45)
        {
            ageGroupCount[2]++;
        }
        else if (patient.age >= 46 && patient.age <= 60)
        {
            ageGroupCount[3]++;
        }
        else if (patient.age >= 61 && patient.age <= 100)
        {
            ageGroupCount[4]++;
        }
    }

    string ageGroupNames[5] =
    {
        "Pediatrics & Adolescents",
        "Young Adults / University Students",
        "Working Adults (Early Career)",
        "Working Adults (Late Career)",
        "Senior Citizens / Geriatric Care"
    };

    cout << "\n" << facilityName << "\n\n";

    cout << "================================================================================\n";
    cout << "                         AGE GROUP ANALYSIS\n";
    cout << "================================================================================\n";

    cout << left
         << setw(45) << "Age Group"
         << setw(15) << "Patients" << endl;

    cout << "--------------------------------------------------------------------------------\n";

    int total = 0;

    for (int i = 0; i < 5; i++)
    {
        if (ageGroupCount[i] > 0)
        {
            cout << left
                 << setw(45) << ageGroupNames[i]
                 << setw(15) << ageGroupCount[i]
                 << endl;
        }

        total += ageGroupCount[i];
    }

    cout << "--------------------------------------------------------------------------------\n";

    cout << left
         << setw(45) << "TOTAL"
         << setw(15) << total
         << endl;

    cout << "================================================================================\n";
}

#endif