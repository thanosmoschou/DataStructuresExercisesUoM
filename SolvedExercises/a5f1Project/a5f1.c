#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define megisto_plithos 1000         //μέγιστο πλήθος στοιχείων συνόλου

typedef enum {
    FALSE, TRUE
} boolean;

typedef boolean typos_synolou[megisto_plithos];
typedef int stoixeio_synolou;

//Function prototypes
void Dimiourgia(typos_synolou synolo);
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo);
void displayset(typos_synolou set);
boolean isFibonacci(typos_synolou set, stoixeio_synolou num);
void createFibonacciSet(typos_synolou fibonaccifreq, stoixeio_synolou threshold);

//Main function
int main()
{
	typos_synolou fibonaccifreq;
	stoixeio_synolou num, threshold;
	char ch;

	do //Input within the limits
	{
		printf("Give the max number for the fibonacci frequence[2...1000]: ");
		scanf("%d%c", &threshold, &ch); //ch is for \n
	}
	while(threshold<2 || threshold>1000);

	createFibonacciSet(fibonaccifreq, threshold); //Create the Fibonacci frequence
	displayset(fibonaccifreq); //Show frequence on the screen

	while(1)
	{
		printf("Insert a number in order to check if it is in the fibonacci frequence of %d(Give negative to stop): ", threshold);
		scanf("%d%c", &num, &ch); //ch is for \n

		if(num<0)
			break;

		if(isFibonacci(fibonaccifreq, num))
			printf("Fibonacci!\n");
		else
			printf("Not Fibonacci...\n");

	}

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

void displayset(typos_synolou set)
{
	stoixeio_synolou i;

	for (i=0;i < megisto_plithos;i++)
	{
		if(Melos(i,set))
			printf(" %d",i);
	}
	printf("\n");
}

boolean isFibonacci(typos_synolou set, stoixeio_synolou num)
{
	return Melos(num,set);
}

void createFibonacciSet(typos_synolou fibonaccifreq, stoixeio_synolou threshold)
{
	stoixeio_synolou i1, i2, sum;

	Dimiourgia(fibonaccifreq);

	i1=0;
	i2=1;
	sum=i1+i2;

	Eisagogi(i1, fibonaccifreq);
	Eisagogi(i2,fibonaccifreq);

	while(sum<=threshold)
	{
		Eisagogi(sum, fibonaccifreq); //Check fibonacci theory
		i1=i2;
		i2=sum;
		sum=i1+i2;
	}
}
