#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define megisto_plithos 256
#define LSIZE 26
#define SIZESET1 4
#define SIZESET2 9

typedef enum {
    FALSE, TRUE
} boolean;

typedef boolean typos_synolou[megisto_plithos];
typedef int stoixeio_synolou;

//Function prototypes
void Dimiourgia(typos_synolou synolo);
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean IsaSynola(typos_synolou s1, typos_synolou s2);
boolean Yposynolo(typos_synolou s1, typos_synolou s2);
void EnosiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou enosi);
void TomiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou tomi);
void DiaforaSynolou(typos_synolou s1, typos_synolou s2, typos_synolou diafora);
void create(typos_synolou capital, typos_synolou S, typos_synolou T, int sizeset1, int sizeset2, int letsize);
void EmfanisiSynolou(stoixeio_synolou row, typos_synolou set);



int main()
{
	typos_synolou Capital, S, T, EnosiSet, TomiSet, DiaforaSet ;


	create(Capital, S, T, SIZESET1,SIZESET2, LSIZE);
	EmfanisiSynolou(megisto_plithos, Capital);
	EmfanisiSynolou(megisto_plithos, S);
	EmfanisiSynolou(megisto_plithos, T);

	if(IsaSynola(S,T))
		printf("ISA SYNOLA\n");
	if(Yposynolo(S,T))
		printf("S YPOSYNOLO T\n");
	if(IsaSynola(T,S))
		printf("T YPOSYNOLO S\n");

	EnosiSynolou(S,T, EnosiSet);
	TomiSynolou(S,T, TomiSet);
	DiaforaSynolou(S,T, DiaforaSet);

	EmfanisiSynolou(megisto_plithos,EnosiSet );
	EmfanisiSynolou(megisto_plithos,TomiSet);
	EmfanisiSynolou(megisto_plithos,DiaforaSet );

	system("pause");
	return 0;
}

//Function definition
void Dimiourgia(typos_synolou synolo)
/* Λειτουργία: Δημιουργεί ένα σύνολο χωρίς στοιχεία, δηλαδή το κενό σύνολο.
   Επιστρέφει: Το κενό σύνολο
*/
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        synolo[i] = FALSE;
}


void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo)
/* Δέχεται:    Ένα σύνολο και ένα στοιχείο.
   Λειτουργία: Εισάγει το στοιχείο στο σύνολο.
   Επιστρέφει: Το τροποποιημένο σύνολο
*/
{
    synolo[stoixeio] = TRUE;
}


boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo)
/* Δέχεται:    Ένα σύνολο και ένα στοιχείο.
   Λειτουργία: Ελέγχει αν το στοιχείο είναι μέλος του συνόλου.
   Επιστρέφει: Επιστρέφει TRUE αν το στοιχείο είναι μέλος του και FALSE διαφορετικά
*/
{
    return synolo[stoixeio];
}


boolean IsaSynola(typos_synolou s1, typos_synolou s2)
/* Δέχεται:     Δύο σύνολα s1 και s2.
   Λειτουργία: Ελέγχει αν τα δύο σύνολα είναι ίσα.
   Επιστρέφει: Επιστρέφει TRUE αν τα δύο σύνολα έχουν τα ίδια στοιχεία και FALSE διαφορετικά
*/
{
    stoixeio_synolou i;
    boolean isa;

    isa = TRUE;
    i=0;
    while (i < megisto_plithos && isa)
        if (Melos(i,s1) != Melos(i,s2))
            isa = FALSE;
        else
            i++;
    return isa;
}

boolean Yposynolo(typos_synolou s1, typos_synolou s2)
/* Δέχεται:     Δύο σύνολα s1 και s2.
   Λειτουργία: Ελέγχει αν το σύνολο s1 είναι υποσύνολο του s2.
   Επιστρέφει: Επιστρέφει true αν το σύνολο s1 είναι ένα υποσύνολο του s2,
                δηλαδή αν κάθε στοιχείο του s1 είναι και στοιχείο του s2
*/
{
    stoixeio_synolou i;
    boolean yposyn;

    yposyn = TRUE;
    i=0;
    while (i < megisto_plithos && yposyn)
        if (Melos(i, s1) && !Melos(i, s2))
            yposyn = FALSE;
        else
            i++;
    return yposyn;
}

void EnosiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou enosi)
/* Δέχεται:     Δύο σύνολα s1 και s2.
   Λειτουργία: Δημιουργεί ένα νέο σύνολο με τα στοιχεία που ανήκουν ή στο s1 ή
                στο s2 ή και στα δύο σύνολα.
   Επιστρέφει: Επιστρέφει το σύνολο enosi που προκύπτει από την ένωση των συνόλων s1 και s2
*/
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        enosi[i] = Melos(i, s1) || Melos(i, s2);
}

void TomiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou tomi)
/* Δέχεται:     Δύο σύνολα s1 και s2.
   Λειτουργία: Δημιουργεί ένα νέο σύνολο με τα στοιχεία που ανήκουν και στα δύο σύνολα s1 και s2.
   Επιστρέφει: Επιστρέφει το σύνολο tomi που προκύπτει από την τομή των συνόλων s1 και s2
*/
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        tomi[i] = Melos(i, s1) && Melos(i, s2);
}

void DiaforaSynolou(typos_synolou s1, typos_synolou s2, typos_synolou diafora)
/* Δέχεται: Δύο σύνολα s1 και s2.
 Λειτουργία: Δημιουργεί ένα νέο σύνολο με τα στοιχεία που ανήκουν στο σύνολο s1 και δεν ανήκουν στο s2.
 Επιστρέφει: Επιστρέφει το σύνολο diafora που προκύπτει από την διαφορά των συνόλων s1-s2.
*/
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        diafora[i] = Melos(i, s1) && (!Melos(i, s2));
}


void create(typos_synolou capital, typos_synolou S, typos_synolou T, int sizeset1, int sizeset2, int letsize)
{
	stoixeio_synolou i;

	Dimiourgia(capital);
	Dimiourgia(S);
	Dimiourgia(T);

	for(i=0; i<letsize; i++)
		Eisagogi('A'+i, capital);

	for(i=0; i<sizeset1; i++)
		Eisagogi('A'+i, S);

	for(i=0; i<sizeset2; i+=2)
		Eisagogi('A'+i, T);

}


void EmfanisiSynolou(stoixeio_synolou row, typos_synolou set)
{
	stoixeio_synolou i;
	char Alpha[27]={'\0'};

	for(i=0; i<LSIZE; i++)
		Alpha[i]='A'+i; //Define a string with value ABCDEFG....Z

	for(i=0; i< LSIZE; i++)
	{
			if(Melos(Alpha[i], set))
				printf(" %c", Alpha[i]);
	}
	printf("\n");
}
