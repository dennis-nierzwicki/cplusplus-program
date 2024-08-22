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

// Setting default constructor
InterestReport::InterestReport() {
    m_openingAmount = 0.0;
    m_depositedAmount = 0.0;
    m_annualInterest = 0.0;
    m_years = 0;
}

// Setter for initial amount depositied
void InterestReport::setInitialAmount() {
    auto userStartingAmount = 0.00;

    // Input validation loop
    while (userStartingAmount <= 0) {
        // Successful try and catch!
        try {
            cout << "Initial Investment Amount: $";
            cin >> userStartingAmount;

            // Deposit can't be negative
            if (userStartingAmount < 0) {
                throw runtime_error(
                "That is not a valid dollar amount.");
            }

            // Deposit can't be a letter or symbol
            if (cin.fail()) {
                throw runtime_error(
                "That is not a number, please try again.");
            }

            m_openingAmount = userStartingAmount;
        } catch (const exception& e) {
            // Clear cin or it will loop
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            // Display runtime_error message
            cout << e.what() << endl;
        }
    }
}

// Setter for monthly depisits
void InterestReport::setMonthlyDeposit() {
    auto userMonthlyDeposit = -1;

    while (userMonthlyDeposit < 0) {
        try {
            cout << "Monthly Deposit: $";
            cin >> userMonthlyDeposit;
            // Monthly deposit can't be negative
            if (userMonthlyDeposit < 0) {
                throw runtime_error(
                "That is not a valid dollar amount.");
            }
            // Monthly deposit can't be a letter
            if (cin.fail()) {
                throw runtime_error(
                "That is not a number, please try again.");
            }
            m_depositedAmount = userMonthlyDeposit;
        } catch (const exception& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            userMonthlyDeposit = -1;
            cout << endl;
            cout << e.what() << endl;
        }
    }
}

// Setter for annual interest
void InterestReport::setAnnualInterest() {
    // Interest COULD technically be 0
    auto userInterest = -1.00;

    while (userInterest < 0) {
        try {
            cout << "Annual Interest: %";
            cin >> userInterest;
            if (userInterest < 0) {
                // It cannot be negative
                throw runtime_error(
                "Please enter a positive number.");
            }
            if (cin.fail()) {
                // It cannot be a letter
                throw runtime_error(
                "That is not a number, please try again.");
            }
            m_annualInterest = userInterest;
        } catch (const exception& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            cout << e.what() << endl;
            userInterest = -1;
        }
    }
}

void InterestReport::setYearsToGrow() {
    auto userYears = 0;

    while (userYears <= 0) {
        try {
            cout << "Number Of Years:";
            cin >> userYears;
            if (userYears <= 0) {
                // Years being zero makes no sense
                // Letters also throw this because variable is never updated
                throw runtime_error(
                "Please enter a number greater than zero.");
            }
            m_years = userYears;
        } catch (const exception& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            cout << e.what() << endl;
        }
    }
}

// Getters just pull value from the object
double InterestReport::getInitialAmount() const {
    return m_openingAmount;
}

double InterestReport::getMonthlyDeposit() const {
    return m_depositedAmount;
}

double InterestReport::getAnnualInterest() const {
    return m_annualInterest;
}

int InterestReport::getYearsOfGrowth() const {
    return m_years;
}

// This is NOT how I initially did this program but the Sense tool steered me into a MESS
// I was able to consolidate calculations into ONE function
double InterestReport::calculateBalance(double const t_initialInvestment, double const t_monthDeposit, double const t_interestRate,
    int const t_numberOfYears, bool const t_deposits) const {
    // We need a few local scoped variables
    double const numberOfMonths = t_numberOfYears * MONTHS_IN_YEAR;
    double totalBalance = t_initialInvestment + t_monthDeposit;
    double yearlyInterestEarned = 0.00;
    double totalInterest = 0.00;

    // This prints the header depending on deposits or not
    // We could assume if monthly Deposit is set by user at 0 we print no deposits
    printHeader(t_deposits);

    // Loop each month to correctly calculate the interest
    for (int i = 1; i <= numberOfMonths; ++i) {
        double const interestDollars = ((t_interestRate / CONVERT_TO_DECIMAL) / MONTHS_IN_YEAR) * totalBalance;
        // Add on to keep track each month
        yearlyInterestEarned = yearlyInterestEarned + interestDollars;
        totalBalance = totalBalance + interestDollars;

        // Print after 12 months
        if (i % 12 == 0) {
            printDetails(i, totalBalance, yearlyInterestEarned);
            // We want to see total earned interest
            totalInterest = totalInterest + yearlyInterestEarned;
            // Reset interest dollar amount after a year
            yearlyInterestEarned = 0.00;
        }
        // Update our total balance for the next momnth
        totalBalance = totalBalance + t_monthDeposit;

    }
    return totalInterest;
}

void InterestReport::printHeader(bool const t_deposits) {

    // Simply to print the correct header without repeating myself
    if (t_deposits) {
        cout << setfill(' ') << setw(65) << "Balance and Interest With Additional Monthly Deposits" << endl;
    }
    else {
        cout << setfill(' ') << setw(62) << "Balance and Interest Without Monthly Deposits" << endl;
    }
    cout << setfill('=') << setw(80) << "" << endl;
    cout << setfill(' ') << setw(5) << right << "YEAR" << setw(35) << right << "YEAR END BALANCE"
        << setw(40) << right <<  "YEAR END EARNED INTEREST" << endl;
    cout << setfill('-') << setw(80) << "" << endl;
    cout << endl;
}

// Each loop prints the data
void InterestReport::printDetails(int const t_yearIndex, double const t_balance, double const t_interestEarnedThisYear) const {
        cout << setfill(' ') << setw(5) << right << (t_yearIndex / MONTHS_IN_YEAR) << setw(35) << right << fixed << setprecision(2) << t_balance
             << setw(40) << right <<  setprecision(2) << t_interestEarnedThisYear << endl;
        cout << endl;
    }

// Afterward, print the total interest earned
void InterestReport::printTotalInterest(double const t_totalInterest) {
    cout << setfill('-') << setw(80) << "" << endl;
    cout << "TOTAL EARNED INTEREST: $" << t_totalInterest << endl;
    cout << endl;
}

// Loop to run a new report
bool InterestReport::printRunNewReport(bool t_newEntry) {
    // Set char to space
    auto userInput = ' ';

     // Loop unless we get a y or n uppercase for case insensitive
     while (toupper(userInput) != 'Y' && toupper(userInput) != 'N') {
         cout << "Shall we run a new annual interest prediction? (Y / N): ";
         cin >> userInput;
         // Switch makes input validation easier
         switch(toupper(userInput)) { // Convert input to uppercase
             case 'N':
                 // Set the main loop bool
                 t_newEntry = false;
             break;
             case 'Y':
                 t_newEntry = true;
             break;
             default:
                 cout << "Sorry, I didn't understand that. Try again." << endl;
             break;
         }
     }
     // Return the main loop bool
     return t_newEntry;
}