#include "Client.h"
#include "Car.h"
#include <iomanip>
#include <limits> 
#include <algorithm> 


Car car_pool[5] = {
    {"Toyota", "Camry", 2020, 50.0, "AA1234AA", 10.0, 5000, false},
    {"Honda", "Civic", 2018, 40.0, "BB5678BB", 8.0, 7000, false},
    {"BMW", "X5", 2022, 120.0, "CC9012CC", 25.0, 2000, false},
    {"Tesla", "Model 3", 2023, 100.0, "DD3456DD", 20.0, 1000, false},
    {"Ford", "Focus", 2017, 35.0, "EE7890EE", 7.0, 15000, true} 
};

Client client_registry[2] = {
    {"Ivanenko I.I.", "i.ivan@mail.com", "AB123456", "0987654321", 500.0},
    {"Petrov P.P.", "p.petrov@mail.com", "CD654321", "0971234567", 100.0}
};

Client* dynamic_client = new Client("Olenko O.O.", "o.olen@mail.com", "EF987654", "0501112233", 800.0);
Car* dynamic_car_array = new Car[3]{
    Car("Fiat", "Punto", 2016, 30.0, "OP1212OP", 5.0, 20000),
    Car("Lexus", "RX", 2021, 150.0, "QR3434QR", 30.0, 3000),
    Car("Skoda", "Octavia", 2019, 60.0, "ST5656ST", 12.0, 10000)
};

void sectionSeparator(const string& title) {
    cout << "\n========================================================" << endl;
    cout << "|| " << title << " ||" << endl;
    cout << "========================================================" << endl;
}

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


Car& selectCar(int& index) {
    int choice;
    const int CAR_COUNT = sizeof(car_pool) / sizeof(Car);

    cout << "\n--- Available Cars ---" << endl;
    for (int i = 0; i < CAR_COUNT; ++i) {
        cout << i + 1 << ". " << car_pool[i].getMake() << " " << car_pool[i].getModel()
            << " (" << car_pool[i].plateNumber << ") - Status: " << (car_pool[i].getIsRented() ? "Rented" : "Available") << endl;
    }

    while (true) {
        cout << "Enter the number of the car to select (1-" << CAR_COUNT << "): ";
        if (cin >> choice && choice >= 1 && choice <= CAR_COUNT) {
            clearInputBuffer();
            index = choice - 1;
            return car_pool[choice - 1];
        }
        else {
            cout << "Invalid selection. Please try again." << endl;
            cin.clear();
            clearInputBuffer();
        }
    }
}


Client& selectClient(int& index) {
    int choice;
    const int CLIENT_COUNT = sizeof(client_registry) / sizeof(Client);

    cout << "\n--- Registered Clients ---" << endl;
    for (int i = 0; i < CLIENT_COUNT; ++i) {
        cout << i + 1 << ". " << client_registry[i].fullName << endl;
    }

    while (true) {
        cout << "Enter the number of the client to select (1-" << CLIENT_COUNT << "): ";
        if (cin >> choice && choice >= 1 && choice <= CLIENT_COUNT) {
            clearInputBuffer();
            index = choice - 1;
            return client_registry[choice - 1];
        }
        else {
            cout << "Invalid selection. Please try again." << endl;
            cin.clear();
            clearInputBuffer();
        }
    }
}


void carMethodsDemo() {
    sectionSeparator("2. CAR METHODS DEMONSTRATION");
    int carIndex;
    Car& selectedCar = selectCar(carIndex);

    cout << "\nSelected Car: " << selectedCar.plateNumber << " (" << selectedCar.getMake() << " " << selectedCar.getModel() << ")" << endl;

    selectedCar.displayCarInfo();

    cout << "\n[M2] Total rent for 5 days (No Insurance): $" << selectedCar.calculateTotalRent(5) << endl;

    cout << "[M3] Total rent for 5 days (WITH Insurance): $" << selectedCar.calculateTotalRent(5, true) << endl;

    selectedCar.rentOut();

    Car damagePlaceholder("Placeholder", "Damage", 0, 0.0);
    Car damageReport = selectedCar.returnCar(selectedCar.mileage + 100, damagePlaceholder);
    if (damageReport.getMake() != "N/A") {
        cout << "\n[M5] Car returned. Damage reported: " << damageReport.getModel() << endl;
    }

    cout << "[M6] Car is available: " << (selectedCar.checkAvailability() ? "Yes" : "No") << endl;

    cout << "\n[File I/O] Writing car data to file..." << endl;
    selectedCar.writeToFile("car_data_demo.txt");

    Car carRead;
    carRead.readFromFile("car_data_demo.txt");
    cout << "[File I/O] Data read. New car state:" << endl;
    carRead.displayCarInfo();
}


void clientMethodsDemo() {
    sectionSeparator("3. CLIENT METHODS DEMONSTRATION");
    int clientIndex;
    Client& selectedClient = selectClient(clientIndex);
    Car demoCar = car_pool[0]; 

    cout << "\nSelected Client: " << selectedClient.fullName << endl;

    selectedClient.displayClientInfo();

    cout << "\n[M2] Client requesting 4-day rental for " << demoCar.plateNumber << endl;
    selectedClient.requestRental(demoCar, 4);

    Car demoCar2 = car_pool[1]; 
    cout << "[M3] Client requesting default 7-day rental for " << demoCar2.plateNumber << endl;
    selectedClient.requestRental(demoCar2);
    selectedClient.cancelRental("Changed mind after default request."); 

    cout << "\n[M6] Applying a $5 fine (Expired ID check)." << endl;
    selectedClient.applyFine(5.0);

    cout << "\n[File I/O] Writing client data to file..." << endl;
    selectedClient.writeToFile("client_data_demo.txt");

    Client clientRead;
    clientRead.readFromFile("client_data_demo.txt");
    cout << "[File I/O] Data read. New client state:" << endl;
    clientRead.displayClientInfo();
}


