#include "CarRental.h"

// --- Vehicle Implementation ---
Vehicle::Vehicle(string m, double rate) : model(m), dailyRate(rate) {}

string Vehicle::getModel() const { return model; }
double Vehicle::getRate() const { return dailyRate; }

void Vehicle::displayInfo() const {
    cout << "[Vehicle] Model: " << model << ", Rate: $" << dailyRate << "/day" << endl;
}

// --- EconomyCar Implementation ---
EconomyCar::EconomyCar(string m, double rate) : Vehicle(m, rate) {}

double EconomyCar::calculateTotal(int days, bool insurance) const {
    double total = dailyRate * days;
    if (insurance) {
        total += 10.0 * days; // Фіксована низька страховка
    }
    return total;
}

void EconomyCar::displayInfo() const {
    cout << "[Economy Class] " << model << ". Cheap and reliable." << endl;
}

// --- SUV Implementation ---
SUV::SUV(string m, double rate) : Vehicle(m, rate) {}

double SUV::calculateTotal(int days, bool insurance) const {
    double total = dailyRate * days;
    if (insurance) {
        total += (dailyRate * 0.15) * days; // Страховка залежить від ціни (15%)
    }
    return total;
}

void SUV::displayInfo() const {
    cout << "[SUV Class] " << model << ". Good for off-road." << endl;
}

// --- LuxuryCar Implementation ---
LuxuryCar::LuxuryCar(string m, double rate) : Vehicle(m, rate) {}

double LuxuryCar::calculateTotal(int days, bool insurance) const {
    double total = dailyRate * days;
    // Luxury податок + висока страховка
    total += 50.0; // Податок на розкіш разовий
    if (insurance) {
        total += (dailyRate * 0.25) * days; // 25% страховка
    }
    return total;
}

void LuxuryCar::displayInfo() const {
    cout << "[Luxury Class] " << model << ". Premium comfort." << endl;
}

// --- Order Implementation ---
Order::Order(Vehicle* v, string name, string pass, int d, bool ins)
    : car(v), clientName(name), passportData(pass), days(d), insurance(ins) {
    status = PENDING;
    fines = 0;
    // Поліморфний виклик методу розрахунку ціни!
    finalAmount = car->calculateTotal(days, insurance);
}

void Order::cancelOrder(string reason) {
    if (status == PENDING) {
        status = CANCELED;
        cout << ">>> Client " << clientName << " canceled the order. Reason: " << reason << endl;
    }
    else {
        cout << ">>> Cannot cancel. Order already processed." << endl;
    }
}

void Order::adminProcess(bool approve, string reason) {
    if (status != PENDING) return;

    if (approve) {
        status = APPROVED;
        cout << ">>> ADMIN: Order Approved. Please pay $" << finalAmount << endl;
    }
    else {
        status = REJECTED;
        cout << ">>> ADMIN: Order Rejected. Reason: " << reason << endl;
    }
}

void Order::payOrder() {
    if (status == APPROVED) {
        status = PAID;
        cout << ">>> PAYMENT: Success. Amount $" << finalAmount << " received. Car is yours." << endl;
    }
    else {
        cout << ">>> PAYMENT ERROR: Order is not approved yet." << endl;
    }
}

void Order::addDamageFine(double amount) {
    fines += amount;
    cout << ">>> ADMIN: Damage reported! Fine added: $" << amount << endl;
}

void Order::returnCar(bool lateReturn) {
    if (status == PAID) {
        if (lateReturn) {
            double penalty = 100.0; // Штраф за запізнення
            fines += penalty;
            cout << ">>> SYSTEM: Late return detected. Penalty: $" << penalty << endl;
        }

        double totalToPay = fines;
        if (totalToPay > 0) {
            cout << ">>> RETURN: You have outstanding fines: $" << totalToPay << ". Please pay now." << endl;
        }
        else {
            cout << ">>> RETURN: Car returned successfully. No extra charges." << endl;
        }
        status = CLOSED;
    }
}

void Order::showStatus() const {
    cout << "--- Order Status for " << clientName << " (" << car->getModel() << ") ---" << endl;
    cout << "Status Code: " << status << " | Total Price: $" << finalAmount << endl;
}