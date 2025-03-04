#include <iostream>
#include <string>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time() to seed the random number generator

using namespace std;
//Class: BankAccount 
class BankAccount {
private:
    string accountHolderName;    //string for accountHolderName 
    string accountNumber;        //string for name 
    double balance;              //double for balance 

public:
    //  initialize constructor account with name and balance
    BankAccount(string name, double startingBalance) {
        accountHolderName = name; 
        balance = startingBalance;

        //random number generator w/ current time 
        srand(time(0));

        // Generate a random 8-digit account number
        accountNumber = "Act" + to_string(rand() % 1000000000
        ); // 8 digit limits 
    }

    // Deposit function
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
        }
        else {
            cout << "Warning: Deposit amount must be positive." << endl;
        }
    }

    // Withdraw function
    void withdraw(double amount) {
        if (amount > 0) {
            if (balance >= amount) {
                balance -= amount;
                cout << "Withdrew: $" << amount << endl;
            }
            else {
                cout << "Insufficient funds!" << endl;
            }
        }
        else {
            cout << "Warning: Withdrawal amount must be positive." << endl;
        }
    }

    // Get balance function
    double getBalance() {
        return balance;
    }

    // Display account details
    void displayAccountInfo() {
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Current Balance: $" << balance << endl;
    }
};

// Function to handle user input safely
double getUserInput() {
    double input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear();  // clear input 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
            cout << "Invalid input! Please enter a valid number: ";
        }
        else {
            return input;
        }
    }
}

int main() {
    BankAccount* account = nullptr;
    int choice;
    string name;
    double amount;

    while (true) {
        cout << "\n===== Simple Banking System =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. View Account Balance\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            // Create a new account
            cout << "Enter account holder's name: ";
            cin.ignore();  // clear the newline from previous input
            getline(cin, name);
            cout << "Enter initial deposit amount: $";
            amount = getUserInput();
            if (amount < 0) {
                cout << "Warning: Cannot create an account with a negative balance.\n";
            }
            else {
                account = new BankAccount(name, amount);
                cout << "Account created successfully!\n";
            }
            break;

        case 2:
            if (account == nullptr) {
                cout << "Warning: You must create an account first.\n";
                break;
            }
            cout << "Enter deposit amount: $";
            amount = getUserInput();
            account->deposit(amount);
            break;

        case 3:
            if (account == nullptr) {
                cout << "Warning: You must create an account first.\n";
                break;
            }
            cout << "Enter withdrawal amount: $";
            amount = getUserInput();
            account->withdraw(amount);
            break;

        case 4:
            if (account == nullptr) {
                cout << "Warning: You must create an account first.\n";
                break;
            }
            account->displayAccountInfo();
            break;

        case 5:
            cout << "Thank you for using the Simple Banking System!\n";
            delete account;  // Delete account 
            return 0;  // Exit the program

        default:
            cout << "Invalid choice! Please choose a valid option from 1 to 5.\n";
        }
    }

    return 0;
}
