#pragma once
#ifndef CARRENTAL_H
#define CARRENTAL_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

// Статуси замовлення
enum OrderStatus { PENDING, APPROVED, REJECTED, CANCELED, PAID, CLOSED };

// === Абстрактний базовий клас ===
class Vehicle {
protected:
    string model;
    double dailyRate;

public:
    Vehicle(string m, double rate);
    virtual ~Vehicle() {}

    string getModel() const;
    double getRate() const;

    // Чисто віртуальна функція (Requirement 2)
    virtual double calculateTotal(int days, bool insurance) const = 0;

    // Віртуальна функція для виведення інформації
    virtual void displayInfo() const;
};

// === Похідний клас 1: Економ ===
class EconomyCar : public Vehicle {
public:
    EconomyCar(string m, double rate);
    // Реалізація віртуальної функції
    double calculateTotal(int days, bool insurance) const override;
    void displayInfo() const override;
};

// === Похідний клас 2: Позашляховик ===
class SUV : public Vehicle {
public:
    SUV(string m, double rate);
    double calculateTotal(int days, bool insurance) const override;
    void displayInfo() const override;
};

// === Похідний клас 3: Преміум ===
class LuxuryCar : public Vehicle {
public:
    LuxuryCar(string m, double rate);
    double calculateTotal(int days, bool insurance) const override;
    void displayInfo() const override;
};

// === Клас Замовлення (керує логікою процесу) ===
class Order {
private:
    Vehicle* car;          // Агрегація (вказівник на абстрактний клас)
    string clientName;
    string passportData;
    int days;
    bool insurance;
    OrderStatus status;
    double finalAmount;
    double fines;

public:
    Order(Vehicle* v, string name, string pass, int d, bool ins);

    // Дії клієнта
    void cancelOrder(string reason);
    void payOrder();

    // Дії адміністратора
    void adminProcess(bool approve, string reason = "");
    void addDamageFine(double amount);
    void returnCar(bool lateReturn);

    // Інфо
    void showStatus() const;
};

#endif