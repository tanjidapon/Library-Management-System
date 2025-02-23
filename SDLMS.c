#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function Declarations
void adminLogin();
void userLogin();
void adminPage();
void userPage();
void deleteUser();
void viewAllUsers();
void borrowBook();
void returnBook();
void viewUserDetails();
void signUp();
void listAvailableBooks();
void listAllBooks();
void addBook();
void backToDashboard();
void viewPaidBooks();

// Structure for storing user data
typedef struct {
    char username[50];
    char password[50];
    int isDeleted; // Flag to indicate if the user is deleted
    char borrowedBooks[5][50]; // List of borrowed books by the user
    int borrowedCount; // Number of books borrowed by the user
} User;

// Array to store users
User users[10]; // Let's assume we can store up to 10 users
int userCount = 0; // Counter for number of users

// Books available in the library
char books[5][50] = {"C Programming", "Data Structures", "Algorithms", "Operating System", "Database Systems"};
int availableBooks[5] = {5, 3, 4, 2, 6};  // Available copies of each book

// Paid books (simulating paid books with an index)
char paidBooks[2][50] = {"Advanced Algorithms", "Machine Learning"};
int availablePaidBooks[2] = {3, 5};  // Available copies of paid books

// Main Dashboard (Admin/User Selection)
void showMainDashboard() {
    printf("\n----------------------------------------------------\n");
    printf("Welcome to the Library Management System\n");
    printf("----------------------------------------------------\n");
    printf("1. Admin Login\n");
    printf("2. User Login\n");
    printf("3. Exit\n");
    printf("----------------------------------------------------\n");
}

// Admin Login
void adminLogin() {
    char username[50], password[50];

    printf("Enter Admin Username: ");
    scanf("%s", username);
    printf("Enter Admin Password: ");
    scanf("%s", password);

    if (strcmp(username, "Apon") == 0 && strcmp(password, "23666488") == 0) {
        printf("\nLogin Successful! Welcome, Admin.\n");
        adminPage();  // Admin login successful
    } else {
        printf("\nInvalid credentials! Try again.\n");
    }
}

// Admin Dashboard
void adminDashboard() {
    printf("\n------------------------ Admin Dashboard ------------------------\n");
    printf("1. View All Users\n");
    printf("2. Delete User\n");
    printf("3. List Available Books\n");
    printf("4. Add a Book\n");
    printf("5. View Paid Books\n");
    printf("6. Back to Dashboard\n");
    printf("-------------------------------------------------------------------\n");
}

// Admin Page (After Login)
void adminPage() {
    int choice;
    while (1) {
        adminDashboard();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewAllUsers();
                break;
            case 2:
                deleteUser();
                break;
            case 3:
                listAllBooks();  // List available books for Admin
                break;
            case 4:
                addBook();  // Add a new book to the library
                break;
            case 5:
                viewPaidBooks();  // Show available paid books
                break;
            case 6:
                backToDashboard();  // Go back to the dashboard
                return;
            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }
}

// View All Users
void viewAllUsers() {
    printf("\n------------------- All Registered Users -------------------\n");
    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (users[i].isDeleted == 0) { // Only show non-deleted users
            printf("User: %s\n", users[i].username);
            found = 1;
        }
    }
    if (!found) {
        printf("No users found.\n");
    }
    printf("--------------------------------------------------------------\n");
}

// Delete User
void deleteUser() {
    char username[50];
    printf("Enter the username of the user to delete: ");
    scanf("%s", username);

    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (users[i].isDeleted == 0 && strcmp(users[i].username, username) == 0) {
            users[i].isDeleted = 1; // Mark the user as deleted
            printf("\nUser %s has been deleted.\n", users[i].username);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nUser not found or user is already deleted.\n");
    }
}

// User Login
void userLogin() {
    char username[50], password[50];

    printf("Enter User Username: ");
    scanf("%s", username);
    printf("Enter User Password: ");
    scanf("%s", password);

    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (users[i].isDeleted == 0 && strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("\nLogin Successful! Welcome, User.\n");
            userPage();  // User login successful
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nInvalid credentials or user is deleted! Try again.\n");
    }
}

// User Dashboard
void userDashboard() {
    printf("\n--------------------------- User Dashboard ----------------------------\n");
    printf("1. View Your Details\n");
    printf("2. Borrow Book\n");
    printf("3. Return Book\n");
    printf("4. List Available Books\n");
    printf("5. Exit to Main Dashboard\n");
    printf("----------------------------------------------------------------------\n");
}

// User Page (After Login)
void userPage() {
    int choice;
    while (1) {
        userDashboard();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewUserDetails();
                break;
            case 2:
                borrowBook();
                break;
            case 3:
                returnBook();
                break;
            case 4:
                listAvailableBooks();  // Show available books for User
                break;
            case 5:
                printf("\nReturning to Main Dashboard...\n");
                return;
            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }
}

