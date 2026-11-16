#pragma once
#include "Item.h"

class Book : public Item {
    std::string author;
public:
    Book(int i, std::string t, std::string a, bool av = true)
        : Item(i, std::move(t), av), author(std::move(a)) {}
    const std::string& getAuthor() const { return author; }
    std::string type() const override { return "Book"; }
    std::string toCsv() const override {
        return std::to_string(id) + "," + title + "," + author + "," + (available ? "1" : "0");
    }
    void display() const override {
        std::cout << "  [" << id << "] " << title << " by " << author
                  << " - " << (available ? "Available" : "Issued") << "\n";
    }
};
