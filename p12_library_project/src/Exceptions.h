#pragma once
#include <stdexcept>
#include <string>

// Base class for every library-related error
class LibraryException : public std::runtime_error {
public:
    explicit LibraryException(const std::string& m) : std::runtime_error(m) {}
};
class BookNotFound : public LibraryException {
public:
    explicit BookNotFound(int id) : LibraryException("Book ID " + std::to_string(id) + " not found") {}
};
class BookUnavailable : public LibraryException {
public:
    explicit BookUnavailable(const std::string& t) : LibraryException("'" + t + "' is already issued") {}
};
class BookNotIssued : public LibraryException {
public:
    explicit BookNotIssued(const std::string& t) : LibraryException("'" + t + "' was not issued") {}
};
class DuplicateBook : public LibraryException {
public:
    explicit DuplicateBook(int id) : LibraryException("Book ID " + std::to_string(id) + " already exists") {}
};
class InvalidInput : public LibraryException {
public:
    explicit InvalidInput(const std::string& m) : LibraryException("Invalid input: " + m) {}
};
