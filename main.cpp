#include <bits/stdc++.h>
#include "User/User.h"
#include "AdminPanel/AdminPanel.h"
using namespace std;

void printHeader()
{
    std::cout << "========================================\n";
    std::cout << "      BANKING MANAGEMENT SYSTEM         \n";
    std::cout << "========================================\n";
    std::cout << "       Secure | Reliable | Fast         \n";
    std::cout << "========================================\n\n";
}

int main()
{

    printHeader();
    cout << endl;
    cout << endl;

    cout << "Enter what you want to do today:- " << endl;

    cout << endl;
    cout << "1. Create an Account " << endl;
    cout << "2. Deposit Amount " << endl;
    cout << "3. Withdraw Amount " << endl;
    cout << "4. Admin Panel " << endl;
    cout << "5. Exit " << endl;
    cout << "6. Back " << endl;

    int choice;
    cin >> choice;

    while (true)
    {
        if (choice == 5)
        {
            cout << "Thank you for banking with us!" << endl;
            break;
        }

        if (choice == 1)
        {
            User newUser;
            newUser.createUser();
            User :: userLists.push_back(newUser);
            newUser.displayUser();

            choice = 5;
        }

        if(choice == 4) {
            
        }

        if (choice == 5)
        {
            cout << "1. Create an Account " << endl;
            cout << "2. Deposit Amount " << endl;
            cout << "3. Withdraw Amount " << endl;
            cout << "4. Admin Panel " << endl;
            cout << "5. Exit " << endl;
            cout << "6. Back " << endl;
        }

        //test

        if(choice == 100) {
            AdminPanel adminPanel;
            adminPanel.showUsers();
        }

        cin >> choice;
    }

    return 0;
}
