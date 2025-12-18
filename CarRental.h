#ifndef CARRENTAL_H
#define CARRENTAL_H

#include <string>
#include <iostream>
#include <vector> 

using namespace std;

// Статуси замовлення
enum OrderStatus { PENDING, APPROVED, REJECTED, CANCELED, PAID, CLOSED };

// 1. Абстрактний базовий клас 
class Vehicle {
protected:
    string model;
    double dailyRate;

public:
    Vehicle(string m, double rate);
    virtual ~Vehicle() {} 

    string getModel() const;
    double getRate() const;

    virtual double calculateTotal(int days, bool insurance) const = 0;

    virtual void displayInfo() const;
};

//  Похідні класи 
class EconomyCar : public Vehicle {
public:
    EconomyCar(string m, double rate);
    double calculateTotal(int days, bool insurance) const override;
    void displayInfo() const override;
};

class SUV : public Vehicle {
public:
    SUV(string m, double rate);
    double calculateTotal(int days, bool insurance) const override;
    void displayInfo() const override;
};

class LuxuryCar : public Vehicle {
public:
    LuxuryCar(string m, double rate);
    double calculateTotal(int days, bool insurance) const override;
    void displayInfo() const override;
};

// 2. Клас Замовлення з перевантаженням операторів 
class Order {
private:
    Vehicle* car;         
    string clientName;
    string passportData;
    int days;
    bool insurance;
    OrderStatus status;
    double finalAmount;
    double fines;

    void updateCost(); 

public:
    Order(Vehicle* v, string name, string pass, int d, bool ins);

    Order& operator++();      
    Order operator++(int);     
    Order& operator--();       
    Order operator--(int);     

    void cancelOrder(string reason);
    void payOrder();
    void adminProcess(bool approve, string reason = "");
    void showStatus() const;

    string getClientName() const { return clientName; }
};

// 3. Клас-менеджер з використанням STL Vector
class RentalSystem {
private:
    // Вектор вказівників (поліморфний контейнер)
    vector<Vehicle*> fleet;

    // Вектор об'єктів (зберігання історії)
    vector<Order> orders;

public:
    ~RentalSystem(); // Деструктор для очищення пам'яті fleet

    // Методи роботи з вектором машин
    void addCar(Vehicle* car);                 // push_back
    void addVipCarFront(Vehicle* car);         // insert (в початок)
    void removeCar(int index);                 // erase (видалення з середини)
    void showFleet() const;                    // ітерація

    // Методи роботи з вектором замовлень
    void createOrder(int carIndex, string name, string pass, int days, bool ins);
    void removeLastOrder();                    // pop_back
    Order& getLastOrder();                     // back()
    void showOrdersHistory() const;
};

#endif