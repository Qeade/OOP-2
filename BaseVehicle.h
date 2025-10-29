#pragma once
#ifndef BASEVEHICLE_H
#define BASEVEHICLE_H

#include <iostream>
#include <string>

using namespace std;

// 1. Визначення ієрархії класів (Базовий клас)
class BaseVehicle {
private:
    // 2. Керування доступом: private поле
    string internalID;
    // 2. Керування доступом: private метод
    void logInternal() const; // 2. private метод

protected:
    // 1. Поля базового класу
    string make;
    string model;
    int year;
    double rentalRatePerDay;

    // 2. Керування доступом: protected поле
    string maintenanceRecord;
    // 2. Керування доступом: protected метод
    void protectedMethod() const; // 2. protected метод

public:
    string plateNumber;
    bool isRented;

    // 2. Керування доступом: public поле
    string publicVIN;
    // 2. Керування доступом: public метод
    void publicMethod() const; // 2. public метод

    // --- Конструктори та Деструктор ---

    // 5. Конструктор базового класу (приймає 6 аргументів)
    BaseVehicle(string make, string model, int year, double rate, string plate, string vin);

    // 1. Конструктор за замовчуванням
    BaseVehicle();

    // 7. Деструктор (для демонстрації порядку виклику)
    virtual ~BaseVehicle();

    // Метод для демонстрації доступу зсередини (П. 2)
    void demoInternalAccess() const;
};

#endif