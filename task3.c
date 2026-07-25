/*
====================================================
ST5004CEM Operating Systems and Security

Task 3: Secure File Management System

Features:
- User authentication
- File creation
- File reading
- File writing
- File deletion
- File permissions
- File encryption/decryption
- Audit logging

====================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX 256


// Default user credentials
char username[] = "Richard";
char password[] = "12345";


// Login status
int loggedIn = 0;



/*
----------------------------------------------------
Function: logAction()

Purpose:
Creates audit logs for user activities.
----------------------------------------------------
*/
void logAction(const char *action)
{
    FILE *log = fopen("audit.log", "a");

    if(log == NULL)
        return;

    fprintf(log, "%s\n", action);

    fclose(log);
}



/*
----------------------------------------------------
Function: login()

Purpose:
Authenticates user.
----------------------------------------------------
*/
void login()
{
    char user[50];
    char pass[50];


    printf("\nUsername: ");
    scanf("%s", user);


    printf("Password: ");
    scanf("%s", pass);



    if(strcmp(user, username) == 0 &&
       strcmp(pass, password) == 0)
    {
        loggedIn = 1;

        printf("\nLogin Successful.\n");

        logAction("User logged in.");
    }
    else
    {
        printf("\nInvalid Login.\n");

        logAction("Failed login attempt.");
    }
}



/*
----------------------------------------------------
Function: createFile()

Creates a new file.
----------------------------------------------------
*/
void createFile()
{
    if(!loggedIn)
    {
        printf("\nPlease login first.\n");
        return;
    }


    char filename[MAX];


    printf("\nEnter file name: ");
    scanf("%s", filename);


    FILE *fp = fopen(filename, "w");


    if(fp == NULL)
    {
        printf("File creation failed.\n");
        return;
    }


    fclose(fp);


    printf("File created successfully.\n");


    char log[300];

    sprintf(log,"File created: %s",filename);

    logAction(log);
}




/*
----------------------------------------------------
Function: writeFile()

Writes data into a file.
----------------------------------------------------
*/
void writeFile()
{
    if(!loggedIn)
    {
        printf("\nPlease login first.\n");
        return;
    }


    char filename[MAX];
    char text[500];


    printf("\nEnter file name: ");
    scanf("%s", filename);


    FILE *fp = fopen(filename,"a");


    if(fp == NULL)
    {
        printf("File not found.\n");
        return;
    }


    getchar();


    printf("Enter text: ");

    fgets(text,sizeof(text),stdin);



    fprintf(fp,"%s",text);


    fclose(fp);


    printf("Data written successfully.\n");


    char log[300];

    sprintf(log,"Data written: %s",filename);

    logAction(log);
}




/*
----------------------------------------------------
Function: readFile()

Reads file contents.
----------------------------------------------------
*/
void readFile()
{
    if(!loggedIn)
    {
        printf("\nPlease login first.\n");
        return;
    }


    char filename[MAX];
    char ch;


    printf("\nEnter file name: ");

    scanf("%s",filename);



    FILE *fp = fopen(filename,"r");


    if(fp == NULL)
    {
        printf("File not found.\n");
        return;
    }


    printf("\n----- File Content -----\n");


    while((ch=fgetc(fp))!=EOF)
    {
        putchar(ch);
    }


    fclose(fp);


    printf("\n------------------------\n");


    char log[300];

    sprintf(log,"File read: %s",filename);

    logAction(log);
}




/*
----------------------------------------------------
Function: deleteFile()

Deletes a file.
----------------------------------------------------
*/
void deleteFile()
{
    if(!loggedIn)
    {
        printf("\nPlease login first.\n");
        return;
    }


    char filename[MAX];


    printf("\nEnter file name: ");

    scanf("%s",filename);



    if(remove(filename)==0)
    {
        printf("File deleted successfully.\n");


        char log[300];

        sprintf(log,"File deleted: %s",filename);

        logAction(log);
    }
    else
    {
        printf("Delete failed.\n");
    }
}




/*
----------------------------------------------------
Function: encryptFile()

Encrypts file using XOR encryption.
----------------------------------------------------
*/
void encryptFile()
{
    if(!loggedIn)
    {
        printf("\nPlease login first.\n");
        return;
    }


    char filename[MAX];

    char key='K';

    char ch;



    printf("\nEnter file name: ");

    scanf("%s",filename);



    FILE *fp=fopen(filename,"r+");


    if(fp==NULL)
    {
        printf("File not found.\n");
        return;
    }



    while((ch=fgetc(fp))!=EOF)
    {
        fseek(fp,-1,SEEK_CUR);

        fputc(ch^key,fp);

        fflush(fp);
    }



    fclose(fp);



    printf("Encryption completed.\n");


    logAction("File encrypted.");
}





/*
----------------------------------------------------
Function: decryptFile()

Decrypts file.
----------------------------------------------------
*/
void decryptFile()
{
    encryptFile();

    printf("Decryption completed.\n");
}




/*
----------------------------------------------------
Function: setPermissions()

Changes file permissions.
----------------------------------------------------
*/
void setPermissions()
{
    if(!loggedIn)
    {
        printf("\nPlease login first.\n");
        return;
    }


    char filename[MAX];


    printf("\nEnter file name: ");

    scanf("%s",filename);



    if(chmod(filename,0644)==0)
    {
        printf("Permissions changed successfully.\n");

        logAction("File permissions changed.");
    }
    else
    {
        printf("Permission change failed.\n");
    }
}





/*
----------------------------------------------------
Function: viewLog()

Displays audit log.
----------------------------------------------------
*/
void viewLog()
{
    FILE *fp=fopen("audit.log","r");


    if(fp==NULL)
    {
        printf("No audit log found.\n");
        return;
    }


    char ch;


    printf("\n===== Audit Log =====\n");


    while((ch=fgetc(fp))!=EOF)
    {
        putchar(ch);
    }


    fclose(fp);
}




/*
----------------------------------------------------
MAIN FUNCTION

Menu-driven file management system.
----------------------------------------------------
*/
int main()
{
    int choice;


    do
    {

        printf("\n====================================\n");
        printf(" Secure File Management System\n");
        printf("====================================\n");


        printf("1. Login\n");
        printf("2. Create File\n");
        printf("3. Write File\n");
        printf("4. Read File\n");
        printf("5. Delete File\n");
        printf("6. Encrypt File\n");
        printf("7. Decrypt File\n");
        printf("8. Set Permissions\n");
        printf("9. View Audit Log\n");
        printf("10. Exit\n");


        printf("\nEnter choice: ");

        scanf("%d",&choice);



        switch(choice)
        {
            case 1:
                login();
                break;

            case 2:
                createFile();
                break;

            case 3:
                writeFile();
                break;

            case 4:
                readFile();
                break;

            case 5:
                deleteFile();
                break;

            case 6:
                encryptFile();
                break;

            case 7:
                decryptFile();
                break;

            case 8:
                setPermissions();
                break;

            case 9:
                viewLog();
                break;

            case 10:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }


    }while(choice!=10);



    return 0;
}