void interactionScenario() {
    sectionSeparator("4. INTERACTION SCENARIO: CLIENT RENTS A CAR (P. 10)");

    int clientIndex, carIndex;

    cout << "--- Selecting Client for Rental ---" << endl;
    Client& rentClient = selectClient(clientIndex);

    cout << "--- Selecting Car for Rental ---" << endl;
    Car& carToRent = selectCar(carIndex);

    if (carToRent.getIsRented()) {
        cout << "\nERROR: Car " << carToRent.plateNumber << " is currently rented. Cannot proceed with this car." << endl;
        return;
    }

    int rentalDays;
    cout << "Enter rental duration in days: ";
    if (!(cin >> rentalDays)) {
        cout << "Invalid input for days." << endl;
        cin.clear(); clearInputBuffer(); return;
    }
    clearInputBuffer();

    int insuranceChoice;
    cout << "Add insurance? (1 for Yes / 0 for No): ";
    if (!(cin >> insuranceChoice) || (insuranceChoice != 0 && insuranceChoice != 1)) {
        cout << "Invalid insurance choice." << endl;
        cin.clear(); clearInputBuffer(); return;
    }
    clearInputBuffer();
    bool withInsurance = (insuranceChoice == 1);

    double calculatedCost = carToRent.calculateTotalRent(rentalDays, withInsurance);

    cout << "\n" << rentClient.fullName << " is attempting to rent " << carToRent.plateNumber << " for " << rentalDays << " days." << endl;

    rentClient.requestRental(carToRent, rentalDays);
    cout << "Total Cost: $" << calculatedCost << endl;

    Client approvedClient = rentClient.approveRental(calculatedCost);

    if (approvedClient.getHasActiveRental()) {
        carToRent.rentOut();

        approvedClient.rentedCar = carToRent;

        client_registry[clientIndex] = approvedClient;

        cout << "\nSUCCESS: Rental completed." << endl;
        client_registry[clientIndex].displayClientInfo();
    }
    else {
        cout << "\nFAILURE: Rental was not approved (Insufficient funds or Admin rejection)." << endl;
    }
}

void dynamicMemoryDemo() {
    sectionSeparator("5. DYNAMIC MEMORY AND POINTER DEMONSTRATION (P. 6, 7, 11, 12)");

    cout << "\n[P. 11] Pointer to Client Instance:" << endl;
    Client* activeClientPtr = dynamic_client;
    cout << "Dynamically created client: " << activeClientPtr->fullName << endl;
    cout << "Checking balance via pointer: $" << activeClientPtr->getCurrentBalance() << endl;

    cout << "\n[P. 7 & 8] Dynamic Array of Car Objects:" << endl;
    cout << "Second car in dynamic array: " << dynamic_car_array[1].plateNumber << endl;
    dynamic_car_array[1].rentOut(); 
    dynamic_car_array[1].displayCarInfo();

    cout << "\n[P. 12] Dynamic Memory Allocation & Sorting:" << endl;
    car_pool[0].allocateAndSortMileage(); 
    dynamic_client->allocateAndSortDuration(); 
}

void showMainMenu() {
    sectionSeparator("MAIN MENU (C++ RENTAL SYSTEM DEMO)");
    cout << "1. Display All Objects (Static/Array)" << endl;
    cout << "2. Demonstrate Car Methods (Interactive Selection)" << endl;
    cout << "3. Demonstrate Client Methods (Interactive Selection)" << endl;
    cout << "4. SCENARIO: Client Rents a Car (Interactive Interaction)" << endl;
    cout << "5. Dynamic Memory and Pointer Demonstration (Pointers/Arrays/Sorting)" << endl;
    cout << "0. Exit Program and Cleanup Dynamic Memory" << endl;
    cout << "Enter your choice: ";
}


int main() {
    int choice;

    do {
        showMainMenu();
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            clearInputBuffer();
            continue;
        }
        clearInputBuffer(); 

        switch (choice) {
        case 1:
            sectionSeparator("1. DISPLAY ALL OBJECTS (STATIC/ARRAY)");
            cout << "\n--- Static Car Pool ---" << endl;
            for (int i = 0; i < 5; ++i) {
                cout << i + 1 << ". ";
                car_pool[i].displayCarInfo();
            }
            cout << "\n--- Static Client Registry (Array) ---" << endl;
            for (int i = 0; i < 2; ++i) {
                cout << i + 1 << ". ";
                client_registry[i].displayClientInfo();
            }
            break;
        case 2:
            carMethodsDemo();
            break;
        case 3:
            clientMethodsDemo();
            break;
        case 4:
            interactionScenario();
            break;
        case 5:
            dynamicMemoryDemo();
            break;
        case 0:
            cout << "\nExiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please select an option from the menu." << endl;
            break;
        }
    } while (choice != 0);

    cout << "\nCleaning up dynamic memory (Client, Car Array)..." << endl;
    delete dynamic_client;
    delete[] dynamic_car_array;

    return 0;
}