// View User Details (Including borrowed books)
void viewUserDetails() {
    printf("\n----------------- Your User Details -----------------\n");
    printf("Username: %s\n", users[userCount - 1].username);
    printf("Borrowed Books:\n");

    if (users[userCount - 1].borrowedCount == 0) {
        printf("You haven't borrowed any books yet.\n");
    } else {
        for (int i = 0; i < users[userCount - 1].borrowedCount; i++) {
            printf("%d. %s\n", i + 1, users[userCount - 1].borrowedBooks[i]);
        }
    }
    printf("-------------------------------------------------------\n");
}

// Borrow Book
void borrowBook() {
    int bookChoice;
    printf("\nSelect a book to borrow:\n");
    listAvailableBooks();
    printf("Enter book number to borrow: ");
    scanf("%d", &bookChoice);

    if (bookChoice >= 1 && bookChoice <= 5 && availableBooks[bookChoice - 1] > 0) {
        availableBooks[bookChoice - 1]--;
        strcpy(users[userCount - 1].borrowedBooks[users[userCount - 1].borrowedCount], books[bookChoice - 1]);
        users[userCount - 1].borrowedCount++;
        printf("\nYou have borrowed: %s\n", books[bookChoice - 1]);
    } else {
        printf("\nInvalid choice or no copies available.\n");
    }
}

// Return Book
void returnBook() {
    int bookChoice;
    printf("\nSelect a book to return:\n");
    listAvailableBooks();
    printf("Enter book number to return: ");
    scanf("%d", &bookChoice);

    if (bookChoice >= 1 && bookChoice <= 5) {
        availableBooks[bookChoice - 1]++;
        printf("\nYou have returned: %s\n", books[bookChoice - 1]);

        // Remove the book from borrowed books list
        for (int i = 0; i < users[userCount - 1].borrowedCount; i++) {
            if (strcmp(users[userCount - 1].borrowedBooks[i], books[bookChoice - 1]) == 0) {
                // Shift the books to remove the returned one
                for (int j = i; j < users[userCount - 1].borrowedCount - 1; j++) {
                    strcpy(users[userCount - 1].borrowedBooks[j], users[userCount - 1].borrowedBooks[j + 1]);
                }
                users[userCount - 1].borrowedCount--;
                break;
            }
        }
    } else {
        printf("\nInvalid book selection.\n");
    }
}

// List Available Books
void listAvailableBooks() {
    printf("\n------------------ Available Books ------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %s - Available Copies: %d\n", i + 1, books[i], availableBooks[i]);
    }
    printf("------------------------------------------------------\n");
}

// List All Books
void listAllBooks() {
    printf("\n------------------ All Available Books ------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %s - Available Copies: %d\n", i + 1, books[i], availableBooks[i]);
    }
    printf("---------------------------------------------------------\n");
}

// Admin Add Book
void addBook() {
    char newBook[50];
    printf("\nEnter the name of the book to add: ");
    scanf("%s", newBook);

    // Add the book to the available books list
    strcpy(books[5], newBook);
    availableBooks[5] = 10;  // Setting a default number of copies
    printf("\nBook '%s' has been added to the library.\n", newBook);
}

// Admin View Paid Books
void viewPaidBooks() {
    printf("\n------------------ Paid Books ------------------\n");
    for (int i = 0; i < 2; i++) {
        printf("%d. %s - Available Copies: %d\n", i + 1, paidBooks[i], availablePaidBooks[i]);
    }
    printf("-------------------------------------------------\n");
}

// Back to Admin Dashboard
void backToDashboard() {
    printf("\nReturning to Admin Dashboard...\n");
}

// Sign Up (Creating a new user)
void signUp() {
    printf("\nSign Up - Create a new user account\n");

    printf("Enter a new username: ");
    scanf("%s", users[userCount].username);

    printf("Enter a new password: ");
    scanf("%s", users[userCount].password);

    users[userCount].isDeleted = 0; // Initially, the user is not deleted
    users[userCount].borrowedCount = 0; // No borrowed books initially
    userCount++;

    printf("\nSign Up successful! You can now login with your new account.\n");
}

// Main Function
int main() {
    int choice;

    while (1) {
        showMainDashboard();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminLogin();  // Admin login
                break;
            case 2:
                printf("\n1. Sign Up\n2. Sign In\n");
                printf("Choose an option: ");
                int loginChoice;
                scanf("%d", &loginChoice);
                if (loginChoice == 1) {
                    signUp();  // Sign Up for new users
                } else if (loginChoice == 2) {
                    userLogin();  // User login
                } else {
                    printf("\nInvalid choice!\n");
                }
                break;
            case 3:
                printf("\nExiting the system...\n");
                exit(0);
            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}
