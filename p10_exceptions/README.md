# Practical 10: Custom Exceptions (Banking)

InvalidAmount and InsufficientFunds exception classes used in withdraw(). Successful and failed transactions are shown.

## Source Code (`main.cpp`)

```cpp
// Practical 10: Custom exceptions in a banking program
#include <iostream>
#include <exception>
using namespace std;

// Custom exception 1: amount is zero or negative
class InvalidAmount : public exception {
public:
    const char* what() const noexcept {
        return "Invalid amount: it must be greater than 0";
    }
};

// Custom exception 2: amount is more than the balance
class InsufficientFunds : public exception {
public:
    const char* what() const noexcept {
        return "Insufficient funds: balance is too low";
    }
};

class BankAccount {
    double balance;
public:
    BankAccount(double b) { balance = b; }

    void withdraw(double amount) {
        if (amount <= 0)
            throw InvalidAmount();
        if (amount > balance)
            throw InsufficientFunds();
        balance = balance - amount;     // changed only if no error
    }

    double getBalance() { return balance; }
};

int main() {
    BankAccount acc(1000);
    double amounts[5] = {300, -50, 0, 5000, 200};

    for (int i = 0; i < 5; i++) {
        cout << "Withdraw " << amounts[i] << " : ";
        try {
            acc.withdraw(amounts[i]);
            cout << "done, balance = " << acc.getBalance() << "\n";
        }
        catch (InvalidAmount& e) {
            cout << e.what() << "\n";
        }
        catch (InsufficientFunds& e) {
            cout << e.what() << "\n";
        }
    }
    cout << "Final balance = " << acc.getBalance() << "\n";
    return 0;
}
```

## Output

```text
Withdraw 300 : done, balance = 700
Withdraw -50 : Invalid amount: it must be greater than 0
Withdraw 0 : Invalid amount: it must be greater than 0
Withdraw 5000 : Insufficient funds: balance is too low
Withdraw 200 : done, balance = 500
Final balance = 500
```

## Notes: What each exception means

- InvalidAmount: thrown when the amount is zero or negative. InsufficientFunds: thrown when the amount is more than the balance.
- Both are derived from std::exception and give their message through what(). The balance changes only after both checks pass, so a failed withdrawal does not change it.

## Compile and run

```bash
g++ -o app main.cpp
./app
```
