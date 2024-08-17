#include <iostream>
#include "libs/List.h"
#include "libs/Customer.h"
#include "libs/BinaryFileHandler.h"
#include "libs/TextFileHandler.h"

using namespace std;


void printMenu();
void printCustomers(List<Customer> customers);

int main() {
    
    string customersBinaryFileName = "customers.hbt";

    string loadingFromMessage = binaryFileExists(customersBinaryFileName) 
        ? "Cargando clientes desde archivo .hbt..." 
        : "Cargando clientes desde entry_point.txt...";

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
                cout << "Opción 1 no implementada aún.\n";
                break;
            case 2:
                // Code for option 2
                cout << "Opción 2 no implementada aún.\n";
                break;
            case 3:
                // Code for option 3
                cout << "Opción 3 no implementada aún.\n";
                break;

            case 4:
                // Code for option 4
                cout << "Opcción 4 no implementada aún.\n";
                break;
            case 5:
                printCustomers(customers);
                break;
            case 0:
                // Exit the program
                cout << "Exiting...\n";
                break;
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
                break;
        }
        
        cout << "\n";
    } while (choice != 0);
    
    return 0;
}

void printMenu() {
            cout << "==========HellBank==========\n";
            cout << "1. Mostrar la sumatoria de transacciones, de acuerdo al tipo, de un cliente \n";
            cout << "2. Mostrar el saldo de una cuenta \n";
            cout << "3. Exportar reporte\n";
            cout << "4. Guardar archivo .hbt\n";
            cout << "5. Mostrar todos los clientes \n";
            cout << "0. Exit\n";
            cout << "Ingresa la opción deseada: ";
}

void printCustomers(List<Customer> customers) {
    
    cout << "Clientes: " << customers.size << endl;
    for (int i = 0; i < customers.size; i++) {
        cout << "Cliente: " << endl;
        Customer customer = customers.get(i);
        cout << "  ID: " << customer.id << endl;
        cout << "  Nombre: " << customer.name << endl;
        cout << "    Cuentas: " << customer.accounts.size << endl;

        for (int j = 0; j < customer.accounts.size; j++) {
            Account account = customer.accounts.get(j);
            cout << "    Cuenta: " << endl;
            cout << "      ID: " << account.id << endl;
            string type = account.type == 'A' ? "Ahorros" : "Corriente";
            cout << "      Tipo: " << type << endl;
            cout << "      Transacciones: " << account.transactions.size << endl << endl;
        
            for (int k = 0; k < account.transactions.size; k++) {
                Transaction transaction = account.transactions.get(k);

                string type = transaction.type == 'D' ? "Débito" : "Crédito";
                cout << "      Transacción: " << endl;
                cout << "        Tipo: " << type << endl;
                cout << "        Monto: " << transaction.amount << endl;
            }
        }
    }
}
