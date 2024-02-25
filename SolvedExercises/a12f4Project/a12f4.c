#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


typedef struct
{
    char surn[16];
    char name[16];
    long int phone;
    int ticketType;
} QueueElementType;           /*ο τύπος των στοιχείων της συνδεδεμένης ουράς ενδεικτικά τύπου int*/

typedef struct QueueNode *QueuePointer;

typedef struct QueueNode
{
	QueueElementType Data;
    QueuePointer Next;
} QueueNode;

typedef struct
{
    QueuePointer Front;
    QueuePointer Rear;
} QueueType;

typedef enum {
    FALSE, TRUE
} boolean;


//Function prototypes
void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
void AddQ(QueueType *Queue, QueueElementType Item);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void menu(int *choice);
void TraverseQ(QueueType Queue);


//Main function
int main()
{
    QueueType AQueue;
    int emptySeats;
    char decision;
    QueueElementType tempPasseng;

    CreateQ(&AQueue);

    while(1)
    {
        printf("New entry Y/N (Y=Yes, N=No)? ");
        do
        {
            scanf(" %c", &decision);
            while((getchar()) != '\n');
            if(decision != 'y' && decision != 'Y' && decision != 'n' && decision != 'N')
                printf("Enter valid decision.\n\nNew entry Y/N (Y=Yes, N=No)? ");
        }while(decision != 'y' && decision != 'Y' && decision != 'n' && decision != 'N');

        if(decision == 'n' || decision == 'N')
            break;

        printf("Please enter passenger's credentials for the waiting queue\n");
        printf("Please enter the passenger's surname: ");
        scanf("%15[^\n]", tempPasseng.surn);
        while((getchar()) != '\n');

        printf("Please enter the passenger's name: ");
        scanf("%15[^\n]", tempPasseng.name);
        while((getchar()) != '\n');

        printf("Please enter the passenger's phone number: ");
        scanf("%ld", &tempPasseng.phone);

        printf("Please enter the passenger's ticket type: ");
        scanf("%d", &tempPasseng.ticketType);

        AddQ(&AQueue, tempPasseng);
    }

    printf("\nHolding Queue:\n");
    TraverseQ(AQueue);

    printf("Please enter the number of the flight's empty seats: ");
    scanf("%d", &emptySeats);

    for(int i = 0; i < emptySeats; i++)
    {
        RemoveQ(&AQueue, &tempPasseng);
        printf("Credentials of passenger No%d:\nSurname: %s\nName: %s\nPhone Number: %ld\nTicket type: %d\n", i+1, tempPasseng.surn,
               tempPasseng.name, tempPasseng.phone, tempPasseng.ticketType);
    }

    printf("\nEdited waiting queue:\n");
    TraverseQ(AQueue);

    return 0;
}


//Function definition
void menu(int *choice)
{
    printf("                  MENOY                  \n");
    printf("-------------------------------------------------\n");
    printf("1 ---- DHMIOYRGIA OURAS\n");
    printf("2 ---- ADEIASMA THS OYRAS\n");
    printf("3 ---- ELEGXOS KENHS OYRAS\n");
    printf("4 ---  DIAGRAFH STOIXEIOY APO TH KORYFH THS OYRAS\n");
    printf("5 ---  PROS8HKH STOIXEIOY STO TELOS THS OYRAS\n");
    printf("6 ---- EMFANISH STOIXEIWN OURAS (BOH8HTHKH)\n");
    printf("7 ---- EXIT\n");
    printf("\nChoice: ");
    do
    {
    	scanf("%d", choice);
    } while (*choice<1 && *choice>7);
}


void TraverseQ(QueueType Queue)
{
	QueuePointer CurrPtr;

   if (EmptyQ(Queue))
    {
   	    printf("EMPTY Queue\n");
    }
   else
   {
   	    CurrPtr = Queue.Front;
         while ( CurrPtr!=NULL )
        {
      	     printf("Surname: %s\nName: %s\nPhone Number: %ld\nTicket type: %d\n\n", CurrPtr->Data.surn, CurrPtr->Data.name,
                   CurrPtr->Data.phone, CurrPtr->Data.ticketType);
             CurrPtr = CurrPtr->Next;
        }
   }
    printf("\n");
}


void CreateQ(QueueType *Queue)
/* Λειτουργία: Δημιουργεί μια κενή συνδεδεμένη ουρά.
   Επιστρέφει: Μια κενή συνδεδεμένη ουρά
*/
{
	(*Queue).Front = NULL;
	Queue->Rear = NULL;
}


boolean EmptyQ(QueueType Queue)
/* Δέχεται:    Μια συνδεδεμένη ουρά.
   Λειτουργία: Ελέγχει αν η συνδεδεμένη ουρά είναι κενή.
   Επιστρέφει: True αν η ουρά είναι κενή, false  διαφορετικά
*/
{
	return (Queue.Front==NULL);
}


void AddQ(QueueType *Queue, QueueElementType Item)
/* Δέχεται:    Μια συνδεδεμένη ουρά Queue και ένα  στοιχείο Item.
   Λειτουργία: Προσθέτει το στοιχείο Item στο τέλος της συνδεδεμένης ουράς Queue.
   Επιστρέφει: Την τροποποιημένη ουρά
*/
{
	QueuePointer TempPtr;

    TempPtr= (QueuePointer)malloc(sizeof(struct QueueNode));
    TempPtr->Data = Item;
    TempPtr->Next = NULL;
    if (Queue->Front==NULL)
        Queue->Front=TempPtr;
    else
        Queue->Rear->Next = TempPtr;
    Queue->Rear=TempPtr;
}


void RemoveQ(QueueType *Queue, QueueElementType *Item)
/* Δέχεται:    Μια συνδεδεμένη ουρά.
   Λειτουργία: Αφαιρεί το στοιχείο Item από την  κορυφή της συνδεδεμένης ουράς,
                αν δεν είναι  κενή.
   Επιστρέφει: Το στοιχείο Item και την τροποποιημένη συνδεδεμένη ουρά.
   Έξοδος:     Μήνυμα κενής ουράς, αν η ουρά είναι  κενή
*/
{
    QueuePointer TempPtr;

    if (EmptyQ(*Queue)) {
   	    printf("EMPTY Queue\n");
    }
   else
   {
        TempPtr = Queue->Front;
        *Item=TempPtr->Data;
        Queue->Front = Queue->Front->Next;
        free(TempPtr);
        if (Queue->Front==NULL) Queue->Rear=NULL;
    }
}


