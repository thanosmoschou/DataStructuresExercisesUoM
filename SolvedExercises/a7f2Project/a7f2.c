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


void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);
void TraverseStack(StackType Stack);
void Filling(StackType *stackT);
void GetNthElementA(StackType *stackT, StackElementType num , StackElementType *item);
void GetNthElementB(StackType stackT, StackElementType num, StackElementType *item);


int main()
{
    StackType stack1;
    StackElementType item1, item2, num;

    CreateStack(&stack1);
    Filling(&stack1);

    TraverseStack(stack1);

    printf("Dwse n:");
    do
    {
        scanf("%d", &num);
        getchar();
    }
    while (num < 1 || num > 50);

    GetNthElementA(&stack1, num, &item1);
    printf("Top with GetNthElementA = %d\n", item1);
    TraverseStack(stack1);

    GetNthElementB(stack1,num , &item2);
    printf("Top with GetNthElementB = %d\n", item2);
    TraverseStack(stack1);


    //system("pause");
    return 0;
}


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


void Filling(StackType *stackT)
{
    StackElementType i;

    for(i=2; i<=StackLimit; i+=2)
        Push(stackT, i);


}


void GetNthElementA(StackType *stackT, StackElementType num, StackElementType *item)
{
    StackElementType i, itemtemp;
    StackType temp;

    CreateStack(&temp);


    for(i = 0; i < num; i++)
    {
        Pop(stackT, &itemtemp);
        Push(&temp, itemtemp);
    }

    *item=itemtemp;

    for(i= 0; i < num; i++)
    {
        Pop(&temp, &itemtemp);
        Push(stackT, itemtemp);
    }
}


void GetNthElementB(StackType stackT, StackElementType num, StackElementType *item)
{
    (*item) = stackT.Element[stackT.Top-num+1];
}
