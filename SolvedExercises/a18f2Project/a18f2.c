#include <stdio.h>
#include <stdlib.h>

#define StackLimit 50   // το όριο μεγέθους της στοίβας, ενδεικτικά ίσο με 50
#define LIMIT 6

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
void FunctionFilling(StackType stackT, StackType minstack);


int main()
{
    StackType stackT, minstack;

    CreateStack(&stackT);
    CreateStack(&minstack);

    FunctionFilling(stackT, minstack);

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
    printf("plithos sto stack %d\n",Stack.Top+1);
    for (i=0;i<=Stack.Top;i++) {
        printf("%d ",Stack.Element[i]);
    }
    printf("\n");
}


void FunctionFilling(StackType stackT, StackType minstack)
{
    StackElementType i, element, min;

    for(i=0; i < LIMIT; i++)
    {
        printf("Dwse to epomeno stoixeio: ");
        scanf("%d", &element);
        getchar();

        if(i==0)
        {
            min=element;
        }

        Push(&stackT, element);
        if(stackT.Element[stackT.Top] <= min)
        {
            min=stackT.Element[stackT.Top];
            Push(&minstack, min);
        }

        TraverseStack(stackT);
        printf("Min=%d\n", minstack.Element[minstack.Top]);

    }

    printf("\nEmptying stack\n");
    for(i=0; i < LIMIT; i++)
    {
        if(stackT.Element[stackT.Top]==minstack.Element[minstack.Top])
        {
            Pop(&minstack, &min);
            if(!EmptyStack(minstack))
                printf("Min=%d\n", minstack.Element[minstack.Top]);
            Pop(&stackT, &element);
            TraverseStack(stackT);
        }
        else
        {
            Pop(&stackT, &element);
            TraverseStack(stackT);
        }
    }
}








