# Practical 04: RAII and Smart Pointers

Raw pointer vs unique_ptr vs shared_ptr. Shows ownership, use_count() and automatic deletion. Checked with Valgrind (no leaks).

## Source Code (`main.cpp`)

```cpp
// Practical 04: RAII and smart pointers
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Resource {
public:
    string name;
    Resource(string n) {
        name = n;
        cout << name << " created\n";
    }
    ~Resource() {
        cout << name << " deleted\n";
    }
    void use() {
        cout << "using " << name << "\n";
    }
};

int main() {
    // 1. Raw pointer: we must call delete ourselves
    cout << "--- raw pointer ---\n";
    Resource* r = new Resource("raw");
    r->use();
    delete r;

    // 2. unique_ptr: only ONE owner, deleted automatically
    cout << "\n--- unique_ptr ---\n";
    unique_ptr<Resource> u(new Resource("unique"));
    u->use();
    unique_ptr<Resource> u2 = move(u);   // ownership moves to u2
    if (u == nullptr)
        cout << "u is empty now, u2 is the owner\n";
    u2->use();

    // 3. shared_ptr: many owners, deleted when the last owner is gone
    cout << "\n--- shared_ptr ---\n";
    shared_ptr<Resource> s1 = make_shared<Resource>("shared");
    cout << "owners = " << s1.use_count() << "\n";
    {
        shared_ptr<Resource> s2 = s1;    // second owner
        cout << "owners = " << s1.use_count() << "\n";
    }                                    // s2 goes out of scope here
    cout << "owners = " << s1.use_count() << "\n";

    // 4. Many iterations without any delete
    cout << "\n--- 1000 iterations with unique_ptr ---\n";
    for (int i = 0; i < 1000; i++) {
        unique_ptr<int> p(new int(i));
    }
    cout << "done, no leak\n";

    cout << "\n--- end of main ---\n";
    return 0;
}
```

## Output

```text
--- raw pointer ---
raw created
using raw
raw deleted

--- unique_ptr ---
unique created
using unique
u is empty now, u2 is the owner
using unique

--- shared_ptr ---
shared created
owners = 1
owners = 2
owners = 1

--- 1000 iterations with unique_ptr ---
done, no leak

--- end of main ---
shared deleted
unique deleted
```

## Valgrind output (memory check)

```text
Memcheck, a memory error detector
Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
Command: ./app


HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: 1,005 allocs, 1,005 frees, 81,936 bytes allocated

All heap blocks were freed -- no leaks are possible

For lists of detected and suppressed errors, rerun with: -s
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Notes: Raw pointer vs unique_ptr vs shared_ptr

- Raw pointer: we must call delete ourselves; it leaks if we forget.
- unique_ptr: exactly one owner, cannot be copied (only moved), freed automatically at the end of its scope.
- shared_ptr: many owners, counted with use_count() (1, then 2, then 1 in the output); freed when the last owner goes away.
- Memory check: Valgrind (--leak-check=full) shows 1005 allocations, 1005 frees, 0 errors, including the loop of 1000 iterations without any delete.

## Compile and run

```bash
g++ -o app main.cpp
./app
```
