#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define WEIGHTLIM 10
#define WEIGHTWORTHCOST 300

typedef float StackElementType;           /*ο τύπος των στοιχείων της στοίβας
                                        ενδεικτικά τύπου int */
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
void fillTheTruck(StackPointer *AStack, StackPointer *BStack, float *sWeight);



//Main function
int main()
{
    StackPointer AStack, BStack;
    float sWeight = 0;

    CreateStack(&AStack);
    CreateStack(&BStack);

    fillTheTruck(&AStack, &BStack, &sWeight);
    printf("--Truck--\n");
    TraverseStack(AStack);

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
      	     printf("%.2f\n", CurrPtr->Data);
             CurrPtr = CurrPtr->Next;
        }
   }
    printf("\n");
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


void fillTheTruck(StackPointer *AStack, StackPointer *BStack, float *sWeight)
{
    StackElementType itemWeight, valueItem, tempItem;
    float worth;
    StackPointer curr;

    //Default values for truck
    Push(AStack, 3);
    Push(AStack, 2);
    Push(AStack, 1);
    Push(AStack, 0.5);
    Push(AStack, 0.4);
    (*sWeight) += 6.9;

    while(TRUE)
    {
        worth = 0;

        if(*sWeight == WEIGHTLIM)
            break;

        printf("Give the weight: ");
        scanf("%f", &itemWeight);
        if(itemWeight < 0)
            break;

        printf("Give the value: ");
        scanf("%f", &valueItem);
        if(valueItem < 0)
            break;

        while(!EmptyStack(*AStack))
        {
            curr = *AStack;
            while(curr != NULL)
            {
                if(curr->Data < itemWeight)
                    worth += (curr->Data * WEIGHTWORTHCOST);
                else
                    break;
                curr = curr->Next;
            }
            break;
        }

        if(worth >= valueItem)
            printf("Not enough value.\n");
        else
        {
            if(*sWeight + itemWeight > WEIGHTLIM)
            {
                printf("Not enough weight capacity.\n");
                continue;
            }


            while(!EmptyStack(*AStack))
            {
                curr = *AStack;
                if(curr->Data < itemWeight)
                {
                    Pop(AStack, &tempItem);
                    Push(BStack, tempItem);
                }
                else
                    break;
                curr = curr->Next;
            }

            Push(AStack, itemWeight);
            (*sWeight) += itemWeight;

            printf("--Platform--\n");
            TraverseStack(*BStack);
            printf("--Truck--\n");
            TraverseStack(*AStack);

            while(!EmptyStack(*BStack))
            {
                Pop(BStack, &tempItem);
                Push(AStack, tempItem);
            }
        }
    }
}
