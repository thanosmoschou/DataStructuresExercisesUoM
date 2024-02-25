#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NAMELIM 9


typedef char QueueElementType[NAMELIM];           /*ο τύπος των στοιχείων της συνδεδεμένης ουράς
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
void doTheWork(QueueType *adminQueue, QueueType *userQueue);
boolean searchName(FILE *infile, QueueElementType AnItem);
boolean searchToQueue(QueueElementType AnItem, QueueType *Queue);



//Main function
int main()
{
    QueueType adminQueue, userQueue;

    CreateQ(&adminQueue);
    CreateQ(&userQueue);

    doTheWork(&adminQueue, &userQueue);

    printf("Oura Diaxeiristwn\n");
    TraverseQ(adminQueue);

    printf("Oura Aplwn Xrhstwn\n");
    TraverseQ(userQueue);

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
      	     printf("%s\n", CurrPtr->Data);
             CurrPtr = CurrPtr->Next;
        }
   }
    //printf("\n");
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
    strncpy(TempPtr->Data, Item, strlen(Item));
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
        strncpy(*Item, TempPtr->Data, strlen(TempPtr->Data));
        Queue->Front = Queue->Front->Next;
        free(TempPtr);
        if (Queue->Front==NULL) Queue->Rear=NULL;
    }
}


void doTheWork(QueueType *adminQueue, QueueType *userQueue)
{
    QueueElementType AnItem;
    boolean found, queueFound;
    FILE *infile;
    char decision;

    while(TRUE)
    {
        printf("USERNAME: ");
        scanf("%8[^\n]", AnItem);
        while((getchar()) != '\n'); //like fflush(stdin)

        infile = fopen("I11F4.dat", "r");
        if(infile == NULL)
        {
            printf("Problem with file %s\n", "I11F4.dat");
            exit(1);
        }

        found = searchName(infile, AnItem);
        if(found)
        {
            if(strncmp(AnItem, "USR", 3) == 0)
            {
                queueFound = searchToQueue(AnItem, userQueue);
                if(!queueFound)
                    AddQ(userQueue, AnItem);
                else
                {
                    printf("You have logged in to the system from another terminal. New access is forbidden.\n");
                }
            }
            else
            {
                queueFound = searchToQueue(AnItem, adminQueue);
                if(!queueFound)
                    AddQ(adminQueue, AnItem);
                else
                {
                    printf("You have logged in to the system from another terminal. New access is forbidden.\n");
                }
            }
        }
        else
        {
            printf("Wrong user ID\n");
        }

        fclose(infile);

        printf("New insertion Y/N (Y=yes, N=No)");
        do
        {
            scanf("%c", &decision);
            while((getchar()) != '\n');

            if(decision != 'Y' && decision != 'y' && decision != 'N' && decision != 'n')
                printf("Enter valid data.\nNew insertion Y/N (Y=yes, N=No)");
        }while(decision != 'Y' && decision != 'y' && decision != 'N' && decision != 'n');

        if(decision == 'N' || decision == 'n')
            break;
    }
}


boolean searchName(FILE *infile, QueueElementType AnItem)
{
    char tempname[NAMELIM], term1,term2;
    int line = 0, thingsScanned;

    while(TRUE)
    {
        thingsScanned = fscanf(infile, "%8[^\r]%c%c", tempname, &term1, &term2);
        if(thingsScanned != 3 && thingsScanned != EOF)
        {
            printf("Problem in line %d\n", line);
            exit(1);
        }
        line++;

        if(thingsScanned == EOF)
            break;

        if(strncmp(AnItem, tempname, strlen(tempname)) == 0)
            return TRUE;
    }

    return FALSE;
}


boolean searchToQueue(QueueElementType AnItem, QueueType *Queue)
{
    QueuePointer curr;

    if(!EmptyQ(*Queue))
    {
        curr = Queue->Front;
        while(curr != NULL)
        {
            if(strncmp(AnItem, curr->Data, strlen(AnItem)) == 0)
            {
                return TRUE;
            }

            curr = curr->Next;
        }
    }

    return FALSE;
}
