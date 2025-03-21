#ifndef USER_H
#define USER_H

#include<bits/stdc++.h>
#include<iomanip>
#include<fstream>
#include<random>

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
    string password;

    public:

    static vector<User> userLists;
    void createUser(void);
    void displayUser(void);
    void depositMoney(void);
    void setPassword(void);
    void withdrawMoney(void);

    friend class AdminPanel;
};

//-----------------utility functions---------------------------

long long generateRandom8DigitInt() {
    random_device rd;
    mt19937 generator(rd());  
    uniform_int_distribution<long long> distribution(10000000, 99999999); 

    return distribution(generator);
}

bool isFileEmpty(const string& filename){
    ifstream file(filename);
    return file.peek() == ifstream::traits_type::eof();
}

//------------------------constants---------------------------------
long long User :: id = 1;
vector<User> User::userLists;


//--------------------------Functions--------------------------------
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

    setPassword();

    userId = id++;
    User ::userLists.push_back(*this);

    ofstream file("userlists.csv", ios::app);

    if(!file.is_open()){
        cout << "Error opening file" << endl;
        return;
    }

    if(isFileEmpty("userlists.csv")){
        file << "ID, Account Number, Name, Account Type, Branch Name, Balance\n" ;

    }
    

        file << userId << "," 
            << accountNo << "," 
            << name << "," 
            << accountType << "," 
            << branchName << "," 
            << balance << "\n";

            file.close();

            cout << "Data Saved Successfully" << endl;
    
}

void User :: setPassword(void){
    cout << "Enter Password" << endl;
    string password;
    cin >> password;
}

void User :: withdrawMoney(void) {
    int getID;
    cout << "Enter ID:- " << endl;
    cin >> getID;

    auto it = find_if(User :: userLists.begin(), User :: userLists.end(), [&](const User &user)
    {
        return user.userId == getID;
    });

    if(it != User :: userLists.end()){
        double amt;
        cout << "Enter amount you want to withdraw:- " << endl;
        cin >> amt;

        if(amt > (it -> balance)){
            cout << "Insufficient balance";
            return;
        }


        else{
            it -> balance -= amt;
            cout << "Amount Withdrawn Successfully" << endl;
            cout << "Balance:- " << it -> balance << endl;
            return;
        }
    }
    else{
        cout << "User not found" << endl;
        return;
    }
}

void User :: depositMoney(void){
    int getID;
    cout << "Enter ID:- " << endl;
    cin >> getID;

    auto it = find_if(User :: userLists.begin(), User :: userLists.end(), [&](const User &user)
    {
        return user.userId == getID;
    });

    if(it != User :: userLists.end()){
        double amt;
        cout << "Enter amount you want to withdraw:- " << endl;
        cin >> amt;

        it -> balance += amt;
        cout << "Amount Added Successfully" << endl;
        cout << "Balance:- " << it -> balance << endl;
    }
}

void User :: displayUser(void) {
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