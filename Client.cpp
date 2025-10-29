#include "Client.h"
#include <sstream>

// 3. Ініціалізація статичного поля (забезпечення спільного використання)
int Client::clientCount = 0;

// 1, 2, 7. КОНСТРУКТОРИ ТА ОПЕРАТОР ПРИСВОЄННЯ

// 1.1. Конструктор без параметрів. (П. 1, П. 7)
Client::Client()
	: fullName("N/A"), email("N/A"), rentedCar(Car()), passportID("000000"), phoneNumber("N/A"),
	currentBalance(0.0), hasActiveRental(false), rentalDurationDays(0), refPassportID(passportID) {
	clientCount++; // Використання статичного поля (П. 3)
}

// 1.2. Конструктор з 8 параметрами. (П. 1, П. 7)
Client::Client(string fn, string mail, string passID, string phone, double balance, bool active, int days, const Car& car)
	: fullName(fn), email(mail), rentedCar(car), passportID(passID), phoneNumber(phone),
	currentBalance(balance), hasActiveRental(active), rentalDurationDays(days), refPassportID(passportID) {
	clientCount++; // Використання статичного поля (П. 3)
}

// 1.3. Конструктор копіювання. (П. 1, П. 7)
Client::Client(const Client& other)
	: fullName(other.fullName), email(other.email), rentedCar(other.rentedCar), passportID(other.passportID),
	phoneNumber(other.phoneNumber), currentBalance(other.currentBalance), hasActiveRental(other.hasActiveRental),
	rentalDurationDays(other.rentalDurationDays), refPassportID(passportID) {
	clientCount++; // Використання статичного поля (П. 3)
}

// 2. Конструктор зі списком ініціалізації (для поля-посилання). Задання посилання. (П. 2, П. 7)
Client::Client(string fn, string passID, const string& passportReference)
	: fullName(fn), passportID(passID), refPassportID(passportReference), // Ініціалізація посилання у списку (П. 2)
	email("unknown"), phoneNumber("unknown"), currentBalance(100.0),
	hasActiveRental(false), rentalDurationDays(0), rentedCar(Car()) {
	clientCount++; // Використання статичного поля (П. 3)
}

// Оператор присвоєння копіювання 
Client& Client::operator=(const Client& other) {
	if (this != &other) {
		passportID = other.passportID;
		phoneNumber = other.phoneNumber;
		currentBalance = other.currentBalance;
		hasActiveRental = other.hasActiveRental;
		rentalDurationDays = other.rentalDurationDays;
		fullName = other.fullName;
		email = other.email;
		rentedCar = other.rentedCar; 

	}
	return *this;
}

// 3. СТАТИЧНИЙ МЕТОД

// 3. Статичний метод для демонстрації статичного поля clientCount. (П. 3)
void Client::displayTotalClientCount() {
	cout << "\n[Static Method] Total number of Client objects in existence: " << clientCount << endl; // Використання статичного поля (П. 3)
}



void Client::displayClientInfo() const {
	cout << "--- Client Information ---" << endl;
	cout << "Reference Passport ID: " << refPassportID << " (Reference Field)" << endl; // Використання поля-посилання (П. 2)
	cout << "Name: " << fullName << endl;
	cout << "Email: " << email << endl;
	cout << "Phone: " << phoneNumber << endl;
	cout << "Passport ID (Hidden): " << passportID.substr(0, 4) << "..." << endl;
	cout << "Balance: $" << currentBalance << endl;
	cout << "Active Rental: " << (hasActiveRental ? "YES" : "NO") << endl;
	if (hasActiveRental) {
		cout << "Duration: " << rentalDurationDays << " days." << endl;
		rentedCar.displayCarInfo();
	}
}

void Client::requestRental(const Car& carToRent, int days) {
	cout << fullName << " is requesting car " << carToRent.getMake() << " " << carToRent.getModel()
		<< " for " << days << " days using ID: " << passportID.substr(0, 4) << "..." << endl;
	if (!carToRent.getIsRented()) {
		rentalDurationDays = days;
		rentedCar = carToRent;
		cout << "Request submitted. Awaiting administrator approval." << endl;
	}
	else {
		cout << "ERROR: Car is not available for rent." << endl;
	}
}

