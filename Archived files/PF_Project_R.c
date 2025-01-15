#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Book Structure to hold an array of books. Each book has the below mentioned members. Available has a value of 0 or 1 with 1 meaning the book is available for issuing while 0 means its not.
struct Book{ 
	char name[150];
	long long isbn;
	char author[150];
	char publisher[100];
	int year;
	int available;
};

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

int main(){
	int numofBooks; //IMPORTANT MAIN
	struct Book *books; //IMPORTANT MAIN
	books = (struct Book*)malloc(20*sizeof(struct Book));// IMPORTANT MAIN
	if(books==NULL){
		printf("Memory Allocation Failed.");
	}//IMPORTANT MAIN
	numofBooks = BookCount(&books);//IMPORTANT MAIN
	LoadBooks(books, numofBooks);//IMPORTANT MAIN
	displayBooks(books,numofBooks);
	SaveBooks(books,numofBooks);//IMPORTANT MAIN
	free(books);//IMPORTANT MAIN
}
