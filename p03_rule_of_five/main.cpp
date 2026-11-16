// Practical 03: Constructors and the Rule of Five
// IntArray owns a dynamically allocated int array.
#include <iostream>
#include <utility>
using namespace std;

class IntArray {
private:
    int* data;
    size_t size;

public:
    // Default constructor: empty array, no memory owned
    IntArray() : data(nullptr), size(0) {
        cout << "[default ctor]\n";
    }

    // Parameterized constructor: allocates n elements, all set to 'value'
    IntArray(size_t n, int value) : data(new int[n]), size(n) {
        for (size_t i = 0; i < n; ++i) data[i] = value;
        cout << "[parameterized ctor] size=" << size << "\n";
    }

    // 1) Destructor: releases the owned memory
    ~IntArray() {
        cout << "[destructor] size=" << size << "\n";
        delete[] data;
    }

    // 2) Copy constructor: DEEP copy, new object gets its own memory
    IntArray(const IntArray& other) : data(new int[other.size]), size(other.size) {
        for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
        cout << "[copy ctor] size=" << size << "\n";
    }

    // 3) Copy assignment: free old memory, then deep copy (self-assignment safe)
    IntArray& operator=(const IntArray& other) {
        cout << "[copy assignment]\n";
        if (this != &other) {
            int* newData = new int[other.size];
            for (size_t i = 0; i < other.size; ++i) newData[i] = other.data[i];
            delete[] data;
            data = newData;
            size = other.size;
        }
        return *this;
    }

    // 4) Move constructor: steal the pointer, leave source empty
    IntArray(IntArray&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "[move ctor] size=" << size << "\n";
    }

    // 5) Move assignment: release own memory, then steal from source
    IntArray& operator=(IntArray&& other) noexcept {
        cout << "[move assignment]\n";
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    void set(size_t i, int v) { if (i < size) data[i] = v; }

    void print(const char* label) const {
        cout << label << " (size " << size << "): ";
        for (size_t i = 0; i < size; ++i) cout << data[i] << ' ';
        cout << "\n";
    }
};

int main() {
    cout << "== Default and parameterized ==\n";
    IntArray a;                  // default
    IntArray b(4, 7);            // parameterized
    b.print("b");

    cout << "\n== Copy constructor (deep copy) ==\n";
    IntArray c(b);
    c.set(0, 99);                // changing c must not change b
    b.print("b");
    c.print("c");

    cout << "\n== Copy assignment ==\n";
    a = b;
    a.print("a");

    cout << "\n== Move constructor ==\n";
    IntArray d(std::move(c));
    d.print("d");
    c.print("c (moved-from)");

    cout << "\n== Move assignment ==\n";
    IntArray e(2, 1);
    e = std::move(d);
    e.print("e");
    d.print("d (moved-from)");

    cout << "\n== End of main, destructors run ==\n";
    return 0;
}
