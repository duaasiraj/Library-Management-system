#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct BooksBorrowed{
	char DofIssue[11];
	char DofReturn[11];
	int overduedays;
	long long isbn;
};


struct User{
	int ID;
	char name[100];
	long long contact;
	char email[150];
	int numofBorrowed;
	struct BooksBorrowed borrowed[5];
};

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


int main(){
	struct User *users = (struct User*)malloc(5*sizeof(struct User)); //IMPORTANT MAIN
	int numofUsers, i;

	numofUsers = UserCount(&users); //IMPORTANT MAIN
	LoadUsers(users,numofUsers); //IMPORTANT MAIN

	displayUsers(users,numofUsers);
	
	SaveUsers(users,numofUsers); //IMPORTANT MAIN
	free(users); //IMPORTANT MAIN
}
