#ifndef CARE_TYPE_ANALYSIS_HPP
#define CARE_TYPE_ANALYSIS_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "patient.hpp"

using namespace std;

void careTypeAnalysis(const vector<Patient>& patients,
                          const string& facilityName)
{
     string careTypeNames[20];
     double totalMedicalCosts[20];
     int careTypeCounts[20];
     double careTypeDurations[20];
     double careTypeCosts[20];

     int careTypeCount = 0;

     double totalBilling = 0.0;
     double totalStayHours = 0.0;
     bool showCareTypeCost = facilityName != "ALL FACILITIES";

     for (const Patient& patient : patients)
     {
          string careType = patient.careType;

          int position = -1;
          
          //search whether the careType already exists in the careTypeNames array
          for (int i = 0; i < careTypeCount; i++)
          {
               if (careTypeNames[i] == careType)
               {
                    position = i;
                    break;
               }
          }

          // Calculate total stay hours and total medical cost   
          double totalStay = patient.lengthOfStay*patient.daysVisitsPerYear;
          
          double medicalCost = patient.lengthOfStay*patient.baseCostPerHour*patient.daysVisitsPerYear;

          totalBilling += medicalCost;
          totalStayHours += totalStay;

          if (position == -1)
          {
               careTypeNames[careTypeCount] = careType;
               totalMedicalCosts[careTypeCount] = medicalCost;
               careTypeCounts[careTypeCount] = 1;
               careTypeDurations[careTypeCount] = totalStay;
               careTypeCosts[careTypeCount] = patient.baseCostPerHour;

               careTypeCount++;
          }
          else
          {
               totalMedicalCosts[position] += medicalCost;
               careTypeCounts[position]++;
               careTypeDurations[position] += totalStay;
          }
     }

     cout << "\n" << facilityName << "\n\n";

     cout << "====================================================================================================\n";
     cout << "                                     CARE TYPE ANALYSIS\n";
     cout << "====================================================================================================\n";

     if (patients.empty())
     {
          cout << "No patient data available.\n";
          cout << "====================================================================================================\n";
          return;
     }

     cout << fixed << setprecision(2);

     cout << left
              << setw(20) << "Care Type"
              << setw(20) << "Total Patients"
              << setw(20) << "Total Stay Hours";

     if (showCareTypeCost)
     {
             cout << setw(20) << "Cost/hr (RM)";
     }

     cout
              << setw(20) << "Total Cost (RM)"
         << endl;

    cout << "----------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < careTypeCount; i++)
    {
     cout << left
          << setw(20) << careTypeNames[i]
          << setw(20) << careTypeCounts[i]
          << setw(20) << setprecision(0) << careTypeDurations[i];
          
          cout << setprecision(2);

          if (showCareTypeCost)
          {
            cout << setw(20) << careTypeCosts[i];
          }

          cout
             << setw(20) << totalMedicalCosts[i]
             << endl;
    }

    cout << "====================================================================================================\n";
    cout << "                                     FACILITY SUMMARY\n";
    cout << "====================================================================================================\n";

    cout << left
         << setw(30) << "Total Patients"
         << ": " << patients.size()
         << endl;

     cout << left
         << setw(30) << "Total Stay Hours"
           << setprecision(0) << ": "<< totalStayHours << " hours"
         << endl;

    cout << left
         << setw(30) << "Total Billing Cost (RM)"
          << setprecision(2) << ": RM " << totalBilling
         << endl;

     cout << "====================================================================================================\n";

}

#endif