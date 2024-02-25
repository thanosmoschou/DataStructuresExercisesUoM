#include <stdio.h>
#include <stdlib.h>

#define StackLimit 50   // το όριο μεγέθους της στοίβας, ενδεικτικά ίσο με 50


typedef char StackElementType;   // ο τύπος των στοιχείων  της στοίβας
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
void InverseLetters(StackType *Stack1, StackType *Stack2, StackType *Stack3);


//Main function
int main()
{
    StackType Stack1, Stack2, Stack3;

    CreateStack(&Stack1);
    CreateStack(&Stack2);
    CreateStack(&Stack3);

    InverseLetters(&Stack1, &Stack2, &Stack3);


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
        printf("%c ",Stack.Element[i]);
    }
    printf("\n\n");
}


void InverseLetters(StackType *Stack1, StackType *Stack2, StackType *Stack3)
{
    StackElementType letter;
    int i;


    printf("Dwse 6 grammata gia eisagosi stin stoiva kai antistrofi tous:\n");
    for(i=0; i < 6; i++)
    {
        printf("Dwse to %do gramma:", i+1);
        scanf("%c", &letter);
        getchar();
        Push(Stack1, letter);
    }

    printf("Stack1\n");
    TraverseStack(*Stack1);

    for(i = Stack1->Top; i > -1; i--)
    {
        Pop(Stack1, &letter);
        Push(Stack2, letter);
    }

    printf("Stack2\n");
    TraverseStack(*Stack2);

    for(i = Stack2->Top; i > -1; i--)
    {
        Pop(Stack2, &letter);
        Push(Stack3, letter);
    }

    printf("Stack3\n");
    TraverseStack(*Stack3);

    for(i = Stack3->Top; i > -1; i--)
    {
        Pop(Stack3, &letter);
        Push(Stack1, letter);
    }

    printf("Stack1\n");
    TraverseStack(*Stack1);

}
