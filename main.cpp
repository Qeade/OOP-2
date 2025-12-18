#include <iostream>
#include "CarRental.h"

using namespace std;

int main() {
    SUV myJeep("Jeep Wrangler", 100.0);
    Order order(&myJeep, "Alex Murphy", "AA000000", 3, true);

    cout << "=== INITIAL STATE ===" << endl;
    order.showStatus(); 

    cout << "\n=== TESTING PREFIX INCREMENT (++order) ===" << endl;
    cout << "Extending rental by 1 day..." << endl;
    ++order; 
    order.showStatus();

    cout << "\n=== TESTING POSTFIX INCREMENT (order++) ===" << endl;
    cout << "Extending rental by another day (saving old state)..." << endl;

    Order oldState = order++;

    cout << "Old State (copy): ";
    oldState.showStatus();

    cout << "Current State:    ";
    order.showStatus();

    cout << "\n=== TESTING DECREMENT (--order) ===" << endl;
    cout << "Reducing rental by 1 day..." << endl;
    --order; 
    order.showStatus();

    cout << "\n=== TESTING BOUNDARY (Try to reduce below 1) ===" << endl;
    Order shortOrder(&myJeep, "Test User", "000", 1, false);
    cout << "Short order created (1 day): ";
    shortOrder.showStatus();

    cout << "Trying to decrement 1-day order..." << endl;
    shortOrder--; 
    shortOrder.showStatus();

    return 0;
}