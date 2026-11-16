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
