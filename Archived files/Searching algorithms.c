#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



struct Book{ 
	char name[150];
	long long isbn;
	char author[150];
	char publisher[100];
	int year;
	int available;
	char genre[100];
};

//declaration of all functions

void searchbyname(struct Book *books, int num, char sname[150]);
void searchbyisbn(struct Book *books, int num, long long int sisbn);
void searchbyauthor(struct Book *books, int num, char name[150]);
void searchbypub(struct Book *books, int num, char name[150]);
void searchbyyr(struct Book *books, int num, int year);
void searchaboveyear(struct Book *books, int num, int year);
void searchlowyear(struct Book *books, int num, int year);
void searchallav(struct Book *books, int num);
void searchbygenre(struct Book *books, int num, char name[100]);


int main() {

    struct Book books[20];

    // Assign values to each book
    strcpy(books[0].name, "The Catcher in the Rye");
    books[0].isbn = 9780316769488;
    strcpy(books[0].author, "J.D. Salinger");
    strcpy(books[0].publisher, "Little, Brown and Company");
    books[0].year = 1951;
    books[0].available = 5;
    strcpy(books[0].genre, "Fiction");

    strcpy(books[1].name, "To Kill a Mockingbird");
    books[1].isbn = 9780061120084;
    strcpy(books[1].author, "Harper Lee");
    strcpy(books[1].publisher, "J.B. Lippincott & Co.");
    books[1].year = 1960;
    books[1].available = 2;
    strcpy(books[1].genre, "Fiction");

    strcpy(books[2].name, "1984");
    books[2].isbn = 9780451524935;
    strcpy(books[2].author, "George Orwell");
    strcpy(books[2].publisher, "Secker & Warburg");
    books[2].year = 1949;
    books[2].available = 4;
    strcpy(books[2].genre, "Dystopian");

    strcpy(books[3].name, "The Great Gatsby");
    books[3].isbn = 9780743273565;
    strcpy(books[3].author, "F. Scott Fitzgerald");
    strcpy(books[3].publisher, "Charles Scribner's Sons");
    books[3].year = 1925;
    books[3].available = 3;
    strcpy(books[3].genre, "Fiction");

    strcpy(books[4].name, "Moby-Dick");
    books[4].isbn = 9781503280786;
    strcpy(books[4].author, "Herman Melville");
    strcpy(books[4].publisher, "Harper & Brothers");
    books[4].year = 1851;
    books[4].available = 1;
    strcpy(books[4].genre, "Adventure");

    strcpy(books[5].name, "Pride and Prejudice");
    books[5].isbn = 9781503290563;
    strcpy(books[5].author, "Jane Austen");
    strcpy(books[5].publisher, "T. Egerton");
    books[5].year = 1813;
    books[5].available = 6;
    strcpy(books[5].genre, "Romance");

    strcpy(books[6].name, "The Hobbit");
    books[6].isbn = 9780261103344;
    strcpy(books[6].author, "J.R.R. Tolkien");
    strcpy(books[6].publisher, "George Allen & Unwin");
    books[6].year = 1937;
    books[6].available = 8;
    strcpy(books[6].genre, "Fantasy");

    strcpy(books[7].name, "The Lord of the Rings");
    books[7].isbn = 9780261103573;
    strcpy(books[7].author, "J.R.R. Tolkien");
    strcpy(books[7].publisher, "George Allen & Unwin");
    books[7].year = 1954;
    books[7].available = 3;
    strcpy(books[7].genre, "Fantasy");

    strcpy(books[8].name, "The Chronicles of Narnia");
    books[8].isbn = 9780064471193;
    strcpy(books[8].author, "C.S. Lewis");
    strcpy(books[8].publisher, "Geoffrey Bles");
    books[8].year = 1950;
    books[8].available = 4;
    strcpy(books[8].genre, "Fantasy");

    strcpy(books[9].name, "Brave New World");
    books[9].isbn = 9780060850524;
    strcpy(books[9].author, "Aldous Huxley");
    strcpy(books[9].publisher, "Chatto & Windus");
    books[9].year = 1932;
    books[9].available = 5;
    strcpy(books[9].genre, "Dystopian");

    strcpy(books[10].name, "Crime and Punishment");
    books[10].isbn = 9780486415871;
    strcpy(books[10].author, "Fyodor Dostoevsky");
    strcpy(books[10].publisher, "The Russian Messenger");
    books[10].year = 1866;
    books[10].available = 2;
    strcpy(books[10].genre, "Psychological Fiction");

    strcpy(books[11].name, "War and Peace");
    books[11].isbn = 9781400079988;
    strcpy(books[11].author, "Leo Tolstoy");
    strcpy(books[11].publisher, "The Russian Messenger");
    books[11].year = 1869;
    books[11].available = 3;
    strcpy(books[11].genre, "Historical Fiction");

    strcpy(books[12].name, "The Odyssey");
    books[12].isbn = 9780143039952;
    strcpy(books[12].author, "Homer");
    strcpy(books[12].publisher, "Penguin Classics");
    books[12].year = -800;
    books[12].available = 5;
    strcpy(books[12].genre, "Epic Poetry");

    strcpy(books[13].name, "Frankenstein");
    books[13].isbn = 9780486282114;
    strcpy(books[13].author, "Mary Shelley");
    strcpy(books[13].publisher, "Lackington, Hughes, Harding, Mavor & Jones");
    books[13].year = 1818;
    books[13].available = 7;
    strcpy(books[13].genre, "Science Fiction");

    strcpy(books[14].name, "Dracula");
    books[14].isbn = 9780141439846;
    strcpy(books[14].author, "Bram Stoker");
    strcpy(books[14].publisher, "Archibald Constable and Company");
    books[14].year = 1897;
    books[14].available = 4;
    strcpy(books[14].genre, "Horror");

    strcpy(books[15].name, "Wuthering Heights");
    books[15].isbn = 9780141439556;
    strcpy(books[15].author, "Emily Bronte");
    strcpy(books[15].publisher, "Thomas Cautley Newby");
    books[15].year = 1847;
    books[15].available = 6;
    strcpy(books[15].genre, "Romance");

    strcpy(books[16].name, "The Picture of Dorian Gray");
    books[16].isbn = 9780141439570;
    strcpy(books[16].author, "Oscar Wilde");
    strcpy(books[16].publisher, "Lippincott's Monthly Magazine");
    books[16].year = 1890;
    books[16].available = 4;
    strcpy(books[16].genre, "Gothic Fiction");

    strcpy(books[17].name, "Les Miserables");
    books[17].isbn = 9780451419439;
    strcpy(books[17].author, "Victor Hugo");
    strcpy(books[17].publisher, "A. Lacroix, Verboeckhoven & Cie");
    books[17].year = 1862;
    books[17].available = 5;
    strcpy(books[17].genre, "Historical Fiction");

    strcpy(books[18].name, "The Divine Comedy");
    books[18].isbn = 9780140448955;
    strcpy(books[18].author, "Dante Alighieri");
    strcpy(books[18].publisher, "Felice Le Monnier");
    books[18].year = 1320;
    books[18].available = 8;
    strcpy(books[18].genre, "Epic Poetry");

    strcpy(books[19].name, "The Canterbury Tales");
    books[19].isbn = 9780140422344;
    strcpy(books[19].author, "Geoffrey Chaucer");
    strcpy(books[19].publisher, "William Caxton");
    books[19].year = 1400;
    books[19].available = 6;
    strcpy(books[19].genre, "Poetry");
    int num_books = 20;

    return 0;
}



//definition of all

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
	
