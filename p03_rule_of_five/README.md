# Practical 03: Constructors and Rule of Five

IntArray class with default, parameterized, copy and move constructors, copy/move assignment and destructor. Checked with Valgrind (no leaks).

## Source Code (`main.cpp`)

```cpp
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
```

## Output

```text
== Default and parameterized ==
[default ctor]
[parameterized ctor] size=4
b (size 4): 7 7 7 7 

== Copy constructor (deep copy) ==
[copy ctor] size=4
b (size 4): 7 7 7 7 
c (size 4): 99 7 7 7 

== Copy assignment ==
[copy assignment]
a (size 4): 7 7 7 7 

== Move constructor ==
[move ctor] size=4
d (size 4): 99 7 7 7 
c (moved-from) (size 0): 

== Move assignment ==
[parameterized ctor] size=2
[move assignment]
e (size 4): 99 7 7 7 
d (moved-from) (size 0): 

== End of main, destructors run ==
[destructor] size=4
[destructor] size=0
[destructor] size=0
[destructor] size=4
[destructor] size=4
```

## Valgrind output (memory check)

```text
Memcheck, a memory error detector
Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
Command: ./app


HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: 6 allocs, 6 frees, 77,880 bytes allocated

All heap blocks were freed -- no leaks are possible

For lists of detected and suppressed errors, rerun with: -s
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Notes: The five special members

- Destructor: frees the owned array with delete[].
- Copy constructor: makes a deep copy (new memory). Changing c[0] did not change b, so the memory is not shared.
- Copy assignment: copies into new memory, frees the old memory, and is safe for self-assignment.
- Move constructor and move assignment: take the pointer from the other object and leave it empty (size 0), so nothing is copied.
- Valgrind: 6 allocations, 6 frees, no leaks, 0 errors.

## Compile and run

```bash
g++ -o app main.cpp
./app
```
