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
void menu(char *choice);
void ReadData(StackType *Numberstack, StackType *OperationStack);
void Operation(StackType *StackNum, StackType *OperationStack, StackElementType num1, StackElementType num2, StackElementType *times);



//Main function
int main()
{
   // int choice;
    StackType NumberStack, OperationStack;

    CreateStack(&NumberStack);
    CreateStack(&OperationStack);

    ReadData(&NumberStack, &OperationStack);


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



void menu(char *choice)
{
    printf("\nDIATHESIMES LEITOURGIES: +,-,*,/,c,s,q,u\n");
    printf("c = clear, s = show result, q = quit, u = undo\n");
    printf("Operation: ");

    do
    {
        scanf("%c", choice);
        //printf("%d\n", *choice);
        getchar();
    }
   while (*choice != '+' && *choice != '-' && *choice != '*' && *choice != '/' && *choice != 'c' && *choice != 's'
             && *choice != 'q' && *choice != 'u' );
    //getchar();
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


void ReadData(StackType *Numberstack, StackType *OperationStack)
{
    int oper;
    StackElementType tempn;
    char choice;
    StackElementType times=0, num1,num2;

    menu(&choice);


    while(choice != 'q')
    {
        if(times==0)
        {
            printf("Number1: ");
            scanf("%d", &num1);
            getchar();
            printf("Number2: ");
            scanf("%d", &num2);
            getchar();
            times++;

            Push(Numberstack, num1);
            Push(Numberstack, num2);
            Push(OperationStack, choice);

            Operation(Numberstack, OperationStack, num1, num2, &times);

        }
        else if(choice == 's')
            printf("Result: %d\n", Numberstack->Element[Numberstack->Top]);
        else if(choice == 'u')
        {
            Pop(OperationStack, &oper);
            for(StackElementType i = 0; i < 2; i++)
                Pop(Numberstack, &tempn);
        }
        else if(choice == 'c')
        {
            for(StackElementType i = Numberstack->Top; i > -1; i--)
                Pop(Numberstack, &tempn);

            for(StackElementType i = OperationStack->Top; i > -1; i--)
                Pop(OperationStack, &oper);

            times = 0;

        }
        else
        {
            printf("Number: ");
            scanf("%d", &num2);
            getchar();

            num1 = Numberstack->Element[Numberstack->Top];
            Push(Numberstack, num2);
            Push(OperationStack, choice);

            Operation(Numberstack, OperationStack, num1, num2, &times);
        }
        menu(&choice);
    }

    TraverseStack(*Numberstack);
    TraverseStack(*OperationStack); //Due to the implementation of this function we store the ASCII code of every operator
}


void Operation(StackType *StackNum, StackType *OperationStack, StackElementType num1, StackElementType num2, StackElementType *times)
{
    StackElementType tempnum;
    StackElementType res;
    int oper;

    switch(OperationStack->Element[OperationStack->Top])
    {
        case '+':
            res = num1 + num2;
            Push(StackNum, res);
            break;
        case '-':
            res = num1 - num2;
            Push(StackNum, res);
            break;
        case '*':
            res = num1 * num2;
            Push(StackNum, res);
            break;
        case '/':
            if(num2 != 0)
            {
                res = num1 / num2;
                Push(StackNum, res);
                break;
            }
            else
            {
                printf("Division by 0...\n");
                Pop(StackNum, &tempnum);
                Pop(OperationStack, &oper);
                break;
            }
        case 'q':
            return ;

    }
}
