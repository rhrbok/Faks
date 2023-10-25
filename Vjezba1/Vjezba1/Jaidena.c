/*1. Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata zapisanih u datoteci. Nakon toga
potrebno je dinamièki alocirati prostor za niz struktura studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran
ispisati ime, prezime, apsolutni i relativni broj bodova. Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj
bodova na kolokviju. relatvan_br_bodova = br_bodova/max_br_bodova*100*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_BUFFER_SIZE (1024)
#define MAX_FILE_NAME (128)
#define MAX_NAME_SIZE (128)
#define MAX_LINE (128)
#define FILE_OPENING_ERROR (-1)
#define GET_INFO_SUCCESS (0)
#define MAX_NUM_POINTS (60)
#define SUCCESS (0)
#define MEMORY_ALLOC_FAIL (-1)


struct _Student;

typedef struct _Student
{
    char name[MAX_NAME_SIZE];
    char surname[MAX_NAME_SIZE];
    int points;

}Student;


int readNoRowsInFile();
int countStudentsFromFile(char*);
int getStudentInfo(char*, int, Student*);
void printStudentInfo(int, Student*);


int main(void)
{

    int i, noRows = 0;
    noRows = readNoRowsInFile();

    if (noRows > 0) {

        FILE* filePointer;
        filePointer = fopen("students.txt", "r");

        Student* stud;
        stud = (Student*)malloc(noRows * sizeof(Student));

        for (i = 0; i < noRows; i++) {
            fscanf(filePointer, " %s %s %lf ", stud[i].name, stud[i].surname, &stud[i].points);
        }

        for (i = 0; i < noRows; i++) {
            printf("%s %s %.2lf %.2lf\%\n", stud[i].name, stud[i].surname, stud[i].points, stud[i].points / MAX_POINTS * 100);
        }

        fclose(filePointer);
    }

    Student* studenti = NULL;
    int i = 0;
    int show = -1;

    
    char fileName[MAX_FILE_NAME] = { 0 };
    int numOfStudents = 0;

    printf("Insert filename > ");
    scanf(" %s", fileName);

    numOfStudents = countStudentsFromFile(fileName);

    if (numOfStudents > 0)
    {
        studenti = (Student*)calloc(numOfStudents, sizeof(Student));
        
        if (studenti == NULL)
        {
            printf("Failed while allocating the memory, exiting the program...\n");
            return MEMORY_ALLOC_FAIL;
        }
    }

   
    if (numOfStudents >= 0)
    {
        printf("Broj studenata u datoteci '%s' je %d\n", fileName, numOfStudents);
     
        show = getStudentInfo(fileName, numOfStudents, studenti);
    }

    
    if (show == 0)
    {
        printStudentInfo(numOfStudents, studenti);
    }
    else
    {
        printf("Error when getting student info from the file!\n");
    }

    
    free(studenti);

    return SUCCESS;
}

int readNoRowsInFile() {
    int counter = 0;
    FILE* filePointer;
    char buffer[MAX_LINE] = { 0 };

    filePointer = fopen("students.txt", "r");
    if (!filePointer) {
        printf("File is not open!\n");
        return FILE_ERROR_OPEN;
    }

    while (!feof(filePointer)) {
        fgets(buffer, MAX_LINE, filePointer);
        counter++;
    }

    fclose(filePointer);

    return counter;
}


int getStudentInfo(char* fileName, int numOfStudents, Student* studenti)
{
    int i = 0;
    int count = 0;
    char buffer[MAX_LINE] = { 0 };

   
    FILE* fp = NULL;
    fp = fopen(fileName, "r");


    
    if (fp == NULL)
    {
        printf("The file '%s' didn't open!\r\n", fileName);
        return FILE_OPENING_ERROR;
    }

    
    for (i = 0; i < numOfStudents; i++)
    {
        char nameInp[MAX_NAME_SIZE] = "";
        char surnameInp[MAX_NAME_SIZE] = "";
        int pointsInp = 0;

        
        while (1)
        {
            fgets(buffer, MAX_BUFFER_SIZE, fp);

            if (strcmp("\n", buffer) != 0)
            {
                break;
            }
        }

        
        sscanf(buffer, "%s %s %d", nameInp, surnameInp, &pointsInp);


        Student* currentStudent = studenti + i;

        
        strcpy(currentStudent->name, nameInp);
        strcpy(currentStudent->surname, surnameInp);
        currentStudent->points = pointsInp;

    }

    
    fclose(fp);

    return GET_INFO_SUCCESS;
}


void printStudentInfo(int numOfStudents, Student* studenti)
{
    int i = 0;
    float rel_points = 0.0;
    printf("\nPrinting student info:\n");

    
    for (i = 0; i < numOfStudents; i++)
    {
        Student stud = *(studenti + i);
       
        rel_points = (((float)stud.points / MAX_NUM_POINTS) * 100);

       
        printf("Student %s %s ima %d apsolutnih odnosno %.2f%% bodova!\n", stud.name, stud.surname, stud.points, rel_points);
    }

}



int countStudentsFromFile(char* fileName)
{
   
    FILE* fp = NULL;
    fp = fopen(fileName, "r");

    int count = 0;
    char buffer[MAX_LINE] = { 0 };


    
    if (fp == NULL)
    {
        printf("The file %s didn't open!\r\n", fileName);
        return FILE_OPENING_ERROR;
    }

    
    while (!feof(fp))
    {
        fgets(buffer, MAX_BUFFER_SIZE, fp);

        if (strcmp("\n", buffer) != 0)
        {
            count++;
        }
    }

    
    fclose(fp);

    
    return count;
}