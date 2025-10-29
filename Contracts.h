#pragma once
#ifndef CONTRACTS_H
#define CONTRACTS_H

#include "Car.h" // Потрібен для наслідування
#include <iostream>
#include <string>

using namespace std;

// 4. Додатковий клас 1 для множинного наслідування (Страхування)
class InsurancePolicy { // 4. Базовий клас для множинного наслідування
protected:
    double premium;

public:
    InsurancePolicy(double p);
    // 7. Деструктор
    virtual ~InsurancePolicy();
    void applyInsurance();
};

// 4. Додатковий клас 2 для множинного наслідування (Штрафи)
class FineController { // 4. Базовий клас для множинного наслідування
protected:
    double outstandingFines;

public:
    FineController(double fines);
    // 7. Деструктор
    virtual ~FineController();
    void applyFine(double amount);
};

// 4. Клас, що реалізує множинне наслідування (П. 4)
class RentalAgreement : public Car, public InsurancePolicy, public FineController { // 4. Множинне наслідування
private:
    string clientPassportID;
    int rentalDurationDays;

public:
    // 4 & 7. Конструктор для множинного наслідування
    RentalAgreement(
        string make, string model, int year, double rate, string plate, string vin, double carInsurance, int mil,
        double policyPremium,
        double initialFines,
        string passport, int days);

    // 7. Деструктор
    ~RentalAgreement();

    // 8. Сценарій функціонування (метод, що об'єднує функціонал)
    void showFullAgreement() const;

    // 8. Методи для сценарію
    void approveAgreement();
    void cancelAgreement();
};

// 4 & 5. Зовнішні функції
// 5. Функція, що повертає об'єкт класу Car. (П. 5)
Car createDemoCar();

// 4. Зовнішня функція, що приймає об'єкт Car та здійснює обчислення. (П. 4)
void calculateCarEstimate(const Car& car);


#endif