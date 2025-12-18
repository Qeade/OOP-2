#ifndef CARRENTAL_H
#define CARRENTAL_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum OrderStatus { PENDING, APPROVED, REJECTED, CANCELED, PAID, CLOSED };

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


    // Prefix ++ (e.g., ++order)
    Order& operator++();

    // Postfix ++ (e.g., order++) 
    Order operator++(int);

    // Prefix -- (e.g., --order)
    Order& operator--();

    // Postfix -- (e.g., order--)
    Order operator--(int);


    void cancelOrder(string reason);
    void payOrder();
    void adminProcess(bool approve, string reason = "");
    void addDamageFine(double amount);
    void returnCar(bool lateReturn);
    void showStatus() const;

    int getDays() const { return days; }
};

#endif