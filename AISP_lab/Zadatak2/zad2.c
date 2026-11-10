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
int dodPoc(osoba*, osoba*);
int dodKraj(osoba*, osoba*);
int printLista(osoba*);
int findPrezime(osoba*);
int uklOsobu(osoba*);


int main()
{
	osoba* head = (osoba*)malloc(sizeof(osoba));
	strcpy(head->ime, "Header");
	head->next = NULL;
	
	osoba* os1 = stvOsobu();
	osoba* os2 = stvOsobu();
	osoba* os3 = stvOsobu();

	dodPoc(head, os1);
	dodKraj(head, os2);
	dodPoc(head, os3);
	printLista(head);
	findPrezime(head);
	uklOsobu(head);
	printLista(head);

	return 0;
}


osoba* stvOsobu()
{
	osoba* os = (osoba*)malloc(sizeof(osoba));
	os->next = NULL;

	printf("Unesite ime osobe: ");
	fgets(os->ime, sizeof(os->ime), stdin);
	
	printf("Unesite prezime osobe: ");
	fgets(os->prezime, sizeof(os->prezime), stdin);

	printf("Unesite godinu rodjenja osobe: ");
	scanf("%d", &os->godina);
	getchar();

	return os;
}


int dodPoc(osoba* head, osoba* os)
{
	os->next = head->next;
	head->next = os;

	return 0;
}


int dodKraj(osoba* head, osoba* os)
{
	osoba* i = head->next;

	while (i->next != NULL)
		i = i->next;

	i->next = os;

	return 0;
}


int uklOsobu(osoba* head)
{
	char* prezime = (char*)malloc(sizeof(head->prezime));
	
	printf("Napisite prezime osobe koju zelite ukloniti: ");
	fgets(prezime, sizeof(prezime), stdin);

	osoba* i = head;

	while (i->next != NULL && strcmp(prezime, i->next->prezime) != 0)
		i = i->next;

	if (i->next != NULL)
	{
		printf("Pronasao osobu!\n");
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


int findPrezime(osoba* head)
{
	char* prezime = (char*)malloc(sizeof(head->prezime));

	printf("Unesite prezime osobe koju zelite pronaci: ");
	fgets(prezime, sizeof(prezime), stdin);

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