# Smart-Banking-Management-System
A Command-Line Interface (CLI) based Smart Banking Management System developed in C++. The system allows users to perform basic banking operations such as creating accounts, viewing account details, making transactions, and maintaining transaction history. The system supports both admin and user functionalities and handles transaction records using CSV files for persistence.

# H2 Features
# H3 Admin Panel
View all users

Search for a user by ID

Delete user accounts

View all transaction logs

# H3 User Panel
Create an account

View account details

Transfer money to other users

View transaction history

Deposit and withdraw money

# H3 Transaction Management

Each transaction (transfer, deposit, withdrawal) is stored in a CSV file

View transaction history for individual users

Generate reports for auditing

# H2 Programming Concepts
Password Hasher

C++ - Core programming language

CSV file handling - For data storage

OOP concepts - Classes like AdminPanel, User, and TransactionHistory

# H2 Folder Structure
<pre lang="markdown"> <code> ``` Smart-Banking-Management-System/ ├── main.cpp ├── AdminPanel.h ├── AdminPanel.cpp ├── User.h ├── User.cpp ├── TransactionHistory.h ├── TransactionHistory.cpp ├── data/ │ ├── users.csv │ └── transactions.csv └── README.md ``` </code> </pre>