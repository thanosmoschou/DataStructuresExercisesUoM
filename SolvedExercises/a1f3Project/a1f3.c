#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Queue */
#define QueueLimit 21  //το όριο μεγέθους της ουράς
#define LIMQUESTA 20
#define LIMQUESTB 10

typedef int QueueElementType;   /* ο τύπος δεδομένων των στοιχείων της ουράς
                                  ενδεικτικά τύπος int */

typedef struct {
	int Front, Rear;
	QueueElementType Element[QueueLimit];
} QueueType;

typedef enum {FALSE, TRUE} boolean;

//Function prototypes
void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
boolean FullQ(QueueType Queue);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void AddQ(QueueType *Queue, QueueElementType Item);
void TraverseQ(QueueType Queue);
int QSizeA(QueueType Q);
int QSizeB(QueueType *Q);
void EditQueues(QueueType *Q1, int quest);


//Main function
int main()
{
    QueueType Q1;
    QueueElementType element;

    CreateQ(&Q1);

    for(int i = 0; i < LIMQUESTA; i++)
        AddQ(&Q1, i);

    printf("Question a\n");
    EditQueues(&Q1, 1);
    printf("\n");


    for(int i = 0; i < LIMQUESTA; i++)
        AddQ(&Q1, i);

    for(int i = 0; i < LIMQUESTB; i++)
        RemoveQ(&Q1, &element);


    printf("Question b\n");
    EditQueues(&Q1, 2);
    printf("\n");


    printf("Question c\n");
    EditQueues(&Q1, 3);

    return 0;
}


//Function definition
void CreateQ(QueueType *Queue)
/*  Λειτουργία:  Δημιουργεί μια κενή ουρά.
    Επιστρέφει:  Κενή ουρά
*/
{
	Queue->Front = 0;
	Queue->Rear = 0;
}


boolean EmptyQ(QueueType Queue)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Ελέγχει αν η ουρά είναι κενή.
   Επιστρέφει: True αν η ουρά είναι κενή, False διαφορετικά
*/
{
	return (Queue.Front == Queue.Rear);
}


boolean FullQ(QueueType Queue)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Ελέγχει αν η ουρά είναι γεμάτη.
   Επιστρέφει: True αν η ουρά είναι γεμάτη, False διαφορετικά
*/
{
	return ((Queue.Front) == ((Queue.Rear +1) % QueueLimit));
}


void RemoveQ(QueueType *Queue, QueueElementType *Item)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Αφαιρεί το στοιχείο Item από την εμπρός άκρη της ουράς
                αν η ουρά δεν είναι κενή.
   Επιστρέφει: Το στοιχείο Item και την τροποποιημένη ουρά.
   Έξοδος:     Μήνυμα κενής ουρά αν η ουρά είναι κενή
*/
{
	if(!EmptyQ(*Queue))
	{
		*Item = Queue ->Element[Queue -> Front];
		Queue ->Front  = (Queue ->Front + 1) % QueueLimit;
	}
	else
		printf("Empty Queue\n");
}


void AddQ(QueueType *Queue, QueueElementType Item)
/* Δέχεται:    Μια ουρά Queue και ένα στοιχείο Item.
   Λειτουργία: Προσθέτει το στοιχείο Item στην ουρά Queue
                αν η ουρά δεν είναι γεμάτη.
   Επιστρέφει: Την τροποποιημένη ουρά.
   Έξοδος:     Μήνυμα γεμάτης ουράς αν η ουρά είναι γεμάτη
*/
{
	if(!FullQ(*Queue))
	{
		Queue ->Element[Queue ->Rear] = Item;
		Queue ->Rear = (Queue ->Rear + 1) % QueueLimit;
	}
	else
		printf("Full Queue\n");
}


void TraverseQ(QueueType Queue) {
	int current;
	if (!EmptyQ(Queue)) {
        current = Queue.Front;
	    while (current != Queue.Rear) {
            printf("%d ", Queue.Element[current]);
		  current = (current + 1) % QueueLimit;
	   }
	   printf("\n");
    }
    else printf("Empty Queue\n");
}


int QSizeA(QueueType Q)
{
    return (QueueLimit + Q.Rear - Q.Front) % QueueLimit; //Ilopoiisi me kykliki ouraa
}


int QSizeB(QueueType *Q)
{
    QueueType temp;
    QueueElementType ctr, elem;

    CreateQ(&temp);

    ctr = 0;

    while(!EmptyQ(*Q))
    {
        RemoveQ(Q, &elem);
        AddQ(&temp, elem);
        ctr++;
    }

    return ctr;
}


void EditQueues(QueueType *Q1, int quest)
{
    QueueElementType size1 = 0;

    if(quest != 3)
    {
        printf("Printing Queue\n");
        TraverseQ(*Q1);
        size1 = QSizeA(*Q1);
        printf("(QSizeA) size=%d\n", size1);

        printf("Printing Queue\n");
        TraverseQ(*Q1);
        size1 = QSizeB(Q1);
        printf("(QSizeB) size=%d\n", size1);

        printf("Printing Queue\n");
        TraverseQ(*Q1);
    }
    else //Gia logous emfnisis sto c erotima
    {
        size1 = QSizeA(*Q1);
        printf("(QSizeA) size=%d\n", size1);
        printf("Printing Queue\n");
        TraverseQ(*Q1);

        size1 = QSizeB(Q1);
        printf("(QSizeB) size=%d\n", size1);
        printf("Printing Queue\n");
        TraverseQ(*Q1);
    }
}
