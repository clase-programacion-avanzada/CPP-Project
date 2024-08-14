#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "List.h"
#include "Transaction.h"

using namespace std;

struct Account {
    string id;
    char type; // Can be 'A' or 'C'
    List<Transaction> transactions;
};


#endif