#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book{
	char name[150];
	long long isbn;
	char author[150];
	char publisher[100];
	int year;
	int available;
};

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


void displayBooks(struct Book *books, int n){
	int i;
	
	for(i=0;i<n;i++){
		printf("%-30s\t %lld\t %-20s\t %d\t %-30s\t %d\n",books[i].name,books[i].isbn,books[i].author,books[i].year,books[i].publisher,books[i].available);
	}
}

int AddBook(struct Book **books, int n){
    *books = (struct Book*)realloc(*books,(n+1)*sizeof(struct Book));
    
    if (*books == NULL) {
        printf("Memory allocation failed.");
        return n;
    }
    fflush(stdin);
    printf("Enter book name: ");
    fgets((*books)[n].name, 150, stdin);
    (*books)[n].name[strcspn((*books)[n].name,"\n")]='\0';
    
    printf("Enter author name: ");
    fgets((*books)[n].author, 150, stdin);
    (*books)[n].author[strcspn((*books)[n].author,"\n")]='\0';
    
    printf("Enter publisher name: ");
    fgets((*books)[n].publisher, 150, stdin);
    (*books)[n].publisher[strcspn((*books)[n].publisher,"\n")]='\0';
    
	printf("Enter ISBN: ");
	scanf("%lld",&(*books)[n].isbn);
    
    printf("Enter publishing year: ");
	scanf("%d",&(*books)[n].year);
	
	(*books)[n].available = 1;
    return n+1;
}

int main(){
	int i;
	int numofBooks;
	struct Book *books;
	books = (struct Book*)malloc(20*sizeof(struct Book));
	if(books==NULL){
		printf("Memory Allocation Failed.");
	}
	numofBooks = BookCount(&books);
	
	LoadBooks(books, numofBooks);
	displayBooks(books,numofBooks);
	SaveBooks(books,numofBooks);
	free(books);
}
