#include "Car.h"
#include <iostream>

using namespace std;

// --- Реалізація класу Car (Public наслідування) ---

// 5. Конструктор похідного класу (П. 5)
Car::Car(string make, string model, int year, double rate, string plate, string vin, double insurance, int mil)
// 5. Передача 6 параметрів конструктору базового класу
    : BaseVehicle(make, model, year, rate, plate, vin),
    insuranceCost(insurance), mileage(mil)
{
    // 7. Конструктор Car викликаний
    cout << "Car (Param) created." << endl;
}

Car::Car() : BaseVehicle(), insuranceCost(0.0), mileage(0) {
    // 7. Конструктор Car (Default) викликаний
    cout << "Car (Default) created." << endl;
}

// 7. Реалізація деструктора
Car::~Car() {
    cout << "Car destroyed." << endl;
}

// 2 & 6. Демонстрація керування доступом з похідного класу (public наслідування)
void Car::demoDerivedAccess() const { // 2. Демонстрація доступу
    cout << "\nCar Derived class access check (public inheritance):" << endl;

    // 2. Доступ до public (OK)
    cout << "  Public data (publicVIN): " << publicVIN << " (OK)" << endl;
    publicMethod();

    // 2. Доступ до protected (OK)
    cout << "  Protected data (maintenanceRecord): " << maintenanceRecord << " (OK)" << endl;
    protectedMethod();

    // 2. Доступ до private (Access Denied)
    cout << "  Private data (internalID): (Access Denied)" << endl;

    // 6. Демонстрація доступу через оператор глобального доступу
    cout << "Car Access via Scope (::) operator:" << endl;
    BaseVehicle::publicMethod();
}

// 8. Метод для сценарію
void Car::displayInfo() const {
    cout << "  Car Details: " << make << " " << model << " (" << plateNumber << ")" << endl;
}


// --- Реалізація класу CommercialTruck (Private наслідування) (П. 3) ---

// 3. Конструктор похідного класу (private наслідування)
CommercialTruck::CommercialTruck(string make, string model, int year, double rate, string plate, string vin)
    : BaseVehicle(make, model, year, rate, plate, vin)
{
    // 7. Конструктор CommercialTruck викликаний
    cout << "CommercialTruck created (Private inheritance)." << endl;
}

// 7. Реалізація деструктора
CommercialTruck::~CommercialTruck() {
    cout << "CommercialTruck destroyed." << endl;
}