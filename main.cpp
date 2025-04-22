#include <bits/stdc++.h>
#include "User/User.h"
#include "AdminPanel/AdminPanel.h"
#include "TransactionHistory/TransactionHistory.h"
#include "Loan/Loan.h"

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

    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm *localTime = localtime(&currentTime);

    cout << "===============================================" << endl;
    cout << "|        What do you want to do today?        |" << endl;
    cout << "===============================================" << endl;
    cout << "|   Date: " << put_time(localTime, "%Y-%m-%d")
         << "  Time: " << put_time(localTime, "%H:%M:%S") << "   |" << endl;
    cout << "+--------------------------------------+" << endl;
    cout << "| " << setw(2) << "1." << " Create an Account             |" << endl;
    cout << "| " << setw(2) << "2." << " Deposit Amount                |" << endl;
    cout << "| " << setw(2) << "3." << " Withdraw Amount               |" << endl;
    cout << "| " << setw(2) << "4." << " Admin Panel                   |" << endl;
    cout << "| " << setw(2) << "5." << " Exit                          |" << endl;
    cout << "| " << setw(2) << "6." << " Back                          |" << endl;
    cout << "| " << setw(2) << "7." << " Transaction Options           |" << endl;
    cout << "| " << setw(2) << "8." << " Loan                          |" << endl;
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

        if (choice == 2)
        {
            User user;
            user.depositMoney();
        }

        if (choice == 3)
        {
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
            cout << "| " << setw(2) << "1." << " Create an Account             |" << endl;
            cout << "| " << setw(2) << "2." << " Deposit Amount                |" << endl;
            cout << "| " << setw(2) << "3." << " Withdraw Amount               |" << endl;
            cout << "| " << setw(2) << "4." << " Admin Panel                   |" << endl;
            cout << "| " << setw(2) << "5." << " Exit                          |" << endl;
            cout << "| " << setw(2) << "6." << " Back                          |" << endl;
            cout << "| " << setw(2) << "7." << " Transaction Options                          |" << endl;
            cout << "| " << setw(2) << "8." << " Loan                           |" << endl;
            cout << "===============================================" << endl;
        }

        if (choice == 7)
        {
            TransactionHistory newTransaction;
            newTransaction.showTransactionHistoryPanel();
        }

        if (choice == 8)
        {
            Loan loan;
            loan.showLoanPanel();
        }

        cin >> choice;
    }

    return 0;
}
