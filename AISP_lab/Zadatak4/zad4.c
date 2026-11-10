#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct poly
{
	int coef;
	int expo;
	struct poly* next;

} poly;



int printPoly(poly*);
poly* createPoly(char*);
poly* sortPoly(poly*);
int sumPoly(poly*, poly*);
int multPoly(poly*, poly*);



int main()
{
	poly* poly1 = createPoly("poly1.txt");
	poly* poly2 = createPoly("poly2.txt");

	poly1 = sortPoly(poly1);
	poly2 = sortPoly(poly2);

	sumPoly(poly1, poly2);
	multPoly(poly1, poly2);

	return 0;
}



int printPoly(poly* polynomial)
{
	poly* i = polynomial->next;
	while (i != NULL)
	{
		if (i->expo == 0)
			printf("%d ", i->coef);
		else if (i->coef == 0)
			1;
		else
			printf("%dx^%d ", i->coef, i->expo);
		i = i->next;
	}

	return 0;
}



poly* createPoly(char* filename)
{
	FILE* file = fopen(filename, "r");

	if (file == NULL)
	{
		return 1;
	}


	char* polyStr = (char*)malloc(1024*sizeof(char));
	fgets(polyStr, strlen(polyStr), file);

	poly* newPoly = (poly*)malloc(sizeof(poly));
	newPoly->next = NULL;

	int i = 0;
	int b = 0;
	int coef = 0;
	int expo = 0;
	char* buffer = (char*)malloc(10*sizeof(char));

	for (i; i <= strlen(polyStr); i++)
	{
		if (polyStr[i] == 'x')
		{
			buffer[b] = '\0';
			coef = atoi(buffer);
			buffer = (char*)malloc(10 * sizeof(char));
			b = 0;
		}
		else if (polyStr[i] == ' ' || i == strlen(polyStr))
		{
			buffer[b] = '\0';
			expo = atoi(buffer);
			buffer = (char*)malloc(10 * sizeof(char));
			b = 0;

			poly* element = (poly*)malloc(sizeof(element));
			element->coef = coef;
			element->expo = expo;
			element->next = newPoly->next;
			newPoly->next = element;
		}
		else
		{
			buffer[b] = polyStr[i];
			b++;
		}
	}


	fclose(file);
	free(polyStr);
	free(buffer);

	return newPoly;
}



poly* sortPoly(poly* polynomial)
{
	poly* sortedPoly = (poly*)malloc(sizeof(poly));
	sortedPoly->next = NULL;

	poly* p = polynomial->next;
	poly* s = sortedPoly;

	while (p != NULL)
	{
		poly* element = (poly*)malloc(sizeof(poly));
		element->coef = p->coef;
		element->expo = p->expo;
		element->next = NULL;

		if (s->next == NULL)
			s->next = element;
		else
		{
			while (s->next != NULL && s->next->expo > element->expo)
				s = s->next;

			element->next = s->next;
			s->next = element;
		}

		p = p->next;
		s = sortedPoly;
	}

	return sortedPoly;
}



int sumPoly(poly* poly1, poly* poly2)
{
	poly* summedPoly = (poly*)malloc(sizeof(poly));
	summedPoly->next = NULL;


	poly* p1 = poly1->next;

	while (p1 != NULL)
	{
		poly* element = (poly*)malloc(sizeof(poly));
		element->expo = p1->expo;
		element->coef = p1->coef;

		element->next = summedPoly->next;
		summedPoly->next = element;

		p1 = p1->next;
	}


	poly* p2 = poly2->next;

	while (p2 != NULL)
	{
		poly* element = (poly*)malloc(sizeof(poly));
		element->expo = p2->expo;
		element->coef = p2->coef;

		element->next = summedPoly->next;
		summedPoly->next = element;

		p2 = p2->next;
	}


	summedPoly = sortPoly(summedPoly);


	poly* s = summedPoly->next;

	while (s->next != NULL)
	{
		if (s->expo == s->next->expo)
		{
			s->coef = s->coef + s->next->coef;
			s->next = s->next->next;
		}
		else
			s = s->next;
	}


	printPoly(summedPoly);

	return 0;
}



int multPoly(poly* poly1, poly* poly2)
{
	poly* multedPoly = (poly*)malloc(sizeof(poly));
	multedPoly->next = NULL;

	poly* p1 = poly1->next;
	poly* p2 = poly2->next;

	while (p1 != NULL)
	{
		while (p2 != NULL)
		{
			poly* element = (poly*)malloc(sizeof(poly));
			element->coef = p1->coef * p2->coef;
			element->expo = p1->expo + p2->expo;

			element->next = multedPoly->next;
			multedPoly->next = element;

			p2 = p2->next;
		}

		p1 = p1->next;
	}

	multedPoly = sortPoly(multedPoly);
	printPoly(multedPoly);

	return 0;
}