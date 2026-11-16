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
