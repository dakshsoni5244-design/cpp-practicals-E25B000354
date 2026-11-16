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
