#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
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
void MoveElem(QueueType *QEven, QueueType *QOdd);
void Filling(QueueType *QEven, QueueType *QOdd);


//Main function
int main()
{
    QueueType qOdd, qEven;

    CreateQ(&qOdd);
    CreateQ(&qEven);

    Filling(&qEven, &qOdd);
    MoveElem(&qEven, &qOdd);

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


void Filling(QueueType *QEven, QueueType *QOdd)
{
    QueueElementType i,el;

    srand(time(NULL));

    for(i = 0; i < QueueLimit; i++)
    {
        el = rand() % 21;
        if(el %2 == 0)
            AddQ(QEven, el);
        else
            AddQ(QOdd, el);
    }
}


void MoveElem(QueueType *QEven, QueueType *QOdd)
{
    QueueElementType el;
    QueueElementType randomEven, randomOdd, sizeOdd, sizeEven, countr;

    srand(time(NULL));

    sizeOdd = (QueueLimit + QOdd->Rear - QOdd->Front) % QueueLimit;
    sizeEven = (QueueLimit + QEven->Rear - QEven->Front) % QueueLimit;

    printf("Size of EvenQueue: %d\n", sizeEven);
    TraverseQ(*QEven);

    printf("Size of OddQueue: %d\n", sizeOdd);
    TraverseQ(*QOdd);

    randomEven = rand() % sizeEven;
    randomOdd = rand() % sizeOdd;

    printf("random number of items=%d\n", randomEven); //For even queue
    countr = 0;

    while(countr < randomEven) //Remove from the head and place it back at the tail
    {
        RemoveQ(QEven, &el);
        AddQ(QEven, el);
        countr++;
    }

    printf("Size of EvenQueue: %d\n", sizeEven);
    TraverseQ(*QEven);


    printf("random number of items=%d\n", randomOdd);
    countr = 0;

    while(countr < randomOdd)
    {
        RemoveQ(QOdd, &el);
        AddQ(QOdd, el);
        countr++;
    }

    printf("Size of OddQueue: %d\n", sizeOdd);
    TraverseQ(*QOdd);

}
