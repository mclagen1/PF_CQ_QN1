#include <iostream>
#include <unordered_map>
#include <limits>
#include <string>

using namespace std;

// Structure to store account details
struct Account {
    string password;
    double balance;
};

// Global map to store user accounts
unordered_map<string, Account> accounts;

// Function to clear the input stream
void clearInputStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to create a new bank account
void createAccount() {
    string userId, password;
    cout << "Please enter your user name: ";
    cin >> userId;

    if (accounts.find(userId) != accounts.end()) {
        cout << "User ID already exists. Please choose a different ID." << endl;
        return;
    }

    cout << "Please enter your password: ";
    cin >> password;

    accounts[userId] = {password, 0.0};
    cout << "Thank You! Your account has been created!" << endl;
}

// Function to login with user ID and password
string login() {
    string userId, password;
    cout << "Please enter your user id: ";
    cin >> userId;

    auto it = accounts.find(userId);
    if (it == accounts.end()) {
        cout << "*** LOGIN FAILED! ***" << endl;
        return "";
    }

    cout << "Please enter your password: ";
    cin >> password;

    if (it->second.password == password) {
        cout << "Access Granted!" << endl;
        return userId;
    } else {
        cout << "*** LOGIN FAILED! ***" << endl;
        return "";
    }
}

// Function to withdraw money from the account
void withdrawMoney(Account& acc) {
    double amount;
    cout << "Amount of withdrawal: $";
    cin >> amount;

    if (amount > acc.balance) {
        cout << "Insufficient funds." << endl;
    } else {
        acc.balance -= amount;
        cout << "Withdrawal successful. New balance: $" << acc.balance << endl;
    }
}

// Function to deposit money into the account
void depositMoney(Account& acc) {
    double amount;
    cout << "Amount of deposit: $";
    cin >> amount;

    acc.balance += amount;
    cout << "Deposit successful. New balance: $" << acc.balance << endl;
}

// Function to request the balance of the account
void requestBalance(const Account& acc) {
    cout << "Your balance is $" << acc.balance << endl;
}

// Main menu function for logged-in users
void mainMenu(const string& userId) {
    while (true) {
        cout << "\nd -> Deposit Money" << endl;
        cout << "w -> Withdraw Money" << endl;
        cout << "r -> Request Balance" << endl;
        cout << "q -> Quit" << endl;
        cout << "Select an option: ";
        
        char choice;
        cin >> choice;
        clearInputStream();  // Clear the input stream to handle invalid input

        auto it = accounts.find(userId);
        if (it == accounts.end()) {
            cout << "User account not found!" << endl;
            return;
        }
        Account& acc = it->second;

        switch (choice) {
            case 'd':
                depositMoney(acc);
                break;
            case 'w':
                withdrawMoney(acc);
                break;
            case 'r':
                requestBalance(acc);
                break;
            case 'q':
                cout << "Quitting..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

// Introduction menu function
void introductionMenu() {
    while (true) {
        cout << "\nHi! Welcome to the ATM Machine!" << endl;
        cout << "Please select an option from the menu below:" << endl;
        cout << "l -> Login" << endl;
        cout << "c -> Create New Account" << endl;
        cout << "q -> Quit" << endl;
        cout << "Select an option: ";
        
        char choice;
        cin >> choice;
        clearInputStream();  // Clear the input stream to handle invalid input

        switch (choice) {
            case 'l':
                {
                    string userId = login();
                    if (!userId.empty()) {
                        mainMenu(userId);
                    }
                }
                break;
            case 'c':
                createAccount();
                break;
            case 'q':
                cout << "Quitting..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

// Main function
int main() {
    introductionMenu();
    return 0;
}
