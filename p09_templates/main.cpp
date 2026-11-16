// Practical 09: Generic Stack using class templates
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

template <typename T>
class Stack {
    vector<T> items;            // STL container used internally
public:
    void push(const T& value) { items.push_back(value); }

    void pop() {
        if (empty()) throw underflow_error("Stack is empty: cannot pop");
        items.pop_back();
    }

    // Safe access to the next (top) item
    const T& top() const {
        if (empty()) throw underflow_error("Stack is empty: no top element");
        return items.back();
    }

    bool empty() const { return items.empty(); }
    size_t size() const { return items.size(); }
};

// Test helper: works for any element type
template <typename T>
void testStack(const string& label, const T& a, const T& b, const T& c) {
    cout << "--- Stack<" << label << "> ---\n";
    Stack<T> s;
    s.push(a); s.push(b); s.push(c);
    cout << "size after 3 pushes: " << s.size() << "\n";
    while (!s.empty()) {
        cout << "top = " << s.top() << " -> pop\n";
        s.pop();
    }
    try {
        s.pop();                // invalid operation on an empty stack
    } catch (const underflow_error& e) {
        cout << "Caught: " << e.what() << "\n";
    }
    cout << "\n";
}

int main() {
    testStack<int>("int", 10, 20, 30);
    testStack<float>("float", 1.5f, 2.5f, 3.5f);
    testStack<string>("string", "apple", "banana", "cherry");
    return 0;
}
