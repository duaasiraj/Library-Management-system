#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void calculateReturnDate(int day, int month, int year, int *retDay, int *retMonth, int *retYear) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Adjust for leap year in February
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }
    
    // Add 5 days
    day += 5;

    // Handle overflow of days into the next month
    if (day > daysInMonth[month - 1]) {
        day -= daysInMonth[month - 1];
        month++;

        // Handle overflow of months into the next year
        if (month > 12) {
            month = 1;
            year++;
        }
    }

    // Update return date
    *retDay = day;
    *retMonth = month;
    *retYear = year;
}
    
void UpdateBookStatus(struct Book *books, int numofBooks, struct User **users, long long userID, long long isbn, int borrow, int day, int month, int year) {
    // Find the user by userID
    int userIndex = -1;  // Initialize userIndex to -1 to indicate not found
    for (int i = 0; i < numofBooks; i++) {
        if (users[i]->id == userID) {  // Check if the userID matches
            userIndex = i;  // Update userIndex if found
            break;
        }
    }

    if (userIndex == -1) {  // User not found
        printf("User with ID %lld not found.\n", userID);
        return;
    }

    // Find the book by ISBN
    for (int i = 0; i < numofBooks; i++) {
        if (books[i].isbn == isbn) {  // Check if the book's ISBN matches
            // Borrowing a book
            if (borrow) {
                if (books[i].available > 0) {  // Check if the book is available
                    if (users[userIndex]->numofBorrowed < 5) {  // Check if user can borrow more
                        books[i].available--;  // Decrease the available books

                        // Update user's borrowed books list
                        int index = users[userIndex]->numofBorrowed;
                        users[userIndex]->borrowed[index].isbn = isbn;

                        // Set issue and return dates
                        sprintf(users[userIndex]->borrowed[index].DofIssue, "%02d-%02d-%04d", day, month, year);
                        int retDay, retMonth, retYear;
                        calculateReturnDate(day, month, year, &retDay, &retMonth, &retYear);
                        sprintf(users[userIndex]->borrowed[index].DofReturn, "%02d-%02d-%04d", retDay, retMonth, retYear);

                        users[userIndex]->borrowed[index].overduedays = 0;  // Reset overdue days
                        users[userIndex]->numofBorrowed++;  // Increment the number of borrowed books

                        printf("Book '%s' borrowed successfully.\n", books[i].name);
                        printf("Return by: %s\n", users[userIndex]->borrowed[index].DofReturn);
                    } else {
                        printf("Cannot borrow more books. Maximum limit of 5 reached.\n");
                    }
                } else {
                    printf("Book '%s' is currently unavailable.\n", books[i].name);
                }
            } 
            // Returning a book
            else {
                for (int j = 0; j < users[userIndex]->numofBorrowed; j++) {  // Loop through borrowed books
                    if (users[userIndex]->borrowed[j].isbn == isbn) {  // Find the borrowed book by ISBN
                        books[i].available++;  // Increase available books

                        // Remove book from user's borrowed list
                        for (int k = j; k < users[userIndex]->numofBorrowed - 1; k++) {
                            users[userIndex]->borrowed[k] = users[userIndex]->borrowed[k + 1];
                        }
                        users[userIndex]->numofBorrowed--;  // Decrement the number of borrowed books

                        printf("Book '%s' returned successfully.\n", books[i].name);
                        return;
                    }
                }
                printf("Book with ISBN %lld not found in user's borrowed list.\n", isbn);
            }
            return;
        }
    }

    printf("Book with ISBN %lld not found in library.\n", isbn);
}

// Display all books currently borrowed by a user
void PrintBorrowedBooks(struct User *users, int numofUsers, int userID) {
    for (int i = 0; i < numofUsers; i++) {
        if (users[i].ID == userID) {
            printf("Books borrowed by %s (ID: %d):\n", users[i].name, users[i].ID);
            if (users[i].numofBorrowed > 0) {
                for (int j = 0; j < users[i].numofBorrowed; j++) {
                    printf("ISBN: %lld | Issued on: %s | Due by: %s\n",
                           users[i].borrowed[j].isbn,
                           users[i].borrowed[j].DofIssue,
                           users[i].borrowed[j].DofReturn);
                }
            } else {
                printf("No books currently borrowed.\n");
            }
            return;
        }
    }
    printf("User with ID %d not found.\n", userID);
}

// Display the names of users with overdue books
void UsersPastDueDate(struct User *users, int numofUsers) {
    int found = 0;
    printf("Users with overdue books (over 5 days):\n");
    for (int i = 0; i < numofUsers; i++) {
        for (int j = 0; j < users[i].numofBorrowed; j++) {
            if (users[i].borrowed[j].overduedays > 5) {
                printf("User: %s (ID: %d) | Overdue by %d days | ISBN: %lld\n",
                       users[i].name,
                       users[i].ID,
                       users[i].borrowed[j].overduedays,
                       users[i].borrowed[j].isbn);
                found = 1;
                break;
            }
        }
    }
    if (!found) {
        printf("No users have overdue books beyond 5 days.\n");
    }
}

// Display the names of users borrowing a specific number of books
void UsersWithSpecificBooks(struct User *users, int numofUsers, int numBooks) {
    int found = 0;
    printf("Users borrowing %d book(s):\n", numBooks);
    for (int i = 0; i < numofUsers; i++) {
        if (users[i].numofBorrowed == numBooks) {
            printf("User: %s (ID: %d)\n", users[i].name, users[i].ID);
            found = 1;
        }
    }
    if (!found) {
        printf("No users are borrowing %d book(s).\n", numBooks);
    }
}