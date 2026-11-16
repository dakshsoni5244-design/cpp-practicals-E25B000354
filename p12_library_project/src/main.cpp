// Practical 12: Library Management System (simple console project)
// Run:  ./library          -> menu
//       ./library --demo   -> demo with normal and error cases
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <exception>
using namespace std;

// ---------- Exception class ----------
class LibraryError : public exception {
    string message;
public:
    LibraryError(string m) { message = m; }
    const char* what() const noexcept { return message.c_str(); }
};

// ---------- Base class ----------
class Item {
protected:
    int id;
    string title;
public:
    Item(int i, string t) { id = i; title = t; }
    int getId() { return id; }
    string getTitle() { return title; }
    virtual void display() = 0;        // pure virtual -> Item is abstract
    virtual ~Item() {}
};

// ---------- Derived class ----------
class Book : public Item {
    string author;
    bool available;
public:
    Book(int i, string t, string a, bool av = true) : Item(i, t) {
        author = a;
        available = av;
    }
    string getAuthor() { return author; }
    bool isAvailable() { return available; }
    void setAvailable(bool v) { available = v; }

    void display() {
        cout << id << " | " << title << " | " << author << " | "
             << (available ? "Available" : "Issued") << "\n";
    }
};

// ---------- Library class ----------
class Library {
    vector<Book> books;                // STL container

    int findIndex(int id) {
        for (int i = 0; i < (int)books.size(); i++)
            if (books[i].getId() == id) return i;
        throw LibraryError("Book ID " + to_string(id) + " not found");
    }
public:
    void addBook(int id, string title, string author) {
        if (id <= 0 || title == "" || author == "")
            throw LibraryError("ID must be positive and title/author cannot be empty");
        for (int i = 0; i < (int)books.size(); i++)
            if (books[i].getId() == id)
                throw LibraryError("Book ID " + to_string(id) + " already exists");
        books.push_back(Book(id, title, author));
    }

    void issueBook(int id) {
        int i = findIndex(id);
        if (!books[i].isAvailable())
            throw LibraryError("'" + books[i].getTitle() + "' is already issued");
        books[i].setAvailable(false);
    }

    void returnBook(int id) {
        int i = findIndex(id);
        if (books[i].isAvailable())
            throw LibraryError("'" + books[i].getTitle() + "' was not issued");
        books[i].setAvailable(true);
    }

    void search(string word) {
        bool found = false;
        for (int i = 0; i < (int)books.size(); i++) {
            if (books[i].getTitle().find(word) != string::npos ||
                books[i].getAuthor().find(word) != string::npos) {
                books[i].display();
                found = true;
            }
        }
        if (!found) cout << "No book found\n";
    }

    void listAll() {
        for (int i = 0; i < (int)books.size(); i++)
            books[i].display();
    }

    // Save all books to a CSV file
    void save(string file) {
        ofstream out(file);
        if (!out) throw LibraryError("Cannot open file " + file);
        out << "id,title,author,available\n";
        for (int i = 0; i < (int)books.size(); i++)
            out << books[i].getId() << "," << books[i].getTitle() << ","
                << books[i].getAuthor() << "," << books[i].isAvailable() << "\n";
    }

    // Load books from a CSV file
    void load(string file) {
        ifstream in(file);
        if (!in) throw LibraryError("Cannot open file " + file);
        string line;
        getline(in, line);                       // skip header line
        while (getline(in, line)) {
            stringstream ss(line);
            string id, title, author, av;
            getline(ss, id, ',');
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, av, ',');
            if (id == "" || title == "" || author == "" || av == "") continue; // bad line
            books.push_back(Book(stoi(id), title, author, av == "1"));
        }
    }
};

// ---------- Helper for the demo ----------
void tryIt(string text, Library& lib, int action, int id) {
    cout << text << " -> ";
    try {
        if (action == 1) lib.issueBook(id);
        if (action == 2) lib.returnBook(id);
        cout << "OK\n";
    } catch (exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

int main(int argc, char* argv[]) {
    Library lib;
    string file = "data/books.csv";

    try {
        lib.load(file);
    } catch (exception& e) {
        cout << e.what() << " (starting with empty library)\n";
    }

    if (argc > 1 && string(argv[1]) == "--demo") {
        cout << "=== All books ===\n";
        lib.listAll();
        cout << "\n";
        try { lib.addBook(106, "Operating Systems", "Silberschatz"); cout << "Add book 106 -> OK\n"; }
        catch (exception& e) { cout << "Error: " << e.what() << "\n"; }
        try { lib.addBook(101, "Duplicate", "Nobody"); }
        catch (exception& e) { cout << "Add book 101 again -> Error: " << e.what() << "\n"; }
        try { lib.addBook(107, "", "Someone"); }
        catch (exception& e) { cout << "Add book with empty title -> Error: " << e.what() << "\n"; }
        tryIt("Issue book 102", lib, 1, 102);
        tryIt("Issue book 102 again", lib, 1, 102);
        tryIt("Issue book 999", lib, 1, 999);
        tryIt("Return book 103 (not issued)", lib, 2, 103);
        tryIt("Return book 102", lib, 2, 102);
        tryIt("Issue book 104", lib, 1, 104);
        cout << "\nSearch for 'Data':\n";
        lib.search("Data");
        cout << "\n=== All books now ===\n";
        lib.listAll();
        lib.save(file);
        cout << "\nSaved to " << file << "\n";
        return 0;
    }

    int choice = -1;
    while (choice != 0) {
        cout << "\n1. Add book\n2. List books\n3. Search\n4. Issue book\n5. Return book\n0. Save and exit\n";
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
                int id; string title, author;
                cout << "ID: "; cin >> id; cin.ignore(1000, '\n');
                cout << "Title: "; getline(cin, title);
                cout << "Author: "; getline(cin, author);
                lib.addBook(id, title, author);
                cout << "Book added\n";
            } else if (choice == 2) {
                lib.listAll();
            } else if (choice == 3) {
                string word;
                cout << "Search word: "; getline(cin, word);
                lib.search(word);
            } else if (choice == 4) {
                int id; cout << "Book ID: "; cin >> id;
                lib.issueBook(id);
                cout << "Book issued\n";
            } else if (choice == 5) {
                int id; cout << "Book ID: "; cin >> id;
                lib.returnBook(id);
                cout << "Book returned\n";
            } else if (choice == 0) {
                lib.save(file);
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
