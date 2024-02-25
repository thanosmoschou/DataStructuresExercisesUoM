#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Queue */
#define QueueLimit 20  //το όριο μεγέθους της ουράς

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
void GetFrontElementA(QueueType *Q, QueueElementType *el);
void GetFrontElementB(QueueType *Q, QueueElementType *el);
void GetRearElementB(QueueType *Q, QueueElementType *el);
void GetRearElementA(QueueType *Q, QueueElementType *el);


//Main function
int main()
{
    QueueType q;
    QueueElementType i, elem;

    CreateQ(&q);
    for(i = 1; i <= 50; i++)
    {
        if((i % 3) == 0)
            AddQ(&q, i);
    }

    printf("after AddQ: ");
    TraverseQ(q);

    GetFrontElementA(&q, &elem);
    printf("a) -> %d\n", elem);
    printf("after GetFrontElementA: ");
    TraverseQ(q);

    GetFrontElementB(&q, &elem);
    printf("b) -> %d\n", elem);
    printf("after GetFrontElementA: ");
    TraverseQ(q);

    GetRearElementB(&q, &elem);
    printf("c) -> %d\n", elem);
    printf("after GetRearElementB: ");
    TraverseQ(q);

    GetRearElementA(&q, &elem);
    printf("d) -> %d\n", elem);
    printf("after GetFrontElementA: ");
    TraverseQ(q);

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


void GetFrontElementA(QueueType *Q, QueueElementType *el)
{
    //QueueElementType temp;

    RemoveQ(Q, el);
}


void GetFrontElementB(QueueType *Q, QueueElementType *el)
{
    //QueueElementType temp;
    //QueueType qtemp;

    *el = Q->Element[Q->Front];
}


void GetRearElementB(QueueType *Q, QueueElementType *el)
{
    *el = Q->Element[Q->Rear-1];
}


void GetRearElementA(QueueType *Q, QueueElementType *el)
{
    while(!EmptyQ(*Q))
        RemoveQ(Q, el);

}




