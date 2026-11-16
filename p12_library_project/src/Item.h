#pragma once
#include <iostream>
#include <string>

// Abstract base class: shows encapsulation + polymorphism
class Item {
protected:
    int id;
    std::string title;
    bool available;
public:
    Item(int i, std::string t, bool a = true) : id(i), title(std::move(t)), available(a) {}
    virtual ~Item() = default;

    int getId() const { return id; }
    const std::string& getTitle() const { return title; }
    bool isAvailable() const { return available; }
    void setAvailable(bool a) { available = a; }

    virtual std::string type() const = 0;
    virtual std::string toCsv() const = 0;           // one line of the data file
    virtual void display() const = 0;
};
