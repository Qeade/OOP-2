#include "CarRental.h"

//      Vehicle & Derived Implementation


Vehicle::Vehicle(string m, double rate) : model(m), dailyRate(rate) {}
string Vehicle::getModel() const { return model; }
double Vehicle::getRate() const { return dailyRate; }
void Vehicle::displayInfo() const {
    cout << "[Vehicle] " << model << " ($" << dailyRate << "/day)" << endl;
}

// Economy
EconomyCar::EconomyCar(string m, double rate) : Vehicle(m, rate) {}
double EconomyCar::calculateTotal(int days, bool ins) const {
    double total = dailyRate * days;
    if (ins) total += 10.0 * days; 
    return total;
}
void EconomyCar::displayInfo() const {
    cout << "[Economy] " << model << " (Rate: $" << dailyRate << ")" << endl;
}

// SUV
SUV::SUV(string m, double rate) : Vehicle(m, rate) {}
double SUV::calculateTotal(int days, bool ins) const {
    double total = dailyRate * days;
    if (ins) total += (dailyRate * 0.15) * days; 
    return total;
}
void SUV::displayInfo() const {
    cout << "[SUV] " << model << " (Rate: $" << dailyRate << ")" << endl;
}

// Luxury
LuxuryCar::LuxuryCar(string m, double rate) : Vehicle(m, rate) {}
double LuxuryCar::calculateTotal(int days, bool ins) const {
    double total = dailyRate * days + 50.0; 
    if (ins) total += (dailyRate * 0.25) * days; 
    return total;
}
void LuxuryCar::displayInfo() const {
    cout << "[Luxury] " << model << " (Rate: $" << dailyRate << ")" << endl;
}

//         Order Implementation

Order::Order(Vehicle* v, string name, string pass, int d, bool ins)
    : car(v), clientName(name), passportData(pass), days(d), insurance(ins) {
    status = PENDING;
    fines = 0;
    updateCost();
}

void Order::updateCost() {
    finalAmount = car->calculateTotal(days, insurance);
}

// Перевантаження операторів
Order& Order::operator++() { // Prefix
    days++; updateCost(); return *this;
}
Order Order::operator++(int) { // Postfix
    Order temp = *this; days++; updateCost(); return temp;
}
Order& Order::operator--() { // Prefix
    if (days > 1) days--; updateCost(); return *this;
}
Order Order::operator--(int) { // Postfix
    Order temp = *this; if (days > 1) days--; updateCost(); return temp;
}

void Order::cancelOrder(string reason) {
    if (status == PENDING) { status = CANCELED; }
}
void Order::payOrder() {
    if (status == APPROVED) { status = PAID; }
}
void Order::adminProcess(bool approve, string reason) {
    status = approve ? APPROVED : REJECTED;
}
void Order::showStatus() const {
    cout << "   -> Order: " << clientName << " | Days: " << days
        << " | Total: $" << finalAmount << " | Status Code: " << status << endl;
}

//      RentalSystem Implementation (STL)

RentalSystem::~RentalSystem() {
    // Очищення динамічної пам'яті для вказівників у векторі
    for (Vehicle* v : fleet) {
        delete v;
    }
    fleet.clear();
}

void RentalSystem::addCar(Vehicle* car) {
    fleet.push_back(car); // Додавання в кінець
}

void RentalSystem::addVipCarFront(Vehicle* car) {
    // Вставка на початок using iterator
    fleet.insert(fleet.begin(), car);
    cout << ">>> SYSTEM: VIP Car inserted at the front!" << endl;
}

void RentalSystem::removeCar(int index) {
    if (index >= 0 && index < fleet.size()) {
        Vehicle* v = fleet[index];
        delete v; 
        // Видалення елемента з вектора using iterator arithmetic
        fleet.erase(fleet.begin() + index);
        cout << ">>> SYSTEM: Car at index " << index << " removed from fleet." << endl;
    }
}

void RentalSystem::showFleet() const {
    cout << "\n--- CURRENT FLEET ---" << endl;
    for (size_t i = 0; i < fleet.size(); ++i) {
        cout << i << ". ";
        fleet[i]->displayInfo();
    }
    cout << "---------------------" << endl;
}

void RentalSystem::createOrder(int carIndex, string name, string pass, int days, bool ins) {
    if (carIndex >= 0 && carIndex < fleet.size()) {
        Vehicle* selectedCar = fleet[carIndex];
        // Створення тимчасового об'єкта і додавання його копії у вектор
        orders.push_back(Order(selectedCar, name, pass, days, ins));
        cout << ">>> SYSTEM: Order created for " << name << endl;
    }
    else {
        cout << ">>> ERROR: Car index out of bounds!" << endl;
    }
}

void RentalSystem::removeLastOrder() {
    if (!orders.empty()) {
        orders.pop_back(); // Видалення останнього елемента
        cout << ">>> SYSTEM: Last order canceled (pop_back executed)." << endl;
    }
}

Order& RentalSystem::getLastOrder() {
    return orders.back(); // Посилання на останній елемент
}

void RentalSystem::showOrdersHistory() const {
    cout << "\n--- ORDER HISTORY ---" << endl;
    if (orders.empty()) {
        cout << "(Empty)" << endl;
    }
    else {
        for (const auto& ord : orders) {
            ord.showStatus();
        }
    }
    cout << "---------------------" << endl;
}