#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"


// main menu decleared.
int main() {
    int choice;
    do {
        printf("\n=======WELCOME TO XYZ BANK=======\n");
        printf("\n         1. Login as Clerk\n");
        printf("         2. Login as Customer\n");
        printf("         3. Quit");
        printf("\n====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
            // Here Calling the function for bank clerk login
                clerkLogin();
                break;

            case 2:
            // Here Calling the function for customer login
                customerLogin();
                break;

            case 3:
            // Here adding fucn of Quit the application
                printf("\nQuitting Application...");
                printf("\nThank you for using the Bank Management System. Visit Again!\n");
                break;

            default:
            //here implimented invalid fuction when an invalid choice is entered
                printf("\nInvalid choice. Please try again.\n");
                break;
                
        }
    } while (choice != 3);

    return 0;
}