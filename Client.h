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

	// 2. Поле-посилання 
	const string& refPassportID;

	// 3. Статичне поле 
	static int clientCount;

public:
	string fullName;
	string email;
	Car rentedCar;

	// 1 і 7. КОНСТРУКТОРИ
	// 1.1. Конструктор без параметрів. (П. 1, П. 7)
	Client();

	// 1.2. Конструктор з 8 параметрами. (П. 1, П. 7)
	Client(string fn, string email, string passID, string phone, double balance, bool active, int days, const Car& car);

	// 1.3. Конструктор копіювання. (П. 1, П. 7)
	Client(const Client& other);

	// 2. Конструктор зі списком ініціалізації. (П. 2, П. 7)
	Client(string fn, string passID, const string& passportReference);


	Client& operator=(const Client& other);

	~Client() { clientCount--; }

	// 3. СТАТИЧНІ ЕЛЕМЕНТИ
	// 3.2. Статичний метод 
	static void displayTotalClientCount();


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
	const string& getRefPassportID() const { return refPassportID; }
};

// 5. Функція, оголошена поза класом, що повертає об'єкт класу Client. (П. 5)
Client createNewClient(string name, double balance);

// 4. Зовнішня функція, що приймає об'єкт Client та здійснює обчислення. (П. 4)
void calculateClientNetWorth(const Client& client);

#endif