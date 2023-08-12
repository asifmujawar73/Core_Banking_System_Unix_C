#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct {
    int accountNumber;        // Account number
    char type[50];            // Account type
    char customerID[50];      // Customer ID associated with the account
    char status[20];          // Account status (active, closed, etc.)
    double balance;           // Account balance
    char openingDate[50];    // Date when the account was opened
} Account;

#endif

