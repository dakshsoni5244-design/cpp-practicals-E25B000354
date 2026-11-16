// Practical 04: RAII and smart pointers (unique_ptr and shared_ptr)
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Resource {
    string name;
public:
    explicit Resource(string n) : name(move(n)) { cout << "  Resource '" << name << "' acquired\n"; }
    ~Resource() { cout << "  Resource '" << name << "' released\n"; }
    void use() const { cout << "  Using '" << name << "'\n"; }
};

// Raw pointer version: the programmer must remember to delete.
void rawPointerDemo() {
    cout << "[raw pointer]\n";
    Resource* r = new Resource("raw");
    r->use();
    delete r;               // forgetting this line would leak; an exception before it would too
}

// unique_ptr: exactly ONE owner. Freed automatically at end of scope.
void uniquePtrDemo() {
    cout << "[unique_ptr]\n";
    unique_ptr<Resource> u = make_unique<Resource>("unique");
    u->use();
    // unique_ptr<Resource> copy = u;          // ERROR: cannot copy
    unique_ptr<Resource> moved = move(u);      // ownership transferred
    cout << "  original is " << (u ? "non-null" : "null") << " after move\n";
    moved->use();
}   // 'moved' goes out of scope, resource released here

// shared_ptr: several owners, freed when the LAST owner goes away.
class Document {
    shared_ptr<Resource> font;   // font is shared between documents
public:
    explicit Document(shared_ptr<Resource> f) : font(move(f)) {}
    void print() const { font->use(); }
};

void sharedPtrDemo() {
    cout << "[shared_ptr]\n";
    auto font = make_shared<Resource>("shared-font");
    cout << "  use_count after creation: " << font.use_count() << "\n";
    {
        Document d1(font);
        Document d2(font);
        cout << "  use_count with two documents: " << font.use_count() << "\n";
        d1.print();
        d2.print();
    }   // documents destroyed, count goes down
    cout << "  use_count after documents destroyed: " << font.use_count() << "\n";
}

int main() {
    rawPointerDemo();
    uniquePtrDemo();
    sharedPtrDemo();

    // Stress test: many iterations, no manual delete, no leak.
    cout << "[stress test]\n";
    auto start = chrono::steady_clock::now();
    long long sum = 0;
    for (int i = 0; i < 100000; ++i) {
        unique_ptr<int[]> arr = make_unique<int[]>(100);
        arr[0] = i;
        sum += arr[0];
    }
    auto end = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "  100000 allocations done, checksum=" << sum << ", time=" << ms << " ms\n";
    return 0;
}
