#include "Car.h"
#include <sstream>

// 3. Ініціалізація статичного поля (забезпечення спільного використання)
int Car::carCount = 0;

// 1, 2, 7. КОНСТРУКТОРИ ТА ОПЕРАТОР ПРИСВОЄННЯ

// 1.1. Конструктор без параметрів (Default). (П. 1, П. 7)
Car::Car() : make("N/A"), model("N/A"), year(0), rentalRatePerDay(0.0), isRented(false),
plateNumber("N/A"), insuranceCost(0.0), mileage(0), MAX_RENTAL_DAYS(30) {
	carCount++; // Використання статичного поля (П. 3)
}

// 1.2. Конструктор з 8 параметрами (Основний). (П. 1, П. 7)
Car::Car(string mk, string md, int yr, double rate, string plate, double insurance, int mil, bool rented)
	: make(mk), model(md), year(yr), rentalRatePerDay(rate), isRented(rented),
	plateNumber(plate), insuranceCost(insurance), mileage(mil), MAX_RENTAL_DAYS(14) {
	carCount++; // Використання статичного поля (П. 3)
}

// 1.3. Конструктор копіювання. (П. 1, П. 7)
Car::Car(const Car& other)
	: make(other.make), model(other.model), year(other.year), rentalRatePerDay(other.rentalRatePerDay),
	isRented(other.isRented), plateNumber(other.plateNumber), insuranceCost(other.insuranceCost),
	mileage(other.mileage), MAX_RENTAL_DAYS(other.MAX_RENTAL_DAYS) {
	carCount++; // Використання статичного поля (П. 3)
}

// 2. Конструктор зі списком ініціалізації. Задання константного поля MAX_RENTAL_DAYS. (П. 2, П. 7)
Car::Car(string mk, string md, int maxDays)
	: make(mk), model(md), MAX_RENTAL_DAYS(maxDays), // Ініціалізація константи у списку (П. 2)
	year(2025), rentalRatePerDay(150.0), isRented(false),
	plateNumber("NEW"), insuranceCost(30.0), mileage(0) {
	carCount++; // Використання статичного поля (П. 3)
}

// Оператор присвоєння копіювання 
Car& Car::operator=(const Car& other) {
	if (this != &other) {
		make = other.make;
		model = other.model;
		year = other.year;
		rentalRatePerDay = other.rentalRatePerDay;
		isRented = other.isRented;
		plateNumber = other.plateNumber;
		insuranceCost = other.insuranceCost;
		mileage = other.mileage;
	}
	return *this;
}

// 3. СТАТИЧНИЙ МЕТОД

// 3. Статичний метод для демонстрації статичного поля carCount. (П. 3)
void Car::displayTotalCarCount() {
	cout << "\n[Static Method] Total number of Car objects in existence: " << carCount << endl; // Використання статичного поля (П. 3)
}


void Car::displayCarInfo() const {
	cout << "--- Car Information ---" << endl;
	cout << "Max Rental Days: " << MAX_RENTAL_DAYS << " days (Constant Field)" << endl; // Використання константного поля (П. 2)
	cout << "Make/Model: " << make << " " << model << " (" << year << ")" << endl;
	cout << "Plate Number: " << plateNumber << endl;
	cout << "Rate per day: $" << rentalRatePerDay << endl;
	cout << "Insurance Cost: $" << insuranceCost << endl;
	cout << "Current Mileage: " << mileage << " km" << endl;
	cout << "Status: " << (isRented ? "Rented" : "Available") << endl;
}

double Car::calculateTotalRent(int days) const {
	return days * rentalRatePerDay;
}

double Car::calculateTotalRent(int days, bool withInsurance) const {
	double total = days * rentalRatePerDay;
	if (withInsurance) {
		total += insuranceCost;
		cout << "Insurance option added. Total: $" << total << endl;
	}
	return total;
}

void Car::rentOut() {
	if (!isRented) {
		isRented = true;
		cout << "Car " << plateNumber << " is now rented." << endl;
	}
	else {
		cout << "Car " << plateNumber << " is already rented." << endl;
	}
}

