#ifndef USER_H
#define USER_H

typedef struct {
    int userID;
    char customerID[50];
    char password[50];
    char userType;
    int loginStatus;
} User;

void clerkLogin();      // Function to handle clerk login
void customerLogin();   // Function to handle customer login

#endif