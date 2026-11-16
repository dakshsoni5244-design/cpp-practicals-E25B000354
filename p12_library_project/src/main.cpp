// Practical 12: Library Management System (console application)
// Usage:  ./library          -> interactive menu
//         ./library --demo   -> scripted demo with normal and error cases
#include <iostream>
#include <limits>
#include <string>
#include "Library.h"
using namespace std;

static const string DATA_FILE = "data/books.csv";

static int readInt(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    try {
        size_t pos;
        int v = stoi(s, &pos);
        if (pos != s.size()) throw InvalidInput("'" + s + "' is not a number");
        return v;
    } catch (const invalid_argument&) {
        throw InvalidInput("'" + s + "' is not a number");
    } catch (const out_of_range&) {
        throw InvalidInput("number out of range");
    }
}

static string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}


static void demo(Library& lib) {
    auto attempt = [&](const string& label, auto action) {
        cout << label << "\n";
        try { action(); cout << "  OK\n"; }
        catch (const LibraryException& e) { cout << "  Error: " << e.what() << "\n"; }
    };
    cout << "=== All books ===\n"; lib.listAll();
    attempt("Add book 106 'Operating Systems' by Silberschatz", [&] { lib.addBook(106, "Operating Systems", "Silberschatz"); });
    attempt("Add duplicate book ID 101",                          [&] { lib.addBook(101, "Duplicate", "Nobody"); });
    attempt("Add book with empty title",                          [&] { lib.addBook(107, "", "Someone"); });
    attempt("Issue book 102",                                     [&] { lib.issueBook(102); });
    attempt("Issue book 102 again (already issued)",              [&] { lib.issueBook(102); });
    attempt("Issue book 999 (unknown ID)",                        [&] { lib.issueBook(999); });
    attempt("Return book 103 (never issued)",                     [&] { lib.returnBook(103); });
    attempt("Return book 102",                                    [&] { lib.returnBook(102); });
    attempt("Issue book 104",                                     [&] { lib.issueBook(104); });
    cout << "Search 'data':\n";
    for (const Book* b : lib.search("data")) b->display();
    cout << "=== Final list ===\n"; lib.listAll();
    lib.save(DATA_FILE);
    cout << "Saved " << lib.count() << " books to " << DATA_FILE << "\n";
}

int main(int argc, char* argv[]) {
    Library lib;
    try {
        int n = lib.load(DATA_FILE);
        cout << "Loaded " << n << " books from " << DATA_FILE << "\n";
    } catch (const LibraryException& e) {
        cout << e.what() << " - starting with an empty library\n";
    }

    if (argc > 1 && string(argv[1]) == "--demo") { demo(lib); return 0; }

    int choice = -1;
    while (choice != 0) {
        cout << "\n===== LIBRARY MENU =====\n"
                "1. Add book\n2. List books\n3. Search\n4. Issue book\n5. Return book\n0. Save & exit\n";
        try {
            choice = readInt("Choice: ");
            switch (choice) {
                case 1: { int id = readInt("ID: "); string t = readLine("Title: "), a = readLine("Author: ");
                          lib.addBook(id, t, a); cout << "Book added\n"; break; }
                case 2: lib.listAll(); break;
                case 3: { for (const Book* b : lib.search(readLine("Keyword: "))) b->display(); break; }
                case 4: lib.issueBook(readInt("Book ID: ")); cout << "Book issued\n"; break;
                case 5: lib.returnBook(readInt("Book ID: ")); cout << "Book returned\n"; break;
                case 0: lib.save(DATA_FILE); cout << "Saved. Goodbye!\n"; break;
                default: cout << "Unknown option\n";
            }
        } catch (const LibraryException& e) {
            cout << "  Error: " << e.what() << "\n";
        }
        if (!cin) break;
    }
    return 0;
}
