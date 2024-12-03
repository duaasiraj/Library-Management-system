#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
struct Login {
    char username[50];
    char password[50];
};

struct BooksBorrowed {
    char DofIssue[11];
    char DofReturn[11];
    int overduedays;
    long long isbn;
};

struct User {
    int ID;
    char name[100];
    long long contact;
    char email[150];
    int numofBorrowed;
    struct BooksBorrowed borrowed[5];
};

// User Management Functions
int UserCount(struct User **users) {
    FILE *fileptr = fopen("Users.txt", "r");
    if (fileptr == NULL) {
        printf("Error opening Users.txt. Returning 0 users.\n");
        return 0;
    }

    char line[500];
    int n = 0;

    while (fgets(line, sizeof(line), fileptr) != NULL) {
        n++;
    }

    *users = (struct User *)malloc(n * sizeof(struct User));
    if (*users == NULL) {
        printf("Memory allocation failed for users.\n");
        fclose(fileptr);
        return 0;
    }

    fclose(fileptr);
    return n;
}

void LoadUsers(struct User *users, int n) {
    FILE *fileptr = fopen("Users.txt", "r");
    if (fileptr == NULL) {
        printf("Error opening Users.txt.\n");
        return;
    }

    char line[500];
    for (int i = 0; i < n; i++) {
        fgets(line, sizeof(line), fileptr);
        sscanf(line, "%d %[^\t] %lld %[^\n]",
               &users[i].ID, users[i].name, &users[i].contact, users[i].email);
    }
    fclose(fileptr);
}

