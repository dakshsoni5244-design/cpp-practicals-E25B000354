// Mini Project: Student Portal (simple console application)
// Run:  ./portal          -> menu
//       ./portal --demo   -> demo with normal and error cases
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <exception>
using namespace std;

// ---------- Exception class ----------
class PortalError : public exception {
    string message;
public:
    PortalError(string m) { message = m; }
    const char* what() const noexcept { return message.c_str(); }
};

// ---------- Base class ----------
class Person {
protected:
    string name;
public:
    Person(string n) { name = n; }
    string getName() { return name; }
    virtual void display() = 0;        // pure virtual -> Person is abstract
    virtual ~Person() {}
};

// ---------- Derived class ----------
class Student : public Person {
    int id;
    string course;
    double marks;
public:
    Student(int i, string n, string c, double m) : Person(n) {
        id = i;
        course = c;
        marks = m;
    }
    int getId() { return id; }
    string getCourse() { return course; }
    double getMarks() { return marks; }
    void setMarks(double m) { marks = m; }

    // Simple result: grade and pass/fail from the marks
    char getGrade() {
        if (marks >= 75) return 'A';
        if (marks >= 60) return 'B';
        if (marks >= 40) return 'C';
        return 'F';
    }
    string getResult() { return marks >= 40 ? "PASS" : "FAIL"; }

    void display() {
        cout << id << " | " << name << " | " << course << " | "
             << marks << " | Grade " << getGrade() << " | " << getResult() << "\n";
    }
};

// ---------- Portal class ----------
class Portal {
    vector<Student> students;          // STL container

    int findIndex(int id) {
        for (int i = 0; i < (int)students.size(); i++)
            if (students[i].getId() == id) return i;
        throw PortalError("Student ID " + to_string(id) + " not found");
    }
public:
    // Validate ID and marks before adding
    void addStudent(int id, string name, string course, double marks) {
        if (id <= 0)
            throw PortalError("ID must be a positive number");
        if (name == "" || course == "")
            throw PortalError("Name and course cannot be empty");
        if (marks < 0 || marks > 100)
            throw PortalError("Marks must be between 0 and 100");
        for (int i = 0; i < (int)students.size(); i++)
            if (students[i].getId() == id)
                throw PortalError("Student ID " + to_string(id) + " already exists");
        students.push_back(Student(id, name, course, marks));
    }

    void updateMarks(int id, double marks) {
        if (marks < 0 || marks > 100)
            throw PortalError("Marks must be between 0 and 100");
        students[findIndex(id)].setMarks(marks);
    }

    void showStudent(int id) {
        students[findIndex(id)].display();
    }

    void searchByName(string word) {
        bool found = false;
        for (int i = 0; i < (int)students.size(); i++) {
            if (students[i].getName().find(word) != string::npos) {
                students[i].display();
                found = true;
            }
        }
        if (!found) cout << "No student found\n";
    }

    void listAll() {
        for (int i = 0; i < (int)students.size(); i++)
            students[i].display();
    }

    void showSummary() {
        if (students.size() == 0) { cout << "No students\n"; return; }
        double total = 0; int passed = 0;
        for (int i = 0; i < (int)students.size(); i++) {
            total += students[i].getMarks();
            if (students[i].getMarks() >= 40) passed++;
        }
        cout << "Students: " << students.size() << ", Average marks: "
             << total / students.size() << ", Passed: " << passed << "\n";
    }

    // Save all students to a CSV file
    void save(string file) {
        ofstream out(file);
        if (!out) throw PortalError("Cannot open file " + file);
        out << "id,name,course,marks\n";
        for (int i = 0; i < (int)students.size(); i++)
            out << students[i].getId() << "," << students[i].getName() << ","
                << students[i].getCourse() << "," << students[i].getMarks() << "\n";
    }

