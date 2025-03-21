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

    cout << "===============================================" << endl;
    cout << "|        What do you want to do today?        |" << endl;
    cout << "===============================================" << endl;
    cout << "| " << setw(2) << "1." << " Create an Account             |" << endl;
    cout << "| " << setw(2) << "2." << " Deposit Amount                |" << endl;
    cout << "| " << setw(2) << "3." << " Withdraw Amount               |" << endl;
    cout << "| " << setw(2) << "4." << " Admin Panel                   |" << endl;
    cout << "| " << setw(2) << "5." << " Exit                          |" << endl;
    cout << "| " << setw(2) << "6." << " Back                          |" << endl;
    cout << "===============================================" << endl;

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
            newUser.displayUser();

            choice = 5;
        }

        if(choice == 3){
            User user;
            user.withdrawMoney();
        }

        if (choice == 4)
        {
            AdminPanel adminPanel;

            string password = adminPanel.getPassword();

            if (password == "Subha@2910")
            {
                cout << "You are authorized! " << endl;
                adminPanel.showAdminPanel();
            }

            else
            {
                cout << "You are not an admin!" << endl;
                choice = 5;
            }
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

        cin >> choice;
    }

    return 0;
}
