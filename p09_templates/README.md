# Practical 09: Generic Stack Using Templates

Stack class template tested with int, float and string, including the empty-stack case.

## Source Code (`main.cpp`)

```cpp
// Practical 09: Stack using a class template
#include <iostream>
#include <string>
using namespace std;

template <class T>
class Stack {
    T items[10];     // fixed size array
    int top;         // index of the top item, -1 means empty
public:
    Stack() { top = -1; }

    bool isEmpty() { return top == -1; }
    bool isFull()  { return top == 9; }

    void push(T value) {
        if (isFull()) {
            cout << "Stack is full\n";
            return;
        }
        top++;
        items[top] = value;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty, cannot pop\n";
            return;
        }
        top--;
    }

    T peek() {       // look at the top item
        return items[top];
    }
};

// works for any type T
template <class T>
void test(T a, T b, T c) {
    Stack<T> s;
    s.push(a);
    s.push(b);
    s.push(c);
    while (!s.isEmpty()) {
        cout << "top = " << s.peek() << "\n";
        s.pop();
    }
    s.pop();   // empty-stack test
}

int main() {
    cout << "--- int stack ---\n";
    test<int>(10, 20, 30);

    cout << "\n--- float stack ---\n";
    test<float>(1.5f, 2.5f, 3.5f);

    cout << "\n--- string stack ---\n";
    test<string>("apple", "banana", "cherry");
    return 0;
}
```

## Output

```text
--- int stack ---
top = 30
top = 20
top = 10
Stack is empty, cannot pop

--- float stack ---
top = 3.5
top = 2.5
top = 1.5
Stack is empty, cannot pop

--- string stack ---
top = cherry
top = banana
top = apple
Stack is empty, cannot pop
```

## Compile and run

```bash
g++ -o app main.cpp
./app
```