    // Load students from a CSV file (bad lines are skipped)
    void load(string file) {
        ifstream in(file);
        if (!in) throw PortalError("Cannot open file " + file);
        string line;
        getline(in, line);                       // skip header line
        while (getline(in, line)) {
            stringstream ss(line);
            string id, name, course, marks;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, course, ',');
            getline(ss, marks, ',');
            if (id == "" || name == "" || course == "" || marks == "") continue;
            try {
                addStudent(stoi(id), name, course, stod(marks));
            } catch (exception& e) {
                cout << "Skipped bad line: " << line << "\n";
            }
        }
    }
};

// ---------- Helper for the demo ----------
void tryAdd(Portal& p, int id, string name, string course, double marks, string text) {
    cout << text << " -> ";
    try { p.addStudent(id, name, course, marks); cout << "OK\n"; }
    catch (exception& e) { cout << "Error: " << e.what() << "\n"; }
}

int main(int argc, char* argv[]) {
    Portal portal;
    string file = "data/students.csv";

    try {
        portal.load(file);
    } catch (exception& e) {
        cout << e.what() << " (starting with empty portal)\n";
    }

    if (argc > 1 && string(argv[1]) == "--demo") {
        cout << "=== All students ===\n";
        portal.listAll();
        cout << "\n";
        tryAdd(portal, 106, "Meera Joshi", "B.Tech AIDS", 82, "Add student 106");
        tryAdd(portal, 101, "Duplicate", "B.Tech AIDS", 50, "Add student 101 again");
        tryAdd(portal, 107, "Rohan Das", "B.Tech AIDS", 150, "Add student with marks 150");
        tryAdd(portal, 0, "Zero Id", "B.Tech AIDS", 50, "Add student with ID 0");
        tryAdd(portal, 108, "", "B.Tech AIDS", 50, "Add student with empty name");
        cout << "Update marks of 104 to 55 -> ";
        try { portal.updateMarks(104, 55); cout << "OK\n"; }
        catch (exception& e) { cout << "Error: " << e.what() << "\n"; }
        cout << "Update marks of 999 -> ";
        try { portal.updateMarks(999, 55); cout << "OK\n"; }
        catch (exception& e) { cout << "Error: " << e.what() << "\n"; }
        cout << "\nSearch for 'Soni':\n";
        portal.searchByName("Soni");
        cout << "\n=== All students now ===\n";
        portal.listAll();
        cout << "\n";
        portal.showSummary();
        portal.save(file);
        cout << "Saved to " << file << "\n";
        return 0;
    }

    int choice = -1;
    while (choice != 0) {
        cout << "\n1. Add student\n2. List students\n3. Search by name\n4. Show result of one student\n"
                "5. Update marks\n6. Summary\n0. Save and exit\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {                 // wrong input like letters
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a number\n";
            choice = -1;
            continue;
        }
        cin.ignore(1000, '\n');
        try {
            if (choice == 1) {
                int id; string name, course; double marks;
                cout << "ID: "; cin >> id; cin.ignore(1000, '\n');
                cout << "Name: "; getline(cin, name);
                cout << "Course: "; getline(cin, course);
                cout << "Marks: "; cin >> marks;
                if (!cin) { cin.clear(); cin.ignore(1000, '\n'); throw PortalError("Marks must be a number"); }
                portal.addStudent(id, name, course, marks);
                cout << "Student added\n";
            } else if (choice == 2) {
                portal.listAll();
            } else if (choice == 3) {
                string word;
                cout << "Search word: "; getline(cin, word);
                portal.searchByName(word);
            } else if (choice == 4) {
                int id; cout << "Student ID: "; cin >> id;
                portal.showStudent(id);
            } else if (choice == 5) {
                int id; double marks;
                cout << "Student ID: "; cin >> id;
                cout << "New marks: "; cin >> marks;
                portal.updateMarks(id, marks);
                cout << "Marks updated\n";
            } else if (choice == 6) {
                portal.showSummary();
            } else if (choice == 0) {
                portal.save(file);
                cout << "Saved. Bye!\n";
            } else {
                cout << "Invalid choice\n";
            }
        } catch (exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}
