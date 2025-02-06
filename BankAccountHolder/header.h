#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double

vector<pair<string, ld>> AccountHolders; 

class AccountHolder
{

    string accNo;
    ld balance;

public:
    string name;
    int age;
    string branchName;

    // Constructor call
    AccountHolder() {}

    //Member functions
    void getInfo();
    void createAccount(string name, string branchName, ld balance = 0.0);

    //Destructor call
    ~AccountHolder() {}
};

void accountHoldersList(){
    for(auto it : AccountHolders){
        cout << it.first << " " << it.second << endl;
    }
}

void AccountHolder::createAccount(string name, string branchName, ld balance)
{
    this->name = name;
    this->branchName = branchName;
    this->balance = balance;
    
    AccountHolders.push_back({name, balance});
    cout << "Congrats " << name << " " << "Account Created Successfully" << endl;
}

void AccountHolder::getInfo()
{

    cout << "Enter your name:- " << endl;
    cin >> this -> name;

    cout << "Enter your branch name:- " << endl;
    cin >> this -> branchName;

    cout << "Enter initial balance:- " << endl;
    cin >> this -> balance;

    createAccount(this->name, this->branchName, this->balance);
}

