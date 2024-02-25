#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define megisto_plithos 201

typedef enum {
    FALSE, TRUE
} boolean;

typedef boolean typos_synolou[megisto_plithos];
typedef int stoixeio_synolou;

//Function prototypes
void displayset(typos_synolou set , stoixeio_synolou first, stoixeio_synolou last);
void Dimiourgia(typos_synolou synolo);
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean isPrime(stoixeio_synolou num);
void inputData(stoixeio_synolou *first, stoixeio_synolou *last);
void createPrimeSet(typos_synolou Primaries, stoixeio_synolou first, stoixeio_synolou last);

int main()
{
	stoixeio_synolou first,last;
	typos_synolou primaries;

	inputData(&first, &last);
	createPrimeSet(primaries, first, last);
	displayset(primaries, first, last);

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

void displayset(typos_synolou set , stoixeio_synolou first, stoixeio_synolou last)
{
	stoixeio_synolou i;

	for (i=first; i <= last; i++)
	{
		if(Melos(i,set))
			printf("%d ",i);
	}
	printf("\n");
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

boolean isPrime(stoixeio_synolou num)
{
	stoixeio_synolou ctr=2; //Numbers to check if my num is divided with them.Start from 2 because 1 is already divide my num

	while(ctr<=num)
	{
		if(num % ctr == 0) //If my mod equals to 0 i must stop because i found a number that divides my num
			break;
		else
			ctr++; //If the mod of division is different than 0 i must check the next number if it divides my num
	}

	if(ctr>=2 && ctr<num) //If the loop stopped i check if there is a number within my limits that divides my num. If that happens my num is not a primary
		return FALSE;
	else
		return TRUE;
}

void inputData(stoixeio_synolou *first, stoixeio_synolou *last)
{
	printf("Insert two numbers. It must be number1 < number2 and\n2 <= numbers <= 200: ");
	do
	{
		scanf("%d%d", first, last);
		if((*first >= *last) || (*first<2 || *first > 200) || (*last < 2 || *last >200))
			printf("Insert valid data.\n");
		getchar();//To absorve the \n from input
	}
	while((*first>= *last) || (*first <2 || *first > 200) || (*last<2 || *last > 200));
}

void createPrimeSet(typos_synolou Primaries, stoixeio_synolou first, stoixeio_synolou last)
{
	Dimiourgia(Primaries);
	stoixeio_synolou ctr=0;

	while(first+ctr <= last)
	{
		Primaries[first+ctr]= isPrime(first+ctr);
		ctr++;
	}
}
