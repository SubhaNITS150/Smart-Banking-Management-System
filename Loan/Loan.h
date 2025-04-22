#include <iostream>
#include "../User/User.h"
#include "../AdminPanel/AdminPanel.h"
using namespace std;

#ifndef LOAN_H
#define LOAN_H
using namespace std;

class Loan : public User
{
    int creditScore;
    double loanAmount;
    float interestRate;
    int loanDuration;
    string status;

public:
    // Constructors
    Loan(int creditScore = 300, int validUpto = 12) {}

    // Class Functions
    void showLoanPanel(void);
    int calculateCreditScore(int baseScore, int validUpto, int repaidIn);
    void seekLoan(void);

    // Getters and Setters
    int getCreditScore() const
    {
        return creditScore;
    }
    double getLoanAmount() const
    {
        return loanAmount;
    }

    float getInterestRate() const
    {
        return interestRate;
    }

    int getLoanDuration() const
    {
        return loanDuration;
    }

    string getStatus() const
    {
        return status;
    }
};

// Constants
static vector<Loan> loanLists;

// Utility functions
void showLoanLists(vector<Loan> &loanLists)
{
    if (loanLists.empty())
    {
        cout << "No loan records available." << endl;
        return;
    }

    cout << "\n+-------------------------------------------------------------+" << endl;
    cout << "|                      All Loan Records                       |" << endl;
    cout << "+-------------------------------------------------------------+" << endl;

    for (const auto &loan : loanLists)
    {
        cout << "User ID         : " << loan.getUserId() << endl;
        cout << "Credit Score    : " << loan.getCreditScore() << endl;
        cout << "Loan Amount     : ₹" << loan.getLoanAmount() << endl;
        cout << "Interest Rate   : " << loan.getInterestRate() << " %" << endl;
        cout << "Loan Duration   : " << loan.getLoanDuration() << " months" << endl;
        cout << "Status          : " << loan.getStatus() << endl;
        cout << "+-------------------------------------------------------------+" << endl;
    }
}

void Loan ::showLoanPanel(void)
{
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm *localTime = localtime(&currentTime);

    cout << "+--------------------------------------+" << endl;
    cout << "|          Welcome to Loan Panel       |" << endl;
    cout << "+--------------------------------------+" << endl;
    cout << "|   Date: " << put_time(localTime, "%Y-%m-%d")
         << "  Time: " << put_time(localTime, "%H:%M:%S") << "   |" << endl;
    cout << "+--------------------------------------+" << endl;

    cout << "|  1. Seek Loan                        |" << endl;
    cout << "|  2. Pay Loan Amount                  |" << endl;
    cout << "|  3. Back                             |" << endl;
    cout << "+--------------------------------------+" << endl;

    int choice;
    cout << "\nEnter your choice" << endl;
    cin >> choice;

    if (choice == 1)
    {
        Loan newLoan;
        newLoan.seekLoan();
    }

    if (choice == 2)
    {
    }

    else
    {
        return;
    }
}

int Loan ::calculateCreditScore(int baseScore, int validUpto, int repaidIn)
{
    int monthsEarly = validUpto - repaidIn;
    int bonusPerMonth = 10;
    int earlyRePaymentBonus = bonusPerMonth * monthsEarly;

    return baseScore + earlyRePaymentBonus;
}

void Loan ::seekLoan(void)
{
    loadUsersFromCSV();

    int getID;
    cout << "Enter your bank ID:- " << endl;
    cin >> getID;

    auto it = find_if(User ::userLists.begin(), User ::userLists.end(), [&](const User &user)
                      { return user.getUserId() == getID; });

    if (it != User ::userLists.end())
    {
        cout << "Enter password:- " << endl;
        string pass;
        cin >> pass;

        PasswordManager pm;
        bool checkPwd = pm.checkPassword(pass, it -> getPassword());

        if (checkPwd)
        {
            cout << "Enter the amount you want to take loan:- " << endl;

            double loanAmount;
            cin >> loanAmount;

            AdminPanel totalSum;
            long long totalMoney = totalSum.totalAmountInBank();

            if (totalMoney > loanAmount)
            {
                int creditScore = 300;
                int validUpto = 12;

                float interestRate = 10.5;
                string loanStatus = "Pending";

                Loan userLoan;
                userLoan.userId = getID;
                userLoan.creditScore = creditScore;
                userLoan.loanAmount = loanAmount;
                userLoan.interestRate = interestRate;
                userLoan.loanDuration = validUpto;
                userLoan.status = loanStatus;

                loanLists.push_back(userLoan);
            }
            it->setBalance(it->getBalance() + loanAmount);
            updateCSV2();
        }
    }

    showLoanLists(loanLists);
}

#endif