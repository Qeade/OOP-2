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

	// 2. Константне поле (Ініціалізація через список для константи)
	const int MAX_RENTAL_DAYS;

	// 3. Статичне поле (Спільне для всіх об'єктів. Демонстрація спільного використання поля даних)
	static int carCount;

public:
	string plateNumber;
	double insuranceCost;
	int mileage;

	
	// 1 і 7. КОНСТРУКТОРИ
	// 1.1. Конструктор без параметрів (Default). (П. 1, П. 7)
	Car();

	// 1.2. Конструктор з 8 параметрами (Основний). (П. 1, П. 7)
	Car(string mk, string md, int yr, double rate, string plate, double insurance, int mil, bool rented);

	// 1.3. Конструктор копіювання. (П. 1, П. 7)
	Car(const Car& other);

	// 2. Конструктор зі списком ініціалізації (для константного поля). (П. 2, П. 7)
	Car(string mk, string md, int maxDays);

	// Оператор присвоєння копіювання (Явно визначений через константне поле)
	Car& operator=(const Car& other);

	// Деструктор (для коректної роботи зі статичним лічильником)
	~Car() { carCount--; }

	// 3. СТАТИЧНІ ЕЛЕМЕНТИ
	// 3.1. Статичний метод (Використовується для демонстрації статичного методу класу)
	static void displayTotalCarCount();


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
	int getMAX_RENTAL_DAYS() const { return MAX_RENTAL_DAYS; } 
};

// 5. Функція, оголошена поза класом, що повертає об'єкт класу Car. (П. 5)
Car createDamageReport(const Car& initialCar);

// 4. Зовнішня функція, що приймає об'єкт Car та здійснює обчислення. (П. 4)
void calculateCarProfitEstimate(const Car& car);

#endif