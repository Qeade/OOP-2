#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include "Car.h" 

class Client {
private:
    string passportID;
    string phoneNumber;
    double currentBalance;
    bool hasActiveRental;
    int rentalDurationDays;

public:
    string fullName;
    string email;
    Car rentedCar; 

    Client(string fn = "N/A", string email = "N/A", string passID = "N/A", string phone = "N/A",
        double balance = 0.0, bool active = false, int days = 0, const Car& car = Car());


    void displayClientInfo() const;

    void requestRental(const Car& carToRent, int days);

    void requestRental(const Car& carToRent);

    Client approveRental(double totalCost);

    void cancelRental(const string& reason);

    void applyFine(double fineAmount);

    void writeToFile(const string& filename) const;
    void readFromFile(const string& filename);

    void allocateAndSortDuration();

    bool getHasActiveRental() const { return hasActiveRental; }
    int getRentalDurationDays() const { return rentalDurationDays; }
    double getCurrentBalance() const { return currentBalance; }
};

#endif 