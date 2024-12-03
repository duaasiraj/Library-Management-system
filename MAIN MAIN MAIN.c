#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


//Start of structures
//login
struct Login {
    char username[50];
    char password[50];
};

//Book Structure to hold an array of books. Each book has the below mentioned members. Available has a value of 0 or 1 with 1 meaning the book is available for issuing while 0 means its not.
struct Book{ 
	char name[150];
	long long isbn;
	char author[150];
	char genre[100];
	char publisher[100];
	int year;
	int available;
};

//BooksBorrowed structure made to hold an array of books borrowed by a user. Consists of an issue date, due date, how many days overdue the book is, and the book's ISBN number.
struct BooksBorrowed{
	char DofIssue[11];
	char DofReturn[11];
	int overduedays;
	long long isbn;
};

//User Structure to hold info about each user. Consists of a unique ID, name, contact details (phone number and email), the number of books currently borrowed, and an array of struct BooksBorrowed.
struct User{
	int ID;
	char name[100];
	long long contact;
	char email[150];
	int numofBorrowed;
	struct BooksBorrowed borrowed[5];
};

//End of structures
void Displaybooks(struct Book *books, int num);
void sortNameAsc(struct Book *books, int num);
void sortPublisherAsc(struct Book *books, int num);
void sortYearAsc(struct Book *books, int num);
void sortIsbnAsc(struct Book *books, int num);
void sortAuthorAsc(struct Book *books, int num);
void sortNameDsc(struct Book *books, int num);
void sortPublisherDsc(struct Book *books, int num);
void sortYearDsc(struct Book *books, int num);
void sortIsbnDsc(struct Book *books, int num);
void sortAuthorDsc(struct Book *books, int num);
void searchbyname(struct Book *books, int num, char sname[150]);
void searchbyisbn(struct Book *books, int num, long long int sisbn);
void searchbyauthor(struct Book *books, int num, char name[150]);
void searchbypub(struct Book *books, int num, char name[150]);
void searchbyyr(struct Book *books, int num, int year);
void searchaboveyear(struct Book *books, int num, int year);
void searchlowyear(struct Book *books, int num, int year);
void searchallav(struct Book *books, int num);
void searchbygenre(struct Book *books, int num, char name[100]);
int UserCount(struct User **users);
void LoadUsers(struct User *users, int n);
void SaveUsers(struct User *users, int n);
int AddUser(struct User **users, int n);
int LoadLoginData(struct Login **logins);
void SaveLoginData(struct Login *logins, int n);
int Signup(struct Login **logins, int n, struct User **users, int *numUsers);
void displayUsers(struct User *users, int n);
void Login(struct Login *logins, int n);
void IssueBook(struct Book *books, int numofBooks, struct User *users, int numofUsers);
void ReturnBook(struct Book *books, int numofBooks, struct User *users, int numofUsers);
void ViewoverdueUsers(struct User *users, int n);
int BookCount(struct Book **books);
void LoadBooks(struct Book *books, int num);
void SaveBooks(struct Book *books, int n);
void displayBooks(struct Book *books, int n);
int AddBook(struct Book **books, int n);
void CalculateFines(struct User *users, int n);


//Start of functions
void ClearScreen() {
    printf("\033[H\033[J"); // ANSI escape code to clear the console screen
}

