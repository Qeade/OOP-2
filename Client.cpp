#include "Client.h"
#include <iostream>

using namespace std;

Client::Client(string name, string passport, int term)
    : fullName(name), passportData(passport), rentalTerm(term) {
    cout << "Client " << fullName << " created." << endl;
}

// 8. Сценарій: Клієнт заповнює форму (створює договір)
void Client::fillOrder(RentalAgreement& agreement) {
    cout << "  Client " << fullName << " is filling the order for " << agreement.getModel() << "." << endl;
}

// 8. Сценарій: Клієнт оплачує (Адмін підтверджує)
void Client::payOrder(RentalAgreement& agreement) {
    cout << "  Client " << fullName << " pays for the order." << endl;
    agreement.approveAgreement(); // Виклик методу з RentalAgreement
}

// 8. Сценарій: Клієнт скасовує (Адмін відхиляє)
void Client::cancelOrder(RentalAgreement& agreement) {
    cout << "  Client " << fullName << " cancels the order." << endl;
    agreement.cancelAgreement(); // Виклик методу з RentalAgreement
}