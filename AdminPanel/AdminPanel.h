#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <iostream>
#include "../User/User.h"
using namespace std;

class User;

class AdminPanel
{
public:
    void showAdminPanel(void);
    void showUsers(void);
    string getPassword(void);
};

void AdminPanel ::showAdminPanel(void)
{
    cout << "Welcome to the Admin Panel" << endl;
    cout << "1. View Users" << endl;
    cout << "2. Delete User" << endl;
    cout << "3. Back to Main Menu" << endl;

    showUsers();
}

string AdminPanel ::getPassword(void)
{
    cout << "Enter password to Access Admin Panel: " << endl;
    string password;
    cin >> password;

    return password;
}

void AdminPanel ::showUsers(void)
{
    for (int i = 0; i < User::userLists.size(); i++)
    {
        cout << User::userLists[i] << endl;
    }
}

#endif