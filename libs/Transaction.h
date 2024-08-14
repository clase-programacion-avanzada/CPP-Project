#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

using namespace std;

struct Transaction {
    char type;
    unsigned long int amount;
};

#endif