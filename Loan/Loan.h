#include<iostream>
#include "../User/User.h"
#include "../AdminPanel/AdminPanel.h"
using namespace std;

#ifndef LOAN_H
#define LOAN_H
using namespace std;

class Loan : public User {
    int creditScore;
    double loanAmount;
    float interestRate;
    int loanDuration;
    string status;

    public:

    //Constructors
    Loan(int creditScore = 300, int validUpto = 12){}

    //Class Functions
    void showLoanPanel(void);
    int calculateCreditScore(int baseScore, int validUpto, int repaidIn);
    void seekLoan(void);
};

void Loan :: showLoanPanel(void) {
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

    if(choice == 1) {

    }

    if(choice == 2) {

    }

    else{
        return;
    }
}

int Loan :: calculateCreditScore(int baseScore, int validUpto, int repaidIn) {
    int monthsEarly = validUpto - repaidIn;
    int bonusPerMonth = 10;
    int earlyRePaymentBonus = bonusPerMonth * monthsEarly;

    return baseScore + earlyRePaymentBonus;
}

void Loan :: seekLoan(void) {
    loadUsersFromCSV();

    int getID;
    cout << "Enter your bank ID:- " << endl;
    cin >> getID;

    auto it = find_if(User ::userLists.begin(), User ::userLists.end(), [&](const User &user)
                      { return user.getUserId() == getID; });

    if(it != User :: userLists.end()){
        cout << "Enter password:- " << endl;
        string pass;
        cin >> pass;

        if(it -> getPassword() == pass){
            cout << "Enter the amount you want to take loan:- " << endl;

            long long loanAmount;
            cin >> loanAmount;

            AdminPanel totalSum;
            long long totalMoney = totalSum.totalAmountInBank();

            if(totalMoney > loanAmount){
                
            }
        }
    }
}

#endif