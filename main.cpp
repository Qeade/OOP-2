#include <iostream>
#include <vector>
#include "CarRental.h" 

using namespace std;

int main() {
    // 1. Створення об'єктів різних класів
    EconomyCar car1("Toyota Corolla", 40.0);
    SUV car2("Jeep Grand Cherokee", 80.0);
    LuxuryCar car3("Porsche Panamera", 250.0);

    cout << "=== DEMONSTRATION 1: POLYMORPHISM ===" << endl;
    // Використовуємо вказівник на базовий клас для демонстрації поліморфізму
    vector<Vehicle*> garage;
    garage.push_back(&car1);
    garage.push_back(&car2);
    garage.push_back(&car3);

    for (const auto& v : garage) {
        v->displayInfo(); // Викликається відповідний метод displayInfo
        // Виклик чисто віртуальної функції calculateTotal
        cout << "   -> Cost for 3 days with insurance: $" << v->calculateTotal(3, true) << endl;
    }
    cout << "====================================================\n" << endl;


    cout << "=== DEMONSTRATION 2: FULL SCENARIO ===" << endl;

    // Крок 1: Клієнт вибирає авто (наприклад, SUV)
    cout << "\n1. Client selects a car and fills the form..." << endl;
    // Створення замовлення: 5 днів, зі страховкою
    Order myOrder(&car2, "John Doe", "US123456", 5, true);
    myOrder.showStatus();

    // Крок 2: Спроба скасування (демо)
    // myOrder.cancelOrder("Changed my mind"); 

    // Крок 3: Адміністратор перевіряє
    cout << "\n2. Admin reviews the order..." << endl;
    myOrder.adminProcess(true); // Схвалено

    // Крок 4: Клієнт оплачує
    cout << "\n3. Client makes payment..." << endl;
    myOrder.payOrder();

    // Крок 5: Користування і повернення (з пошкодженням та запізненням)
    cout << "\n4. Returning the car..." << endl;

    // Адмін помітив пошкодження
    myOrder.addDamageFine(200.0);

    // Повернення із запізненням
    myOrder.returnCar(true);

    return 0;
}