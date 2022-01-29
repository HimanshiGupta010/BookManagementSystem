                         //BOOK MANAGEMENT SYSTEM

//Header Files
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


//Function Declarations
void del(FILE *fp);                  //delete a record from database
void list(FILE *fp);                //display all the existing record
void modify(FILE *fp);               //update record of database
void insert(FILE *fp);               //add a new record in database
void display(FILE *fp);              //display a particular record
void booksold(FILE *fp);             //decrease the number of available books


int verify();                          // for login
int search(FILE *fp, char *name);    //search for a particular record


//Defining Structures
struct
{
    float cost;       //price of the book
    int ncopies;      //total number of available books
    char name[50];    //name of book

}book;                //global variable or object of structre

int count=0;          //global variable to count total number of books present in database

//main function
int main()
{
    FILE *fp;
    int choice;

    fp = fopen("Books.txt","rb+");   //open file in rb+ mode

    if(fp == NULL)
    {
        fp = fopen("Books.txt","wb+");  //if file doesn't exist then open it in wb+ mode

        if(fp == NULL)
        {
            printf("\n\t\tError in opening file\n");
            exit(1);
        }
    }

    verify();     //calling pass() function

    label:

    while(1)                                         //Infinite loop
    {
        system("CLS");
        printf("\t\t\t\t\t ********** BOOK MANAGEMENT SYSTEM ********** \n\n");

        // Menu

        printf("\n\t\t\t1>> Insert a new record\n");
        printf("\t\t\t2>> Delete a record\n");
        printf("\t\t\t3>> Display records of the book\n");
        printf("\t\t\t4>> Modify an existing record\n");
        printf("\t\t\t5>> List all records\n");
        printf("\t\t\t6>> Book Sold\n");
        printf("\t\t\t7>> Exit\n");

        printf("\n\t\t\tEnter your choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            insert(fp);
            system("PAUSE");
            break;
        case 2:
            del(fp);
            system("PAUSE");
            break;
        case 3:
            display(fp);
            system("PAUSE");
            break;
        case 4:
            modify(fp);
            system("PAUSE");
            break;
        case 5:
            list(fp);
            system("PAUSE");
            break;
        case 6:
            booksold(fp);
            system("PAUSE");
            break;
        case 7:
            fclose(fp);
            system("CLS");
            printf("\n\n\n\n\n");
            printf("\t\t\t\t\t ********** HAVE A NICE DAY **********\n\n\n");
            exit(1);
        default:
            goto label;           //For reenter the name of the book
        }
    }
    return 0;
}

int verify()
{
    int a = 0, i = 0;

    char uname[20], c = ' ';
    char pword[10], code[10];
    char user[20] = "Himanshi._010";
    char pass[10] = "password";

    do
    {
        system("CLS");
        printf("\n\t\t\t\t\t  *********  LOGIN FORM  *********  ");
        printf("\n\n\n\n                        ENTER USERNAME: ");
        scanf("%s", &uname);
        printf("\n                        ENTER PASSWORD: ");

        while(i < 10)
        {
            pword[i] = getch();
            c = pword[i];
            if(c == 13)
                break;
            else
                printf("*");
            i++;
        }

        pword[i] = '\0';

        i = 0;

        if(strcmp(uname, user) == 0 && strcmp(pword, pass) == 0)
        {
            printf(" \n\n\n\n\t\t\t\t ********** WELCOME! LOGIN IS SUCCESSFUL **********\n");
            break;
        }
        else
        {
            printf("\n\n\n\n\t\t\t\t\t    SORRY! LOGIN IS UNSUCCESSFUL\n");
            getch();
            a++;
        }

    }while(a <= 2);

    if(a > 2)
    {
        printf("\n\n\n\t\t\tYou have entered the wrong username and password for three times !!!!\n");
        system("PAUSE");
        exit(1);
    }

    getch();
    system("CLS");
}

void insert(FILE *fp)
{
    char name[50];


    NAME:

        system("CLS");

        printf("\t\t\t\t\t ********** BOOK MANAGEMENT SYSTEM ********** \n\n");


        printf("\n\t\t\tEnter book name \t: ");
        fflush(stdin);
        gets(name);

        rewind(fp);

        while(fread(&book, sizeof(book), 1, fp)==1)
        {
            if(strcmp(book.name, name)==0)
            {
                printf("\a\n\n\n\t\t\t\t\t\t   BOOK NAME IS ALREADY EXIST\n\n");
                system("PAUSE");
                goto NAME;
            }
        }

        strcpy(book.name, name);
        printf("\n\t\t\tEnter numbers of copies : ");
        scanf("%d", &book.ncopies);

        printf("\n\t\t\tEnter cost of book \t: ");
        scanf("%f", &book.cost);

        fseek(fp,0,2);

        fwrite(&book, sizeof(book), 1, fp);

        printf("\n\n\n\t\t\t\t\t     ----- RECORD ADDED SUCCESSFULLY -----\n\n\n");
}

