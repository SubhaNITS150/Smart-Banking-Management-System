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
    void payLoanAmount(void);

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

    void setCreditScore(int score)
    {
        creditScore = score;
    }

    void setLoanAmount(double amount)
    {
        loanAmount = amount;
    }

    void setInterestRate(float rate)
    {
        interestRate = rate;
    }

    void setLoanDuration(int duration)
    {
        loanDuration = duration;
    }

    void setStatus(const string &stat)
    {
        status = stat;
    }
};

// Constants
static vector<Loan> loanLists;

// Utility functions
bool fileExists(const std::string &filename)
{
    std::ifstream infile(filename.c_str());
    return infile.good();
}

void loanListsFromCSV(void)
{
    loanLists.clear();

    ifstream file("loanlists.csv");
    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line, token;
    getline(file, line);

    while (getline(file, line))
    {
        istringstream ss(line);
        // string token;
        Loan loan;

        if (line.empty())
            continue;

        getline(ss, token, ',');
        int userId = stoi(token);
        loan.setUserId(userId);

        getline(ss, token, ',');
        loan.setCreditScore(stoi(token));

        getline(ss, token, ',');
        loan.setLoanAmount(stoi(token));

        getline(ss, token, ',');
        loan.setInterestRate(stof(token));

        getline(ss, token, ',');
        loan.setLoanDuration(stoi(token));

        getline(ss, token, ',');
        loan.setStatus(token);

        loanLists.push_back(loan);

        // bool updated = false;
        // for (auto &existingLoan : loanLists)
        // {
        //     if (existingLoan.getUserId() == userId)
        //     {
        //         existingLoan = loan;
        //         updated = true;
        //         break;
        //     }
        // }

        // if (!updated)
        // {
        //     loanLists.push_back(loan);
        // }
    }

    file.close();
}

void writeCSVForLoan(void)
{
    string filename = "loanlists.csv";
    ofstream outFile(filename, ios::app);

    if (!outFile.is_open())
    {
        std::cerr << "Failed to open or create " << filename << std::endl;
        return;
    }

    // loanListsFromCSV();
    if (isFileEmpty("userlists.csv"))
    {
        outFile << "ID,Credit Score,Loan Amount,Interest Rate,Loan Duration,Status" << endl;
    }

    for (const Loan &loan : loanLists)
    {
        outFile << loan.getUserId() << ","
                << loan.getCreditScore() << ","
                << loan.getLoanAmount() << ","
                << loan.getInterestRate() << ","
                << loan.getLoanDuration() << ","
                << loan.getStatus() << endl;
    }
    outFile.close();
    cout << "Data downloaded:- " << filename << " successfully." << endl;
}

void showLoanLists(vector<Loan> &loanLists)
{
    writeCSVForLoan();
}

// Class functions

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
    cout << "|  3. Show Loan List                   |" << endl;
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
        Loan newLoan;
        newLoan.payLoanAmount();
    }

    if (choice == 3)
    {
        showLoanLists(loanLists);
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
        bool checkPwd = pm.checkPassword(pass, it->getPassword());

        if (checkPwd)
        {
            cout << "Enter the amount you want to take loan:- " << endl;

            // userLists.clear();
            // loanListsFromCSV();

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
                userLoan.setUserId(it->getUserId());
                userLoan.setName(it->getName());
                userLoan.creditScore = creditScore;
                userLoan.loanAmount = loanAmount;
                userLoan.interestRate = interestRate;
                userLoan.loanDuration = validUpto;
                userLoan.status = loanStatus;

                loanLists.push_back(userLoan);
            }
            it->setBalance(it->getBalance() + loanAmount);
            updateCSV2();
            writeCSVForLoan();

            cout << "Loan Granted Succesfully!" << endl;
        }
    }
}

void Loan ::payLoanAmount(void)
{
    // loanLists.clear();
    loanListsFromCSV();
    // cout << loanLists.size() << endl;
    // cout << loanLists[1].getUserId() << endl;

    int getID;
    cout << "Enter your ID:- " << endl;
    cin >> getID;

    // Check the user has loan or not
    auto it = find_if(loanLists.begin(), loanLists.end(), [&](const Loan &loan)
                      { return loan.getUserId() == getID; });

    if (it != loanLists.end())
    {
        // cout << "Enter your Password:- " << endl;
        // string pass;
        // cin >> pass;

        // PasswordManager pm;
        // bool checkPwd = pm.checkPassword(pass, it->getPassword());

        // Calculate LOan Amount to be paid
        // Based on Simple Interest --> Amount = SI + (P * R * T) / 100;

        double loanPrincipalAmount = it->loanAmount;
        float loanInterestRate = it->interestRate;
        int loanTime = 1;

        // Calculation
        double loanAmountToPay = loanPrincipalAmount + ((loanPrincipalAmount * loanInterestRate * loanTime) / 100.0);

        // Per month
        double loanAmountToPayPerMonth = loanAmountToPay / (double)(it->loanDuration);

        cout << "You need to Pay Rs. " << loanAmountToPayPerMonth << " in this month" << endl;
        cout << "Are you sure to continue? (press y/n)" << endl;

        char c;
        cin >> c;

        if (c == 'n' || c == 'N')
        {
            it->creditScore -= 20;
            return;
        }

        else if (c == 'y' || c == 'Y')
        {
            loadUsersFromCSV2();
            auto it2 = find_if(User ::userLists.begin(), User ::userLists.end(), [&](const User &user)
                               { return user.getUserId() == getID; });

            if (it2 != User ::userLists.end())
            {
                if (it2->getBalance() < loanAmountToPayPerMonth)
                {
                    it->creditScore -= 60;
                    cout << "Not Enough Balance!!" << endl;
                    return;
                }
                else
                {
                    cout << "Loan Amount Paid Successfully!" << endl;
                    it2->setBalance(it2 -> getBalance() - loanAmountToPayPerMonth);
                    cout << "Remaining Loan Amount:- Rs. " << loanAmountToPay - loanAmountToPayPerMonth << endl;
                    it->creditScore += 20;
                    it->loanAmount = loanAmountToPay - loanAmountToPayPerMonth;

                    writeCSVForLoan();
                    updateCSV2();
                }
            }
        }
    }
    else
    {
        cout << "You dont have any loan!" << endl;
        return;
    }
}

#endif