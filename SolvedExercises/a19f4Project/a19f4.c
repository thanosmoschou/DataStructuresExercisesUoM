#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define COMMENTLIMCHAR 255
#define LINELIM 100
#define READCHCOMBINATION 2


typedef char QueueElementType;           /*ο τύπος των στοιχείων της συνδεδεμένης ουράς
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
void printThingsOnScreen(FILE *infile, QueueType *AQueue);


//Main function
int main()
{
    QueueType AQueue;
    FILE *infile;

    printThingsOnScreen(infile, &AQueue);
    printf("\n\nComments:\n{\n");
    TraverseQ(AQueue);
    printf("}\n");

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
      	     printf("%c", CurrPtr->Data);
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


void printThingsOnScreen(FILE *infile, QueueType *AQueue)
{
    int ch, ch2, ch3;
    boolean flag1 = FALSE, flag2 = FALSE;

    infile = fopen("program.c", "r");
    if(infile == NULL)
    {
        printf("Problem with file: %s\n", "program.c");
        exit(255);
    }

    /*Diavazo chars apo arxeio. An vro / diavazo kai ton epomeno char. An einai * h / apo tous epomenous charactires tha tous vazo se oura. Allios ektipono
    ton charactira stin othoni mou. An einai * h / opos eipa pane oi epomenoi se oura.
    Mexri pote ? Tha diavazo kai an vro * h / eimai standby. An vro ton epomeno / stamatao na vazo sthn oura kai autous tous 2 characthres
    pou diavasa den asxoloumai me autous(oute ektuposi oute stin oura). Allios vazo se oura autous tous 2 charactires kai synexizo kanonika
    to diabasma kai ton elegxo*/

    while((ch = fgetc(infile)) != EOF)
    {
        if(ch == '/' && !flag1) //flag1 = false deixnei oti den exo parei / prin
        {
            ch2 = fgetc(infile);
            if(ch2 == '/' || ch2 == '*')
            {
                flag1 = TRUE;
                continue;
            }
            else
            {
                printf("%c%c", ch, ch2);
                continue;
            }
        }
        else if(!flag1) //den exo parei dipli / apo prin ara ektipono
        {
            printf("%c", ch);
            continue;
        }

        if(flag1)
        {
            if(ch == '/' || ch == '*')
            {
                ch3 = fgetc(infile);
                if(ch3 == '/')
                {
                    flag2 = TRUE;
                }
                else
                {
                    AddQ(AQueue, ch);
                    AddQ(AQueue, ch3);
                    continue;
                }
            }
            else
            {
                AddQ(AQueue, ch);
                continue;
            }
        }

        if(flag2)
        {
            flag1 = flag2 = FALSE;
        }
    }

    fclose(infile);
}
