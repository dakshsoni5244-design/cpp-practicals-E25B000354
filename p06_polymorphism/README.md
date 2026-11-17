# Practical 06: Abstract Class and Runtime Polymorphism

Abstract class Shape with Circle, Rectangle and Triangle. The correct area() is called at run time through a base class pointer.

## Source Code (`main.cpp`)

```cpp
// Practical 06: Abstract class and runtime polymorphism
#include <iostream>
using namespace std;

// Abstract class: it has a pure virtual function (= 0)
class Shape {
public:
    virtual double area() = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
    double r;
public:
    Circle(double radius) { r = radius; }
    double area() { return 3.14159 * r * r; }
};

class Rectangle : public Shape {
    double l, b;
public:
    Rectangle(double length, double breadth) { l = length; b = breadth; }
    double area() { return l * b; }
};

class Triangle : public Shape {
    double base, height;
public:
    Triangle(double bs, double h) { base = bs; height = h; }
    double area() { return 0.5 * base * height; }
};

int main() {
    // Shape s;   // ERROR: cannot create an object of an abstract class

    Shape* shapes[3];
    shapes[0] = new Circle(5);
    shapes[1] = new Rectangle(4, 6);
    shapes[2] = new Triangle(8, 3);

    string names[3] = {"Circle", "Rectangle", "Triangle"};

    for (int i = 0; i < 3; i++) {
        // The function of the real object is called at run time
        cout << names[i] << " area = " << shapes[i]->area() << "\n";
    }

    for (int i = 0; i < 3; i++)
        delete shapes[i];
    return 0;
}
```

## Output

```text
Circle area = 78.5397
Rectangle area = 24
Triangle area = 12
```

## Compile and run

```bash
g++ -o app main.cpp
./app
```
