#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct {
    int transID;          // Transaction ID
    char type[20];        // Transaction type (e.g., deposit, withdrawal, transfer)
    int accountIDSrc;     // Source account ID for transfer transactions
    int accountIDDst;     // Destination account ID for transfer transactions
    double amount;        // Transaction amount
    int accountNumber;    // Account number associated with the transaction
} Transaction;

#endif




