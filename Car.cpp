#include "Car.h"
#include <sstream>
Car::Car(string mk, string md, int yr, double rate, string plate, double insurance, int mil, bool rented)
    : make(mk), model(md), year(yr), rentalRatePerDay(rate), isRented(rented),
    plateNumber(plate), insuranceCost(insurance), mileage(mil) {
}

void Car::displayCarInfo() const {
    cout << "Car Information " << endl;
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
            << plateNumber << "," << insuranceCost << "," << mileage << "," << isRented << "\n";
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

            getline(ss, token, ','); make = token;
            getline(ss, token, ','); model = token;
            getline(ss, token, ','); year = stoi(token);
            getline(ss, token, ','); rentalRatePerDay = stod(token);
            getline(ss, token, ','); plateNumber = token;
            getline(ss, token, ','); insuranceCost = stod(token);
            getline(ss, token, ','); mileage = stoi(token);
            getline(ss, token, ','); isRented = (token == "1" || token == "1\n");

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