// Practical 08: Factory design pattern - creating vehicles by requested type
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
using namespace std;

class Vehicle {
public:
    virtual void drive() const = 0;
    virtual int wheels() const = 0;
    virtual ~Vehicle() = default;
};

class Car : public Vehicle {
public:
    void drive() const override { cout << "Car: driving on the road\n"; }
    int wheels() const override { return 4; }
};

class Bike : public Vehicle {
public:
    void drive() const override { cout << "Bike: riding with two wheels\n"; }
    int wheels() const override { return 2; }
};

class Truck : public Vehicle {
public:
    void drive() const override { cout << "Truck: carrying heavy load\n"; }
    int wheels() const override { return 6; }
};

// Factory: client code asks for a type by name and does not use 'new Car' etc.
class VehicleFactory {
public:
    static unique_ptr<Vehicle> create(const string& type) {
        if (type == "car")   return make_unique<Car>();
        if (type == "bike")  return make_unique<Bike>();
        if (type == "truck") return make_unique<Truck>();
        throw invalid_argument("Unknown vehicle type: " + type);
    }
};

int main() {
    for (const string t : {"car", "bike", "truck", "plane"}) {
        try {
            auto v = VehicleFactory::create(t);
            cout << "Requested '" << t << "' -> wheels: " << v->wheels() << " | ";
            v->drive();
        } catch (const invalid_argument& e) {
            cout << "Requested '" << t << "' -> error: " << e.what() << "\n";
        }
    }
    return 0;
}
