#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NAMELIM 9
#define FILELIM 13

typedef struct
{
    char user[NAMELIM];
    char file[FILELIM];
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
void makeTheQPrint(QueueType *usersQ, QueueType *teachersQ);


//Main function
int main()
{
    QueueType usersQ, teachersQ;
    QueueElementType AnItem;
    char ch;

    CreateQ(&usersQ);
    CreateQ(&teachersQ);

    makeTheQPrint(&usersQ, &teachersQ);
    while(!EmptyQ(teachersQ))
    {
        RemoveQ(&teachersQ, &AnItem);
        printf("Printing the job of %s, %s\nPress any key to continue", AnItem.user, AnItem.file);
        scanf("%c", &ch);
        if(ch != '\n')
            while((getchar()) != '\n');
    }

    while(!EmptyQ(usersQ))
    {
        RemoveQ(&usersQ, &AnItem);
        printf("Printing the job of %s, %s\nPress any key to continue", AnItem.user, AnItem.file);
        scanf("%c", &ch);
        if(ch != '\n')
            while((getchar()) != '\n');
    }

    printf("There are no jobs in the printing queue\n");
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
      	     printf("%d ", CurrPtr->Data);
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


void makeTheQPrint(QueueType *usersQ, QueueType *teachersQ)
{
    QueueElementType data;
    FILE *infile;
    int scanned, line = 0;
    char termch;
    boolean flag = FALSE;

    infile = fopen("I13F4.dat", "r");
    if(infile == NULL)
    {
        printf("Problem with file: %s\n", "I13F4.dat");
        exit(1);
    }

    while(TRUE)
    {
        if(line % 2 == 0)
        {
            scanned = fscanf(infile, "%8[^\n]%c", data.user, &termch);
        }
        else
        {
            scanned = fscanf(infile, "%12[^\n]%c", data.file, &termch);
        }

        if(scanned != 2 && scanned != EOF)
        {
            printf("Problem in line %d\n", line);
            exit(1);
        }
        line++;

        if(scanned == EOF)
            break;

        /*To line eno diavaza xristi eno itan zigo auksithike kai eno thelo na einai zigo oste na
        ksero oti exo xristh tora egine mono. Otan sugkrino an exo USER h FORT
        kai den exo tote tha einai didaskon alla den mou leei kanenas oti den
        sugkrino to arxeio pou diavasa me auta.An isxuei tote tha eisaxthoun
        akura dedomena. Opote prepei tora to line na einai mono
        oste na ksero oti den diabasa akoma arxeio kai exo onoma xristi*/
        if(line % 2 != 0)
        {
            if(strncmp(data.user, "USER", 4) == 0 || strncmp(data.user, "FORT", 4) == 0)
            {
                flag = TRUE;
            }
        }

        //Tora stin epomeni loop diavasa arxeio ara egine to line pali zigo
        //alla me mia flag sigourevo oti exo diavasei kai xristi
        if(line % 2 == 0 && flag)
        {
            AddQ(usersQ, data);
            flag = FALSE;
        }
        else if(line % 2 == 0 && !flag) //exo teacher
        {
            AddQ(teachersQ, data);
            flag = FALSE;
        }
    }
}