// Main Function
int main() {
    struct Login *logins = NULL;
    struct User *users = NULL;
    struct Book *books = NULL;

    int numLogins = LoadLoginData(&logins);
    int numUsers = UserCount(&users);
    int numBooks = BookCount(&books);

    LoadUsers(users, numUsers);
    LoadBooks(books, numBooks);

    while (1) {
        ClearScreen();
        printf("Welcome to the Library Management System\n");
        printf("1. Librarian\n2. Member\n3. Exit\n");
        printf("Select your role: ");
        int choice;
        scanf("%d", &choice);
        getchar(); // Consume leftover newline

        if (choice == 1) {
            // Librarian flow
            ClearScreen();
            printf("Enter Librarian Special Code: ");
            int code;
            scanf("%d", &code);
            getchar();

            if (code != 9834211) {
                printf("Invalid code. Returning to main menu.\n");
                getchar();
                continue;
            }

            while (1) {
                ClearScreen();
                printf("Librarian Menu:\n");
                printf("1. View Overdue Books\n");
                printf("2. Calculate Fines\n");
                printf("3. Add Book\n");
                printf("4. Display Books\n");
                printf("5. Logout\n");
                printf("Select an option: ");
                int librarianChoice;
                scanf("%d", &librarianChoice);
                getchar();

                if (librarianChoice == 1) {
                    ViewoverdueUsers(users, numUsers);
                } else if (librarianChoice == 2) {
                    CalculateFines(users, numUsers);
                } else if (librarianChoice == 3) {
                    numBooks = AddBook(&books, numBooks);
                    SaveBooks(books, numBooks);
                } else if (librarianChoice == 4) {
                    displayBooks(books, numBooks);
                } else if (librarianChoice == 5) {
                    break;
                } else {
                    printf("Invalid choice.\n");
                }
                printf("Press Enter to return to the menu.\n");
                getchar();
            }
        } else if (choice == 2) {
            // Member flow
            ClearScreen();
            printf("1. Login\n2. Signup\n");
            printf("Select an option: ");
            int memberChoice;
            scanf("%d", &memberChoice);
            getchar();

            if (memberChoice == 1) {
                Login(logins, numLogins);
            } else if (memberChoice == 2) {
                numLogins = Signup(&logins, numLogins, &users, &numUsers);
                SaveUsers(users, numUsers);
            } else {
                printf("Invalid choice.\n");
                getchar();
                continue;
            }

            while (1) {
                ClearScreen();
                printf("Member Menu:\n");
                printf("1. Search Books\n");
                printf("2. Issue Book\n");
                printf("3. Return Book\n");
                printf("4. Logout\n");
                printf("Select an option: ");
                int memberMenuChoice;
                scanf("%d", &memberMenuChoice);
                getchar();

                if (memberMenuChoice == 1) {
                    ClearScreen();
                    printf("Search Menu:\n");
                    printf("1. By Name\n2. By Author\n3. By Publisher\n4. By Year\n5. Back\n");
                    printf("Select an option: ");
                    int searchChoice;
                    scanf("%d", &searchChoice);
                    getchar();

                    if (searchChoice == 1) {
                        char name[150];
                        printf("Enter book name: ");
                        fgets(name, 150, stdin);
                        name[strcspn(name, "\n")] = '\0';
                        searchbyname(books, numBooks, name);
                    } else if (searchChoice == 2) {
                        char author[150];
                        printf("Enter author name: ");
                        fgets(author, 150, stdin);
                        author[strcspn(author, "\n")] = '\0';
                        searchbyauthor(books, numBooks, author);
                    } else if (searchChoice == 3) {
                        char publisher[150];
                        printf("Enter publisher name: ");
                        fgets(publisher, 150, stdin);
                        publisher[strcspn(publisher, "\n")] = '\0';
                        searchbypub(books, numBooks, publisher);
                    } else if (searchChoice == 4) {
                        int year;
                        printf("Enter year: ");
                        scanf("%d", &year);
                        searchbyyr(books, numBooks, year);
                    } else {
                        break;
                    }
                } else if (memberMenuChoice == 2) {
                    IssueBook(books, numBooks, users, numUsers);
                    SaveBooks(books, numBooks);
                } else if (memberMenuChoice == 3) {
                    ReturnBook(books, numBooks, users, numUsers);
                    SaveBooks(books, numBooks);
                } else if (memberMenuChoice == 4) {
                    break;
                } else {
                    printf("Invalid choice.\n");
                }
                printf("Press Enter to return to the menu.\n");
                getchar();
            }
        } else if (choice == 3) {
            printf("Thank you for visiting!\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
            getchar();
        }
    }

    SaveUsers(users, numUsers);
    SaveBooks(books, numBooks);
    SaveLoginData(logins, numLogins);

    free(users);
    free(books);
    free(logins);

    return 0;
}



//sort start
//Ascending functions definition-bubble sort
void Displaybooks(struct Book *books,int num){
	for (int i=0;i<num;i++){
		printf("%-35s %15lld\t %-25s %4d %-35s %2d\n",books[i].name,books[i].isbn,books[i].author,books[i].year,books[i].publisher,books[i].available);
	}
}

void sortNameAsc(struct Book *books,int num){
    struct Book temp;
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - 1; j++) {
            if (strcmp(books[j].name, books[j + 1].name) > 0) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
    Displaybooks(books,num);
}


void sortPublisherAsc(struct Book *books,int num){
    struct Book temp;
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num  - 1; j++) {
            if (strcmp(books[j].publisher, books[j + 1].publisher) > 0) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
    Displaybooks(books,num);
}

void sortYearAsc(struct Book *books,int num){
    struct Book temp;
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - 1; j++) {
            if (books[j].year> books[j + 1].year) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
    Displaybooks(books,num);
}

void sortIsbnAsc(struct Book *books,int num){
    struct Book temp;
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - 1; j++) {
            if (books[j].isbn> books[j + 1].isbn) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
    Displaybooks(books,num);
}

void sortAuthorAsc(struct Book *books,int num){
    struct Book temp;
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num  - 1; j++) {
            if (strcmp(books[j].author, books[j + 1].author) > 0) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
    Displaybooks(books,num);
}


//descending
void sortNameDsc(struct Book *books,int num){
    struct Book temp;
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - 1; j++) {
            if (strcmp(books[j].name, books[j + 1].name) < 0) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
    Displaybooks(books,num);
}


void sortPublisherDsc(struct Book *books,int num){
    struct Book temp;
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num  - 1; j++) {
            if (strcmp(books[j].publisher, books[j + 1].publisher) < 0) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
    Displaybooks(books,num);
}

void sortYearDsc(struct Book *books,int num){
    struct Book temp;
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - 1; j++) {
            if (books[j].year< books[j + 1].year) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
    Displaybooks(books,num);
}

void sortIsbnDsc(struct Book *books,int num){
    struct Book temp;
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - 1; j++) {
            if (books[j].isbn< books[j + 1].isbn) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
    Displaybooks(books,num);
}

void sortAuthorDsc(struct Book *books,int num){
    struct Book temp;
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num  - 1; j++) {
            if (strcmp(books[j].author, books[j + 1].author) < 0) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
    Displaybooks(books,num);
}

//sort end

//search start

void searchbyname(struct Book *books,int num, char sname[150]){
	int flag=0;
	for (int i=0;i<num;i++){
		if (strcasecmp(books[i].name,sname)==0){
			printf("%-35s %15lld\t %-25s %4d %-35s %2d\n",books[i].name,books[i].isbn,books[i].author,books[i].year,books[i].publisher,books[i].available);
			flag=1;
		}
	}
	if (flag==0){
		printf("Book not found!");
	}
}

void searchbyisbn(struct Book *books,int num,long long int sisbn){
	int digits = (int)(floor(log10((double)sisbn)) + 1);
	int flag=0;
	if (digits!=13){
		printf("Invalid ISBN! Please ensure your ISBN is 13 digits long.");
		return;
	}
	for (int i=0;i<num;i++){
		if (books[i].isbn==sisbn){
			printf("%-35s %15lld\t %-25s %4d %-35s %2d\n",books[i].name,books[i].isbn,books[i].author,books[i].year,books[i].publisher,books[i].available);
			flag=1;
		}
	}
	if (flag==0){
		printf("Book with ISBN %lld is not found!",sisbn);
	}
}


void searchbyauthor(struct Book *books,int num, char name[150]){
		int flag=0;
	for (int i=0;i<num;i++){
		if (strcasecmp(books[i].author,name)==0){
			printf("%-35s %15lld\t %-25s %4d %-35s %2d\n",books[i].name,books[i].isbn,books[i].author,books[i].year,books[i].publisher,books[i].available);
			flag=1;
		}
	}
	if (flag==0){
		printf("Author not found!");
	}
}

void searchbypub(struct Book *books,int num, char name[150]){
	int flag=0;
	for (int i=0;i<num;i++){
		if (strcasecmp(books[i].publisher,name)==0){
			printf("%-35s %15lld\t %-25s %4d %-35s %2d\n",books[i].name,books[i].isbn,books[i].author,books[i].year,books[i].publisher,books[i].available);
			flag=1;
		}
	}
	if (flag==0){
		printf("Publisher not found!");
	}
}

void searchbyyr(struct Book *books,int num,int year){
	int flag=0;
	for (int i=0;i<num;i++){
		if (books[i].year==year){
			printf("%-35s %15lld\t %-25s %4d %-35s %2d\n",books[i].name,books[i].isbn,books[i].author,books[i].year,books[i].publisher,books[i].available);
			flag=1;
		}
	}
	if (flag==0){
		printf("No results found!");
	}
}

void searchaboveyear(struct Book *books,int num,int year){
	int flag=0;
	for (int i=0;i<num;i++){
		if (books[i].year>=year){
			printf("%-35s %15lld\t %-25s %4d %-35s %2d\n",books[i].name,books[i].isbn,books[i].author,books[i].year,books[i].publisher,books[i].available);
			flag=1;
		}
	}
	if (flag==0){
		printf("No results found!");
	}
}

void searchlowyear(struct Book *books, int num, int year) {
    int flag = 0;
    for (int i = 0; i < num; i++) {
        if (books[i].year <= year) {
            printf("%-35s %15lld\t %-25s %4d %-35s %2d\n", 
                books[i].name, books[i].isbn, books[i].author, 
                books[i].year, books[i].publisher, books[i].available);
            flag = 1;
        }
    }
    if (flag == 0) {
        printf("No results found!\n");
    }
}

void searchallav(struct Book *books, int num){
	int flag = 0;
    for (int i = 0; i < num; i++) {
        if (books[i].available>0) {
            printf("%-35s %15lld\t %-25s %4d %-35s %2d\n", 
                books[i].name, books[i].isbn, books[i].author, 
                books[i].year, books[i].publisher, books[i].available);
            flag = 1;
        }
    }
    if (flag == 0) {
        printf("No results found!\n");
    }
}

void searchbygenre(struct Book *books,int num, char name[100]){
	int flag=0;
	for (int i=0;i<num;i++){
		if (strcasecmp(books[i].genre,name)==0){
			printf("%-35s %15lld\t %-25s %4d %-35s %2d\n",books[i].name,books[i].isbn,books[i].author,books[i].year,books[i].publisher,books[i].available);
			flag=1;
		}
	}
	if (flag==0){
		printf("Results not found!");
	}
}

//search end

//log+loading start

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

void LoadUsers(struct User *users, int n){
	FILE *fileptr = fopen("Users.txt","r");
	int i, j;
	char line[500];
	if(fileptr==NULL){
		printf("Error opening file.\n");
	}
	else{
		for(i = 0; i < n; i++){
	        fgets(line, sizeof(line), fileptr);
	        char *lineptr = line;
	        int offset = 0;
	        
			sscanf(lineptr, "%d %[^\t] %lld %[^\t] %d%n",&users[i].ID, users[i].name, &users[i].contact, users[i].email, &users[i].numofBorrowed, &offset);
	        lineptr+= offset;
	        if(users[i].numofBorrowed>0){
	            for(j=0;j<users[i].numofBorrowed;j++){
	                
	                sscanf(lineptr, "%s %s %d %lld%n",users[i].borrowed[j].DofIssue, users[i].borrowed[j].DofReturn, &users[i].borrowed[j].overduedays, &users[i].borrowed[j].isbn, &offset);
	                lineptr+=offset; 
	            }
	        }
		}
		fclose(fileptr);
	}
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



//log+loading end

//issue  start

// Function to issue a book to a user
void IssueBook(struct Book *books, int numofBooks, struct User *users, int numofUsers) {
    int userID, bookIndex = -1, userIndex = -1;
    long long isbn;
    
    printf("Enter the user ID: ");
    scanf("%d", &userID);

    // Find the user
    for (int i = 0; i < numofUsers; i++) {
        if (users[i].ID == userID) {
            userIndex = i;
            break;
        }
    }
    
    if (userIndex == -1) {
        printf("User not found.\n");
        return;
    }

    if (users[userIndex].numofBorrowed >= 5) {
        printf("User cannot borrow more than 5 books.\n");
        return;
    }

    printf("Enter the ISBN of the book to issue: ");
    scanf("%lld", &isbn);

    // Find the book
    for (int i = 0; i < numofBooks; i++) {
        if (books[i].isbn == isbn) {
            bookIndex = i;
            break;
        }
    }
    
    if (bookIndex == -1) {
        printf("Book not found.\n");
        return;
    }

    if (!books[bookIndex].available) {
        printf("Book is not available for issuing.\n");
        return;
    }

    // Issue the book
    books[bookIndex].available = 0;
    users[userIndex].borrowed[users[userIndex].numofBorrowed].isbn = isbn;
    printf("Enter issue date (dd/mm/yyyy): ");
    scanf("%s", users[userIndex].borrowed[users[userIndex].numofBorrowed].DofIssue);
    printf("Enter due date (dd/mm/yyyy): ");
    scanf("%s", users[userIndex].borrowed[users[userIndex].numofBorrowed].DofReturn);
    users[userIndex].borrowed[users[userIndex].numofBorrowed].overduedays = 0;
    users[userIndex].numofBorrowed++;

    printf("Book issued successfully.\n");
}

// Function to return a book from a user
void ReturnBook(struct Book *books, int numofBooks, struct User *users, int numofUsers) {
    int userID, bookIndex = -1, userIndex = -1, borrowIndex = -1;
    long long isbn;
    
    printf("Enter the user ID: ");
    scanf("%d", &userID);

    // Find the user
    for (int i = 0; i < numofUsers; i++) {
        if (users[i].ID == userID) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        printf("User not found.\n");
        return;
    }

    printf("Enter the ISBN of the book to return: ");
    scanf("%lld", &isbn);

    // Find the book in borrowed list
    for (int i = 0; i < users[userIndex].numofBorrowed; i++) {
        if (users[userIndex].borrowed[i].isbn == isbn) {
            borrowIndex = i;
            break;
        }
    }

    if (borrowIndex == -1) {
        printf("Book not found in user's borrowed list.\n");
        return;
    }

    // Find the book in library
    for (int i = 0; i < numofBooks; i++) {
        if (books[i].isbn == isbn) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex == -1) {
        printf("Book not found in library records.\n");
        return;
    }

    // Return the book
    books[bookIndex].available = 1;
    users[userIndex].borrowed[borrowIndex] = users[userIndex].borrowed[users[userIndex].numofBorrowed - 1];
    users[userIndex].numofBorrowed--;

    printf("Book returned successfully.\n");
}


//issue return end

//view due dates start

void ViewoverdueUsers(struct User *users, int n) {
    int found = 0; // Flag to check if any overdue users are found

    printf("\nUsers with Overdue Books:\n");
    printf("=========================\n");
	int i,j;
    for (i = 0; i < n; i++) {
		if(users[i].numofBorrowed>0){
			for (j = 0; j < users[i].numofBorrowed; j++) {
	            if (users[i].borrowed[j].overduedays > 0) {
	                
	                    printf("\nUser ID: %d\n", users[i].ID);
	                    printf("Name: %s\n", users[i].name);
	                    printf("Contact: +92%lld\n", users[i].contact);
	                    printf("Email: %s\n", users[i].email);
	                    printf("Overdue Books:\n");
	                    found = 1;
	                
	
		                // Print details of each overdue book
		                printf("\tISBN: %lld\n", users[i].borrowed[j].isbn);
		                printf("\tDate of Issue: %s\n", users[i].borrowed[j].DofIssue);
		                printf("\tDue Date: %s\n", users[i].borrowed[j].DofReturn);
		                printf("\tDays Overdue: %d\n", users[i].borrowed[j].overduedays);
		                printf("\n");
	            }
        	}	
		}
        
    }

    if (!found) {
        printf("\nNo users have overdue books.\n");
    }
}

//view due dates end

//BookCount counts the number of books from the Book.txt file an makes sure that the books array is reallocated to hold the correct number of books. It also returns the number of books.
int BookCount(struct Book **books){
	int n;
	char line[416];
	FILE *fileptr = fopen("Books.txt","r");
	if(fileptr == NULL){
		perror("Error opening file");
	}
	while(fgets(line,sizeof(line),fileptr)!=NULL){
		n++;
	}
	
	*books = (struct Book*)realloc(*books, n*sizeof(struct Book));
	
	fclose(fileptr);
	return n;
}

//LoadBooks writes the data from books.txt into the books array. Each data item in the file is seperated by a tab to allow use of spaces in names (hence use of [^\t] which means to read until the tab occurs).
void LoadBooks(struct Book *books, int num){
	int i;
	char line[416];
	FILE *fileptr = fopen("Books.txt","r");
	if(fileptr == NULL){
		perror("Error opening file");
	}
	for(i=0;i<num;i++){
		fgets(line,sizeof(line),fileptr);
		sscanf(line, "%[^'\t'] %lld %[^'\t'] %d %[^\t] %[^\t] %d", books[i].name, &books[i].isbn, books[i].author, &books[i].year, books[i].publisher, books[i].genre, &books[i].available);

	}
	fclose(fileptr);
}

//writes the book array to the books.txt file.
void SaveBooks(struct Book *books, int n){
    int i;
    FILE *fileptr = fopen("Books.txt", "w");
    if(fileptr == NULL){
        printf("Error opening file\n");
        return;
    }
    for(i = 0; i < n; i++){
        fprintf(fileptr, "%s\t%lld\t%s\t%d\t%s\t%s\t%d\n", books[i].name, books[i].isbn, books[i].author, books[i].year, books[i].publisher, books[i].genre, books[i].available);
    }
    
    fclose(fileptr);
}

//displays all the books currently in the array.
void displayBooks(struct Book *books, int n){
	int i;
	
	for(i=0;i<n;i++){
		printf("%-30s\t %lld\t %-20s\t %d\t %-30s\t %-20s\t %d\n",books[i].name,books[i].isbn,books[i].author,books[i].year,books[i].publisher,books[i].genre,books[i].available);
	}
}

//adds a bok to the array and reallocates the array memory to hold one more space for the book. also increments the total count by 1 and makes sure the ISBN entered is 13 digits and unique.
int AddBook(struct Book **books, int n){
	long long isbntemp;
	long long check = 1000000000000;
    int i;
	printf("Enter ISBN: ");
	scanf("%lld",&isbntemp);
	
	if((isbntemp/check)>9||(isbntemp/check<1&&isbntemp!=check)){
		printf("You must enter a valid 13 digit ISBN number.\n\n");
		return n;
	}
	else{
		for(i =0;i<n;i++){
			if((*books)[i].isbn==isbntemp){
				printf("That book already exists. Please check the ISBN number again.\n\n");
				return n;
			}	
		}
	}
    *books = (struct Book*)realloc(*books,(n+1)*sizeof(struct Book));
    
    if (*books == NULL) {
        printf("Memory allocation failed.");
        return n;
    }
    fflush(stdin);
    printf("Enter book name: ");
    fgets((*books)[n].name,150,stdin);
    (*books)[n].name[strcspn((*books)[n].name,"\n")]='\0';
    
    printf("Enter author name: ");
    fgets((*books)[n].author,150,stdin);
    (*books)[n].author[strcspn((*books)[n].author,"\n")]='\0';
    
    printf("Enter publisher name: ");
    fgets((*books)[n].publisher,150,stdin);
    (*books)[n].publisher[strcspn((*books)[n].publisher,"\n")]='\0';
    
    printf("Enter Genre: ");
    fgets((*books)[n].genre,100,stdin);
    (*books)[n].genre[strcspn((*books)[n].genre,"\n")]='\0';
    
    printf("Enter publishing year: ");
	scanf("%d",&(*books)[n].year);
	
	(*books)[n].isbn = isbntemp;
	(*books)[n].available = 1;
    return n+1;
}
//Caculates the fine based on how many days a book is overdue. Displays seperate fines for each book along with a total fine.
void CalculateFines(struct User *users, int n){
	int i, IDsearch, found,j;
	found = -1;
	printf("Displaying User info for users who have books currently borrowed\n\n\n");
	for(i=0;i<n;i++){
		if(users[i].numofBorrowed>0){
			printf("ID: %d\tName: %s\tNumber of Borrowed Books: %d\n\n",users[i].ID,users[i].name,users[i].numofBorrowed);
		}
	}
	printf("Enter the ID you wish to calculate fines for: ");
	scanf("%d",&IDsearch);
	for(i=0;i<n;i++){
		if(users[i].ID==IDsearch){
			found = i;
			break;
		}
	}
	if(found!=-1){
		float indfine = 0;
		float totalfine = 0;
		for(j=0;j<users[found].numofBorrowed;j++){
			
			if(users[found].borrowed[j].overduedays>0){
				indfine = 25.0*users[found].borrowed[j].overduedays;
				printf("Fine for book ISBN %lld: %.2f\n",users[found].borrowed[j].isbn,indfine);
				totalfine+=indfine;
			}
		}
		if(totalfine>0){
			printf("Contact Details:\n\tPhone: +92%lld\n\tEmail: %s\n",users[found].contact,users[found].email);
		}
		else{
			printf("This user has no overdue books.\n");
		}
	}
	else{
		printf("User does not exist.\n");
	}
	
	
} 

//End of functions