#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

/* Queue */
#define QueueLimit 10  //το όριο μεγέθους της ουράς

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
void maxElement(QueueType *Q, QueueElementType *item);
void minElement(QueueType *Q, QueueElementType *item);


//Main function
int main()
{
    QueueType q;
    QueueElementType maxq, minq;

    CreateQ(&q);

    srand(time(NULL));
    for(QueueElementType i = 0; i < QueueLimit; i++)
        AddQ(&q, rand() % 21); //The second Argument is the value of comma expression...check the theory if you do not remember

    TraverseQ(q);

    maxElement(&q, &maxq);
    printf("Max element: %d\n", maxq);

    minElement(&q, &minq);
    printf("Min element: %d\n", minq);

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


void minElement(QueueType *Q, QueueElementType *item)
{
    QueueElementType el;
    QueueType temp;

    CreateQ(&temp);

    RemoveQ(Q, item);
    AddQ(&temp, *item);
    while(!EmptyQ(*Q))
    {
        RemoveQ(Q, &el);
        AddQ(&temp, el);
        if(el < *item)
            *item = el;
    }

    while(!EmptyQ(temp))
    {
        RemoveQ(&temp, &el);
        AddQ(Q, el);
    }
}

void maxElement(QueueType *Q, QueueElementType *item)
{
    QueueElementType el;
    QueueType temp;

    CreateQ(&temp);

    RemoveQ(Q, item);
    AddQ(&temp, *item);
    while(!EmptyQ(*Q))
    {
        RemoveQ(Q, &el);
        AddQ(&temp, el);
        if(el > *item)
            *item = el;
    }

    while(!EmptyQ(temp))
    {
        RemoveQ(&temp, &el);
        AddQ(Q, el);
    }
}
