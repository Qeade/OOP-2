#include "BaseVehicle.h"
#include "Car.h"
#include "Contracts.h"
#include "Client.h"
#include <iostream>

using namespace std;

int main() {


    cout << "---Demonstration Start---" << endl;

    // 2. Демонстрація керування доступом (BaseVehicle)
    cout << "\n--- (N. 2) Access Control Demo (BaseVehicle) ---" << endl;
    BaseVehicle base("Toyota", "Camry", 2021, 50.0, "AA1234AA", "VIN-TOYOTA");

    // 2. Доступ до public (OK)
    cout << "[Main] Accessing public data (publicVIN): " << base.publicVIN << " (OK)" << endl;
    base.publicMethod();

    // 2. Доступ до protected та private неможливий
    cout << "[Main] Accessing protected/private data: (Access Denied)" << endl;

    // 2. Демонстрація доступу зсередини класу (викликає private/protected)
    base.demoInternalAccess();

    // 1, 5, 6, 7. Демонстрація простого наслідування (Car)
    cout << "\n--- (N. 1, 5, 6, 7) Simple Inheritance Demo (Car) ---" << endl;

    // 5 & 7. Створення об'єкта похідного класу (виклик конструкторів BaseVehicle -> Car)
    Car myCar("BMW", "X5", 2023, 120.0, "KA0001KA", "VIN-BMW", 75.0, 5000); // 5. Передача 5+ аргументів

    // 2 & 6. Демонстрація доступу з похідного класу
    myCar.demoDerivedAccess();

    // 6. Демонстрація доступу через 'using'
    cout << "[Main] Accessing 'using' promoted method (N. 6):" << endl;
    myCar.protectedMethod();

    // 3. Демонстрація private наслідування (CommercialTruck)
    cout << "\n--- (N. 3, 6) Private Inheritance Demo (CommercialTruck) ---" << endl;
    // 3. Створення об'єкта (виклик конструкторів BaseVehicle -> CommercialTruck)
    CommercialTruck truck("Volvo", "VNL", 2020, 200.0, "AE5555AE", "VIN-VOLVO");

    // 3. Доступ до public методів BaseVehicle (Неможливий через private наслідування)
    cout << "[Main] Accessing base public method: (Access Denied due to Private Inheritance)" << endl;

    // 3. Демонстрація роботи об'єкта, що оперує методами ієрархії
    truck.showVehicleInfo(); // 3. Об'єкт, що оперує методами з різних класів ієрархії

    // 4 & 5. Демонстрація зовнішніх функцій

    // 4. Виклик зовнішньої функції (N. 4)
    calculateCarEstimate(myCar);

    // 5. Виклик функції, що повертає об'єкт (N. 5)
    Car demo = createDemoCar();
    cout << "[Main] Received car from external function: " << demo.plateNumber << endl;

    // 4, 7, 8. Демонстрація множинного наслідування та Сценарію
    cout << "\n--- (N. 4, 7, 8) Multiple Inheritance & Scenario Demo ---" << endl;

    // 8. Створення об'єкта Client
    Client client("Ivan Ivanenko", "PASSPORT_123456", 7);

    // 4 & 7. Створення об'єкта множинного наслідування (N. 4, 7)
    RentalAgreement agreement(
        "Mercedes", "S-Class", 2024, 250.0, "II0001II", "VIN-MERC", 100.0, 100,
        500.0, // InsurancePolicy
        0.0, // FineController
        client.getPassportData(), client.getRentalTerm());

    // 8. Сценарій функціонування системи: Клієнт взаємодіє з Договором
    client.fillOrder(agreement);
    client.payOrder(agreement);
    client.cancelOrder(agreement); // Скасування для демонстрації штрафу

    agreement.showFullAgreement(); // 8. Фінальний стан

    // 6. Демонстрація розміщення об'єктів у статичній та динамічній пам'яті (N. 6)
    cout << "\n--- (N. 6) Memory Allocation Demo ---" << endl;
    Car staticCar; // 6. Статична пам'ять
    Car* dynamicCar = new Car(); // 6. Динамічна пам'ять

    // 6. Визначення покажчика на екземпляр класу (N. 6)
    Car* carPtr = &staticCar;
    carPtr->publicMethod();

    delete dynamicCar; // 6. Очищення динамічної пам'яті

    // 7. Демонстрація порядку виклику деструкторів (відбудеться автоматично)
    cout << "\n--- Demo End (Destructors will be called) ---" << endl;

    return 0;
}