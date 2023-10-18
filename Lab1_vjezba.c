﻿﻿//Napisati program koji prvo pročita koliko redaka ima datoteka, 
//tj.koliko ima studenatazapisanih u datoteci.Nakon toga potrebno 
//je dinamički alocirati prostor za niz strukturastudenata(ime, prezime, bodovi) 
//i učitati iz datoteke sve zapise.Na ekran ispisati ime, prezime, apsolutni i
//relativni broj bodova.Napomena: Svaki redak datoteke sadrži ime i prezime studenta, 
//te broj bodova na kolokviju.relatvan_br_bodova = br_bodova / max_br_bodova * 100

#include <stdio.h>

#define MAX_SIZE 50
#define MAX_LINE 1024
#define FILE_ERROR_OPEN -1

typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
} Student;

int readNoRowsInFile() {
	int counter = 0;
	FILE* filePointer = NULL;
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

int main() {

	int noRows = 0;
	noRows = readNoRowsInFile();
	printf("%d", noRows);

	return 0;
}