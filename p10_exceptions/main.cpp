// Practical 10: Custom exception hierarchy - banking transactions
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Base class for all bank errors
class BankException : public runtime_error {
public:
    explicit BankException(const string& msg) : runtime_error(msg) {}
};

// Thrown when the amount is zero or negative
class InvalidAmount : public BankException {
public:
    explicit InvalidAmount(double amount)
        : BankException("Invalid amount: " + to_string(amount) + " (must be positive)") {}
};

// Thrown when the withdrawal is more than the balance
class InsufficientFunds : public BankException {
public:
    InsufficientFunds(double balance, double requested)
        : BankException("Insufficient funds: balance " + to_string(balance) +
                        ", requested " + to_string(requested)) {}
};

class BankAccount {
    double balance;
public:
    explicit BankAccount(double b) : balance(b) {}

    void withdraw(double amount) {
        if (amount <= 0) throw InvalidAmount(amount);
        if (amount > balance) throw InsufficientFunds(balance, amount);
        balance -= amount;      // changed only after all checks pass
    }

    void transfer(BankAccount& to, double amount) {
        withdraw(amount);       // if this throws, 'to' is untouched
        to.balance += amount;
    }

    double getBalance() const { return balance; }
};

int main() {
    BankAccount a(1000), b(500);
    double tests[] = {300, -50, 0, 5000, 200};

    for (double amt : tests) {
        cout << "Withdraw " << amt << ": ";
        try {
            a.withdraw(amt);
            cout << "success, balance = " << a.getBalance() << "\n";
        } catch (const InvalidAmount& e) {
            cout << "InvalidAmount caught -> " << e.what() << "\n";
        } catch (const InsufficientFunds& e) {
            cout << "InsufficientFunds caught -> " << e.what() << "\n";
        } catch (const exception& e) {
            cout << "Other error: " << e.what() << "\n";
        }
    }

    cout << "\nTransfer 200 from A to B: ";
    try {
        a.transfer(b, 200);
        cout << "success. A=" << a.getBalance() << " B=" << b.getBalance() << "\n";
    } catch (const BankException& e) {
        cout << e.what() << "\n";
    }

    cout << "Transfer 9999 from A to B: ";
    try {
        a.transfer(b, 9999);
    } catch (const BankException& e) {
        cout << "failed (" << e.what() << ")\n";
    }
    cout << "Balances unchanged by failure. A=" << a.getBalance() << " B=" << b.getBalance() << "\n";
    return 0;
}
