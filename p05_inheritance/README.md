# Practical 05: Single and Multilevel Inheritance

Person -> Student -> GraduateStudent. Shows constructor order and reuse of base class members.

## Source Code (`main.cpp`)

```cpp
// Practical 05: Single and multilevel inheritance
// Person -> Student -> GraduateStudent
#include <iostream>
#include <string>
using namespace std;

class Person {
protected:                      // visible to derived classes, hidden from outside
    string name;
    int age;
public:
    Person(const string& n, int a) : name(n), age(a) {
        cout << "Person constructor: " << name << "\n";
    }
    void displayPerson() const {
        cout << "Name: " << name << ", Age: " << age << "\n";
    }
};

// Single inheritance: Person -> Student
class Student : public Person {
protected:
    string studentId;
    string course;
public:
    Student(const string& n, int a, const string& id, const string& c)
        : Person(n, a), studentId(id), course(c) {
        cout << "Student constructor: " << studentId << "\n";
    }
    void displayStudent() const {
        displayPerson();        // inherited from Person
        cout << "Student ID: " << studentId << ", Course: " << course << "\n";
    }
};

// Multilevel inheritance: Person -> Student -> GraduateStudent
class GraduateStudent : public Student {
    string researchTopic;
    string supervisor;
public:
    GraduateStudent(const string& n, int a, const string& id, const string& c,
                    const string& topic, const string& sup)
        : Student(n, a, id, c), researchTopic(topic), supervisor(sup) {
        cout << "GraduateStudent constructor: " << researchTopic << "\n";
    }
    void displayGraduate() const {
        displayStudent();       // inherited from Student (which inherits Person)
        cout << "Research Topic: " << researchTopic
             << ", Supervisor: " << supervisor << "\n";
    }
};

int main() {
    cout << "=== Single inheritance (Person -> Student) ===\n";
    Student s("Daksh Soni", 19, "E25B000354", "B.Tech AIDS");
    s.displayStudent();

    cout << "\n=== Multilevel inheritance (Person -> Student -> GraduateStudent) ===\n";
    GraduateStudent g("Riya Sharma", 24, "PG2024001", "M.Tech Data Science",
                      "Federated Learning", "Dr. Mehta");
    g.displayGraduate();

    cout << "\nInherited members available to GraduateStudent: ";
    cout << "displayPerson() and displayStudent()\n";
    g.displayPerson();
    return 0;
}
```

## Output

```text
=== Single inheritance (Person -> Student) ===
Person constructor: Daksh Soni
Student constructor: E25B000354
Name: Daksh Soni, Age: 19
Student ID: E25B000354, Course: B.Tech AIDS

=== Multilevel inheritance (Person -> Student -> GraduateStudent) ===
Person constructor: Riya Sharma
Student constructor: PG2024001
GraduateStudent constructor: Federated Learning
Name: Riya Sharma, Age: 24
Student ID: PG2024001, Course: M.Tech Data Science
Research Topic: Federated Learning, Supervisor: Dr. Mehta

Inherited members available to GraduateStudent: displayPerson() and displayStudent()
Name: Riya Sharma, Age: 24
```

## Compile and run

```bash
g++ -o app main.cpp
./app
```
