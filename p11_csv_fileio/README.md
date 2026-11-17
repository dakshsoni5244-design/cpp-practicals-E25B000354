# Practical 11: CSV File Handling

Writes and reads student records in students.csv using fstream, handles a malformed line, and shows tellg/seekg/tellp/seekp on demo.txt.

## Source Code (`main.cpp`)

```cpp
// Practical 11: CSV student records using fstream, plus seekg/seekp/tellg/tellp
// CSV format: id,name,marks   (first line is a header)
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Student {
    int id;
    string name;
    double marks;
};

bool writeCsv(const string& file, const vector<Student>& list) {
    ofstream out(file);
    if (!out.is_open()) { cerr << "Cannot open " << file << " for writing\n"; return false; }
    out << "id,name,marks\n";
    for (const auto& s : list) out << s.id << ',' << s.name << ',' << s.marks << '\n';
    if (!out) { cerr << "Write failed\n"; return false; }
    return true;
}

vector<Student> readCsv(const string& file) {
    vector<Student> list;
    ifstream in(file);
    if (!in.is_open()) { cerr << "Cannot open " << file << " for reading\n"; return list; }
    string line;
    getline(in, line);                  // skip header
    int lineNo = 1;
    while (getline(in, line)) {
        ++lineNo;
        if (line.empty()) continue;
        stringstream ss(line);
        string idS, name, marksS;
        if (!getline(ss, idS, ',') || !getline(ss, name, ',') || !getline(ss, marksS)) {
            cerr << "Malformed line " << lineNo << ": " << line << "\n";
            continue;
        }
        try {
            list.push_back({stoi(idS), name, stod(marksS)});
        } catch (const exception&) {
            cerr << "Bad number on line " << lineNo << ": " << line << "\n";
        }
    }
    return list;
}

void positionDemo() {
    cout << "\n=== File position functions (separate demo file: demo.txt) ===\n";
    {   // create a simple file with fstream
        ofstream out("demo.txt");
        out << "ABCDEFGHIJ";
        cout << "tellp() after writing 10 chars : " << out.tellp() << "\n";
        out.seekp(3);                   // move PUT position to index 3
        cout << "tellp() after seekp(3)         : " << out.tellp() << "\n";
        out << "xyz";                   // overwrite D,E,F
        cout << "tellp() after writing 'xyz'    : " << out.tellp() << "\n";
    }
    ifstream in("demo.txt");
    cout << "tellg() at start                : " << in.tellg() << "\n";
    char c;
    in.get(c);
    cout << "read '" << c << "', tellg() now        : " << in.tellg() << "\n";
    in.seekg(5);                        // move GET position to index 5
    cout << "tellg() after seekg(5)         : " << in.tellg() << "\n";
    in.get(c);
    cout << "char at index 5                : '" << c << "'\n";
    in.seekg(-2, ios::end);             // 2 bytes before end
    in.get(c);
    cout << "char at end-2                  : '" << c << "'\n";
    in.seekg(0);
    string whole;
    getline(in, whole);
    cout << "whole file now                 : " << whole << "\n";
}

int main() {
    vector<Student> students = {
        {101, "Daksh Soni", 88.5},
        {102, "Aman Verma", 76.0},
        {103, "Neha Patel", 91.25},
    };

    if (!writeCsv("students.csv", students)) return 1;
    cout << "Wrote " << students.size() << " records to students.csv\n\n";

    // Append one more record using append mode
    {
        ofstream app("students.csv", ios::app);
        app << 104 << ',' << "Karan Singh" << ',' << 67.5 << '\n';
    }
    // Add a malformed line to show error handling
    {
        ofstream app("students.csv", ios::app);
        app << "bad_line_without_commas\n";
    }

    cout << "Records read back:\n";
    cout << "ID    Name            Marks\n";
    for (const auto& s : readCsv("students.csv"))
        cout << s.id << "   " << s.name << string(16 - s.name.size(), ' ') << s.marks << "\n";

    positionDemo();
    return 0;
}
```

## Output

```text
Wrote 3 records to students.csv

Records read back:
ID    Name            Marks
Malformed line 6: bad_line_without_commas
101   Daksh Soni      88.5
102   Aman Verma      76
103   Neha Patel      91.25
104   Karan Singh     67.5

=== File position functions (separate demo file: demo.txt) ===
tellp() after writing 10 chars : 10
tellp() after seekp(3)         : 3
tellp() after writing 'xyz'    : 6
tellg() at start                : 0
read 'A', tellg() now        : 1
tellg() after seekg(5)         : 5
char at index 5                : 'z'
char at end-2                  : 'I'
whole file now                 : ABCxyzGHIJ
```

## Notes: Get and put positions

- Input (get) position: where the next read happens (tellg, seekg). Output (put) position: where the next write happens (tellp, seekp).
- In the demo, seekp(3) then writing xyz changed ABCDEFGHIJ to ABCxyzGHIJ. seekg(5) moved the read position to the character z, and seekg(-2, ios::end) moved to the second-last character, I.
- CSV format: first line id,name,marks, then one student per line. A malformed line (line 6) is reported and skipped.

## Compile and run

```bash
g++ -o app main.cpp
./app
```
