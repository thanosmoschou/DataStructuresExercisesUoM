#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

/* Queue */
#define QueueLimit 10  //το όριο μεγέθους της ουράς

typedef int QueueElementType;   /* ο τύπος δεδομένων των στοιχείων της ουράς
                                  ενδεικτικά τύπος int */

typedef struct {
	int Front, Rear, Count;
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


//Main function
int main()
{
    QueueType q;
    QueueElementType remel;

    CreateQ(&q);

    for(QueueElementType i = 0; i < QueueLimit; i++)
        AddQ(&q, i);

    printf("---a---\n");
    printf("Queue: ");
    TraverseQ(q);
    printf("Front=%d Rear=%d Count=%d\n", q.Front, q.Rear, q.Count);

    printf("---b---\n");
    srand(time(NULL));
    AddQ(&q, rand() % 101);
    printf("Queue: ");
    TraverseQ(q);
    printf("Front=%d Rear=%d Count=%d\n", q.Front, q.Rear, q.Count);

    RemoveQ(&q, &remel);
    printf("---c---\n");
    printf("Queue: ");
    TraverseQ(q);
    printf("Removed item=%d Front=%d Rear=%d Count=%d\n",remel, q.Front, q.Rear, q.Count);

    printf("---d---\n");
    srand(time(NULL));
    AddQ(&q, rand() % 101);
    printf("Queue: ");
    TraverseQ(q);
    printf("Front=%d Rear=%d Count=%d\n", q.Front, q.Rear, q.Count);

    printf("---e---\n");
    printf("Queue: ");
    TraverseQ(q);
    printf("Front=%d Rear=%d Count=%d\n", q.Front, q.Rear, q.Count);

    printf("---f---\n");
    while(!EmptyQ(q))
    {
        RemoveQ(&q, &remel);
        printf("Queue: ");
        TraverseQ(q);
        printf("Removed item=%d Front=%d Rear=%d Count=%d\n",remel, q.Front, q.Rear, q.Count);
    }


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
	Queue->Count = 0;
}


boolean EmptyQ(QueueType Queue)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Ελέγχει αν η ουρά είναι κενή.
   Επιστρέφει: True αν η ουρά είναι κενή, False διαφορετικά
*/
{
	return (Queue.Count == 0);
}


boolean FullQ(QueueType Queue)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Ελέγχει αν η ουρά είναι γεμάτη.
   Επιστρέφει: True αν η ουρά είναι γεμάτη, False διαφορετικά
*/
{
	return (Queue.Count == QueueLimit);
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
		Queue->Count--;
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
		Queue->Count++;
	}
	else
		printf("Full Queue\n");
}


void TraverseQ(QueueType Queue) {
	int current,ctr;
	if (!EmptyQ(Queue)) {
        current = Queue.Front;
        ctr = 0;
	    while (ctr != Queue.Count) {
            printf("%d ", Queue.Element[current]);
		  current = (current + 1) % QueueLimit;
		  ctr++;
	   }
	   printf("\n");
    }
    else printf("Empty Queue\n");
}
