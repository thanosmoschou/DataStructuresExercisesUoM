#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
    int elem;
    int prot;
} QueueElementType;           /*ο τύπος των στοιχείων της συνδεδεμένης ουράς
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
void readData(QueueElementType *AnItem, int num);
void modifyQ(QueueType *AQueue, QueueElementType AnItem);


//Main function
int main()
{
    QueueType AQueue;
    QueueElementType AnItem;
    int maxElem;

    CreateQ(&AQueue);

    printf("DWSE TO PLITHOS: ");
    scanf("%d", &maxElem);

    for(int i = 0; i < maxElem; i++)
    {
        readData(&AnItem, i);
        modifyQ(&AQueue, AnItem);
    }

    printf("Priority Queue\n");
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
      	     printf("%d %d\n", CurrPtr->Data.prot, CurrPtr->Data.elem);
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


void readData(QueueElementType *AnItem, int num)
{
    printf("DWSE TON KODIKO TOU %dou KOMVOU: ", num + 1);
    do
    {
        scanf("%d", &AnItem->elem);
        if(AnItem->elem < 100 || AnItem->elem > 999)
            printf("Invalid data.\nDWSE TON KODIKO TOU %dou KOMVOU: ", num + 1);
    }while(AnItem->elem < 100 || AnItem->elem > 999);

    printf("DWSE TON VATHMO PROTERAIOTITAS TOU %dou KOMVOU: ", num + 1);
    do
    {
        scanf("%d", &AnItem->prot);
        if(AnItem->prot < 1 || AnItem->prot > 20)
            printf("Invalid data.\nDWSE TON VATHMO PROTERAIOTITAS TOU %dou KOMVOU: ", num + 1);
    }while(AnItem->prot < 1 || AnItem->prot > 20);
}


void modifyQ(QueueType *AQueue, QueueElementType AnItem)
{
    QueueType tempQ;
    QueueElementType tempEl;
    QueuePointer curr, curr2, temppos;
    boolean flag1 = FALSE;
    int elemctr = 0;

    CreateQ(&tempQ);

    curr = AQueue->Front;


    while(curr != NULL)
    {
        if(AnItem.prot >= curr->Data.prot) //na proxoriso pio meta stin oura mou. Kai se isa na peso tha mpei sto telos
        {
            elemctr++;
            curr = curr->Next;
        }
        else
        {
            flag1 = TRUE; //vrika pou prepei na to valo se proteraiothta
            break;
        }
    }

    if(curr == NULL) //an ginei null to flag1 den to peirazei giati an to peirazei tha vgei apo tin loop ara rotao an einai auto null arxika oste na to valo sto telos
    {
        AddQ(AQueue, AnItem);
        return;
    }

    if(elemctr == 0) //prepei na to valo stin arxi arxi ara to vazo se voithitiki, vazo kai ta ypoloipa kai ola mazi ksana stin arxiki
    {
        AddQ(&tempQ, AnItem);

        temppos = AQueue->Front;
        while(temppos != NULL)
        {
            temppos = temppos->Next; //tha svisei o komvos kai to next tha einai null opote tha xaso ton deikti mou
            RemoveQ(AQueue, &tempEl);
            AddQ(&tempQ, tempEl);
        }

        temppos = tempQ.Front;
        while(temppos != NULL)
        {
            temppos = temppos->Next;
            RemoveQ(&tempQ, &tempEl);
            AddQ(AQueue, tempEl);
        }

        return;
    }

    if(flag1) //prepei na mpei metepeita kapou stin oura mou
    {
        temppos = curr; //vrika pou prepei na mpei ara mexri ekei tha mpoun se voithitiki oura oste na valo kai to extra stoixeio, na vgalo kai ta ipoloipa kai meta ola mesa stin arxiki

        curr2 = AQueue->Front;
        while(curr2 != temppos) // .next gia na piasei kai to stoixeio pou einai ekei allios tha ithela extra entoli ekso apo tin while
        {
            curr2 = curr2->Next;
            RemoveQ(AQueue, &tempEl);
            AddQ(&tempQ, tempEl);
        }
        AddQ(&tempQ, AnItem);

        while(temppos != NULL)
        {
            temppos = temppos->Next;
            RemoveQ(AQueue, &tempEl);
            AddQ(&tempQ, tempEl);
        }

        temppos = tempQ.Front;
        while(temppos != NULL)
        {
            temppos = temppos->Next;
            RemoveQ(&tempQ, &tempEl);
            AddQ(AQueue, tempEl);
        }
    }
}