Car Car::returnCar(int newMileage, const Car& damagedCar) {
	cout << "Car " << plateNumber << " returned. Old Mileage: " << mileage << ". New Mileage: " << newMileage << endl;
	mileage = newMileage;
	isRented = false;

	if (damagedCar.getMake() != "N/A") {
		cout << "Note: Damage reported, administrative action required." << endl;
		return damagedCar;
	}
	return Car();
}

bool Car::checkAvailability() const {
	return !isRented;
}

void Car::writeToFile(const string& filename) const {
	ofstream outFile(filename);
	if (outFile.is_open()) {
		outFile << make << "," << model << "," << year << "," << rentalRatePerDay << ","
			<< plateNumber << "," << insuranceCost << "," << mileage << "," << isRented << ","
			<< MAX_RENTAL_DAYS << "\n";
		outFile.close();
		cout << "Car data written to " << filename << endl;
	}
	else {
		cerr << "Unable to open file " << filename << endl;
	}
}

void Car::readFromFile(const string& filename) {
	ifstream inFile(filename);
	if (inFile.is_open()) {
		string line;
		if (getline(inFile, line)) {
			stringstream ss(line);
			string token;

			// Читаємо поля
			getline(ss, token, ','); make = token;
			getline(ss, token, ','); model = token;
			getline(ss, token, ','); year = stoi(token);
			getline(ss, token, ','); rentalRatePerDay = stod(token);
			getline(ss, token, ','); plateNumber = token;
			getline(ss, token, ','); insuranceCost = stod(token);
			getline(ss, token, ','); mileage = stoi(token);
			getline(ss, token, ','); isRented = (token == "1" || token == "1\n");
			getline(ss, token, ','); // Пропускаємо MAX_RENTAL_DAYS

			cout << "Car data read from file and updated. Plate: " << plateNumber << endl;
		}
		else {
			cout << "File " << filename << " is empty or data format is incorrect." << endl;
		}

		inFile.close();
	}
	else {
		cerr << "Unable to open file " << filename << endl;
	}
}

void Car::allocateAndSortMileage() {
	srand(time(0));
	int count = 5;
	int* mileageHistory = new int[count];

	cout << "--- Dynamic Memory Allocation & Sorting (Car) ---" << endl;
	cout << "Original mileage: " << mileage << " km. Generating " << count << " random historical values..." << endl;

	mileageHistory[0] = mileage;
	for (int i = 1; i < count; ++i) {
		mileageHistory[i] = (rand() % 100000) + 1000;
	}

	cout << "Before sorting: ";
	for (int i = 0; i < count; ++i) cout << mileageHistory[i] << (i == count - 1 ? "" : ", ");
	cout << endl;

	sort(mileageHistory, mileageHistory + count);

	cout << "After sorting: ";
	for (int i = 0; i < count; ++i) cout << mileageHistory[i] << (i == count - 1 ? "" : ", ");
	cout << endl;

	delete[] mileageHistory;
	mileageHistory = nullptr;
}


// 4, 5. ЗОВНІШНІ ФУНКЦІЇ

// 5. Функція, що повертає об'єкт класу Car. (П. 5)
Car createDamageReport(const Car& initialCar) {
	cout << "\n[Function Returns Object] Generating damage report for: " << initialCar.getMake() << endl;
	Car report("Report", "Damage", 2025, 0.0, "DAMAGE", 0.0, initialCar.mileage, false);
	return report;
}

// 4. Зовнішня функція, що приймає об'єкт Car та здійснює обчислення. (П. 4)
void calculateCarProfitEstimate(const Car& car) {
	double potentialProfit = car.getRentalRate() * car.getMAX_RENTAL_DAYS() + car.insuranceCost;
	cout << "\n[External Function] Profit Estimate for " << car.getMake() << " " << car.getModel()
		<< " (over Max Days): $" << potentialProfit << endl;
}