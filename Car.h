#pragma once
#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

class Car {
private:
    string make;
    string model;
    int year;
    double rentalRatePerDay;
    bool isRented;

public:
    string plateNumber;
    double insuranceCost;
    int mileage;

    Car(string mk = "N/A", string md = "N/A", int yr = 0, double rate = 0.0,
        string plate = "N/A", double insurance = 0.0, int mil = 0, bool rented = false);


    void displayCarInfo() const;

    double calculateTotalRent(int days) const;

    double calculateTotalRent(int days, bool withInsurance) const;

    void rentOut();

    Car returnCar(int newMileage, const Car& damagedCar);

    bool checkAvailability() const;

    void writeToFile(const string& filename) const;
    void readFromFile(const string& filename);

    void allocateAndSortMileage();

    double getRentalRate() const { return rentalRatePerDay; }
    string getMake() const { return make; }
    string getModel() const { return model; }
    bool getIsRented() const { return isRented; }
};

#endif 