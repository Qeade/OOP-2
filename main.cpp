#include <iostream>
#include "CarRental.h"

using namespace std;

int main() {
    RentalSystem agency;

    cout << "=== STL VECTOR OPERATIONS ===" << endl;

    // 1. push_back: Наповнення автопарку
    cout << "\n[1] Populating Fleet (push_back)..." << endl;
    agency.addCar(new EconomyCar("Ford Fiesta", 30.0));      
    agency.addCar(new SUV("Jeep Wrangler", 90.0));         
    agency.addCar(new LuxuryCar("BMW 7 Series", 220.0));    
    agency.showFleet();

    // 2. insert: Вставка VIP авто на початок
    cout << "\n[2] Adding VIP Car (insert at begin)..." << endl;
    agency.addVipCarFront(new LuxuryCar("ROLLS ROYCE PHANTOM", 500.0));
    // Тепер Rolls Royce = Index 0, всі інші зсунулись
    agency.showFleet();

    // 3. erase: Видалення авто (наприклад, BMW, яка тепер має індекс 3)
    cout << "\n[3] Removing Car (erase index 3)..." << endl;
    agency.removeCar(3);
    agency.showFleet();

    // 4. Створення замовлень
    cout << "\n[4] Creating Orders..." << endl;
    agency.createOrder(0, "Mr. Rich", "VIP001", 1, true);   
    agency.createOrder(1, "John Doe", "US123", 5, false);    

    // 5. Демонстрація операторів ++/-- 
    cout << "\n[5] Modifying Order using Operators..." << endl;
    Order& currentOrder = agency.getLastOrder(); 

    cout << "Before extension:";
    currentOrder.showStatus();

    cout << "Extending by 1 day (++order)..." << endl;
    ++currentOrder;

    cout << "After extension: ";
    currentOrder.showStatus();

    // 6. pop_back: Скасування останнього замовлення
    cout << "\n[6] Canceling last order (pop_back)..." << endl;
    agency.showOrdersHistory(); 
    agency.removeLastOrder();   
    agency.showOrdersHistory(); 


    return 0;
}