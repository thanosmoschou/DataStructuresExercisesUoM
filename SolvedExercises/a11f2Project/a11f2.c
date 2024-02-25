#include <stdio.h>


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
void Filling(StackType *Stack1);
void FilterStack(StackType *Stack1 , StackType *temp);


//Main function
int main()
{
    StackType Stack1,temp;

    CreateStack(&Stack1);
    CreateStack(&temp);

    Filling(&Stack1);
    TraverseStack(Stack1);

    FilterStack(&Stack1, &temp);
    TraverseStack(Stack1);

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


void Filling(StackType *Stack1)
{
    //StackType temp;
    StackElementType limit, num;
    StackElementType i;

    printf("Enter the limit of the numbers you want to insert into the stack:\n");
    scanf("%d", &limit);
    getchar();

    for(i=0; i < limit; i++)
    {
        printf("Insert the number No%d:", i+1);
        scanf("%d", &num);
        getchar();
        Push(Stack1, num);
    }
}


void FilterStack(StackType *Stack1 , StackType *temp)
{
    //StackType temp;
    StackElementType del,elem;

    CreateStack(temp);

    printf("Insert the number that you want to delete from the stack:");
    scanf("%d", &del);
    getchar();

    while(Stack1->Element[Stack1->Top] != del)
    {
        Pop(Stack1, &elem);
        Push(temp, elem);
        TraverseStack(*Stack1);
        TraverseStack(*temp);
    }

    Pop(Stack1, &elem); //Stin loop piga mexri ton arithmo pou thelo alla den ton ekana kati ara tora ton ekxoro

    while(temp->Top > -1)
    {
        Pop(temp, &elem);
        Push(Stack1, elem);
    }
}
