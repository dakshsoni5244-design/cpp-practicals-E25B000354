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
