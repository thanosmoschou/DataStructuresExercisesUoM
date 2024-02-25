#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define DATELIM 11
#define WARE1 1
#define WARE2 2
#define WARE3 3

typedef struct
{
    int boxesNum;
    float boxesWeight;
    char date[DATELIM];
} StackElementType;


typedef struct StackNode *StackPointer;
typedef struct StackNode
{
	StackElementType Data;
    StackPointer Next;
} StackNode;

typedef enum {
    FALSE, TRUE
} boolean;


//Function prototypes
void CreateStack(StackPointer *Stack);
boolean EmptyStack(StackPointer Stack);
void Push(StackPointer *Stack, StackElementType Item);
void Pop(StackPointer *Stack, StackElementType *Item);
void TraverseStack(StackPointer Stack);
void menu(int *choice);
void retMaxBoxes(StackPointer *Stack, int *sumBox);
void readData(StackElementType *AnItem, int num);
void findMinBoxWarehouse(StackPointer *AStack, StackPointer *BStack, StackPointer *CStack, int *minWareh);
void fillTheWarehouses(StackPointer *AStack, StackPointer *BStack, StackPointer *CStack);


//Main function
int main()
{
    StackPointer AStack, BStack, CStack;
    StackElementType AnItem;

    Push(&AStack,AnItem);
    Pop(&AStack, &AnItem);

    CreateStack(&AStack);
    CreateStack(&BStack);
    CreateStack(&CStack);

    fillTheWarehouses(&AStack, &BStack, &CStack);

    printf("WAREHOUSE 1\n");
    TraverseStack(AStack);
    printf("WAREHOUSE 2\n");
    TraverseStack(BStack);
    printf("WAREHOUSE 3\n");
    TraverseStack(CStack);

	return 0;
}


//Function definition
void menu(int *choice)
{
    printf("                  MENOY                  \n");
    printf("-------------------------------------------------\n");
    printf("1 ---- DHMIOYRGIA STOIBAS\n");
    printf("2 ---- ADEIASMA THS STOIBAS\n");
    printf("3 ---- ELEGXOS KENHS STOIBAS\n");
    printf("4 ---  POP STOIXEIOY APO TH KORYFH THS STOIBA\n");
    printf("5 ---  PUSH STH KORYFH THS STOIBAS\n");
    printf("6 ---- EMFANISH STOIXEIWN STOIBAS (BOH8HTHKH)\n");
    printf("7 ---- EXIT\n");
    printf("\nChoice: ");
    do
    {
    	scanf("%d", choice);
    } while (*choice<1 && *choice>7);
}


void TraverseStack(StackPointer Stack)
{
	StackPointer CurrPtr;

   if (EmptyStack(Stack))
   {
   	    printf("EMPTY Stack\n");
    }
   else
   {
   	    CurrPtr = Stack;
         while ( CurrPtr!=NULL )
        {
      	     printf("%d %.2f %s\n", CurrPtr->Data.boxesNum, CurrPtr->Data.boxesWeight, CurrPtr->Data.date);
             CurrPtr = CurrPtr->Next;
        }
   }
    //printf("\n");
}


void CreateStack(StackPointer *Stack)
/* Λειτουργία: Δημιουργεί μια κενή συνδεδεμένη στοίβα.
   Επιστρέφει: Μια κενή συνδεδεμένη στοίβα, Stack
*/
{
	*Stack = NULL;
}


boolean EmptyStack(StackPointer Stack)
/* Δέχεται:     Μια συνδεδεμένη στοίβα, Stack.
   Λειτουργία:  Ελέγχει αν η Stack είναι κενή.
   Επιστρέφει:  TRUE αν η στοίβα είναι κενή, FALSE διαφορετικά
*/
{
	return (Stack==NULL);
}


void Push(StackPointer *Stack, StackElementType Item)
/* Δέχεται:    Μια συνδεδεμένη στοίβα που η κορυφή της δεικτοδοτείται από τον
                δείκτη Stack και ένα στοιχείο Item.
   Λειτουργία: Εισάγει στην κορυφή της συνδεδεμένης στοίβας, το στοιχείο Item.
   Επιστρέφει: Την τροποποιημένη συνδεδεμένη στοίβα
*/
{
	StackPointer TempPtr;

    TempPtr= (StackPointer)malloc(sizeof(struct StackNode));
    TempPtr->Data = Item;
    TempPtr->Next = *Stack;
    *Stack = TempPtr;
}


void Pop(StackPointer *Stack, StackElementType *Item)
/* Δέχεται:    Μια συνδεδεμένη στοίβα που η κορυφή της δεικτοδοτείται από τον δείκτη Stack.
   Λειτουργία: Αφαιρεί από την κορυφή της συνδεδεμένης στοίβας,
                αν η στοίβα δεν είναι κενή, το στοιχείο Item.
   Επιστρέφει: Την τροποποιημένη συνδεδεμένη στοίβα και το στοιχείο Item.
   Έξοδος:     Μήνυμα κενής στοίβας, αν η συνδεδεμένη στοίβα είναι κενή
*/
{
    StackPointer TempPtr;

    if (EmptyStack(*Stack)) {
   	    printf("EMPTY Stack\n");
    }
   else
   {
        TempPtr = *Stack;
        *Item=TempPtr->Data;
        *Stack = TempPtr->Next;
        free(TempPtr);
    }
}


void readData(StackElementType *AnItem, int num)
{
        printf("Arithmos kivwtiwn gia to %do fortio: ", num + 1);
        scanf("%d", &AnItem->boxesNum);
        printf("Synoliko baros gia to %do fortio: ", num + 1);
        scanf("%f", &AnItem->boxesWeight);
        printf("Imeromhnia liksis gia to %do fortio: " , num + 1);
        scanf(" %10[^\n]", &AnItem->date);
        while((getchar()) != '\n');
}


void fillTheWarehouses(StackPointer *AStack, StackPointer *BStack, StackPointer *CStack)
{
    int totalBoxes, i, minware;
    StackElementType AnItem;

    printf("Plithos fortiwn: ");
    scanf("%d", &totalBoxes);

    i = 0;
    while(i < totalBoxes)
    {
        readData(&AnItem, i);
        findMinBoxWarehouse(AStack, BStack, CStack, &minware);

        if(minware == WARE1)
            Push(AStack, AnItem);
        else if(minware == WARE2)
            Push(BStack, AnItem);
        else
            Push(CStack, AnItem);

        i++;
    }

}


void retMaxBoxes(StackPointer *Stack, int *sumBox)
{
    StackPointer curr;

    *sumBox = 0;
    curr = *Stack;
    while(curr != NULL)
    {
        (*sumBox) += curr->Data.boxesNum;
        curr = curr -> Next;
    }
}


void findMinBoxWarehouse(StackPointer *AStack, StackPointer *BStack, StackPointer *CStack, int *minWareh)
{
    int boxA, boxB, boxC;

    retMaxBoxes(AStack, &boxA);
    retMaxBoxes(BStack, &boxB);
    retMaxBoxes(CStack, &boxC);

    //Find smaller only(not for equal)
    if(boxA < boxB && boxA < boxC)
    {
        (*minWareh) = WARE1;
        return;
    }
    else if(boxA <= boxC && boxB < boxC) //to a kai iso na einai me to b tha epilexthei o aukson arithmos ara to b. To idio kai gia to c kato
    {
        (*minWareh) = WARE2;
        return;
    }
    else
    {
        (*minWareh) = WARE3;
        return;
    }
}
