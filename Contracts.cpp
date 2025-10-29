#include "Contracts.h"
#include <iostream>

using namespace std;

// --- Реалізація InsurancePolicy ---

InsurancePolicy::InsurancePolicy(double p) : premium(p) {
    // 7. Конструктор InsurancePolicy викликаний
}

InsurancePolicy::~InsurancePolicy() {
    cout << "InsurancePolicy destroyed." << endl;
}

void InsurancePolicy::applyInsurance() {
    cout << "Policy applied with premium: $" << premium << endl;
}

// --- Реалізація FineController ---

FineController::FineController(double fines) : outstandingFines(fines) {
    // 7. Конструктор FineController викликаний
}

FineController::~FineController() {
    cout << "FineController destroyed." << endl;
}

void FineController::applyFine(double amount) {
    outstandingFines += amount;
    cout << "Fine applied. Total fines: $" << outstandingFines << endl;
}

// --- Реалізація RentalAgreement (П. 4) ---

// 4 & 7. Конструктор для множинного наслідування
RentalAgreement::RentalAgreement(
    string make, string model, int year, double rate, string plate, string vin, double carInsurance, int mil,
    double policyPremium,
    double initialFines,
    string passport, int days)
    : Car(make, model, year, rate, plate, vin, carInsurance, mil), // Виклик конструктора Car
    InsurancePolicy(policyPremium), // Виклик конструктора InsurancePolicy
    FineController(initialFines), // Виклик конструктора FineController
    clientPassportID(passport), rentalDurationDays(days)
{
    // 7. Конструктор RentalAgreement викликаний
    cout << "RentalAgreement created." << endl;
}

// 7. Реалізація деструктора
RentalAgreement::~RentalAgreement() {
    cout << "RentalAgreement destroyed." << endl;
}

// 8. Сценарій функціонування (метод, що об'єднує функціонал)
void RentalAgreement::showFullAgreement() const {
    cout << "\n--- Full Rental Agreement ---" << endl;
    cout << "  Client Passport: " << clientPassportID << " for " << rentalDurationDays << " days." << endl;

    // 8. Виклик методів з усіх базових класів
    displayInfo(); // З Car
    cout << "  Insurance Premium: $" << premium << endl; // З InsurancePolicy
    cout << "  Fines Outstanding: $" << outstandingFines << endl; // З FineController
}

// 8. Методи для сценарію
void RentalAgreement::approveAgreement() {
    cout << "  Agreement Approved. Applying insurance..." << endl;
    applyInsurance(); // Метод з InsurancePolicy
}
void RentalAgreement::cancelAgreement() {
    cout << "  Agreement Cancelled by Admin. Applying fine..." << endl;
    applyFine(50.0); // Метод з FineController
}


// --- Реалізація Зовнішніх Функцій (П. 4, 5) ---

// 5. Функція, що повертає об'єкт класу Car. (П. 5)
Car createDemoCar() {
    cout << "\nExternal Func Calling createDemoCar() ..." << endl;
    Car demo("Ford", "Mustang", 2022, 150.0, "DEMO-01", "VIN-DEMO", 50.0, 100);
    return demo; // Повернення об'єкта класу
}

// 4. Зовнішня функція, що приймає об'єкт Car та здійснює обчислення. (П. 4)
void calculateCarEstimate(const Car& car) {
    cout << "\nExternal Func Calling calculateCarEstimate()..." << endl;
    // 4. Обчислення з числовими даними (використовуємо public поле)
    cout << "  Estimating value for Car VIN: " << car.publicVIN << endl;
}