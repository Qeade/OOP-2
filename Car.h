#pragma once
#ifndef CAR_H
#define CAR_H

#include "BaseVehicle.h"
#include <iostream>
#include <string>

using namespace std;

// 1. Визначення ієрархії класів (Похідний клас 1: public наслідування)
class Car : public BaseVehicle {
private:
    // 1. Додаткові поля
    double insuranceCost;
    int mileage;

public:
    // 5. Конструктор похідного класу (використовує всі параметри)
    Car(string make, string model, int year, double rate, string plate, string vin, double insurance, int mil);

    // 1. Конструктор за замовчуванням
    Car();

    // 7. Деструктор
    ~Car();

    // 2 & 6. Метод для демонстрації керування доступом з похідного класу
    void demoDerivedAccess() const;

    // 6. Демонстрація доступу до методів базового класу через 'using'
    using BaseVehicle::protectedMethod;

    // Методи для сценарію (П. 8)
    void displayInfo() const;
    string getModel() const { return model; } // Потрібно для Client
};


// 3. Додатковий похідний клас (закритий спосіб наслідування)
class CommercialTruck : private BaseVehicle { // 3. Закритий спосіб наслідування
public:
    // 3 & 5. Конструктор, що передає параметри базовому класу
    CommercialTruck(string make, string model, int year, double rate, string plate, string vin);

    // 7. Деструктор
    ~CommercialTruck();

    // 3. Об'єкт, що оперує методами з різних класів ієрархії
    void showVehicleInfo() {
        cout << "[CommercialTruck (П. 3)] Accessing base method via public proxy..." << endl;
        publicMethod(); // Доступно, оскільки ми всередині похідного класу
    }

    // 6. Демонстрація доступу до членів базового класу через 'using'
    using BaseVehicle::publicVIN;
    using BaseVehicle::protectedMethod;
};

#endif