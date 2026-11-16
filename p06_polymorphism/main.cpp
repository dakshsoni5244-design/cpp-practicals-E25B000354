// Practical 06: Runtime polymorphism and abstract classes
#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

// Abstract class: has a pure virtual function, so objects of Shape cannot be created.
class Shape {
public:
    virtual double area() const = 0;            // pure virtual
    virtual string name() const = 0;
    virtual ~Shape() = default;                 // virtual destructor
};

class Circle : public Shape {
    double r;
public:
    explicit Circle(double radius) : r(radius) {}
    double area() const override { return M_PI * r * r; }
    string name() const override { return "Circle"; }
};

class Rectangle : public Shape {
    double l, w;
public:
    Rectangle(double length, double width) : l(length), w(width) {}
    double area() const override { return l * w; }
    string name() const override { return "Rectangle"; }
};

class Triangle : public Shape {
    double b, h;
public:
    Triangle(double base, double height) : b(base), h(height) {}
    double area() const override { return 0.5 * b * h; }
    string name() const override { return "Triangle"; }
};

int main() {
    // Shape s;   // ERROR: cannot instantiate abstract class

    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>(5.0));
    shapes.push_back(make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(make_unique<Triangle>(8.0, 3.0));

    cout << fixed << setprecision(2);
    for (const auto& s : shapes) {
        // The call goes through the base-class interface; the correct
        // derived area() is chosen at run time using the vtable.
        cout << s->name() << " area = " << s->area() << "\n";
    }

    Shape& ref = *shapes[1];    // base-class reference to a Rectangle
    cout << "Via reference: " << ref.name() << " area = " << ref.area() << "\n";
    return 0;
}
