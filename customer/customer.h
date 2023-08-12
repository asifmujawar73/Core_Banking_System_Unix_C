#ifndef CUSTOMER_H
#define CUSTOMER_H

// Structure to represent customer information
typedef struct {
    char customerID[50];
    char name[100];
    char type[50];
    char address1[100];
    char address2[100];
    char address3[100];
    char city[50];
    char state[50];
    char country[50];
    char pinCode[20];
    char phoneNumber[20];
    char email[100];
    char pan[50];
} Customer;

// Function prototypes for customer operations

void customerMenu(char *);            // Function to view customer details
void viewCustomerDetails(char *);     // Function to transfer money from one account to another
void transferMoney(char *);           // Function to query and display customer information
void queryCustomer(char *);
void showDetails(char *);             // Helper function to display customer account and transaction details
#endif