void del(FILE *fp)
{
    FILE *fptr;
    char name[50];

    system("CLS");

    printf("\t\t\t\t\t ********** BOOK MANAGEMENT SYSTEM ********** \n\n");

    printf("\n\n\t\t\tEnter the name of book to be deleted from database : ");
    fflush(stdin);
    gets(name);

    printf("\n");

    if(search(fp, name) == 0)
    {
        return;
    }

    fptr = fopen("temp.txt","wb");

    rewind(fp);

    while(fread(&book, sizeof(book), 1, fp) == 1)
    {
        if(strcmp(name, book.name)!= 0)
        {
            fwrite(&book, sizeof(book), 1, fptr);
        }
    }

    fclose(fp);
    fclose(fptr);

    remove("Books.txt");
    rename("temp.txt", "Books.txt");

    printf("\n\n\n\t\t\t\t\t\t\tRECORD DELETED.......\n\n");

    fp = fopen("Books.txt", "rb+");
}

void modify(FILE *fp)
{
    char name[50];
    long size = sizeof(book);

    system("CLS");

    printf("\t\t\t\t\t ********** BOOK MANAGEMENT SYSTEM ********** \n\n");

    printf("\n\t\t\tEnter the name of the book to be modified : ");
    fflush(stdin);
    gets(name);

    if(search(fp, name) == 1)
    {
         printf("\n\t\t\tEnter new data-->\n\n");


    printf("\n\t\t\tEnter numbers of copies : ");
    scanf("%d", &book.ncopies);

    printf("\n\t\t\tEnter cost of book \t: ");
    scanf("%f", &book.cost);

    fseek(fp, -size, 1);

    fwrite(&book, sizeof(book), 1, fp);

    printf("\n\n\n\t\t\t\t\t     ----- RECORD UPDATED SUCCESSFULLY -----\n\n");

    }
}

void booksold(FILE *fp)
{
    char name[50];
    long size = sizeof(book);

    system("CLS");

    printf("\t\t\t\t\t ********** BOOK MANAGEMENT SYSTEM ********** \n\n");

    printf("\n\n\n\t\t\tEnter the name of the book to be sold : ");
    fflush(stdin);
    gets(name);

    if(search(fp, name) == 1)
    {
        if(book.ncopies > 0)
        {
            book.ncopies--;

            fseek(fp, -size, 1);
            fwrite(&book, sizeof(book), 1, fp);

            printf("\n\n\n\n\n\t\t\t\t\t\t ***** ONE BOOK SOLD *****\n\n\n");
            printf("\n\t\t\t\t\t     NOW NUMBER OF COPIES AVAILABLE : %d\n", book.ncopies);
        }
        else
            printf("\n\n\n\t\t\t\t\t\t    \aBOOK IS OUT OF STOCK.\n\n");
    }
}

void display(FILE *fp)
{
    char name[50];

    system("CLS");

    printf("\t\t\t\t\t ********** BOOK MANAGEMENT SYSTEM ********** \n\n");

    printf("\n\n\t\t\tEnter the name of the book : ");
    fflush(stdin);
    gets(name);

    printf("\n\n\n\t\t\t\t\t\t----------------------------------");
    if(search(fp, name) == 1)
    {
        printf("\n\n\t\t\t\t\t\t     Name    : \t%s\n", book.name);
        printf("\t\t\t\t\t\t     Copies  : \t%d\n", book.ncopies);
        printf("\t\t\t\t\t\t     Cost    : \t%f\n\n", book.cost);
    }

    printf("\t\t\t\t\t\t----------------------------------\n\n");
}

int search(FILE *fp,char *name)
{
    int flag = 0;
    rewind(fp);

    while(fread(&book, sizeof(book), 1, fp) == 1)
    {
        if(strcmp(name, book.name) == 0)
        {
            flag = 1;
            break;
        }
    }

    if(flag == 0)
    {
        printf("\a\n\n\t\t\t\t\t\t     Name not found in file\n\n");
    }

    return flag;
}

void list(FILE *fp)
{

    system("CLS");

    printf("\t\t\t\t\t ********** BOOK MANAGEMENT SYSTEM ********** \n\n\n\n\n");

    printf("\t\t\t\t\t -------------------------------------------");

    printf("\n\n\t\t\t\t\t NAME\t\tCOPIES\t\tCOST\n\n");

    printf("\t\t\t\t\t -------------------------------------------\n");

    rewind(fp);

    if(fread(&book, sizeof(book), 1, fp)==0)
    {
        printf("\n\a\t\t\t\t\t\t\t NO RECORDS!\n");
        printf("\n\t\t\t\t\t -------------------------------------------");
        printf("\n\n\n\n\n");
        return;
    }

    do
    {
        printf("\n\t\t\t\t\t %s\t", book.name);
        printf("\t%d\t\t", book.ncopies);
        printf("%f\n", book.cost);

    }while(fread(&book, sizeof(book), 1, fp)==1);

    printf("\n");
    printf("\t\t\t\t\t -------------------------------------------");
    printf("\n\n");
}

