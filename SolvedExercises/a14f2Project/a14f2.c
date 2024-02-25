#include <stdio.h>
#include <stdlib.h>

#define StackLimit 50   // το όριο μεγέθους της στοίβας, ενδεικτικά ίσο με 50


typedef int StackElementType;   // ο τύπος των στοιχείων  της στοίβας
                                 //ενδεικτικά τύπος int
typedef struct  {
    int Top;
    StackElementType Element[StackLimit];
} StackType;

typedef enum {
    FALSE, TRUE
} boolean;


//Function prototypes
void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);
void TraverseStack(StackType Stack);
void CheckAddressViolation(StackType *commandStack, StackElementType *max, StackElementType *curr);


//Main function
int main()
{
    StackType commandStack;
    StackElementType maxAddr, curr;

    CreateStack(&commandStack);

    CheckAddressViolation(&commandStack, &maxAddr, &curr);

    return 0;
}


//Function definition
void CreateStack(StackType *Stack)
/* Λειτουργία: Δημιουργεί μια κενή στοίβα.
   Επιστρέφει: Κενή Στοίβα.*
*/
{
    Stack -> Top = -1;
   // (*Stack).Top = -1;
}


boolean EmptyStack(StackType Stack)
/* Δέχεται: Μια στοίβα Stack.
   Λειτουργία: Ελέγχει αν η στοίβα Stack είναι κενή.
   Επιστρέφει: True αν η Stack είναι κενή, False διαφορετικά
*/
{
    return (Stack.Top == -1);
}


boolean FullStack(StackType Stack)
/* Δέχεται: Μια στοίβα Stack.
   Λειτουργία: Ελέγχει αν η στοίβα Stack είναι γεμάτη.
   Επιστρέφει: True αν η Stack είναι γεμάτη, False διαφορετικά
*/
{
    return (Stack.Top == (StackLimit - 1));
}


void Push(StackType *Stack, StackElementType Item)
/* Δέχεται: Μια στοίβα Stack και ένα στοιχείο Item.
   Λειτουργία: Εισάγει το στοιχείο Item στην στοίβα Stack αν η Stack δεν είναι γεμάτη.
   Επιστρέφει: Την τροποποιημένη Stack.
   Έξοδος: Μήνυμα γεμάτης στοίβας, αν η στοίβα Stack είναι γεμάτη
*/
{
    if (!FullStack(*Stack)) {
        Stack -> Top++;
        Stack -> Element[Stack -> Top] = Item;
    } else
        printf("Full Stack...");
}


void Pop(StackType *Stack, StackElementType *Item)
/* Δέχεται: Μια στοίβα Stack.
   Λειτουργία: Διαγράφει το στοιχείο Item από την κορυφή της Στοίβας αν η Στοίβα δεν είναι κενή.
   Επιστρέφει: Το στοιχείο Item και την τροποποιημένη Stack.
   Έξοδος:  Μήνυμα κενής στοίβας αν η Stack είναι κενή
*/
{
    if (!EmptyStack(*Stack)) {
        *Item = Stack -> Element[Stack -> Top];
        Stack -> Top--;
    } else
        printf("Empty Stack...");
}


void TraverseStack(StackType Stack)
{
    int i;
    printf("\nplithos sto stack %d\n",Stack.Top+1);
    for (i=0;i<=Stack.Top;i++) {
        printf("%d ",Stack.Element[i]);
    }
    printf("\n");
}


void CheckAddressViolation(StackType *commandStack, StackElementType *max, StackElementType *curr)
{
    StackElementType addr, instrAddr;

    printf("Please enter maximum address: ");
    scanf("%d", max);
    getchar();

    while(1)
    {
        printf("Please enter the next relative memory address: ");
        scanf("%d", &addr);
        getchar();

        if(addr == 0)
            break;
        else
        {
            Push(commandStack, addr);
        }
    }

    printf("Please enter the current memory address: ");
    scanf("%d", curr);

    for(StackElementType i = commandStack->Top; i > -1; i--)
    {
        Pop(commandStack, &addr);
        instrAddr = *curr + addr;
        if(instrAddr > *max || instrAddr < 0)
        {
            printf("Access Violating Exception at address: %d\n", instrAddr);
            break;
        }
        else
        {
            printf("Executing instruction: %d\n", instrAddr);
            *curr = instrAddr;
        }
    }
}


