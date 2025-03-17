#ifndef USER_H
#define USER_H

#include<bits/stdc++.h>
#include<random>
// #include "../AdminPanel/AdminPanel.h"
using namespace std;


class AdminPanel;

class User {
    string name;
    long long userId;
    static long long id;
    unsigned long long accountNo;  
    string accountType;
    string branchName;
    double balance;
    

    public:

    static vector<User> userLists;
    void createUser(void);
    void displayUser(void);
    void depositMoney(void);

    friend class AdminPanel;
};

//Account Number generator

long long generateRandom8DigitInt() {
    random_device rd;
    mt19937 generator(rd());  
    uniform_int_distribution<long long> distribution(10000000, 99999999); 

    return distribution(generator);
}

//constants
long long User :: id = 1;
vector<User> User::userLists;

void User :: createUser(void) {
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

    if(choice == 'y' || choice == 'Y'){
        cout << "Enter balance:-\t";
        double amount;
        cin >> amount;

        cout << "Deposited Successfully!" << endl;
        balance += amount;
    }

    else if(choice == 'n' || choice == 'N'){
        balance = 0.00;
    }

    long long accountNo = generateRandom8DigitInt();

    this -> id = User :: id;
    this -> name = name;
    this -> accountNo = accountNo;
    this -> accountType = accountType;
    this -> branchName = branchName;
    this -> balance = balance;

    userId = id++;
    User ::userLists.push_back(*this);
    
}

void User :: depositMoney(void){

    cout << "Enter the money you want to deposit:- " << endl;
    double amount;
    cin >> amount;

    balance += amount;
    cout << "Amount added Successfully!" << endl;
    cout << endl;
    cout << "Available Balance:- " << balance << endl;
}

void User :: displayUser(void) {
    cout << endl;
    cout << "Bank Account created Successfully!" << endl;
    cout << endl;

    cout << "Details:- " << endl;
    cout << endl;

    cout << "ID:- " << userId << endl;
    cout << "Name:- " << name << endl;
    cout << "Account Number:- " << accountNo << endl;
    cout << "Branch Name:- " << branchName << endl;
    cout << "Balance:- " << balance << endl;

    cout << endl;
    cout << "HAPPY BANKING WITH US!" << endl;
}

#endif