#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include "Contracts.h" 
#include <string>
#include <iostream>

using namespace std;

// 8. Клас Client (необхідний для демонстрації сценарію)
class Client {
private:
    string fullName;
    string passportData;
    int rentalTerm;

public:
    Client(string name, string passport, int term);

    // Гетери для доступу (виправлення помилки main)
    string getPassportData() const { return passportData; }
    int getRentalTerm() const { return rentalTerm; }

    // 8. Методи для сценарію
    void fillOrder(RentalAgreement& agreement);
    void payOrder(RentalAgreement& agreement);
    void cancelOrder(RentalAgreement& agreement);
};

#endif