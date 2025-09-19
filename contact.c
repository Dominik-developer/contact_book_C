#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Single Contact 
typedef struct{
    char name[25];
    char phone [15];
} Contact;


// declaration of function
void addContact();

void showAllContacts();
void removeContact();
void mainMenu();
int endProgram(int endCode);


//====== MAIN ======
int main() {

    mainMenu();

    return 0;
}


// SINGLE CONTACT FUNCTIONS
void addContact(){

    // allocating memory
    Contact *newContact = malloc(sizeof(Contact));

    if(newContact == NULL){
        printf("Memory allocation faild!\n");
        endProgram(1);
    }

    //opening file
    FILE *pFile = fopen("contactList.txt", "a");

    if(pFile == NULL) {
        printf("Error opening file.\n");
        free(newContact); // cleaning memory after error
        endProgram(1);
    }

    // operation of adding new contact
    printf("Enter name: ");
    scanf(" %24[^\n]", newContact->name);
    printf("Enter phone: ");
    scanf(" %14[^\n]", newContact->phone);
    
    fprintf(pFile, "%s,%s\n",newContact->name, newContact->phone);

    // closeing file
    fclose(pFile);

    //cleaning memory - pointers
    free(newContact);
    newContact = NULL;

    printf("Contact added successfully!\n");
}

void removeContact() {

}

////void editContact() {
////
////}


// ALL CONTACT FUNCTIONS 
void showAllContacts(){

    FILE *pFile  =fopen("contactList.txt", "r");

    if(pFile == NULL){
        printf("Could not open file.\n");
        endProgram(1);
    }

    char line[50];

    while(fgets(line, sizeof(line), pFile)){

        // printf without ,
        char *comma = strchr(line, ','); // look for first comma in line
        if(comma) {
            *comma = ' ';// change ',' for ' '
        }

        printf("%s", line);
    }
    fclose(pFile);
}


// PROGRAM FUNCTIONS
int endProgram(int endCode) {
    switch(endCode) {

        case 0:
            printf("Ending program without error.\n");
            exit(0);
            break;

        case 1:
            printf("Ending program with error.\n");
            exit(1);
            break;

        default:
            printf("Error. Ending program...\n");
            exit(1);
    }
}

void mainMenu() {
    int choice = -1;

    while (choice != 0) {
        printf("\n");
        printf("\n==== CONTACT BOOK MENU ====\n");
        printf("0 - End program\n");
        printf("1 - Show contact list\n");
        printf("2 - Add new contact\n");
        printf("3 - Remove contact\n");
        ////printf("4 - Edit contact\n");
        printf("===========================\n");
        printf("Choose action: ");
        scanf("%d", &choice);

        switch(choice) {
            case 0:
                printf("Ending program...\n");
                printf("\n");
                sleep(1);
                endProgram(0);
                break;

            case 1:
                //printf("Showing all contacts...\n");
                printf("\n");
                showAllContacts();
                break;

            case 2:
                //printf("Adding contact...\n");
                printf("\n");
                addContact();
                break;

            case 3:
                //printf("Removing contact...\n");
                printf("\n");
                removeContact();
                break;

            ////case 4:
                ////printf("Editing contact...\n");
                ////editContact();
                ////break;

            default:
                printf("Invalid option!\n");
        }
    }
}



//EOF