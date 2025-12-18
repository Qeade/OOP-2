// CarRental.cpp
#include "CarRental.h"

//  Vehicle Implementation
Vehicle::Vehicle(string m, double rate) : model(m), dailyRate(rate) {}
string Vehicle::getModel() const { return model; }
double Vehicle::getRate() const { return dailyRate; }
void Vehicle::displayInfo() const {
    cout << "[Vehicle] Model: " << model << ", Rate: $" << dailyRate << "/day" << endl;
}

//  Derived Classes Implementation 
EconomyCar::EconomyCar(string m, double rate) : Vehicle(m, rate) {}
double EconomyCar::calculateTotal(int days, bool insurance) const {
    double total = dailyRate * days;
    if (insurance) total += 10.0 * days;
    return total;
}
void EconomyCar::displayInfo() const { cout << "[Economy Class] " << model << endl; }

SUV::SUV(string m, double rate) : Vehicle(m, rate) {}
double SUV::calculateTotal(int days, bool insurance) const {
    double total = dailyRate * days;
    if (insurance) total += (dailyRate * 0.15) * days;
    return total;
}
void SUV::displayInfo() const { cout << "[SUV Class] " << model << endl; }

LuxuryCar::LuxuryCar(string m, double rate) : Vehicle(m, rate) {}
double LuxuryCar::calculateTotal(int days, bool insurance) const {
    double total = dailyRate * days;
    total += 50.0;
    if (insurance) total += (dailyRate * 0.25) * days;
    return total;
}
void LuxuryCar::displayInfo() const { cout << "[Luxury Class] " << model << endl; }

// Order Implementation 

Order::Order(Vehicle* v, string name, string pass, int d, bool ins)
    : car(v), clientName(name), passportData(pass), days(d), insurance(ins) {
    status = PENDING;
    fines = 0;
    updateCost(); 
}

// Приватна функція для перерахунку ціни
void Order::updateCost() {
    finalAmount = car->calculateTotal(days, insurance);
}

// оператори

// Prefix ++: Збільшуємо, потім повертаємо змінений об'єкт
Order& Order::operator++() {
    days++;
    updateCost();
    return *this;
}

// Postfix ++: Створюємо копію, збільшуємо оригінал, повертаємо копію
Order Order::operator++(int) {
    Order temp = *this; 
    days++;
    updateCost();
    return temp; 
}

// Prefix --
Order& Order::operator--() {
    if (days > 1) { // Захист: оренда не може бути 0 днів
        days--;
        updateCost();
    }
    return *this;
}

// Postfix --
Order Order::operator--(int) {
    Order temp = *this;
    if (days > 1) {
        days--;
        updateCost();
    }
    return temp;
}


void Order::cancelOrder(string reason) {
    if (status == PENDING) {
        status = CANCELED;
        cout << ">>> Client " << clientName << " canceled. Reason: " << reason << endl;
    }
    else { cout << ">>> Cannot cancel." << endl; }
}

void Order::adminProcess(bool approve, string reason) {
    if (status != PENDING) return;
    if (approve) {
        status = APPROVED;
        cout << ">>> ADMIN: Approved. Pay $" << finalAmount << endl;
    }
    else {
        status = REJECTED;
        cout << ">>> ADMIN: Rejected. Reason: " << reason << endl;
    }
}

void Order::payOrder() {
    if (status == APPROVED) {
        status = PAID;
        cout << ">>> PAYMENT: Success. Amount $" << finalAmount << " received." << endl;
    }
    else cout << ">>> PAYMENT ERROR: Not approved." << endl;
}

void Order::addDamageFine(double amount) {
    fines += amount;
    cout << ">>> ADMIN: Damage fine added: $" << amount << endl;
}

void Order::returnCar(bool lateReturn) {
    if (status == PAID) {
        if (lateReturn) {
            fines += 100.0;
            cout << ">>> SYSTEM: Late return penalty applied." << endl;
        }
        cout << ">>> RETURN: Final check. Outstanding: $" << fines << endl;
        status = CLOSED;
    }
}

void Order::showStatus() const {
    cout << "   [Order Info] Days: " << days << " | Total: $" << finalAmount << " | Status: " << status << endl;
}