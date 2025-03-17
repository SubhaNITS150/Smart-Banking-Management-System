#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <iostream>
#include "../User/User.h"
#include <iomanip>
using namespace std;

class User;

class AdminPanel {

public:
    void showAdminPanel(void);
    void showUsers(void);
    void deleteUser(int id);
    string getPassword(void);
};

void AdminPanel ::showAdminPanel(void)
{
    cout << "Welcome to the Admin Panel" << endl;
    cout << "1. View Users" << endl;
    cout << "2. Delete User" << endl;
    cout << "3. Find User" << endl;
    cout << "4. Back to Main Menu" << endl;

    cout << "Enter what you want to do:- " << endl;
    int choice;
    cin >> choice;

    if(choice == 1){
        showUsers();
    }
}

string AdminPanel ::getPassword(void)
{
    cout << "Enter password to Access Admin Panel: " << endl;
    string password;
    cin >> password;

    return password;
}

void AdminPanel :: showUsers(void) {
    cout << "\n----------------------------------------------------------------\n";
    cout << setw(10) << left << "ID" 
         << setw(20) << left << "Name" 
         << setw(20) << left << "Account Number" 
         << setw(15) << left << "Balance" << endl;
    cout << "----------------------------------------------------------------\n";

    for (const auto &user : User::userLists) {
        cout << setw(10) << left << user.userId 
             << setw(20) << left << user.name 
             << setw(20) << left << user.accountNo 
             << setw(15) << left << user.balance << endl;
    }

    cout << "----------------------------------------------------------------\n";
}

void AdminPanel :: deleteUser(int id){
    
}

#endif