#ifndef TRANSACTIONHISTORY_H
#define TRANSACTIONHISTORY_H
using namespace std;
#include "../AdminPanel/AdminPanel.h"

class TransactionHistory
{
    long long transactionId;
    unsigned long long fromAccountNo;
    unsigned long long toAccountNo;
    double amount;
    string transactionType;
    string dateTime;
    string status;

public:
    void showTransactionHistoryPanel(void);
    void transferAmount(void);
    void printAllTransactions(void);

    friend void appendTransactionToCSV(const User &user, const string &filename, const TransactionHistory &transaction);
    friend void saveTransactionToCSV(const User &user, const string &filename);
};

// ---------------------------Utility Functions----------------------------

void updateCSV()
{
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

void loadUsersFromCSV(void)
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

void saveTransactionToCSV(const User &user, const string &filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    for (const auto &t : user.listTransactions)
    {
        file << t.transactionId << ","
             << t.fromAccountNo << ","
             << t.toAccountNo << ","
             << t.amount << ","
             << t.transactionType << ","
             << t.status << "\n";
    }
}

void appendTransactionToCSV(const User &user, const string &filename, const TransactionHistory &transaction)
{
    bool fileExists = false;
    ifstream infile(filename);

    if (infile.good())
    {
        fileExists = true;
    }
    infile.close();

    ofstream file;

    if (fileExists)
    {
        file.open(filename, ios ::app);
    }
    else
    {
        file.open(filename);
        file << "Transaction ID, From Account, To Account, Amount, Type, Status\n";
    }

    if (!file.is_open())
    {
        cerr << "Error opening transaction file!" << endl;
        return;
    }

    file << transaction.transactionId << ","
         << transaction.fromAccountNo << ","
         << transaction.toAccountNo << ","
         << transaction.amount << ","
         << transaction.transactionType << ","
         << transaction.status << "\n";

    file.close();
}

// -------------------------Member Functions-------------------------------

void TransactionHistory ::showTransactionHistoryPanel(void)
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

    if (choice == 1)
    {
        TransactionHistory newTransaction;
        newTransaction.transferAmount();
    }
}

void TransactionHistory ::transferAmount(void)
{
    loadUsersFromCSV();

    cout << "Welcome to the Amount Transfer Panel" << endl;

    // Fetch ID of sender
    int getID;
    cout << "Enter the ID of sender:- " << endl;
    cin >> getID;

    auto it = find_if(User ::userLists.begin(), User ::userLists.end(), [&](const User &user)
                      { return user.userId == getID; });

    // it -> sender
    // it2 -> reciever

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

                if (it->balance >= amount)
                {
                    it2->balance += amount;
                    it->balance -= amount;

                    updateCSV();

                    // Sender
                    TransactionHistory t_sender;

                    t_sender.transactionId = 1;
                    t_sender.fromAccountNo = it->accountNo;
                    t_sender.toAccountNo = it2->accountNo;
                    t_sender.amount = amount;
                    t_sender.transactionType = "Debited";
                    t_sender.status = "Success";

                    it->listTransactions.push_back(t_sender);

                    // Reciever
                    TransactionHistory t_reciever;

                    t_reciever.transactionId = 0;
                    t_reciever.fromAccountNo = it->accountNo;
                    t_reciever.toAccountNo = it2->accountNo;
                    t_reciever.amount = amount;
                    t_reciever.transactionType = "Credited";
                    t_reciever.status = "Success";

                    it2->listTransactions.push_back(t_reciever);

                    // Store it in a different file

                    // Store for sender
                    string filename = it->name + to_string(it->accountNo) + ".csv";
                    appendTransactionToCSV(*it, filename, t_sender);

                    // Store for reciever
                    string filename2 = it2->name + to_string(it2->accountNo) + ".csv";
                    appendTransactionToCSV(*it2, filename2, t_reciever);
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

void TransactionHistory ::printAllTransactions(void)
{
}

#endif