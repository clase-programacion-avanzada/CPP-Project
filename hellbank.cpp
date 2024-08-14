#include <iostream>
#include "libs/List.h"
#include "libs/Customer.h"
#include "libs/BinaryFileHandler.h"
#include "libs/TextFileHandler.h"

using namespace std;


void printMenu();

int main() {
    
    string customersBinaryFileName = "customers.hbt";

    string loadingFromMessage = binaryFileExists(customersBinaryFileName) 
        ? "Loading customers from binary file..." 
        : "Loading customers from entry point...";

    cout << loadingFromMessage << endl;
    
    List<Customer> customers = binaryFileExists(customersBinaryFileName)  
        ? List<Customer>() //readCustomersFromBinaryFile(customersBinaryFileName) <- implemente esta función luego de guardar el archivo .hbt
        : readCustomersFromEntryPoint("entry_point.txt");
    
    int choice;
   
    do {
        // Display menu options
        printMenu();
        cin >> choice;
        
        // Process user's choice
        switch (choice) {
            case 1:
                // Code for option 1
                cout << "Option 1 selected.\n";
                break;
            case 2:
                // Code for option 2
                cout << "Option 2 selected.\n";
                break;
            case 3:
                // Code for option 3
                cout << "Option 3 selected.\n";
                break;

            case 4:
                // Code for option 4
                cout << "Option 4 selected.\n";
                break;
            case 0:
                // Exit the program
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
        
        cout << "\n";
    } while (choice != 4);
    
    return 0;
}



void printMenu() {
            cout << "1. Mostrar la sumatoria de transacciones, de acuerdo al tipo, de un cliente \n";
            cout << "2. Mostrar el saldo de una cuenta \n";
            cout << "3. Exportar reporte\n";
            cout << "4. Guardar archivo .hbt\n";
            cout << "0. Exit\n";
            cout << "Ingresa la opción deseada: ";
}

