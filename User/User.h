
#include <bits/stdc++.h>
#include <iomanip>
#include <fstream>
#include <random>
#include "../TransactionHistory/TransactionHistory.h"
#include "../PasswordHasher/PasswordManager.h"

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
    friend void loadUsersFromCSV2(void);
    friend void updateCSV(void);
    friend void saveTransactionToCSV(const User &user, const string &filename);
    friend void updateCSV2(void);
    friend class AdminPanel;

    //Getters and setters (for Loan.h)
    void setUserId(int userId) { this->userId = userId;}
    void setBalance(double balance) {this -> balance = balance;}
    void setName(string name) {this -> name = name;}

    int getUserId() const {return userId;}
    string getPassword() const {return password;}
    string getName() {return name;}
    long long getAccountNo() {return accountNo;}
    double getBalance() {return balance;}

};

//----------------utility functions---------------------------

bool isFileEmpty(const string &filename)
{
    ifstream file(filename);
    return file.peek() == ifstream::traits_type::eof();
}

void updateCSV2()
{
    ofstream outFile("userlists.csv");
    if (!outFile.is_open())
    {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    outFile << "ID,Account Number,Name,Account Type,Branch Name,Balance,Membership,Password\n";

    for (const auto &user : User::userLists)
    {
        outFile << user.userId << ","
                << user.accountNo << ","
                << user.name << ","
                << user.accountType << ","
                << user.branchName << ","
                << fixed << setprecision(2) << user.balance << ","
                << (user.isMember ? "Yes" : "No") << ","
                << user.password << "\n";
    }

    outFile.close();
}

void loadUsersFromCSV2(void)
{
    ifstream file("userlists.csv");

    if (!file.is_open())
    {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    User::userLists.clear();

    string line, token;
    getline(file, line);

    while (std::getline(file, line))
    {
        std::istringstream stream(line);

        User user;
        std::getline(stream, token, ',');
        user.userId = std::stoi(token);

        std::getline(stream, token, ',');
        user.accountNo = std::stoi(token);

        std::getline(stream, token, ',');
        user.name = token;

        std::getline(stream, token, ',');
        user.accountType = token;

        std::getline(stream, token, ',');
        user.branchName = token;

        std::getline(stream, token, ',');
        user.balance = std::stod(token);

        std::getline(stream, token, ',');
        user.isMember = (token == "Yes");

        getline(stream, token, ',');
        user.password = token;

        User::userLists.push_back(user);
    }

    file.close();
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

    //HAsh the password
    PasswordManager pwdmanager;
    string hashPwd = pwdmanager.hashPassword(password);

    this->id = User ::id;
    this->name = name;
    
    this->accountType = accountType;
    this->branchName = branchName;
    this->balance = balance;
    this->password = hashPwd;
    long long accountNo = 60012100 + id;
    this->accountNo = accountNo;
    
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
         << hashPwd << "\n";

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

    loadUsersFromCSV2();

    auto it = find_if(User ::userLists.begin(), User ::userLists.end(), [&](const User &user)
                      { return user.userId == getID; });

    if (it != User ::userLists.end())
    {
        cout << "Enter password:- " << endl;
        string pass;
        cin >> pass;

        PasswordManager pm;
        bool checkPwd = pm.checkPassword(pass, it -> password);

        if(checkPwd){
            cout << "Enter the amount you want to withdraw:- " << endl;
            double amt;
            cin >> amt;

            if(amt > it -> balance) {
                cout << "Insufficient Balance" << endl;
                return;
            }

            else {
                it -> balance -= amt;
                cout << "Amount :- " << amt << "withdrawn successfully" << endl;
                cout << "Available balance:- " << it -> balance << endl;
                updateCSV2();
                return;
            }
        }
        else{
            cout << "Incorrect Password entered" << endl;
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
    cout << "Enter your ID" << endl;
    cin >> getID;

    loadUsersFromCSV2();

    auto it = find_if(User ::userLists.begin(), User ::userLists.end(), [&](const User &user)
                      { return user.userId == getID; });
    
    if(it != User :: userLists.end() && it -> isMember){
        cout << "Enter the amount you want to deposit" << endl;
        double amt;

        cin >> amt;

        it -> balance += amt;
        updateCSV2();

        // saveDebitTransaction(*it, filename, amt);
        // cout << "Transaction saved" << endl;
    }

    else{
        cout << "User not registered with the bank" << endl;
        return;
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