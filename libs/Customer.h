#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "List.h"
#include "Account.h"
#include "TextFileHandler.h"
#include "Transaction.h"

using namespace std;

struct Customer {
    string id;
    string name;
    List<Account> accounts;
};

List<Customer> getCustomersFromLines(List<string>& lines) {
    
    int numberOfCustomers = stoi(lines.get(0));

    List<Customer> customers;

    int lineIndex = 1;

    while (lineIndex < lines.size) {
        Customer customer;
        customer.id = lines.get(lineIndex);
        customer.name = lines.get(lineIndex + 1);
        
        int numberOfAccounts = stoi(lines.get(lineIndex + 2));

        lineIndex += 3;

        for (int i = 0; i < numberOfAccounts; i++) {
            Account account;
            account.id = lines.get(lineIndex);
            account.type = lines.get(lineIndex + 1)[0];

            int numberOfTransactions = stoi(lines.get(lineIndex + 2));

            lineIndex += 3;

            for (int j = 0; j < numberOfTransactions; j++) {
                Transaction transaction;
                transaction.type = lines.get(lineIndex)[0];
                transaction.amount = stol(lines.get(lineIndex + 1));
                account.transactions.add(transaction);
                lineIndex += 2;
            }

            customer.accounts.add(account);
        }

        customers.add(customer);
    }
    return customers;
}

List<Customer> readCustomersFromEntryPoint(string path) {
    TextFileHandler entryPointHandler(path);
    List<string> lines = entryPointHandler.readLines();
    return getCustomersFromLines(lines);
}


#endif