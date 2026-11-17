# Practical 01: C++ Fundamentals

Uses data types, constants, variables, arithmetic/relational/logical operators and cin/cout to find the total, percentage and grade of a student. Marks are checked, so wrong input shows an error.

## Source Code (`main.cpp`)

```cpp
// Practical 01: C++ fundamentals - data types, constants, variables,
// operators and input/output.
#include <iostream>
#include <string>
using namespace std;

int main() {
    const double PASS_PERCENT = 40.0;   // constant: minimum percentage to pass
    const int TOTAL_SUBJECTS = 3;       // constant: number of subjects

    string name;                        // string  - text
    int roll;                           // int     - whole number
    double m1, m2, m3;                  // double  - decimal numbers
    char grade;                         // char    - single character

    cout << "Enter student name: ";
    getline(cin, name);
    cout << "Enter roll number: ";
    cin >> roll;
    cout << "Enter marks of " << TOTAL_SUBJECTS << " subjects (out of 100): ";
    cin >> m1 >> m2 >> m3;

    // Check the input: numbers only, marks between 0 and 100
    if (!cin || m1 < 0 || m1 > 100 || m2 < 0 || m2 > 100 || m3 < 0 || m3 > 100) {
        cout << "\nError: invalid input. Roll number and marks must be numbers, "
                "and marks must be between 0 and 100.\n";
        return 1;
    }

    // Arithmetic operators
    double total = m1 + m2 + m3;
    double percentage = total / TOTAL_SUBJECTS;   // each subject is out of 100
    int wholeTotal = static_cast<int>(total);
    int remainder = wholeTotal % 10;              // modulus operator

    // Relational + logical operators
    bool passedAll = (m1 >= PASS_PERCENT) && (m2 >= PASS_PERCENT) && (m3 >= PASS_PERCENT);
    bool distinction = percentage >= 75.0;
    bool passed = passedAll && !(percentage < PASS_PERCENT);

    if (percentage >= 75)      grade = 'A';
    else if (percentage >= 60) grade = 'B';
    else if (percentage >= 40) grade = 'C';
    else                       grade = 'F';

    cout << "\n----- Result -----\n";
    cout << "Name        : " << name << "\n";
    cout << "Roll number : " << roll << "\n";
    cout << "Total       : " << total << " / " << TOTAL_SUBJECTS * 100 << "\n";
    cout << "Percentage  : " << percentage << "%\n";
    cout << "Total % 10  : " << remainder << "\n";
    cout << "Grade       : " << grade << "\n";
    cout << "Distinction : " << (distinction ? "Yes" : "No") << "\n";
    cout << "Status      : " << (passed ? "PASS" : "FAIL") << "\n";
    return 0;
}
```

## Output

```text
Enter student name: Daksh Soni
Enter roll number: 354
Enter marks of 3 subjects (out of 100): 78 65 82

----- Result -----
Name        : Daksh Soni
Roll number : 354
Total       : 225 / 300
Percentage  : 75%
Total % 10  : 5
Grade       : A
Distinction : Yes
Status      : PASS
```

## Output with invalid input

```text
Enter student name: Daksh Soni
Enter roll number: 354
Enter marks of 3 subjects (out of 100): 78 abc 82

Error: invalid input. Roll number and marks must be numbers, and marks must be between 0 and 100.
```

## Notes: data types and operators

- string, int, double and char store the name, roll number, marks and grade. const values (PASS_PERCENT, TOTAL_SUBJECTS) cannot be changed.
- Arithmetic: +, / and %. Relational: >=, <. Logical: &&, !. The input is checked, so letters or marks outside 0-100 give an error message.

## Compile and run

```bash
g++ -o app main.cpp
./app < input_valid.txt
```
