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

#ifndef INTERESTREPORT_H
#define INTERESTREPORT_H

#include <iomanip>

using namespace std;

// Initialize our class
class InterestReport {
public:
    // Const variables
    // I know these values could just as easily be in the code AS numbers
    // BUT it felt easier to read with them defined
    const int MONTHS_IN_YEAR = 12;
    const int CONVERT_TO_DECIMAL = 100;

    // Default constructor
    InterestReport();

    // Setters
    void setInitialAmount();
    void setMonthlyDeposit();
    void setAnnualInterest();
    void setYearsToGrow();

    // Getters
    [[nodiscard]] double getInitialAmount() const;
    [[nodiscard]] double getMonthlyDeposit() const;
    [[nodiscard]] double getAnnualInterest() const;
    [[nodiscard]] int getYearsOfGrowth() const;

    // Calculations
    [[nodiscard]] double calculateBalance(double t_initialInvestment, double t_monthDeposit, double t_interestRate, int t_numberOfYears, bool t_deposits) const;

    // Print
    static void printHeader(bool t_deposits);
    void printDetails(int t_yearIndex, double t_balance, double t_interestEarnedThisYear) const;
    static void printTotalInterest(double t_totalInterest);
    static bool printRunNewReport(bool t_newEntry);

private:
    // Initialize private variables
    double m_openingAmount{};
    double m_depositedAmount{};
    double m_totalAmount{};
    double m_annualInterest{};
    int m_years{};
};

#endif //INTERESTREPORT_H