void Client::requestRental(const Car& carToRent) {
	requestRental(carToRent, 7);
}

Client Client::approveRental(double totalCost) {
	cout << "Administrator approving rental for " << fullName << "." << endl;

	if (currentBalance >= totalCost) {
		currentBalance -= totalCost;
		hasActiveRental = true;
		cout << "Rental approved and paid ($" << totalCost << "). New balance: $" << currentBalance << endl;
		return *this; 
	}
	else {
		cout << "ERROR: Insufficient funds. Balance: $" << currentBalance << ". Required: $" << totalCost << endl;
		return Client();
	}
}

void Client::cancelRental(const string& reason) {
	if (!hasActiveRental) {
		cout << fullName << " cancelled the request. Reason: " << reason << endl;
		rentedCar = Car();
		rentalDurationDays = 0;
	}
	else {
		cout << "Cannot cancel. Rental is active." << endl;
	}
}

void Client::applyFine(double fineAmount) {
	currentBalance -= fineAmount;
	cout << "Fine of $" << fineAmount << " applied to " << fullName << ". New balance: $" << currentBalance << endl;
}

void Client::writeToFile(const string& filename) const {
	ofstream outFile(filename);
	if (outFile.is_open()) {
		outFile << fullName << "," << email << "," << passportID << "," << phoneNumber << ","
			<< currentBalance << "," << hasActiveRental << "," << rentalDurationDays << "\n";
		outFile.close();
		cout << "Client data written to " << filename << endl;
	}
	else {
		cerr << "Unable to open file " << filename << endl;
	}
}

void Client::readFromFile(const string& filename) {
	ifstream inFile(filename);
	if (inFile.is_open()) {
		string line;
		if (getline(inFile, line)) {
			stringstream ss(line);
			string token;

			getline(ss, token, ','); fullName = token;
			getline(ss, token, ','); email = token;
			getline(ss, token, ','); passportID = token;
			getline(ss, token, ','); phoneNumber = token;
			getline(ss, token, ','); currentBalance = stod(token);
			getline(ss, token, ','); hasActiveRental = (token == "1" || token == "1\n");
			getline(ss, token, ','); rentalDurationDays = stoi(token);

			cout << "Client data read from file and updated. Name: " << fullName << endl;
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

void Client::allocateAndSortDuration() {
	srand(time(0));
	int count = 5;
	int* durationHistory = new int[count];

	cout << "--- Dynamic Memory Allocation & Sorting (Client) ---" << endl;
	cout << "Current rental duration: " << rentalDurationDays << " days. Generating " << count << " random historical values..." << endl;

	durationHistory[0] = rentalDurationDays;
	for (int i = 1; i < count; ++i) {
		durationHistory[i] = (rand() % 30) + 1;
	}

	cout << "Before sorting: ";
	for (int i = 0; i < count; ++i) cout << durationHistory[i] << (i == count - 1 ? "" : ", ");
	cout << endl;

	sort(durationHistory, durationHistory + count);

	cout << "After sorting: ";
	for (int i = 0; i < count; ++i) cout << durationHistory[i] << (i == count - 1 ? "" : ", ");
	cout << endl;

	delete[] durationHistory;
	durationHistory = nullptr;
}


// 4, 5. ЗОВНІШНІ ФУНКЦІЇ

// 5. Функція, що повертає об'єкт класу Client. (П. 5)
Client createNewClient(string name, double balance) {
	Client newClient(name, "new@mail.com", "NEWID", "0000", balance, false, 0, Car());

	Car demoCar;
	newClient.requestRental(demoCar, 1);

	return newClient.approveRental(5.0); 
}

// 4. Зовнішня функція, що приймає об'єкт Client та здійснює обчислення. (П. 4)
void calculateClientNetWorth(const Client& client) {
	double netWorth = client.getCurrentBalance() + client.rentedCar.getRentalRate() * 100;
	cout << "\n[External Function] Net Worth Estimate for " << client.fullName
		<< ": $" << netWorth << endl;
}