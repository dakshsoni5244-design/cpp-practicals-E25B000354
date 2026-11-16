// Practical 02: Classes, access specifiers and member functions (BankAccount)
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    // PRIVATE: data is hidden so outside code cannot set an invalid balance
    // directly. It can only change through validated public functions.
    int accountNumber;
    string holderName;
    double balance;

public:
    // PUBLIC: the interface that other code is allowed to use.
    BankAccount(int accNo, const string& name, double openingBalance) {
        accountNumber = accNo;
        holderName = name;
        // Validate the opening balance
        if (openingBalance < 0) {
            cout << "Invalid opening balance, setting it to 0.\n";
            balance = 0;
        } else {
            balance = openingBalance;
        }
    }

    bool deposit(double amount) {
        if (amount <= 0) {
            cout << "Deposit failed: amount must be positive.\n";
            return false;
        }
        balance += amount;
        cout << "Deposited " << amount << ". New balance: " << balance << "\n";
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Withdraw failed: amount must be positive.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Withdraw failed: insufficient balance.\n";
            return false;
        }
        balance -= amount;
        cout << "Withdrew " << amount << ". New balance: " << balance << "\n";
        return true;
    }

    double getBalance() const { return balance; }   // read-only access

    void display() const {
        cout << "Account No: " << accountNumber << " | Holder: " << holderName
             << " | Balance: " << balance << "\n";
    }
};

int main() {
    BankAccount a1(1001, "Daksh Soni", 5000);
    BankAccount a2(1002, "Aman Verma", 1200);

    cout << "--- Initial details ---\n";
    a1.display();
    a2.display();

    cout << "\n--- Operations on account 1 ---\n";
    a1.deposit(1500);
    a1.withdraw(2000);
    a1.withdraw(10000);   // fails, insufficient balance

    cout << "\n--- Operations on account 2 ---\n";
    a2.deposit(-50);      // fails, invalid amount
    a2.withdraw(200);

    cout << "\n--- Final details ---\n";
    a1.display();
    a2.display();

    // a1.balance = 999999;   // ERROR: 'balance' is private
    return 0;
}
