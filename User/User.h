

#include <bits/stdc++.h>
#include <iomanip>
#include <fstream>
#include <random>
// #include "../AdminPanel/AdminPanel.h"
#include "../TransactionHistory/TransactionHistory.h"

#ifndef USER_H
#define USER_H
using namespace std;

class AdminPanel;
class TransactionHistory;

class User
{
    string name;

protected:
    long long userId;

private:
    static long long id;
    unsigned long long accountNo;
    string accountType;
    string branchName;
    double balance;
    string password;
    bool isMember;
    vector<TransactionHistory> listTransactions;

public:
    static vector<User> userLists;
    void createUser(void);
    void displayUser(void);
    void depositMoney(void);
    void setPassword(void);
    void withdrawMoney(void);

    static void initializeID(const string &filename);

    friend class TransactionHistory;
    friend void loadUsersFromCSV(void);
    friend void updateCSV(void);
    friend void saveTransactionToCSV(const User &user, const string &filename);
    friend class AdminPanel;
};

//----------------utility functions---------------------------

bool isFileEmpty(const string &filename)
{
    ifstream file(filename);
    return file.peek() == ifstream::traits_type::eof();
}

//------------------------constants---------------------------------
long long User ::id = 1;
vector<User> User::userLists;

//--------------------------Functions--------------------------------

void User ::initializeID(const string &filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }

    string line, lastLine;
    while (getline(file, line))
    {
        if (!line.empty() && line.find_first_not_of(" \t") != string::npos)
        {
            lastLine = line;
        }
    }

    file.close();

    if (!lastLine.empty())
    {
        stringstream ss(lastLine);
        string idStr;

        getline(ss, idStr, ',');

        try
        {
            id = stoll(idStr) + 1;
        }

        catch (const exception &e)
        {
            cout << "ID not fetched" << endl;
            id = 1;
        }
    }
}

void User ::createUser(void)
{

    User::initializeID("userlists.csv");

    string name;
    cout << "Enter your name:- " << endl;
    cin >> name;

    string accountType;
    cout << "Enter your account type:- " << endl;
    cin >> accountType;

    string branchName;
    cout << "Enter the branch name:- " << endl;
    cin >> branchName;

    double balance = 0.00;
    cout << "Do you want to deposit initial amount? (y / n) :- " << endl;

    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        cout << "Enter balance:-\t";
        double amount;
        cin >> amount;

        cout << "Deposited Successfully!" << endl;
        balance += amount;
    }

    else if (choice == 'n' || choice == 'N')
    {
        balance = 0.00;
    }

    cout << "Enter password:- " << endl;
    string password;
    cin >> password;

    this->id = User ::id;
    this->name = name;
    this->accountNo = accountNo;
    this->accountType = accountType;
    this->branchName = branchName;
    this->balance = balance;
    this->password = password;
    long long accountNo = 60012100 + id;

    // setPassword();
    isMember = true;

    userId = id++;
    User ::userLists.push_back(*this);

    ofstream file("userlists.csv", ios::app);

    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }

    if (isFileEmpty("userlists.csv"))
    {
        file << "ID, Account Number, Name, Account Type, Branch Name, Balance, Membership, Password\n";
    }

    file << userId << ","
         << accountNo << ","
         << name << ","
         << accountType << ","
         << branchName << ","
         << balance << ","
         << (isMember ? "Yes" : "No") << ","
         << password << "\n";

    file.close();

    cout << "Data Saved Successfully" << endl;
}

void User ::setPassword(void)
{
    cout << "Enter Password" << endl;
    cin >> this->password;
}

void User ::withdrawMoney(void)
{
    int getID;
    cout << "Enter ID:- " << endl;
    cin >> getID;

    auto it = find_if(User ::userLists.begin(), User ::userLists.end(), [&](const User &user)
                      { return user.userId == getID; });

    if (it != User ::userLists.end())
    {
        double amt;
        cout << "Enter amount you want to withdraw:- " << endl;
        cin >> amt;

        if (amt > (it->balance))
        {
            cout << "Insufficient balance";
            return;
        }

        else
        {
            it->balance -= amt;
            cout << "Amount Withdrawn Successfully" << endl;
            cout << "Balance:- " << it->balance << endl;
            return;
        }
    }
    else
    {
        cout << "User not found" << endl;
        return;
    }
}

void User ::depositMoney(void)
{
    int getID;
    cout << "Enter ID:- " << endl;
    cin >> getID;

    auto it = find_if(User ::userLists.begin(), User ::userLists.end(), [&](const User &user)
                      { return user.userId == getID; });

    if (it != User ::userLists.end())
    {
        double amt;
        cout << "Enter amount you want to withdraw:- " << endl;
        cin >> amt;

        it->balance += amt;
        cout << "Amount Added Successfully" << endl;
        cout << "Balance:- " << it->balance << endl;
    }
}

void User ::displayUser(void)
{
    cout << endl;
    cout << "===============================================" << endl;
    cout << "|     Bank Account Created Successfully! |" << endl;
    cout << "===============================================" << endl;
    cout << "| " << setw(15) << left << "ID"
         << "| " << setw(20) << left << userId << " |" << endl;
    cout << "| " << setw(15) << left << "Name"
         << "| " << setw(20) << left << name << " |" << endl;
    cout << "| " << setw(15) << left << "Account Number"
         << "| " << setw(20) << left << accountNo << " |" << endl;
    cout << "| " << setw(15) << left << "Branch Name"
         << "| " << setw(20) << left << branchName << " |" << endl;
    cout << "| " << setw(15) << left << "Balance"
         << "| " << setw(20) << left << fixed << setprecision(2) << balance << " |" << endl;
    cout << "===============================================" << endl;
    cout << "|           HAPPY BANKING WITH US!            |" << endl;
    cout << "===============================================" << endl;
}

#endif