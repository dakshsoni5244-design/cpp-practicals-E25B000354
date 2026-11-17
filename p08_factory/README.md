# Practical 08: Factory Design Pattern

VehicleFactory creates Car, Bike or Truck from a name. An unknown name is handled.

## Source Code (`main.cpp`)

```cpp
// Practical 08: Factory design pattern
#include <iostream>
#include <string>
using namespace std;

class Vehicle {
public:
    virtual void drive() = 0;
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
public:
    void drive() { cout << "Car is running on 4 wheels\n"; }
};

class Bike : public Vehicle {
public:
    void drive() { cout << "Bike is running on 2 wheels\n"; }
};

class Truck : public Vehicle {
public:
    void drive() { cout << "Truck is carrying a heavy load\n"; }
};

// Factory: creates the object according to the name we ask for
class VehicleFactory {
public:
    static Vehicle* create(string type) {
        if (type == "car")   return new Car();
        if (type == "bike")  return new Bike();
        if (type == "truck") return new Truck();
        return nullptr;      // unknown type
    }
};

int main() {
    string types[4] = {"car", "bike", "truck", "plane"};

    for (int i = 0; i < 4; i++) {
        cout << "Asking for: " << types[i] << " -> ";
        Vehicle* v = VehicleFactory::create(types[i]);
        if (v == nullptr) {
            cout << "unknown vehicle type\n";
        } else {
            v->drive();
            delete v;
        }
    }
    return 0;
}
```

## Output

```text
Asking for: car -> Car is running on 4 wheels
Asking for: bike -> Bike is running on 2 wheels
Asking for: truck -> Truck is carrying a heavy load
Asking for: plane -> unknown vehicle type
```

## Notes: Use case and trade-offs

- Use case: when objects are created from a name or setting and used through one common class (Vehicle).
- Benefit: the calling code does not need to know Car, Bike or Truck, so new types are easy to add.
- Trade-off: extra classes, and the factory must be edited when a new type is added.

## Compile and run

```bash
g++ -o app main.cpp
./app
```
