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

int LoadBooks(struct Book *books){
	int num = 0;
	char line[416];
	FILE *fileptr = fopen("Books.txt","r");
	if(fileptr == NULL){
		perror("Error opening file");
	}
	int a=0;
	while(fgets(line,sizeof(line),fileptr)!=NULL){
		sscanf(line, "%[^'\t'] %lld %[^'\t'] %d %[^\t] %d", books[num].name, &books[num].isbn, books[num].author, &books[num].year, books[num].publisher, &books[num].available);
		num++;
	}
	fclose(fileptr);
	return num;

}

void displayBooks(struct Book *books, int n){
	int i;
	
	for(i=0;i<n;i++){
		printf("%-30s\t %lld\t %-20s\t %d\t %-30s\t %d\n",books[i].name,books[i].isbn,books[i].author,books[i].year,books[i].publisher,books[i].available);
	}
}



int main(){
	int num = 20;
	struct Book *books;
	books = (struct Book*)malloc(num*sizeof(struct Book));
	int numofBooks = LoadBooks(books);
	displayBooks(books,numofBooks);

}
