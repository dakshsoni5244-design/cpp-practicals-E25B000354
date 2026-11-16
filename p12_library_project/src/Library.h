#pragma once
#include <algorithm>
#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <vector>
#include "Book.h"
#include "Exceptions.h"

class Library {
    std::map<int, std::unique_ptr<Book>> books;     // STL container, sorted by ID
public:
    void addBook(int id, const std::string& title, const std::string& author) {
        if (id <= 0) throw InvalidInput("book ID must be positive");
        if (title.empty() || author.empty()) throw InvalidInput("title and author cannot be empty");
        if (books.count(id)) throw DuplicateBook(id);
        books[id] = std::make_unique<Book>(id, title, author);
    }

    Book& find(int id) {
        auto it = books.find(id);
        if (it == books.end()) throw BookNotFound(id);
        return *it->second;
    }

    void issueBook(int id) {
        Book& b = find(id);
        if (!b.isAvailable()) throw BookUnavailable(b.getTitle());
        b.setAvailable(false);
    }

    void returnBook(int id) {
        Book& b = find(id);
        if (b.isAvailable()) throw BookNotIssued(b.getTitle());
        b.setAvailable(true);
    }

    std::vector<const Book*> search(const std::string& keyword) const {
        std::vector<const Book*> result;
        auto lower = [](std::string s) { std::transform(s.begin(), s.end(), s.begin(), ::tolower); return s; };
        std::string k = lower(keyword);
        for (const auto& [id, b] : books)
            if (lower(b->getTitle()).find(k) != std::string::npos ||
                lower(b->getAuthor()).find(k) != std::string::npos)
                result.push_back(b.get());
        return result;
    }

    void listAll() const {
        if (books.empty()) { std::cout << "  (no books)\n"; return; }
        for (const auto& [id, b] : books) b->display();
    }

    size_t count() const { return books.size(); }

    // ---- File handling ----
    void save(const std::string& file) const {
        std::ofstream out(file);
        if (!out) throw LibraryException("Cannot open '" + file + "' for writing");
        out << "id,title,author,available\n";
        for (const auto& [id, b] : books) out << b->toCsv() << "\n";
        if (!out) throw LibraryException("Write error on '" + file + "'");
    }

    // Returns number of records loaded; skips bad lines with a warning
    int load(const std::string& file) {
        std::ifstream in(file);
        if (!in) throw LibraryException("Cannot open '" + file + "' for reading");
        std::string line;
        std::getline(in, line);                     // header
        int loaded = 0, lineNo = 1;
        while (std::getline(in, line)) {
            ++lineNo;
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string id, title, author, avail;
            if (!std::getline(ss, id, ',') || !std::getline(ss, title, ',') ||
                !std::getline(ss, author, ',') || !std::getline(ss, avail)) {
                std::cerr << "  Warning: malformed line " << lineNo << " skipped\n";
                continue;
            }
            try {
                int bid = std::stoi(id);
                if (books.count(bid)) continue;
                books[bid] = std::make_unique<Book>(bid, title, author, avail == "1");
                ++loaded;
            } catch (const std::exception&) {
                std::cerr << "  Warning: bad ID on line " << lineNo << " skipped\n";
            }
        }
        return loaded;
    }
};
