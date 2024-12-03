#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Start of structures

//Book Structure to hold an array of books. Each book has the below mentioned members. Available has a value of 0 or 1 with 1 meaning the book is available for issuing while 0 means its not.
struct Book{ 
	char name[150];
	long long isbn;
	char author[150];
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


//Start of functions

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
		sscanf(line, "%[^'\t'] %lld %[^'\t'] %d %[^\t] %d", books[i].name, &books[i].isbn, books[i].author, &books[i].year, books[i].publisher, &books[i].available);

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
        fprintf(fileptr, "%s\t%lld\t%s\t%d\t%s\t%d\n", books[i].name, books[i].isbn, books[i].author, books[i].year, books[i].publisher, books[i].available);
    }
    
    fclose(fileptr);
}

//displays all the books currently in the array.
void displayBooks(struct Book *books, int n){
	int i;
	
	for(i=0;i<n;i++){
		printf("%-30s\t %lld\t %-20s\t %d\t %-30s\t %d\n",books[i].name,books[i].isbn,books[i].author,books[i].year,books[i].publisher,books[i].available);
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
    
    printf("Enter publishing year: ");
	scanf("%d",&(*books)[n].year);
	
	(*books)[n].isbn = isbntemp;
	(*books)[n].available = 1;
    return n+1;
}


//UserCount counts the number of books from the Users.txt file an makes sure that the users array is reallocated to hold the correct number of users. It also returns the number of users.
int UserCount(struct User **users){
	char line[500];
	FILE *fileptr = fopen("Users.txt","r");
	int n=0;
	if(fileptr==NULL){
		printf("Error opening file.\n");
	}
	else{
		while(fgets(line,sizeof(line),fileptr)!=NULL){
			n++;
		}
	
		*users = (struct User*)realloc(*users,n*sizeof(struct User));
			
	}
	fclose(fileptr);
	return n;
}


//LoadUsers writes the data from Users.txt into the users array. Each data item in the file is seperated by a tab to allow use of spaces in names (hence use of [^\t] which means to read until the tab occurs).
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


//displays all the users currently in the array.
void displayUsers(struct User *users, int n){
	int i, j;
	
	for(i=0;i<n;i++){
		printf("ID: %d\tName: %s\tContact: +92%lld\tEmail: %s\tNumber of Borrowed Books: %d\n\n",users[i].ID,users[i].name,users[i].contact,users[i].email,users[i].numofBorrowed);
		if(users[i].numofBorrowed>0){
				printf("\tBorrowed Books:\n");
				for(j=0;j<users[i].numofBorrowed;j++){
					printf("\tBook %d\n",j+1);
					printf("\t\tDate of Issue: %s\n \t\tDue Date: %s\n \t\tDays Overdue: %d\n \t\tISBN: %lld\n",users[i].borrowed[j].DofIssue,users[i].borrowed[j].DofReturn,users[i].borrowed[j].overduedays,users[i].borrowed[j].isbn);
				}
				printf("\n");
		}
	}
}


//writes the user array to the Users.txt file.
void SaveUsers(struct User *users, int n){
    int i, j;
    FILE *fileptr = fopen("Users.txt", "w");
    
	if(fileptr==NULL){
		printf("Error opening file.\n");
	}
	else{
		for(i=0;i<n;i++){
			fprintf(fileptr,"%d\t%s\t%lld\t%s\t%d",users[i].ID,users[i].name,users[i].contact,users[i].email,users[i].numofBorrowed);
			for(j=0;j<users[i].numofBorrowed;j++){
                fprintf(fileptr,"\t%s\t%s\t%d\t%lld", users[i].borrowed[j].DofIssue, users[i].borrowed[j].DofReturn, users[i].borrowed[j].overduedays, users[i].borrowed[j].isbn);
			}
			fprintf(fileptr,"\n");
		}
	}
	fclose(fileptr);	
}


//adds a user to the array and reallocates the array memory to hold one more space for the user. also increments the total count by 1.
int AddUser(struct User **users, int n){
	int tempID, i, j, valid;
	valid = 0;
	fflush(stdin);
	printf("Enter User ID for new member: ");
	scanf("%d", &tempID);
	
    while(!valid) {
        valid = 1;
        for(i=0;i<n;i++){
            if((*users)[i].ID==tempID) {
                printf("This user already exists! The ID must be unique (suggested: %d).\n", n+1);
                printf("Enter User ID for new member: ");
                scanf("%d", &tempID);
                valid = 0;
                break;
            }
        }
    }
	
	*users = (struct User*)realloc(*users,(n+1)*sizeof(struct User));
	
	(*users)[n].ID = tempID;
	fflush(stdin);
	
	printf("Enter name (first and last name): ");
	fgets((*users)[n].name,100,stdin);
	(*users)[n].name[strcspn((*users)[n].name,"\n")]='\0';
	
	printf("Enter email: ");
	fgets((*users)[n].email,150,stdin);
	(*users)[n].email[strcspn((*users)[n].email,"\n")]='\0';
	
	printf("Enter Contact Number: ");
	scanf("%lld", &(*users)[n].contact);
	
	(*users)[n].numofBorrowed = 0;
	
	return n+ 1;
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
			printf("\nTotal fine is: %.2f\n",totalfine);
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


int main(){
//start of back-end initialization
	int numofBooks; //IMPORTANT MAIN
	int numofUsers;
	
	struct Book *books; //IMPORTANT MAIN
	books = (struct Book*)malloc(20*sizeof(struct Book));// IMPORTANT MAIN
	struct User *users = (struct User*)malloc(5*sizeof(struct User)); //IMPORTANT MAIN

	if(books==NULL){
		printf("Memory Allocation Failed.");
	}//IMPORTANT MAIN
	if(users==NULL){
		printf("Memory Allocation Failed.");
	}//IMPORTANT MAIN
	
	numofBooks = BookCount(&books);//IMPORTANT MAIN
	LoadBooks(books, numofBooks);//IMPORTANT MAIN
	numofUsers = UserCount(&users); //IMPORTANT MAIN
	LoadUsers(users,numofUsers); //IMPORTANT MAIN
//end of back-end initialization	
	
	
	
	
	
//start of saving data and freeing memory
	SaveBooks(books,numofBooks);//IMPORTANT MAIN
	free(books);//IMPORTANT MAIN
	SaveUsers(users,numofUsers); //IMPORTANT MAIN
	free(users); //IMPORTANT MAIN
//end of saving data and freeing memory
}
