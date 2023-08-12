#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../data.h"

void clerkLogin()
{
    User user;
    char customerID[50];
    char password[50];

    // function for Prompt for user input
    printf("\nEnter Your UserID: ");
    scanf("%s", customerID);
    printf("Enter Password: ");
    scanf("%s", password);
    FILE *file;
    file = fopen("clerk.txt", "r");
    if (file == NULL)
    {
        printf("\nfailed to open file\n");
    }
    else
    {
    // Read user credentials from file
        fscanf(file, "%s %s", user.customerID, user.password);
        if (strcmp(user.customerID, customerID) == 0 && strcmp(user.password, password) == 0)
        {
            printf("\nLogin Successful.\n");
            clerkMenu();
        }
        else
        {
            printf("\nPlease Enter Valid Credentials.\n");
            clerkLogin();
        }
    }
    fclose(file);
}

void customerLogin()
{
    User user;
    char customerID[50];
    char password[50];
    int flag = 0;

    // Prompt for user input
    printf("\nEnter Customer ID: ");
    scanf("%s", customerID);
    printf("Enter Password: ");
    scanf("%s", password);
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
            if (strcmp(user.customerID, customerID) == 0 && strcmp(user.password, password) == 0)
            {
                flag = 1;
                printf("\nLogin Successful.\n");
                customerMenu(user.customerID);
                break;
            }
            else if (strcmp(user.customerID, customerID) == 0 && strcmp(user.password, password) != 0)
            {
                flag = 1;
                printf("\n!!Incorrect Password. Try Again!!\n");
                fclose(file);
                customerLogin();
                break;
            }
        }
    }
    fclose(file);
    if (flag == 0)
    {
        printf("\n!!Customer not found. Enter a valid CustomerID.!!\n");
        customerLogin();
    }
}