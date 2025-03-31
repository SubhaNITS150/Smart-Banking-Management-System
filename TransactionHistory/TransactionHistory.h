#ifndef TRANSACTIONHISTORY_H
#define TRANSACTIONHISTORY_H
using namespace std;
#include "../AdminPanel/AdminPanel.h"

class TransactionHistory : public User
{
    long long transactionId;
    unsigned long long fromAccountNo;
    unsigned long long toAccountNo;
    double amount;
    string transactionType;
    string dateTime;
    string status;

public:
    // Functions
    void showTransactionOptions(void);
    void transferAmount(void);
    void loadUsersFromCSV(void);
    void updateCSV(void);
};

void TransactionHistory :: updateCSV() {
    ofstream file("userlists.csv", std::ios::trunc);

    if (!file.is_open())
    {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    file << "ID, Account Number, Name, Account Type, Branch Name, Balance, Membership, Password\n";

    for (const auto &user : User::userLists)
    {
        file << user.userId << ","
         << user.accountNo << ","
         << user.name << ","
         << user.accountType << ","
         << user.branchName << ","
         << user.balance << ","
         << (user.isMember ? "Yes" : "No") << ","
         << user.password << "\n";
    }

    file.close();
}

void TransactionHistory :: loadUsersFromCSV()
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

void TransactionHistory ::showTransactionOptions(void)
{
    cout << "===============================================" << endl;
    cout << "|        What do you want to do ?             |" << endl;
    cout << "===============================================" << endl;
    cout << "| " << setw(2) << "1." << " Transfer amount               |" << endl;
    cout << "| " << setw(2) << "2." << " Get Specific Transactions      |" << endl;
    cout << "| " << setw(2) << "3." << " Print all Transactions         |" << endl;
    cout << "| " << setw(2) << "4." << " Exit                            |" << endl;
    cout << "| " << setw(2) << "5." << " Back                            |" << endl;
    cout << "===============================================" << endl;

    int choice;
    cin >> choice;

    if(choice == 1) {
        TransactionHistory newTransaction;
        newTransaction.transferAmount();
    }
}

void TransactionHistory ::transferAmount(void)
{   
    loadUsersFromCSV();
    cout << "Welcome to money transfer panel" << endl;
    cout << "Enter ID " << endl;
    int getID;
    cin >> getID;

    auto it = find_if(User ::userLists.begin(), User ::userLists.end(), [&](const User &user)
                      { return user.userId == getID; });

    if (it != User ::userLists.end())
    {
        cout << "Enter your password:- " << endl;
        string password;
        cin >> password;

        if (password == it->password)
        {
            cout << "Enter the account number of the receipent:- " << endl;
            long long accNo;
            cin >> accNo;

            auto it2 = find_if(User ::userLists.begin(), User ::userLists.end(), [&](const User &user)
                               { return user.accountNo == accNo && user.isMember == true; });

            if (it2 != User ::userLists.end())
            {
                cout << "Enter the amount you want to transfer:- " << endl;
                double amount;
                cin >> amount;

                // it --> sender
                // it2 --> reciever
                if (it->balance >= amount)
                {
                    it2->balance += amount;
                    it->balance -= amount;

                    updateCSV();
                }
                else
                {
                    cout << "Insufficient balance" << endl;
                    return;
                }
            }

            else
            {
                cout << "User does not exists" << endl;
                return;
            }
        }

        else
        {
            cout << "Incorrect Password" << endl;
            return;
        }
    }
    else
    {
        cout << "Incorrect ID" << endl;
        return;
    }
}
#endif