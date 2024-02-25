#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define INSERTLIM 100
#define STOP -1000
#define AE 10
#define BE 20
#define CE 23
#define DE 3
#define AD 7
#define BD 3
#define CD 23
#define DD 20

typedef int QueueElementType;           /*ο τύπος των στοιχείων της συνδεδεμένης ουράς
                                        ενδεικτικά τύπου int*/
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
void fillWithData(QueueType *AQueue, int *elemCtr);
void EncryptMessage(QueueType *AQueue);
void DecryptMessage(QueueType *AQueue);



//Main function
int main()
{
    QueueType AQueue;
    int elemCtr = 0;
    int choice;

    CreateQ(&AQueue);
    fillWithData(&AQueue, &elemCtr);

    menu(&choice);

    if(choice == 1)
    {
        EncryptMessage(&AQueue);
        printf("Encrypted Message:\n");
        TraverseQ(AQueue);

        DecryptMessage(&AQueue);
        printf("Decrypted Message:\n");
        TraverseQ(AQueue);
    }
    else if(choice == 2)
    {
        /*EncryptMessage(&AQueue);
        DecryptMessage(&AQueue);*/
        printf("Decrypted Message:\n");
        TraverseQ(AQueue);

        EncryptMessage(&AQueue);
        printf("Encrypted Message:\n");
        TraverseQ(AQueue);
    }

	return 0;
}


//Function definition
void menu(int *choice)
{
    printf("                  MENOY                  \n");
    printf("-------------------------------------------------\n");
    printf("1 ---- Encrypt\n");
    printf("2 ---- Decrypt\n");
    printf("3 ---- EXIT\n");
    printf("\nChoice: ");
    do
    {
    	scanf("%d", choice);
    } while (*choice<1 || *choice>3);
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
      	     printf("%d\n", CurrPtr->Data);
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


void fillWithData(QueueType *AQueue, int *elemCtr)
{
    QueueElementType AnItem;

    while(TRUE)
    {
        printf("Insert a number < %d. To stop insert %d\nMax limit: %d.\nYou can insert %d elements: ", CE, STOP, INSERTLIM, INSERTLIM - *elemCtr);
        do
        {
            scanf("%d", &AnItem);
            if((AnItem >= CE || AnItem < 0) && AnItem != STOP)
                printf("Enter valid data.\nInsert a number < %d. To stop insert %d\nMax limit: %d.\nYou can insert %d elements: ", CE, STOP, INSERTLIM, INSERTLIM - *elemCtr);
        }while((AnItem >= CE || AnItem < 0) && AnItem != STOP);

        if(AnItem == STOP)
            break;

        AddQ(AQueue, AnItem);
        (*elemCtr)++;
    }
}


void EncryptMessage(QueueType *AQueue)
{
    QueueType tempQ;
    QueueElementType anItem;
    int removedElem = 0;

    CreateQ(&tempQ);

    while(!EmptyQ(*AQueue))
    {
        RemoveQ(AQueue, &anItem);
        anItem = (AE * anItem) + BE + ((DE * removedElem) % CE);
        //anItem = A * anItem + B % C;
        removedElem++;
        AddQ(&tempQ, anItem);
    }

    while(!EmptyQ(tempQ))
    {
        RemoveQ(&tempQ, &anItem);
        AddQ(AQueue, anItem);
    }
}


void DecryptMessage(QueueType *AQueue)
{
    QueueType tempQ;
    QueueElementType anItem;
    int removedElem = 0;

    CreateQ(&tempQ);

    while(!EmptyQ(*AQueue))
    {
        RemoveQ(AQueue, &anItem);
        anItem = AD * (anItem + BD + (DD * removedElem)) % CD;
        //anItem = A * anItem + B % C;
        removedElem++;
        AddQ(&tempQ, anItem);
    }

    while(!EmptyQ(tempQ))
    {
        RemoveQ(&tempQ, &anItem);
        AddQ(AQueue, anItem);
    }
}

