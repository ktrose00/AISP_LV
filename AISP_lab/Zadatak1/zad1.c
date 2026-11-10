#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_BODOVA 100

typedef struct
{
    char ime[50];
    char prezime[50];
    double bodovi;
}Student;

int main()
{
    FILE* dat = NULL;
    Student* studenti = NULL;
    int broj = 0;


    dat = fopen("Student.txt", "r");

    if (dat == NULL)
    {
        printf("Datoteka nije otvorena!");
        return 1;
    }


    while (!feof(dat))
    {
        if (fgetc(dat) == '\n')
            broj++;
    }

    printf("studenata je ukupno: %d\n", broj);



    studenti = (Student*)malloc(broj * sizeof(Student));

    if (studenti == NULL && broj > 0)
    {
        printf("greska u alokaciji memorije!");
        fclose(dat);
        return 2;
    }


    rewind(dat);

    for (int i = 0; i < broj; i++)
    {
        fscanf(dat, "%s %s %lf", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
    }



    printf("\nime\tprezime\tbodovi\trelativnibodovi\n");

    for (int i = 0; i < broj; i++)
    {
        double relativni_bod = (double)studenti[i].bodovi / MAX_BODOVA * 100;

        printf("%s\t%s\t%lf\t%lf \n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativni_bod);
    }


    free(studenti);
    fclose(dat);

    return 0;
}