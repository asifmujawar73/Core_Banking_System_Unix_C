#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../data.h"

void customerMenu(char *customerID)
{
    int choice;
    do
    {
        // Displaying the customer menu

        printf("\n================= Customer Menu ====================\n");
        printf("1. View Customer Details\n");
        printf("2. Transer Money\n");
        printf("3. Query/Report on account details and tansactions.\n");
        printf("4. Logout\n");
        printf("5. Quit Application");
        printf("\n===================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        // Call the function to view customer details
            viewCustomerDetails(customerID);
            break;

        case 2:
        // Call the function to transfer money
            transferMoney(customerID);
            break;

        case 3:
        // Call the function for account queries/reports
            queryCustomer(customerID);
            break;

        case 4:
            printf("\nLogging Out...\n");
            break;
        case 5:
            printf("\nQuitting Application...");
            printf("\nThank you for using the Bank Management System. Visit Again!\n");
            exit(0);
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
            break;
        }
    } while (choice != 4);
}

void viewCustomerDetails(char *customerID)
{
    Customer customer;
    FILE *customerfile = fopen("customer.csv", "r");
    while (fscanf(customerfile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\n]\n", customer.customerID, customer.name, customer.type, customer.address1, customer.address2, customer.address3, customer.city, customer.state, customer.country, customer.pinCode, customer.phoneNumber, customer.email, customer.pan) != EOF)
    {
        if (strcmp(customer.customerID, customerID) == 0)
        {
            // Displaying customer details
            
            printf("\nHere are the details of the customer with CustomerID %s:\n", customer.customerID);
            printf("\nCustomer Name: %s", customer.name);
            printf("\nCustomer Type: %s", customer.type);
            printf("\nAddress: %s, %s, %s", customer.address1, customer.address2, customer.address3);
            printf("\nCity: %s", customer.city);
            printf("\nState: %s", customer.state);
            printf("\nCountry: %s", customer.country);
            printf("\nPin Code: %s", customer.pinCode);
            printf("\nPhone Number: %s", customer.phoneNumber);
            printf("\nEmail: %s", customer.email);
            printf("\nPAN Number: %s\n", customer.pan);
            break;
        }
    }

    fclose(customerfile);
}

void transferMoney(char *customerID)
{
    Account account;
    int srcAccount;
    int destAccount;
    printf("\nEnter the Destination Account No. to tranfer money: ");
    scanf("%d", &destAccount);
    double amount;
    int flag = 0;
    FILE *acc = fopen("account.csv", "r");
    FILE *newacc = fopen("newacc.csv", "w");
    while (fscanf(acc, "%[^,], %d ,%[^,],%[^,], %lf ,%[^,\n]\n", account.customerID, &account.accountNumber, account.type, account.status, &account.balance, account.openingDate) != EOF)
    {
        if (account.accountNumber != destAccount)
        {
            fprintf(newacc, "%s,%d,%s,%s,%lf,%s\n", account.customerID, account.accountNumber, account.type, account.status, account.balance, account.openingDate);
        }
        else
        {
            flag = 1;
            printf("\nEnter the amount to transfer: ");
            scanf("%lf", &amount);
            account.balance += amount;
            fprintf(newacc, "%s,%d,%s,%s,%lf,%s\n", account.customerID, account.accountNumber, account.type, account.status, account.balance, account.openingDate);
        }
    }
    fclose(acc);
    fclose(newacc);
    remove("account.csv");
    rename("newacc.csv", "account.csv");

    if (flag == 1)
    {
        acc = fopen("account.csv", "r");
        newacc = fopen("newacc.csv", "w");
        while (fscanf(acc, "%[^,], %d ,%[^,],%[^,], %lf ,%[^,\n]\n", account.customerID, &account.accountNumber, account.type, account.status, &account.balance, account.openingDate) != EOF)
        {
            if (strcmp(account.customerID, customerID) != 0)
            {
                fprintf(newacc, "%s,%d,%s,%s,%lf,%s\n", account.customerID, account.accountNumber, account.type, account.status, account.balance, account.openingDate);
            }
            else
            {
                srcAccount = account.accountNumber;
                account.balance -= amount;
                fprintf(newacc, "%s,%d,%s,%s,%lf,%s\n", account.customerID, account.accountNumber, account.type, account.status, account.balance, account.openingDate);
            }
        }
        fclose(acc);
        fclose(newacc);
        remove("account.csv");
        rename("newacc.csv", "account.csv");

        FILE *transfile;
        transfile = fopen("transaction.csv", "a+");
        Transaction transaction;
        int transactionID;
        srand(time(0));
        transactionID = rand();
        strcpy(transaction.type, "Debit");
        transaction.transID = transactionID;
        transaction.amount = amount;
        transaction.accountIDSrc = srcAccount;
        transaction.accountIDDst = destAccount;
        transaction.accountNumber = srcAccount;
        fprintf(transfile, "%d,%s,%d,%d,%lf,%d\n", transaction.transID, transaction.type, transaction.accountIDSrc, transaction.accountIDDst, transaction.amount, transaction.accountNumber);

        transactionID = rand();
        transaction.transID = transactionID;
        strcpy(transaction.type, "Credit");
        transaction.amount = amount;
        transaction.accountIDSrc = srcAccount;
        transaction.accountIDDst = destAccount;
        transaction.accountNumber = destAccount;
        fprintf(transfile, "%d,%s,%d,%d,%lf,%d\n", transaction.transID, transaction.type, transaction.accountIDSrc, transaction.accountIDDst, transaction.amount, transaction.accountNumber);
        fclose(transfile);
        printf("\nAmount Transferred Successfully!\n");
    }
    else
    {
        printf("\n!!Invalid Destination Account No.!!\n");
    }
}

void queryCustomer(char *customerID)
{
    User user;
    char inCustomerID[50];
    char password[50];
    printf("\nEnter Your Customer ID: ");
    scanf("%s", inCustomerID);
    printf("Enter Password: ");
    scanf("%s", password);
    int flag = 0;
    FILE *file;
    file = fopen("user.csv", "r");
    if (file == NULL)
    {
        printf("failed to open file");
    }
    else
    {
        while (fscanf(file, "%[^,], %d ,%[^,], %c\n", user.customerID, &user.userID, user.password, &user.userType) != EOF)
        {
            if (strcmp(user.customerID, customerID) == 0 && strcmp(customerID, inCustomerID) == 0 && strcmp(user.password, password) == 0)
            {
                flag = 1;
                printf("\nLogin Successful.\n");
                printf("Here are your Details: \n");
                showDetails(customerID);
                break;
            }
            else if (strcmp(user.customerID, customerID) == 0 && strcmp(user.password, password) != 0)
            {
                flag = 1;
                printf("\nIncorrect Password. Try Again\n");
                fclose(file);
                queryCustomer(customerID);
                break;
            }
        }
        if (flag == 0)
        {
            printf("\n!!Invalid CustomerID!!. Try Again\n");
            queryCustomer(customerID);
        }
    }
    fclose(file);
}

void showDetails(char *customerID)
{
    Account account;
    Transaction transaction;
    int accountNumber;
    FILE *acc = fopen("account.csv", "r");
    FILE *transact = fopen("transaction.csv", "r");
    while (fscanf(acc, "%[^,], %d ,%[^,],%[^,], %lf ,%[^,\n]\n", account.customerID, &account.accountNumber, account.type, account.status, &account.balance, account.openingDate) != EOF)
    {
        if (strcmp(account.customerID, customerID) == 0)
        {
            accountNumber = account.accountNumber;
            printf("\nAccount Details:");
            printf("\nAccount Number: %d", account.accountNumber);
            printf("\nAccount Type: %s", account.type);
            printf("\nAccount Status: %s", account.status);
            printf("\nAccount Balance: ₹%.4lf/-", account.balance);
            printf("\nAccount Opening Date: %s\n", account.openingDate);
            printf("\nTransaction Details:");
            while (fscanf(transact, "%d,%[^,], %d ,%d,%lf,%d\n", &transaction.transID, transaction.type, &transaction.accountIDSrc, &transaction.accountIDDst, &transaction.amount, &transaction.accountNumber) != EOF)
            {
                if (accountNumber == transaction.accountNumber)
                {
                    printf("\nTransactionID: %d", transaction.transID);
                    printf("\nTransaction Type: %s", transaction.type);
                    printf("\nTransaction Source Account('0' is for Clerk): %d", transaction.accountIDSrc);
                    printf("\nTransaction Destination Account('0' is for Clerk): %d", transaction.accountIDDst);
                    printf("\nTransaction Amount: ₹%lf/-", transaction.amount);
                    printf("\nAccount Number: %d\n", transaction.accountNumber);
                }
            }
            fclose(transact);
        }
    }
    fclose(acc);
}