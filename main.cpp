/******************************************************************
**
** CS-210 Project 2
** InterestReport.cpp
**
** Dennis Nierzwicki
** Southern New Hampshire University
** CS-210-11455-M01 Programming Languages 2024 C-4
** Prof. Brittany Sanford
** August 3, 2024
**
******************************************************************/

#include <iomanip>
#include <iostream>
#include "InterestReport.h"

using namespace std;

int main() {
    // Create variable to keep the program in loop
    bool t_newEntry = true;

    // Run the loop while the variable is true
    while (t_newEntry) {
        double const noMonthlyDeposit = 0.00;
        InterestReport userInterestReport; // Create our class

        // Print the data input header
        cout << endl;
        cout << setfill('*') << setw(32) << " " << endl;
        cout << setfill('*') << setw(10) << " " << setfill(' ') << "DATA INPUT " << setfill('*') << setw(11) << " " << endl;

        // Set all header variables
        userInterestReport.setInitialAmount();
        userInterestReport.setMonthlyDeposit();
        userInterestReport.setAnnualInterest();
        userInterestReport.setYearsToGrow();

        // I wanted to keep main() short but header and press key did not make sense being placed in the object
        cout << "Press ENTER to continue..." << endl;
        // Ignore any prior return and reset cin
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();

        // Run the reports - this looks clunky but it was this or store the gets into other variables
        double totalInterest = userInterestReport.calculateBalance(userInterestReport.getInitialAmount(),
            noMonthlyDeposit, userInterestReport.getAnnualInterest(), userInterestReport.getYearsOfGrowth(), false);
        InterestReport::printTotalInterest(totalInterest);

        totalInterest = userInterestReport.calculateBalance(userInterestReport.getInitialAmount(),
            userInterestReport.getMonthlyDeposit(), userInterestReport.getAnnualInterest(), userInterestReport.getYearsOfGrowth(), true);
        InterestReport::printTotalInterest(totalInterest);

        // Loop entry to run a new report
        t_newEntry = InterestReport::printRunNewReport(t_newEntry);
    }

    // User exit validation
    cout << endl;
    cout << "Program will now exit. Have a great day." << endl;

    return 0;
}
