

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE (128)
#define MEMORY_NOT_ALLOCATED_CORRECT (-1)
#define FILE_DIDNT_OPEN_ERROR (-2)
#define ERROR (-1)
struct _person;
typedef struct _person* position;

typedef struct _person {
	char name[MAX_LINE];
	char lastName[MAX_LINE];
	int birthYear;

	position next;
}person;


int AddFrist(position p, char* name, char* lastName, int birthYear);
int AddLast(position p, char* name, char* lastName, int birthYear);
int PrintList(position p);
position FindByLastName(position p, char* lastName);
int DeleteByLastName(position p, position toDelete);
int DeleteList(position p);
int InsertAfterPerson(position p, char* name, char* lastName, int birthYear);
int InsertBeforePerson(position q, position p, char* name, char* lastName, int birthYear, char* lastNameP);
int WriteIntoFile(position p);
int ReadFromFile(position p);
int bubble_sort(position p);
int main(void) {

	char name[MAX_LINE] = { 0 };
	char lastName[MAX_LINE] = { 0 };
	char lastNameTemp[MAX_LINE] = { 0 };
	int birthYear = 0;
	int choice;

	//allocating head element which is always first in the list
	position head = NULL;
	position temp = NULL;
	head = (position)malloc(sizeof(person));

	if (head == NULL) {
		printf("Memory not allocated correctly!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	//asigning head with values of null
	strcpy(head->name, "");
	strcpy(head->lastName, "");
	head->birthYear = 0;
	head->next = NULL;

	//user decides what he wants and enters values if needed
	while (1) {

		printf("\nChoose what you want to do:\n");
		printf("1 - Insert a person at the beginning of the list\n");
		printf("2 - Insert a person at the end of the list\n");
		printf("3 - Print list\n");
		printf("4 - Find person by last name\n");
		printf("5 - Deleate person by last name\n");
		printf("6 - Insert a person after person with certain last name\n");
		printf("7 - Insert a person before person with certain last name\n");
		printf("8 - Write list into file\n");
		printf("9 - Read list from file\n");
		printf("10 - Sort list by LastName\n");
		printf("11 - Exit\n");
		printf("Your choice: ");
		scanf(" %d", &choice);

		switch (choice)
		{
		case 1:
			printf("Type in name of the person you want to insert: ");
			scanf(" %s", name);
			printf("Type in last name of the person you want to insert: ");
			scanf(" %s", lastName);
			printf("Type in birth year of the person you want to insert: ");
			scanf("%d", &birthYear);
			AddFrist(head, name, lastName, birthYear);
			break;

		case 2:
			printf("Type in name of the person you want to insert: ");
			scanf(" %s", name);
			printf("Type in last name of the person you want to insert: ");
			scanf(" %s", lastName);
			printf("Type in birth year of the person you want to insert: ");
			scanf("%d", &birthYear);
			AddLast(head, name, lastName, birthYear);
			break;

		case 3:
			PrintList(head->next);
			break;
		case 4:
			printf("Type in the last name of a person you want to find: ");
			scanf(" %s", lastName);
			temp = FindByLastName(head, lastName);
			if (temp != NULL)
				printf("\nPerson you were looking for is: %s %s, %d\n", temp->name, temp->lastName, temp->birthYear);
			break;
		case 5:
			printf("Type in the last name of a person you want to delete: ");
			scanf(" %s", lastName);
			temp = FindByLastName(head, lastName);
			DeleteByLastName(head, temp);
			break;

		case 6:
			printf("Type in the last name of a person you want to insert after: ");
			scanf(" %s", lastNameTemp);
			temp = FindByLastName(head, lastNameTemp);
			printf("Type in name of the person you want to insert: ");
			scanf(" %s", name);
			printf("Type in last name of the person you want to insert: ");
			scanf(" %s", lastName);
			printf("Type in birth year of the person you want to insert: ");
			scanf("%d", &birthYear);
			InsertAfterPerson(temp, name, lastName, birthYear);
			break;

		case 7:
			printf("Type in the last name of a person you want to insert before: ");
			scanf(" %s", lastNameTemp);
			temp = FindByLastName(head, lastNameTemp);
			printf("Type in name of the person you want to insert: ");
			scanf(" %s", name);
			printf("Type in last name of the person you want to insert: ");
			scanf(" %s", lastName);
			printf("Type in birth year of the person you want to insert: ");
			scanf("%d", &birthYear);
			InsertBeforePerson(temp, head, name, lastName, birthYear, lastName);
			break;

		case 8:
			WriteIntoFile(head->next);
			break;

		case 9:
			ReadFromFile(head);
			break;

		case 10:
			bubble_sort(head);
			PrintList(head->next);
			break;
		case 11:
			DeleteList(head);
			return EXIT_SUCCESS;
			break;
		default:

			break;
		}

	}

	DeleteList(head);
	return EXIT_SUCCESS;
}






int AddFrist(position p, char* name, char* lastName, int birthYear) {
	//set velues to new position q
	position q = (position)malloc(sizeof(person));
	strcpy(q->name, name);
	strcpy(q->lastName, lastName);
	q->birthYear = birthYear;
	q->next = NULL;


	//get new element Next value of the last element 
	q->next = p->next;
	//set last element Next to new element adress
	p->next = q;

	return EXIT_SUCCESS;
}




int AddLast(position p, char* name, char* lastName, int birthYear) {
	//set velues to new position q
	position q = (position)malloc(sizeof(person));
	strcpy(q->name, name);
	strcpy(q->lastName, lastName);
	q->birthYear = birthYear;
	q->next = NULL;

	//go to last current eleemnt of list
	while (p->next != NULL) {
		p = p->next;
	}
	//get new element Next value of the last element 
	q->next = p->next;
	//set last element Next to new element adress
	p->next = q;

	return EXIT_SUCCESS;
}


int PrintList(position p) {
	//if there is no positition head->Next element return error
	if (p == NULL) {
		printf("Nema elemenata, lista je prazna!");
		return ERROR;
	}
	//print values
	else {
		while (p != NULL) {
			printf("%s ", p->name);
			printf("%s ", p->lastName);
			printf("%d\n", p->birthYear);

			p = p->next;
		}
		return EXIT_SUCCESS;
	}
}
position FindByLastName(position p, char* lastName)
{
	while (p != NULL && strcmp(p->lastName, lastName) != 0)
	{
		p = p->next;
	}

	if (p == NULL) {
		printf("There is no that element in the list\n");
	}

	return p;
}
int DeleteByLastName(position p, position toDelete) {
	position temp = NULL;
	position prev = NULL;

	temp = (position)malloc(sizeof(person));
	prev = (position)malloc(sizeof(person));


	if (temp == NULL)
	{
		printf("Memory not allocated correctly!\n");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	if (prev == NULL)
	{
		printf("Memory not allocated correctly!\n");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	temp = toDelete;
	prev = p;
	while (prev != NULL && prev->next != toDelete)
	{
		prev = prev->next;
	}

	prev->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}
int DeleteList(position p) {
	position temp = p;

	while (temp->next != NULL)
	{
		temp = p->next;
		p->next = p->next->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}
int InsertAfterPerson(position p, char* name, char* lastName, int birthYear) {

	position q = (position)malloc(sizeof(person));
	strcpy(q->name, name);
	strcpy(q->lastName, lastName);
	q->birthYear = birthYear;
	q->next = NULL;

	if (q == NULL) {
		printf("Memory not allocated correctly!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	q->next = p->next;
	p->next = q;

	return EXIT_SUCCESS;
}

int InsertBeforePerson(position prev, position p, char* name, char* lastName, int birthYear, char* lastNameP) {

	position q = (position)malloc(sizeof(person));
	strcpy(q->name, name);
	strcpy(q->lastName, lastName);
	q->birthYear = birthYear;
	q->next = NULL;

	if (q == NULL) {
		printf("Memory not allocated correctly!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}



	while (p != NULL && p->next != prev)
	{
		p = p->next;
	}

	q->next = p->next;
	p->next = q;

	return EXIT_SUCCESS;
}

int WriteIntoFile(position p) {

	FILE* fp = NULL;
	fp = fopen("file.txt", "w");

	if (fp == NULL) {
		printf("File didn't open correctly!\n");
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (p != NULL) {
		fprintf(fp, "%s %s %d\n", p->name, p->lastName, p->birthYear);
		p = p->next;
	}

	fclose(fp);

	return EXIT_SUCCESS;

}

int ReadFromFile(position p) {

	FILE* fp = NULL;
	fp = fopen("file.txt", "r");

	char name[MAX_LINE] = { 0 };
	char lastName[MAX_LINE] = { 0 };
	int birthYear = 0;


	if (fp == NULL) {
		printf("File didn't open correctly!\n");
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %s %d\n", name, lastName, &birthYear);
		AddFrist(p, name, lastName, birthYear);
	}


	fclose(fp);

	return EXIT_SUCCESS;
}


int bubble_sort(position p) {

	position j, prev_j, temp, end;

	end = NULL;
	while (p->next != end)
	{
		prev_j = p;
		j = p->next;

		while (j->next != end)
		{
			if (strcmp(j->lastName, j->next->lastName) > 0)
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}

			prev_j = j;
			j = j->next;
		}
		end = j;
	}

	return EXIT_SUCCESS;
}