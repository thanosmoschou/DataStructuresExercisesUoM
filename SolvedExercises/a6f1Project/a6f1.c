#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define megisto_plithos 256       //μέγιστο πλήθος στοιχείων συνόλου //10
#define RANGE 256         //To create a table with positions equal to the max value of extended ASCII in order to place TRUE in the right positions for my capital letters
#define LET 26
#define SIZE 81

typedef enum {
    FALSE, TRUE
} boolean;

typedef boolean typos_synolou[megisto_plithos];
typedef int stoixeio_synolou;

//Function prototypes
void Dimiourgia(typos_synolou synolo);
void Katholiko(typos_synolou synolo);
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo);
void Diagrafi(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean KenoSynolo(typos_synolou synolo);
boolean IsaSynola(typos_synolou s1, typos_synolou s2);
boolean Yposynolo(typos_synolou s1, typos_synolou s2);
void EnosiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou enosi);
void TomiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou tomi);
void DiaforaSynolou(typos_synolou s1, typos_synolou s2, typos_synolou diafora);
void menu(int *choice);
void displayset(typos_synolou set);
void createAlphabetSet(typos_synolou Capital);
void createVowelSet(typos_synolou Vowels);
boolean isVowel(int c, typos_synolou Vowels);
void vowelCount(int row, char str[], typos_synolou Capital, typos_synolou Vowels , stoixeio_synolou *ctr);


//Main function
int main()
{
    typos_synolou Capital;
	typos_synolou Vowels;
	char str[SIZE];
	stoixeio_synolou ctr;

	createVowelSet(Vowels);
	createAlphabetSet(Capital);
	displayset(Capital);
	displayset(Vowels);

	int term=0;

	do
	{
		printf("Give a string with uppercase characters: ");
		gets(str); //Gets doesn't read  \n at the end of a string in contrast with fgets that reads \n and also both of them put \0 at the end

		vowelCount(SIZE, str, Capital, Vowels , &ctr);
		printf("Number of vowels: %d\n", ctr);

		term++;
		for(int i=0; i<strlen(str); i++)
			str[i]='\0';

		printf("\n");
	}while(term<=2);


	system("PAUSE");
	return 0;
}

void menu(int *choice)
{
  printf("\nXRHSIMOPOIHSE TIS PARAKATW ENTOLES GIA NA ELEGJEIS TO unit SetADT\n");
  printf("1 ---- DHMIOYRGIA SYNOLOU\n");
  printf("2 ---- KA8OLIKO\n");
  printf("3 ---- EISAGWGH\n");
  printf("4 ---  DIAGRAFH\n");
  printf("5 ---  MELOS\n");
  printf("6 ---- KENO SYNOLO\n");
  printf("7 ---- ISA SYNOLA\n");
  printf("8 ---- YPOSYNOLO\n");
  printf("9 ---- ENOSH 2 SYNOLWN\n");
  printf("10 ---- TOMH 2 SYNOLWN\n");
  printf("11 ---- DIAFORA SYNOLOU\n");
  printf("12 ---- EXIT\n");
  printf("\nChoice 1-12: ");
  do
    {
    	scanf("%d", choice);
    } while (*choice<1 && *choice>12);
}


void displayset(typos_synolou set)
{
	stoixeio_synolou i;

	for (i=0;i < megisto_plithos;i++)
	{
		if(Melos(i,set))
			printf(" %c",i);
	}
	printf("\n");
}

void Dimiourgia(typos_synolou synolo)
/* Λειτουργία: Δημιουργεί ένα σύνολο χωρίς στοιχεία, δηλαδή το κενό σύνολο.
   Επιστρέφει: Το κενό σύνολο
*/
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        synolo[i] = FALSE;
}

void Katholiko(typos_synolou synolo)
/* Δέχεται:     Ένα σύνολο.
   Λειτουργία: Δημιουργεί ένα σύνολο με όλα τα στοιχεία παρόντα,
                έτσι όπως ορίστηκε στο τμήμα δηλώσεων του προγράμματος.
   Επιστρέφει: Το καθολικό σύνολο που δημιουργήθηκε
*/
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        synolo[i] = TRUE;
}

void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo)
/* Δέχεται:    Ένα σύνολο και ένα στοιχείο.
   Λειτουργία: Εισάγει το στοιχείο στο σύνολο.
   Επιστρέφει: Το τροποποιημένο σύνολο
*/
{
    synolo[stoixeio] = TRUE;
}

void Diagrafi(stoixeio_synolou stoixeio, typos_synolou synolo)
/* Δέχεται:     Ένα σύνολο και ένα στοιχείο.
   Λειτουργία:  Διαγράφει το στοιχείο από το σύνολο.
   Επιστρέφει:  Το τροποποιημένο σύνολο
*/
{
    synolo[stoixeio] = FALSE;
}

boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo)
/* Δέχεται:    Ένα σύνολο και ένα στοιχείο.
   Λειτουργία: Ελέγχει αν το στοιχείο είναι μέλος του συνόλου.
   Επιστρέφει: Επιστρέφει TRUE αν το στοιχείο είναι μέλος του και FALSE διαφορετικά
*/
{
    return synolo[stoixeio];
}

boolean KenoSynolo(typos_synolou synolo)
/*
Δέχεται: Ένα σύνολο.
 Λειτουργία: Ελέγχει αν το σύνολο είναι κενό.
 Επιστρέφει: Επιστρέφει TRUE αν το σύνολο είναι κενό και FALSE διαφορετικά
*/
{
    stoixeio_synolou i;
    boolean keno;

    keno=TRUE;
    i = 0;

    while (i < megisto_plithos  && keno) {
        if (Melos(i, synolo))
            keno = FALSE;
        else
            i++;
    }
    return keno;
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

void createAlphabetSet(typos_synolou Capital)
{
	stoixeio_synolou i;

	Dimiourgia(Capital);

	for(i=0; i<LET; i++)
		Eisagogi('A'+i, Capital);
}

void createVowelSet(typos_synolou Vowels)
{
	Dimiourgia(Vowels);

	Eisagogi('A', Vowels);
	Eisagogi('E', Vowels);
	Eisagogi('I', Vowels);
	Eisagogi('O', Vowels);
	Eisagogi('U', Vowels);
	Eisagogi('Y', Vowels);
}

boolean isVowel(int c, typos_synolou Vowels)
{
	return Melos(c, Vowels); //Don't mind because c is a character because characters are small integers so this variable is equal to an integer index
}


void vowelCount(int row, char str[], typos_synolou Capital, typos_synolou Vowels , stoixeio_synolou *ctr)
{
	*ctr=0;

	stoixeio_synolou i=0;

	while(i<strlen(str))
	{
		if(!Melos(str[i],Capital))
			printf("Invalid character detected: %c-%d\n", str[i], str[i]);

		if(isVowel(str[i], Vowels))
			(*ctr)++;
		i++;
	}
}
