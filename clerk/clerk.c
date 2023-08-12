#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../data.h"

void clerkMenu()
{
    int choice;
    do
    {
        // Displaying the customer menu

        printf("\n==================Menu======================\n");
        printf("\n1. Add a Customer Account into the system\n");
        printf("2. Delete a Customer Account from the system\n");
        printf("3. Modify Customer Details\n");
        printf("4. Credit Money to Customer account\n");
        printf("5. Debit Money from Customer account\n");
        printf("6. Query/Report\n");
        printf("7. Logout\n");
        printf("8. Quit Application");
        printf("\n============================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        // Call the function to view customer details
            addCustomerAccount();
            break;

        case 2:
        // Call the function to transfer money
            deleteCustomerAccount();
            break;
        case 3:
        // Call the function for account queries/reports
            modifyCustomerDetails();
            break;
        case 4:
            creditMoney();
            break;
        case 5:
            debitMoney();
            break;
        case 6:
            queryClerk();
            break;
        case 7:
            printf("\nLogging Out...\n");
            break;
        case 8:
            printf("\nQuitting Application...");
            printf("\nThank you for using the Bank Management System. Visit Again!\n");
            exit(0);
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
            break;
        }
    } while (choice != 7);
}

void addCustomerAccount()
{
    char str[50];
    User newUser;
    Customer newCustomer;
    Account newAccount;

    srand(time(0));
    sprintf(str, "%d", rand());
    strcpy(newUser.customerID, str);
    strcpy(newCustomer.customerID, str);
    strcpy(newAccount.customerID, str);
    newUser.userID = rand();
    newUser.userType = 'C';
    printf("\nSet password for customer login: ");
    scanf("%s", newUser.password);
    FILE *user = fopen("user.csv", "a+");
    fprintf(user, "%s,%d,%s,%c\n", newUser.customerID, newUser.userID, newUser.password, newUser.userType);
    fclose(user);

    printf("\nEnter Customer Details: \n");
    printf("Enter Customer Name:");
    scanf(" %[^\n]%*c", newCustomer.name);
    printf("\nEnter Customer Type(Individual or Corporate): ");
    scanf(" %[^\n]%*c", newCustomer.type);
    printf("\nEnter Address part-1: ");
    scanf(" %[^\n]%*c", newCustomer.address1);
    printf("\nEnter Address part-2: ");
    scanf(" %[^\n]%*c", newCustomer.address2);
    printf("\nEnter Address part-3: ");
    scanf(" %[^\n]%*c", newCustomer.address3);
    printf("\nEnter City: ");
    scanf(" %[^\n]%*c", newCustomer.city);
    printf("\nEnter State: ");
    scanf(" %[^\n]%*c", newCustomer.state);
    printf("\nEnter Country: ");
    scanf(" %[^\n]%*c", newCustomer.country);
    printf("\nEnter Pin Code: ");
    scanf(" %[^\n]%*c", newCustomer.pinCode);
    printf("\nEnter Phone Number: ");
    scanf(" %[^\n]%*c", newCustomer.phoneNumber);
    printf("\nEnter Email: ");
    scanf(" %[^\n]%*c", newCustomer.email);
    printf("\nEnter Pan: ");
    scanf(" %[^\n]%*c", newCustomer.pan);
    FILE *customer = fopen("customer.csv", "a+");
    fprintf(customer, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", newCustomer.customerID, newCustomer.name, newCustomer.type, newCustomer.address1, newCustomer.address2, newCustomer.address3, newCustomer.city, newCustomer.state, newCustomer.country, newCustomer.pinCode, newCustomer.phoneNumber, newCustomer.email, newCustomer.pan);
    fclose(customer);

    printf("\nEnter Account Details: \n");
    newAccount.accountNumber = rand();
    strcpy(newAccount.status, "Enabled");
    printf("Enter Account Type(Savings or Current): ");
    scanf("%s", newAccount.type);
    printf("\nEnter Opening Balance: ");
    scanf("%lf", &newAccount.balance);
    printf("\nEnter Account Opening Date: ");
    scanf("%s", newAccount.openingDate);
    FILE *account = fopen("account.csv", "a+");
    fprintf(account, "%s,%d,%s,%s,%lf,%s\n", newAccount.customerID, newAccount.accountNumber, newAccount.type, newAccount.status, newAccount.balance, newAccount.openingDate);
    fclose(account);

    printf("\nCustomer %s Added Successfully\n", newCustomer.name);
    printf("CustomerID is: %s", str);
    printf("\nUserID is: %d", newUser.userID);
    printf("\n Password is: %s", newUser.password);
    printf("\n Account Number is: %d\n", newAccount.accountNumber);
}

void deleteCustomerAccount()
{
    User user;
    Customer customer;
    Account account;
    Transaction transaction;
    int accountNumber;
    int userID;
    char customerID[50];
    int flag = 0;
    printf("Enter the userID of the customer to delete: ");
    scanf("%d", &userID);
    FILE *olduser = fopen("user.csv", "r");
    FILE *newuser = fopen("newuser.csv", "w");
    FILE *oldcustomer = fopen("customer.csv", "r");
    FILE *newcustomer = fopen("newcustomer.csv", "w");
    FILE *oldaccount = fopen("account.csv", "r");
    FILE *newaccount = fopen("newaccount.csv", "w");
    FILE *oldtransact = fopen("transaction.csv","r");
    FILE *newtransact = fopen("newtransact.csv","w");
    while (fscanf(olduser, "%[^,], %d ,%[^,], %c\n", user.customerID, &user.userID, user.password, &user.userType) != EOF)
    {
        if (user.userID != userID)
        {
            fprintf(newuser, "%s,%d,%s,%c\n", user.customerID, user.userID, user.password, user.userType);
        }
        else
        {
            strcpy(customerID, user.customerID);
            flag++;
        }
    }

    while (fscanf(oldcustomer, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\n]\n", customer.customerID, customer.name, customer.type, customer.address1, customer.address2, customer.address3, customer.city, customer.state, customer.country, customer.pinCode, customer.phoneNumber, customer.email, customer.pan) != EOF)
    {
        if (strcmp(customer.customerID, customerID) != 0)
        {
            fprintf(newcustomer, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", customer.customerID, customer.name, customer.type, customer.address1, customer.address2, customer.address3, customer.city, customer.state, customer.country, customer.pinCode, customer.phoneNumber, customer.email, customer.pan);
        }
        else
        {
            flag++;
        }
    }

    while (fscanf(oldaccount, "%[^,], %d ,%[^,],%[^,], %lf ,%[^,\n]\n", account.customerID, &account.accountNumber, account.type, account.status, &account.balance, account.openingDate) != EOF)
    {
        if (strcmp(account.customerID, customerID) != 0)
        {
            fprintf(newaccount, "%s,%d,%s,%s,%lf,%s\n", account.customerID, account.accountNumber, account.type, account.status, account.balance, account.openingDate);
        }
        else
        {
            accountNumber = account.accountNumber;
            flag++;
        }
    }

    while (fscanf(oldtransact, "%d,%[^,], %d ,%d,%lf,%d\n", &transaction.transID, transaction.type, &transaction.accountIDSrc, &transaction.accountIDDst, &transaction.amount, &transaction.accountNumber) != EOF)
    {
        if(transaction.accountNumber != accountNumber)
        {
            fprintf(newtransact, "%d,%s,%d,%d,%lf,%d\n",transaction.transID, transaction.type, transaction.accountIDSrc, transaction.accountIDDst, transaction.amount, transaction.accountNumber);
        }
        else
        {
            flag++;
        }
    }
    
    fclose(olduser);
    fclose(oldcustomer);
    fclose(oldaccount);
    fclose(newuser);
    fclose(newcustomer);
    fclose(newaccount);
    fclose(oldtransact);
    fclose(newtransact);
    remove("user.csv");
    rename("newuser.csv", "user.csv");
    remove("customer.csv");
    rename("newcustomer.csv", "customer.csv");
    remove("account.csv");
    rename("newaccount.csv", "account.csv");
    remove("transaction.csv");
    rename("newtransact.csv", "transaction.csv");

    if (flag == 0)
    {
        printf("\nCustomer Not Found!!\n");
    }
    else
    {
        printf("\nCustomer Deleted Suuccessfully\n");
    }
}

void modifyCustomerDetails()
{
    Customer customer;
    char customerID[50];
    int flag = 0;
    printf("\nEnter the customerID to modify: ");
    scanf("%s", customerID);
    FILE *oldcustomer = fopen("customer.csv", "r");
    FILE *newcustomer = fopen("newcustomer.csv", "w");
    while (fscanf(oldcustomer, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\n]\n", customer.customerID, customer.name, customer.type, customer.address1, customer.address2, customer.address3, customer.city, customer.state, customer.country, customer.pinCode, customer.phoneNumber, customer.email, customer.pan) != EOF)
    {
        if (strcmp(customer.customerID, customerID) != 0)
        {
            fprintf(newcustomer, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", customer.customerID, customer.name, customer.type, customer.address1, customer.address2, customer.address3, customer.city, customer.state, customer.country, customer.pinCode, customer.phoneNumber, customer.email, customer.pan);
        }
        else if (strcmp(customer.customerID, customerID) == 0)
        {
            flag = 1;
            printf("\nEnter new details: \n");
            printf("Enter Customer Name:");
            scanf(" %[^\n]%*c", customer.name);
            printf("\nEnter Customer Type(Individual or Corporate): ");
            scanf(" %[^\n]%*c", customer.type);
            printf("\nEnter Address part-1: ");
            scanf(" %[^\n]%*c", customer.address1);
            printf("\nEnter Address part-2: ");
            scanf(" %[^\n]%*c", customer.address2);
            printf("\nEnter Address part-3: ");
            scanf(" %[^\n]%*c", customer.address3);
            printf("\nEnter City: ");
            scanf(" %[^\n]%*c", customer.city);
            printf("\nEnter State: ");
            scanf(" %[^\n]%*c", customer.state);
            printf("\nEnter Country: ");
            scanf(" %[^\n]%*c", customer.country);
            printf("\nEnter Pin Code: ");
            scanf(" %[^\n]%*c", customer.pinCode);
            printf("\nEnter Phone Number: ");
            scanf(" %[^\n]%*c", customer.phoneNumber);
            printf("\nEnter Email: ");
            scanf(" %[^\n]%*c", customer.email);
            printf("\nEnter Pan: ");
            scanf(" %[^\n]%*c", customer.pan);
            fprintf(newcustomer, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", customer.customerID, customer.name, customer.type, customer.address1, customer.address2, customer.address3, customer.city, customer.state, customer.country, customer.pinCode, customer.phoneNumber, customer.email, customer.pan);
        }
    }
    if (flag == 0)
    {
        printf("\nCustomer not found\n");
    }
    else
    {
        printf("\nCustomer Details modified successfuly\n");
    }
    fclose(oldcustomer);
    fclose(newcustomer);
    remove("customer.csv");
    rename("newcustomer.csv", "customer.csv");
}

void creditMoney()
{
    Account account;
    double amount;
    char customerID[50];
    int accountNumber;

    printf("\nEnter the customerID of the customer to credit Money: ");
    scanf("%s", customerID);
    printf("\nEnter the amount to credit: ");
    scanf("%lf", &amount);
    FILE *old;
    FILE *new;
    old = fopen("account.csv", "r");
    new = fopen("newaccount.csv", "w");
    int flag = 0;
    while (fscanf(old, "%[^,], %d ,%[^,],%[^,], %lf ,%[^,\n]\n", account.customerID, &account.accountNumber, account.type, account.status, &account.balance, account.openingDate) != EOF)
    {
        if (strcmp(account.customerID, customerID) != 0)
        {
            fprintf(new, "%s,%d,%s,%s,%lf,%s\n", account.customerID, account.accountNumber, account.type, account.status, account.balance, account.openingDate);
        }
        else
        {
            flag = 1;
            account.balance += amount;
            accountNumber = account.accountNumber;
            fprintf(new, "%s,%d,%s,%s,%lf,%s\n", account.customerID, account.accountNumber, account.type, account.status, account.balance, account.openingDate);
        }
    }
    if (flag == 0)
    {
        printf("\n!!!Customer not found. Enter Correct CustomerID!!!.\n");
    }
    else
    {
        FILE *transfile;
        transfile = fopen("transaction.csv", "a+");
        Transaction transaction;
        int transactionID;
        srand(time(0));
        transactionID = rand();
        strcpy(transaction.type, "Credit");
        transaction.transID = transactionID;
        transaction.amount = amount;
        transaction.accountIDSrc = 0;
        transaction.accountIDDst = accountNumber;
        transaction.accountNumber = accountNumber;
        fprintf(transfile, "%d,%s,%d,%d,%lf,%d\n", transaction.transID, transaction.type, transaction.accountIDSrc, transaction.accountIDDst, transaction.amount, transaction.accountNumber);
        fclose(transfile);
        printf("\nAmount Credited successfully!\n");
    }

    fclose(old);
    fclose(new);
    remove("account.csv");
    rename("newaccount.csv", "account.csv");
}

void debitMoney()
{
    Account account;
    double amount;
    char customerID[50];
    int accountNumber;

    printf("\nEnter the customerID of the customer to debit Money: ");
    scanf("%s", customerID);
    printf("\nEnter the amount to debit: ");
    scanf("%lf", &amount);
    FILE *old;
    FILE *new;
    old = fopen("account.csv", "r");
    new = fopen("newaccount.csv", "w");
    int flag = 0;
    while (fscanf(old, "%[^,], %d ,%[^,],%[^,], %lf ,%[^,\n]\n", account.customerID, &account.accountNumber, account.type, account.status, &account.balance, account.openingDate) != EOF)
    {
        if (strcmp(account.customerID, customerID) != 0)
        {
            fprintf(new, "%s,%d,%s,%s,%lf,%s\n", account.customerID, account.accountNumber, account.type, account.status, account.balance, account.openingDate);
        }
        else
        {
            if (amount > account.balance)
            {
                flag = 1;
                fprintf(new, "%s,%d,%s,%s,%lf,%s\n", account.customerID, account.accountNumber, account.type, account.status, account.balance, account.openingDate);
            }
            else
            {
                flag = 2;
                accountNumber = account.accountNumber;
                account.balance -= amount;
                fprintf(new, "%s,%d,%s,%s,%lf,%s\n", account.customerID, account.accountNumber, account.type, account.status, account.balance, account.openingDate);
            }
        }
    }
    if (flag == 0)
    {
        printf("\n!!!Customer not found. Enter Correct CustomerID!!!.\n");
    }
    else if (flag == 1)
    {
        printf("\n!!!Insufficient Balance in Customer Account!!!");
    }
    else
    {
        FILE *transfile;
        transfile = fopen("transaction.csv", "a+");
        Transaction transaction;
        int transactionID;
        srand(time(0));
        transactionID = rand();
        strcpy(transaction.type, "Debit");
        transaction.transID = transactionID;
        transaction.amount = amount;
        transaction.accountIDSrc = 0;
        transaction.accountIDDst = accountNumber;
        transaction.accountNumber = accountNumber;
        fprintf(transfile, "%d,%s,%d,%d,%lf,%d\n", transaction.transID, transaction.type, transaction.accountIDSrc, transaction.accountIDDst, transaction.amount, transaction.accountNumber);
        fclose(transfile);
        printf("\nAmount Debited successfully!\n");
    }
    fclose(old);
    fclose(new);
    remove("account.csv");
    rename("newaccount.csv", "account.csv");
}

void queryClerk()
{
    Account account;
    Transaction transaction;
    char customerID[50];
    int accountNumber;
    FILE *cust = fopen("customer.csv", "r");
    FILE *acc = fopen("account.csv", "r");
    FILE *transact = fopen("transaction.csv", "r");
    char buffer[500];
    printf("\nList of all the Customers:\n");
    printf("\nCustomerID,Name,CustomerType,Address1,Address2,Address3,City,State,Country,PinCode,PhoneNumber,Email,PAN\n");
    while (fgets(buffer, 500, cust) != NULL)
    {
        printf("\n%s", buffer);
    }
    fclose(cust);
    printf("\n\nEnter CustomerID to display customer's account and transaction details:");
    scanf("%s", customerID);
    int flag = 0;
    while (fscanf(acc, "%[^,], %d ,%[^,],%[^,], %lf ,%[^,\n]\n", account.customerID, &account.accountNumber, account.type, account.status, &account.balance, account.openingDate) != EOF)
    {
        if (strcmp(account.customerID, customerID) == 0)
        {
            flag = 1;
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
    if (flag == 0)
    {
        printf("\n!!!Invalid CustomerID!!!\n");
    }
}