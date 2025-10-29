#include "BaseVehicle.h"
#include <iostream>

using namespace std;

// 5. Реалізація конструктора базового класу (з 6 параметрами)
BaseVehicle::BaseVehicle(string mk, string md, int yr, double rate, string plate, string vin)
    : internalID("ID_999"), maintenanceRecord("Clean"), // 2. Ініціалізація private/protected полів
    make(mk), model(md), year(yr), rentalRatePerDay(rate),
    plateNumber(plate), isRented(false), publicVIN(vin)
{
    // 7. Демонстрація порядку виклику конструкторів
    cout << "   BaseVehicle (Param) created." << endl;
}

// Реалізація конструктора за замовчуванням
BaseVehicle::BaseVehicle()
    : internalID("ID_000"), maintenanceRecord("N/A"),
    make("N/A"), model("N/A"), year(2000), rentalRatePerDay(0.0),
    plateNumber("N/A"), isRented(false), publicVIN("N/A")
{
    // 7. Демонстрація порядку виклику конструкторів
    cout << "   BaseVehicle (Default) created." << endl;
}

// 7. Реалізація деструктора
BaseVehicle::~BaseVehicle() {
    // 7. Демонстрація порядку виклику деструкторів
    cout << "  BaseVehicle Dtor BaseVehicle destroyed." << endl;
}

// 2. Реалізація private методу (Виправлення LNK2019)
void BaseVehicle::logInternal() const {
    cout << "  BaseVehicle Private logInternal() call OK." << endl;
}

// 2. Реалізація protected методу (П. 2)
void BaseVehicle::protectedMethod() const {
    cout << "  BaseVehicle Protected protectedMethod() call OK." << endl;
}

// 2. Реалізація public методу (П. 2)
void BaseVehicle::publicMethod() const {
    cout << "  BaseVehicle Public publicMethod() call OK." << endl;
}

// 2. Демонстрація керування доступом (зсередини класу)
void BaseVehicle::demoInternalAccess() const { // 2. Демонстрація доступу
    cout << "\nBaseVehicle Internal access check:" << endl;
    // Доступ до private, protected, public зсередини класу дозволено
    cout << "  Private data (internalID): " << internalID << " (OK)" << endl;
    logInternal();
    cout << "  Protected data (maintenanceRecord): " << maintenanceRecord << " (OK)" << endl;
    protectedMethod();
    cout << "  Public data (publicVIN): " << publicVIN << " (OK)" << endl;
    publicMethod();
}