#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_NAME_LEN 25
#define MAX_PHONE_LEN 20
#define MAX_LINE_LEN 50

// Single Contact 
typedef struct{
    char name[MAX_NAME_LEN];
    char phone [MAX_PHONE_LEN];
} Contact;

// declaration of function
void addContact();

void showAllContacts();
void removeContact();
void editContact();
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
    printf("Enter phone number: ");
    scanf(" %19[^\n]", newContact->phone);
    
    fprintf(pFile, "%s,%s\n",newContact->name, newContact->phone);

    // closeing file
    fclose(pFile);

    //cleaning memory - pointers
    free(newContact);
    newContact = NULL;

    printf("Contact added successfully!\n");
}

void removeContact() {

    FILE *pFile = fopen("contactList.txt", "r+");

    if(pFile == NULL){
        printf("Could not open file.\n");
        endProgram(1);
    }

    char contactName[MAX_NAME_LEN]; 

    printf("Who you want to delete form contact list (name)? ");
    scanf(" %24[^\n]", contactName);

    FILE *pTempFile = fopen("temp.txt", "w");

    if(pTempFile == NULL){
        printf("Could not open file.\n");
        endProgram(1);
    }

    char line[MAX_LINE_LEN];
    bool found = false;

    while(fgets(line, sizeof(line), pFile)){ 
        line[strcspn(line, "\n")] = 0; // clean out of \n
        char *name = strtok(line, ","); // devides line onto two part with comma, first call returns first part
        if(strcmp(name, contactName) == 0) { // strcmp return 0 if both params are equal
            found = true;
            continue;
        }
        fprintf(pTempFile, "%s,%s\n", name, strtok(NULL, ","));
    }

    // closing both files
    fclose(pTempFile);
    fclose(pFile);

    // remove old file and rename temp file for main file 
    remove("contactList.txt");
    rename("temp.txt", "contactList.txt");

    printf("\n");

    if(found) {
        printf("Contact deleted.\n");
    } 
    else
    {
        printf("Contact not found.\n");
    }
}

void editContact() {

    FILE *pFile = fopen("contactList.txt","r");

    if(pFile == NULL){
        printf("Could not open file.\n");
        endProgram(1);
    }

    FILE *pTempFile = fopen("temp.txt", "w");

    if(pTempFile == NULL){
        printf("Could not open file.\n");
        endProgram(1);
    }

    char contactName[MAX_NAME_LEN]; 

    char newName[MAX_NAME_LEN];
    char newPhone[MAX_PHONE_LEN];

    printf("Which contact do you want to edit (name)? ");
    scanf(" %24[^\n]", contactName);

    char line[MAX_LINE_LEN];
    bool found = false;

    while(fgets(line, sizeof(line), pFile)){ 
        line[strcspn(line, "\n")] = 0;
        char *name = strtok(line, ","); 
        char *phone = strtok(NULL, ",");
        if (phone == NULL) phone = "";
        if(strcmp(name, contactName) == 0) { 
            found = true;

            printf("Enter new name: ");
            scanf(" %24[^\n]", newName);
            printf("Enter new phone number: ");
            scanf(" %19[^\n]", newPhone);

            fprintf(pTempFile, "%s,%s\n", newName, newPhone);
            continue;
        }
        fprintf(pTempFile, "%s,%s\n", name, phone);
    }

    fclose(pTempFile);
    fclose(pFile);

    remove("contactList.txt");
    rename("temp.txt", "contactList.txt");

    printf("\n");

    if(found) {
        printf("Contact edited.\n");
    } 
    else
    {
        printf("Contact not found.\n");
    }
}


// ALL CONTACT FUNCTIONS 
void showAllContacts(){

    FILE *pFile  =fopen("contactList.txt", "r");

    if(pFile == NULL){
        printf("Could not open file.\n");
        endProgram(1);
    }

    char line[MAX_LINE_LEN];

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
        printf("4 - Edit contact\n");
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

            case 4:
                //printf("Editing contact...\n");
                printf("\n");
                editContact();
                break;

            default:
                printf("Invalid option!\n");
        }
    }
}



//EOF