void SaveUsers(struct User *users, int n) {
    int i, j;
    FILE *fileptr = fopen("Users.txt", "w");

    if (fileptr == NULL) {
        printf("Error opening Users.txt for writing.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        fprintf(fileptr, "%d\t%s\t%lld\t%s\t%d", users[i].ID, users[i].name, users[i].contact, users[i].email, users[i].numofBorrowed);
        if (users[i].numofBorrowed > 0) {
            for (j = 0; j < users[i].numofBorrowed; j++) {
                fprintf(fileptr, "\t%s\t%s\t%d\t%lld",
                        users[i].borrowed[j].DofIssue, users[i].borrowed[j].DofReturn,
                        users[i].borrowed[j].overduedays, users[i].borrowed[j].isbn);
            }
        } else {
            fprintf(fileptr, "\t0\t0\t0\t0");
        }
        fprintf(fileptr, "\n");
    }

    fclose(fileptr);
}

int AddUser(struct User **users, int n) {
    int tempID, i, j, valid = 0;

    printf("Enter User ID for new member: ");
    scanf("%d", &tempID);
    getchar(); 

    while (!valid) {
        valid = 1;
        for (i = 0; i < n; i++) {
            if ((*users)[i].ID == tempID) {
                printf("This user already exists! The ID must be unique (suggested: %d).\n", n + 1);
                printf("Enter User ID for new member: ");
                scanf("%d", &tempID);
                getchar(); 
                valid = 0;
                break;
            }
        }
    }

    *users = (struct User *)realloc(*users, (n + 1) * sizeof(struct User));
    if (*users == NULL) {
        printf("Error reallocating memory for users.\n");
        return n;
    }

    (*users)[n].ID = tempID;
    printf("Enter name (first and last name): ");
    fgets((*users)[n].name, 100, stdin);
    (*users)[n].name[strcspn((*users)[n].name, "\n")] = '\0';

    printf("Enter email: ");
    fgets((*users)[n].email, 150, stdin);
    (*users)[n].email[strcspn((*users)[n].email, "\n")] = '\0';

    printf("Enter Contact Number: ");
    scanf("%lld", &(*users)[n].contact);
    getchar(); 

    (*users)[n].numofBorrowed = 0;
    for (i = 0; i < 5; i++) {
        (*users)[n].borrowed[i].isbn = 0;
        (*users)[n].borrowed[i].overduedays = 0;
        (*users)[n].borrowed[i].DofIssue[0] = '\0';
        (*users)[n].borrowed[i].DofReturn[0] = '\0';
    }

    SaveUsers(*users, n + 1);
    return n + 1;
}

// Login Management Functions
int LoadLoginData(struct Login **logins) {
    FILE *fileptr = fopen("login.txt", "r");
    if (fileptr == NULL) {
        printf("Error opening login.txt. Returning 0 logins.\n");
        return 0;
    }

    char line[150];
    int n = 0;

    while (fgets(line, sizeof(line), fileptr) != NULL) {
        n++;
    }

    *logins = (struct Login *)malloc(n * sizeof(struct Login));
    if (*logins == NULL) {
        printf("Memory allocation failed for logins.\n");
        fclose(fileptr);
        return 0;
    }

    rewind(fileptr);
    for (int i = 0; i < n; i++) {
        fgets(line, sizeof(line), fileptr);
        sscanf(line, "%49s %49s", (*logins)[i].username, (*logins)[i].password);
    }
    fclose(fileptr);
    return n;
}

void SaveLoginData(struct Login *logins, int n) {
    FILE *fileptr = fopen("login.txt", "w");
    if (fileptr == NULL) {
        printf("Error opening login.txt for writing.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fileptr, "%s %s\n", logins[i].username, logins[i].password);
    }
    fclose(fileptr);
}

int Signup(struct Login **logins, int n, struct User **users, int *numUsers) {
    char tempUsername[50];
    char tempPassword[50];
    int valid = 0;

    while (!valid) {
        valid = 1;

        printf("Enter username for signup: ");
        scanf("%49s", tempUsername);
        getchar(); 

        for (int i = 0; i < n; i++) {
            if (strcmp((*logins)[i].username, tempUsername) == 0) {
                printf("Error: Username already exists. Try another.\n");
                valid = 0;
                break;
            }
        }
    }

    printf("Enter password: ");
    scanf("%49s", tempPassword);
    getchar(); 

    *logins = (struct Login *)realloc(*logins, (n + 1) * sizeof(struct Login));
    if (*logins == NULL) {
        printf("Error reallocating memory for logins.\n");
        return n;
    }

    strcpy((*logins)[n].username, tempUsername);
    strcpy((*logins)[n].password, tempPassword);
    SaveLoginData(*logins, n + 1);

    printf("Now, create a user profile for this account.\n");
    *numUsers = AddUser(users, *numUsers);
    printf("Signup successful! You can now log in.\n");
    return n + 1;
}

void displayUsers(struct User *users, int n) {
    for (int i = 0; i < n; i++) {
        printf("ID: %d, Name: %s, Contact: %lld, Email: %s, Borrowed Books: %d\n",
               users[i].ID, users[i].name, users[i].contact, users[i].email, users[i].numofBorrowed);
    }
}

void Login(struct Login *logins, int n) {
    char tempUsername[50];
    char tempPassword[50];
    int loggedIn = 0;

    printf("Enter username: ");
    scanf("%49s", tempUsername);
    getchar(); 

    printf("Enter password: ");
    scanf("%49s", tempPassword);
    getchar(); 

    for (int i = 0; i < n; i++) {
        if (strcmp(logins[i].username, tempUsername) == 0 &&
            strcmp(logins[i].password, tempPassword) == 0) {
            printf("Login successful! Welcome, %s.\n", tempUsername);
            loggedIn = 1;
            break;
        }
    }

    if (!loggedIn) {
        printf("Invalid username or password. Please try again.\n");
    }
}

// Main Program
int main() {
    struct User *users = NULL;
    struct Login *logins = NULL;

    int numUsers = UserCount(&users);
    int numLogins = LoadLoginData(&logins);

    LoadUsers(users, numUsers);

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Signup\n2. Display Users\n3. Login\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the buffer

        switch (choice) {
            case 1:
                numLogins = Signup(&logins, numLogins, &users, &numUsers);
                break;

            case 2:
                displayUsers(users, numUsers);
                break;

            case 3:
                Login(logins, numLogins);
                break;

            case 4:
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    free(users);
    free(logins);
    return 0;
}
