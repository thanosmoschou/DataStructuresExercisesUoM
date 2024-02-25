#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Queue */
#define QueueLimit 100  //το όριο μεγέθους της ουράς

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
QueueElementType GetNthElementA(QueueType *Q, QueueElementType num);
QueueElementType GetNthElementB(QueueType *Q, QueueElementType num);


//Main function
int main()
{
    QueueType q;
    QueueElementType num;
    QueueElementType element;

    CreateQ(&q);

    for(QueueElementType i = 5; i <= 100; i+=5)
        AddQ(&q, i);


    TraverseQ(q);

    printf("Please give a number within [%d...%d]: ", q.Front , q.Rear - 1); //To rear deixnei se poia thesi mporo na valo stoixeio ara thelo tin amesos prohgoumeni thesi
    do
    {
        scanf("%d", &num);
        if(num < q.Front || num > q.Rear - 1)
            printf("Give valid data.\n");
    }while(num < q.Front || num > q.Rear - 1);

    element = GetNthElementA(&q, num);
    printf("The element is(With GetNthElementA): %d\n", element);

    element = GetNthElementB(&q, num);
    printf("The element is(With GetNthElementB): %d\n", element);


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


QueueElementType GetNthElementA(QueueType *Q, QueueElementType num)
{
    QueueType temp;
    QueueElementType el, ret;
    QueueElementType ctr = 0;

    CreateQ(&temp);

    while(!EmptyQ(*Q))
    {
        RemoveQ(Q, &el);
        AddQ(&temp, el);
        if(ctr == num)
            ret = el;

        ctr++;
    }

    while(!EmptyQ(temp))
    {
        RemoveQ(&temp, &el);
        AddQ(Q, el);
    }

    return ret;
}


QueueElementType GetNthElementB(QueueType *Q, QueueElementType num)
{
    //QueueElementType el;

    return Q->Element[(Q->Front + num) % QueueLimit];
}
