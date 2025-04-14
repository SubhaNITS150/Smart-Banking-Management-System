
#include "../User/User.h"
// #include "../TransactionHistory/TransactionHistory.h"
#ifndef ADMINPANEL_H
#define ADMINPANEL_H
#include<conio.h>
using namespace std;

class User;

class AdminPanel
{

public:
    void showAdminPanel(void);
    void showUsers(void);
    void deleteUser(void);
    void findUser(void);
    void changePassword(void);
    void updateUserDetails(void);
    void loadUsersFromCSV(void);
    void updateCSV(void);
    void totalAmountInBank(void);
    string getPassword(void);
};

void AdminPanel ::showAdminPanel(void)
{
    cout << "Welcome to the Admin Panel" << endl;
    cout << "1. View Users" << endl;
    cout << "2. Delete User" << endl;
    cout << "3. Find User" << endl;
    cout << "4. Change Password of an User" << endl;
    cout << "5. Update User Details" << endl;
    cout << "6. Back to Main Menu" << endl;
    cout << "7. Display Total Amount in Bank" << endl;

    cout << "Enter what you want to do:- " << endl;
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        showUsers();
    }

    if (choice == 2)
    {
        deleteUser();
    }

    if (choice == 3)
    {
        findUser();
    }

    if (choice == 4)
    {
        changePassword();
    }

    if (choice == 5)
    {
        updateUserDetails();
    }

    if (choice == 7) {
        totalAmountInBank();
    }

    else
    {
        showAdminPanel();
    }
}

string AdminPanel ::getPassword(void)
{
    cout << "Enter password to Access Admin Panel: " << endl;
    string password = "";
    char ch;
    // cin >> password;

    while((ch = _getch()) != '\r'){
        if(ch == '\b'){
            if(!password.empty()){
                cout << "\b \b";
                password.pop_back();
            }
        }
        else{
            password += ch;
            cout << "*";
        }
    }
    cout << endl;

    return password;
}

void AdminPanel ::showUsers(void)
{
    loadUsersFromCSV();

    cout << "\n----------------------------------------------------------------\n";
    cout << setw(10) << left << "ID"
         << setw(20) << left << "Name"
         << setw(20) << left << "Account Number"
         << setw(15) << left << "Balance" << endl;
    cout << "----------------------------------------------------------------\n";

    for (const auto &user : User::userLists)
    {
        if(user.isMember){
            cout << setw(10) << left << user.userId
                 << setw(20) << left << user.name
                 << setw(20) << left << user.accountNo
                 << setw(15) << left << user.balance << endl;
        }
    }

    cout << "----------------------------------------------------------------\n";
}

void AdminPanel :: loadUsersFromCSV()
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

void AdminPanel ::updateCSV()
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

void AdminPanel ::deleteUser()
{
    int getID;
    cout << "Enter ID:- " << endl;
    cin >> getID;

    loadUsersFromCSV();

    auto it = find_if(User ::userLists.begin(), User ::userLists.end(), [&](const User &user)
                      { return user.userId == getID; });

    if (it != User ::userLists.end())
    {
        it->isMember = false;

        updateCSV();
        cout << "Membership cancelled successfully!" << endl;
    }

    else
    {
        cout << "ID not found" << endl;
    }
}

void AdminPanel ::findUser()
{
    int getID;
    cout << "Enter ID:- " << endl;
    cin >> getID;

    loadUsersFromCSV();

    auto it = find_if(User ::userLists.begin(), User ::userLists.end(), [&](const User &user)
                      { return user.userId == getID; });

    if (it != User::userLists.end() && it -> isMember)
    {
        
        cout << "\n---------------------------------------------\n";
        cout << setw(10) << "ID" << setw(20) << "Name" << setw(20)
             << "Account No" << setw(20) << "Account Type" << setw(15)
             << "Branch" << setw(12) << "Balance" << endl;
        cout << "---------------------------------------------\n";
        cout << setw(10) << it->userId << setw(20) << it->name << setw(20)
             << it->accountNo << setw(20) << it->accountType << setw(15)
             << it->branchName << setw(12) << fixed << setprecision(2) << it->balance << endl;
        cout << "---------------------------------------------\n";
    }
    else
    {
        cout << "ID not found!" << endl;
    }
}

void AdminPanel ::changePassword(void)
{
    int getID;
    cout << "Enter ID:- " << endl;
    cin >> getID;

    auto it = find_if(User ::userLists.begin(), User ::userLists.end(), [&](const User &user)
                      { return user.userId == getID; });

    if (it != User ::userLists.end())
    {
        cout << "Previous Password" << endl;
        cout << it->password << endl;

        cout << "Enter New Password:- " << endl;
        string pass;
        cin >> pass;

        it->password = pass;
        cout << "New Password" << endl;
        cout << it->password << endl;
    }
}

void AdminPanel ::updateUserDetails(void)
{
    int getID;
    cout << "Enter ID:- " << endl;
    cin >> getID;

    auto it = find_if(User ::userLists.begin(), User ::userLists.end(), [&](const User &user)
                      { return user.userId == getID; });

    if (it != User::userLists.end())
    {
        string name;
        cin >> name;
        cout << "Enter name:- " << endl;
        it->name = name;

        string accountType;
        cin >> accountType;
        cout << "Enter account type:- " << endl;
        it->accountType = accountType;

        string branchName;
        cin >> branchName;
        cout << "Enter branch name:- " << endl;
        it->branchName = branchName;

        cout << "Updated Details:- " << endl;

        cout << "\n---------------------------------------------\n";
        cout << setw(10) << "ID" << setw(20) << "Name" << setw(20)
             << "Account No" << setw(20) << "Account Type" << setw(15)
             << "Branch" << setw(12) << "Balance" << endl;
        cout << "---------------------------------------------\n";
        cout << setw(10) << it->userId << setw(20) << it->name << setw(20)
             << it->accountNo << setw(20) << it->accountType << setw(15)
             << it->branchName << setw(12) << fixed << setprecision(2) << it->balance << endl;
        cout << "---------------------------------------------\n";
    }
}

void AdminPanel :: totalAmountInBank(void) {
    loadUsersFromCSV();
    long long sum = 0;

    for(auto it : User :: userLists) {
        sum += it.balance;
    }

    cout << "Total amount in bank:- " << sum << endl;
}

#endif