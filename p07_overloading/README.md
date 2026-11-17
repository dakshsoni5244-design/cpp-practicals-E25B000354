# Practical 07: Function and Operator Overloading

Overloaded add() functions and a ComplexNumber class with overloaded +, - and * operators.

## Source Code (`main.cpp`)

```cpp
// Practical 07: Function overloading and operator overloading (ComplexNumber)
#include <iostream>
using namespace std;

// ---- Function overloading: same name, different parameter lists ----
int add(int a, int b)                { return a + b; }
double add(double a, double b)       { return a + b; }
int add(int a, int b, int c)         { return a + b + c; }

class ComplexNumber {
    double real, imag;
public:
    ComplexNumber(double r = 0, double i = 0) : real(r), imag(i) {}

    // ---- Operator overloading: + combines two complex numbers ----
    ComplexNumber operator+(const ComplexNumber& other) const {
        return ComplexNumber(real + other.real, imag + other.imag);
    }
    ComplexNumber operator-(const ComplexNumber& other) const {
        return ComplexNumber(real - other.real, imag - other.imag);
    }
    ComplexNumber operator*(const ComplexNumber& o) const {
        return ComplexNumber(real * o.real - imag * o.imag,
                             real * o.imag + imag * o.real);
    }

    void display() const {
        cout << real << (imag < 0 ? " - " : " + ") << (imag < 0 ? -imag : imag) << "i";
    }
};

int main() {
    cout << "--- Function overloading ---\n";
    cout << "add(int,int)       : add(3, 4)       = " << add(3, 4) << "\n";
    cout << "add(double,double) : add(2.5, 3.7)   = " << add(2.5, 3.7) << "\n";
    cout << "add(int,int,int)   : add(1, 2, 3)    = " << add(1, 2, 3) << "\n";

    cout << "\n--- Operator overloading ---\n";
    ComplexNumber c1(3, 4), c2(1, -2);
    cout << "c1 = "; c1.display(); cout << "\n";
    cout << "c2 = "; c2.display(); cout << "\n";
    cout << "c1 + c2 = "; (c1 + c2).display(); cout << "\n";
    cout << "c1 - c2 = "; (c1 - c2).display(); cout << "\n";
    cout << "c1 * c2 = "; (c1 * c2).display(); cout << "\n";
    return 0;
}
```

## Output

```text
--- Function overloading ---
add(int,int)       : add(3, 4)       = 7
add(double,double) : add(2.5, 3.7)   = 6.2
add(int,int,int)   : add(1, 2, 3)    = 6

--- Operator overloading ---
c1 = 3 + 4i
c2 = 1 - 2i
c1 + c2 = 4 + 2i
c1 - c2 = 2 + 6i
c1 * c2 = 11 - 2i
```

## Notes: Overloading vs runtime polymorphism

- Function overloading: same name, different parameters; the compiler picks one at compile time.
- Operator overloading: gives +, - and * a meaning for ComplexNumber, so c1 + c2 can be written directly. It is also decided at compile time.
- Runtime polymorphism (practical 6): the function is chosen while the program runs, using virtual functions and the real object type.

## Compile and run

```bash
g++ -o app main.cpp
./app
```
