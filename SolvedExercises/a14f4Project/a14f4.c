#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef char StackElementType;           /*ο τύπος των στοιχείων της στοίβας
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


//Main function
int main()
{
    StackPointer AStack;
    int ctr = 0, parCtr = 0;
    StackElementType AnItem;
    char stringMessage[21];
    boolean corr;

    CreateStack(&AStack);

    printf("Please enter a parenthetic string: ");
    scanf("%20[^\n]", stringMessage);
    while((getchar()) != '\n');

    corr = TRUE;
    while(stringMessage[ctr] != '\0')
    {
        if(stringMessage[ctr] == '(' || stringMessage[ctr] == '[' || stringMessage[ctr] == '{')
            Push(&AStack, stringMessage[ctr]);
        else if(stringMessage[ctr] == ')' || stringMessage[ctr] == ']' || stringMessage[ctr] == '}')
        {
            if(!EmptyStack(AStack))
            {
                Pop(&AStack, &AnItem);
                if((AnItem == '(' && stringMessage[ctr] != ')') || (AnItem == '[' && stringMessage[ctr] != ']') || (AnItem == '{' && stringMessage[ctr] != '}'))
                {
                    corr = FALSE;
                    parCtr = 0;
                    break;
                }
                else
                    parCtr++;
            }
            else
            {
                corr = FALSE;

            }
        }
        ctr++;
    }


    if(corr && parCtr > 0 && EmptyStack(AStack))
        printf("Correct\n");
    else
    {
        printf("Wrong\n");
    }

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
      	     printf("%d ", CurrPtr->Data);
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
