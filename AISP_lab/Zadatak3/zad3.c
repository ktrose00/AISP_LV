#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct osoba
{
	char ime[50];
	char prezime[50];
	int godina;
	struct osoba* next;

} osoba;


osoba* stvOsobu(void);
int printLista(osoba*);
int dodPoc(osoba*, osoba*);
int dodKraj(osoba*, osoba*);
int dodIza(osoba*, osoba*);
int dodIspred(osoba*, osoba*);
int uklOsobu(osoba*);
int findPrezime(osoba*);
int sortPrez(osoba*);
int writeDat(osoba*);
int readDat(osoba*);


int main()
{
	osoba* head = (osoba*)malloc(sizeof(osoba));
	strcpy(head->ime, "Header");
	head->next = NULL;

	printf("\nDodavanje osobe na pocetak:\n");
	osoba* os1 = stvOsobu();
	dodPoc(head, os1);
	printLista(head);

	printf("\nDodavanje osobe na kraj:\n");
	osoba* os2 = stvOsobu();
	dodKraj(head, os2);
	printLista(head);

	printf("\nDodavanje osobe iza neke druge po prezimenu:\n");
	osoba* os3 = stvOsobu();
	dodIza(head, os3);
	printLista(head);

	printf("\nDodavanje osobe na ispred neke druge po prezimenu:\n");
	osoba* os4 = stvOsobu();
	dodIspred(head, os4);
	printLista(head);

	printf("\nPretrazivanje osobe po prezimenu:\n");
	findPrezime(head);

	printf("\nUklanjanje osobe po prezimenu:\n");
	uklOsobu(head);
	printLista(head);

	printf("\nSortiranje osoba po prezimenu:\n");
	sortPrez(head);

	printf("\nUpis u datoteku, citanje iz datoteke i ispis nove liste:\n");
	writeDat(head);
	osoba* head1 = (osoba*)malloc(sizeof(osoba));
	strcpy(head1->ime, "Header");
	head1->next = NULL;
	readDat(head1);
	printLista(head1);

	return 0;
}


osoba* stvOsobu()
{
	osoba* os = (osoba*)malloc(sizeof(osoba));
	os->next = NULL;

	printf("Unesite ime, prezime i godinu rodjenja osobe: ");
	scanf("%s %s %d", os->ime, os->prezime, &os->godina);

	return os;
}


int printLista(osoba* head)
{
	osoba* i = head->next;
	while (i != NULL)
	{
		printf("\nIme: %s\nPrezime: %s\nGodina rodjenja: %d\n----------------------\n", i->ime, i->prezime, i->godina);
		i = i->next;
	}

	return 0;
}


int dodPoc(osoba* head, osoba* os)
{
	os->next = head->next;
	head->next = os;

	return 0;
}


int dodKraj(osoba* head, osoba* os)
{
	osoba* i = head;

	while (i->next != NULL)
		i = i->next;

	i->next = os;

	return 0;
}


int dodIza(osoba* head, osoba* os)
{
	char* prezime = (char*)malloc(sizeof(head->prezime));

	printf("Napisite prezime osobe iza koje zelite dodati element: ");
	scanf("%s", prezime);

	osoba* i = head->next;

	while (i != NULL && strcmp(i->prezime, prezime) != 0)
		i = i->next;

	if (i != NULL)
	{
		printf("Osoba pronadjena! Dodavam...\n");
		os->next = i->next;
		i->next = os;
	}
	else
	{
		printf("Osoba nije u listi!\n");
	}

	return 0;
}


int dodIspred(osoba* head, osoba* os)
{
	char* prezime = (char*)malloc(sizeof(head->prezime));

	printf("Napisite prezime osobe ispred koje zelite dodati element: ");
	scanf("%s", prezime);

	osoba* i = head;

	while (i->next != NULL && strcmp(i->next->prezime, prezime) != 0)
		i = i->next;

	if (i->next != NULL)
	{
		printf("Osoba pronadjena! Dodavam...\n");
		os->next = i->next;
		i->next = os;
	}
	else
	{
		printf("Osoba nije u listi!\n");
	}

	return 0;
}


int findPrezime(osoba* head)
{
	char* prezime = (char*)malloc(sizeof(head->prezime));

	printf("Unesite prezime osobe koju zelite pronaci: ");
	scanf("%s", prezime);

	osoba* i = head->next;

	while (i != NULL && strcmp(i->prezime, prezime) != 0)
		i = i->next;

	if (i != NULL)
	{
		printf("Osoba pronadjena!\n");
	}
	else
	{
		printf("Osoba nije u listi!\n");
	}

	return 0;
}


int sortPrez(osoba* head)
{
	osoba* sortedHead = (osoba*)malloc(sizeof(osoba));
	strcpy(sortedHead->ime, "Header");
	sortedHead->next = NULL;

	osoba* i = head->next;

	while (i != NULL)
	{
		osoba* j = sortedHead;

		while (j->next != NULL && strcmp(i->prezime, j->next->prezime) > 0)
			j = j->next;

		osoba* os = (osoba*)malloc(sizeof(osoba));
		strcpy(os->ime, i->ime);
		strcpy(os->prezime, i->prezime);
		os->godina = i->godina;
		os->next = NULL;

		if (j->next == NULL)
		{
			j->next = os;
		}
		else
		{
			os->next = j->next;
			j->next = os;
		}

		i = i->next;
	}

	printLista(sortedHead);

	return 0;
}


int uklOsobu(osoba* head)
{
	char* prezime = (char*)malloc(sizeof(head->prezime));

	printf("Napisite prezime osobe koju zelite ukloniti: ");
	scanf("%s", prezime);

	osoba* i = head;

	while (i->next != NULL && strcmp(prezime, i->next->prezime) != 0)
		i = i->next;

	if (i->next != NULL)
	{
		printf("Pronasao osobu! Uklanjam...\n");
		osoba* osl = i->next;
		i->next = i->next->next;
		free(osl);
	}
	else
	{
		printf("Te osobe nema u listi!\n");
	}

	return 0;
}


int writeDat(osoba* head)
{
	FILE* fileW = fopen("studenti.txt", "w");

	if (fileW == NULL)
	{
		return 1;
	}
	else
	{
		osoba* i = head->next;

		while (i != NULL)
		{
			fprintf(fileW, "%s %s %d\n", i->ime, i->prezime, i->godina);
			i = i->next;
		}

		fclose(fileW);
		return 0;
	}
}


int readDat(osoba* head)
{
	FILE* fileR = fopen("studenti.txt", "r");

	if (fileR == NULL)
	{
		return 1;
	}
	else
	{
		osoba* i = head;

		while (feof(fileR) == 0)
		{
			osoba* os = (osoba*)malloc(sizeof(osoba));
			os->next = NULL;

			fscanf(fileR, "%s %s %d\n", os->ime, os->prezime, &os->godina);
			i->next = os;
			i = i->next;
		}

		fclose(fileR);
		return 0;
	}
}