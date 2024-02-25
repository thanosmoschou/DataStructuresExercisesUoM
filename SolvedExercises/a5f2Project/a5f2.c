#include <stdio.h>
#include <stdlib.h>

#define StackLimit 50   // το όριο μεγέθους της στοίβας, ενδεικτικά ίσο με 50
#define LIMIT 15

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
void FunctionF(StackType *stackT, StackType *temp,StackElementType *x1, StackElementType *x2, StackElementType *x3, StackElementType *x4, StackElementType *x5, StackElementType *x6, StackElementType *x7);



int main()
{
    StackType stackT,temp;;
    StackElementType x1,x2,x3,x4,x5,x6,x7;


    CreateStack(&stackT);
    CreateStack(&temp);

    FunctionF(&stackT, &temp, &x1, &x2, &x3, &x4, &x5, &x6, &x7);

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

void FunctionF(StackType *stackT, StackType *temp,StackElementType *x1, StackElementType *x2, StackElementType *x3, StackElementType *x4, StackElementType *x5, StackElementType *x6, StackElementType *x7)
{
    StackElementType num,i,element;


    for(i=0; i < LIMIT; i++)
        Push(stackT, i*10);

    TraverseStack(*stackT);
    printf("Give nth element (n<=6) ");
    scanf("%d", &num);
    getchar();

    //a

    for(i=0; i < 2; i++)
        Pop(stackT, &element);

    *x1= element;

    printf("Question a: x=%d\n", *x1);
    TraverseStack(*stackT);
    printf("\n");

    //b

    for(i=0; i < 2; i++)
    {
        Pop(stackT, &element);
        Push(temp, element);
    }

    *x2= element;

    for(i=0; i < 2; i++)
    {
        Pop(temp, &element);
        Push(stackT, element);
    }

    printf("Question b: x=%d\n", *x2);
    TraverseStack(*stackT);
    printf("\n");


    //c

    for(i=0; i < num; i++)
        Pop(stackT, &element);

    *x3=element;

    printf("Question c: x=%d\n", *x3);
    TraverseStack(*stackT);
    printf("\n");


    //d

    for(i=0; i < num; i++)
    {
        Pop(stackT, &element);
        Push(temp, element);
    }

    *x4= element;

    for(i=0; i < num; i++)
    {
        Pop(temp, &element);
        Push(stackT, element);
    }

    printf("Question d: x=%d\n", *x4);
    TraverseStack(*stackT);
    printf("\n");


    //e

    for(i= stackT->Top; i > -1; i--)
    {
        Pop(stackT, &element);
        Push(temp, element);
    }

    *x5= element;

    for(i= temp->Top; i > -1; i--)
    {
        Pop(temp, &element);
        Push(stackT, element);
    }

    printf("Question e: x=%d\n", *x5);
    TraverseStack(*stackT);
    printf("\n");


    //f

    for(i= stackT->Top; i > 1; i--)
    {
        Pop(stackT, &element);
        Push(temp, element);
    }

    *x6= element;

    for(i= temp->Top; i > -1; i--)
    {
        Pop(temp, &element);
        Push(stackT, element);
    }

    printf("Question f: x=%d\n", *x6);
    TraverseStack(*stackT);
    printf("\n");

    //g

    for(i= stackT->Top; i > -1; i--)
        Pop(stackT, &element);

    *x7= element;

    printf("Question g: x=%d\n", *x7);
    TraverseStack(*stackT);
    printf("\n");


}
