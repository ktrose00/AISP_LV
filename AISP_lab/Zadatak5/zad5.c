#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct element
{
	int broj;
	struct element* next;

} element;



int ispisiListu(element*);
element* sortirajListu(element*);
element* presjekLista(element*, element*);
element* unijaLista(element*, element*);



int main()
{
	element* L1 = (element*)malloc(sizeof(element));
	L1->next = NULL;
	element* L2 = (element*)malloc(sizeof(element));
	L2->next = NULL;


	int i1 = 0;
	printf("Unesite koliko elemenata ima prva lista: ");
	scanf("%d", &i1);

	for (i1; i1 > 0; i1--)
	{
		element* noviEl = (element*)malloc(sizeof(element));
		printf("Unesite neki broj: ");
		scanf("%d", &noviEl->broj);

		noviEl->next = L1->next;
		L1->next = noviEl;
	}


	int i2 = 0;
	printf("Unesite koliko elemenata ima druga lista: ");
	scanf("%d", &i2);

	for (i2; i2 > 0; i2--)
	{
		element* noviEl = (element*)malloc(sizeof(element));
		printf("Unesite neki broj: ");
		scanf("%d", &noviEl->broj);

		noviEl->next = L2->next;
		L2->next = noviEl;
	}


	L1 = sortirajListu(L1);
	L2 = sortirajListu(L2);

	printf("\nPrva lista je: ");
	ispisiListu(L1);

	printf("\nDruga lista je: ");
	ispisiListu(L2);


	element* presjek = presjekLista(L1, L2);

	element* unija = unijaLista(L1, L2);
	unija = sortirajListu(unija);

	printf("\nPresjek dvaju lista je: ");
	ispisiListu(presjek);

	printf("\nUnija dvaju lista je: ");
	ispisiListu(unija);


	return 0;
}



int ispisiListu(element* lista)
{
	element* i = lista->next;

	while (i != NULL)
	{
		printf("%d ", i->broj);
		i = i->next;
	}

	return 0;
}



element* sortirajListu(element* lista)
{
	element* sortLista = (element*)malloc(sizeof(element));
	sortLista->next = NULL;
	element* s = sortLista;


	element* i = lista->next;

	while (i != NULL)
	{
		while (s->next != NULL && i != NULL && s->next->broj < i->broj)
			s = s->next;

		if (s->next == NULL)
		{
			element* noviEl = (element*)malloc(sizeof(element));
			noviEl->broj = i->broj;

			noviEl->next = s->next;
			s->next = noviEl;
		}
		else
		{
			element* noviEl = (element*)malloc(sizeof(element));
			noviEl->broj = i->broj;

			noviEl->next = s->next;
			s->next = noviEl;
		}

		s = sortLista;
		i = i->next;
	}


	return sortLista;
}



element* presjekLista(element* L1, element* L2)
{
	element* presjek = (element*)malloc(sizeof(element));
	presjek->next = NULL;


	element* i1 = L1->next;
	element* i2 = L2->next;


	while (i1 != NULL)
	{
		i2 = L2->next;

		while (i2 != NULL)
		{
			if (i1->broj == i2->broj)
			{
				element* noviEl = (element*)malloc(sizeof(element));
				noviEl->broj = i1->broj;

				noviEl->next = presjek->next;
				presjek->next = noviEl;
			}

			i2 = i2->next;
		}

		i1 = i1->next;
	}


	presjek = sortirajListu(presjek);
	return presjek;
}



element* unijaLista(element* L1, element* L2)
{
	element* unija = (element*)malloc(sizeof(element));
	unija->next = NULL;


	element* i1 = L1->next;

	while (i1 != NULL)
	{
		element* noviEl = (element*)malloc(sizeof(element));
		noviEl->broj = i1->broj;

		noviEl->next = unija->next;
		unija->next = noviEl;

		i1 = i1->next;
	}


	element* i2 = L1->next;

	while (i2 != NULL)
	{
		element* noviEl = (element*)malloc(sizeof(element));
		noviEl->broj = i2->broj;

		noviEl->next = unija->next;
		unija->next = noviEl;

		i2 = i2->next;
	}


	unija = sortirajListu(unija);
	return unija;
}