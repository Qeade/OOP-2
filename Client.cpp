#include "Client.h"
#include <sstream>

Client::Client(string fn, string mail, string passID, string phone, double balance, bool active, int days, const Car& car)
    : fullName(fn), email(mail), rentedCar(car), passportID(passID), phoneNumber(phone),
    currentBalance(balance), hasActiveRental(active), rentalDurationDays(days) {
}

void Client::displayClientInfo() const {
    cout << "--- Client Information ---" << endl;
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

// Method 5
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

// Method 6
void Client::applyFine(double fineAmount) {
    currentBalance -= fineAmount;
    cout << "Fine of $" << fineAmount << " applied to " << fullName << ". New balance: $" << currentBalance << endl;
}

// File I/O (5)
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

// Dynamic Memory Method (12)
void Client::allocateAndSortDuration() {
    srand(time(0));
    int count = 5;
    int* durationHistory = new int[count];

    cout << "--- Dynamic Memory Allocation & Sorting (Client) ---" << endl;
    cout << "Current rental duration: " << rentalDurationDays << " days. Generating " << count << " random historical values..." << endl;

    durationHistory[0] = rentalDurationDays;
    for (int i = 1; i < count; ++i) {
        durationHistory[i] = (rand() % 30) + 1; // Random duration
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