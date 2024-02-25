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
void DoTheWork(StackType *volume, StackType *Price, StackElementType *profit);


//MAin function
int main()
{
    StackType volume, Price;
    StackElementType profit;

    CreateStack(&volume);
    CreateStack(&Price);


    DoTheWork(&volume, &Price, &profit);
    printf("Total profit: %d\n", profit);

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


void DoTheWork(StackType *volume, StackType *Price, StackElementType *profit)
{
    StackElementType volumeStock, decision_Stock, priceStock;
    StackElementType remainvol, remainprice;
    StackElementType tempprof;
    StackElementType tempvol;


    *profit = 0;
    while(1)
    {
        tempprof = 0;
        printf("Enter the orderType(0-Buy, 1-Sell),volume,price(Separate with comma all the values): ");
        scanf("%d,%d,%d", &decision_Stock, &volumeStock, &priceStock);
        getchar();

        if(decision_Stock < 0 || volumeStock < 0 || priceStock < 0)
        {
            printf("Transaction profit: %d\n", tempprof);
            break;
        }

        if(decision_Stock == 0)
        {
            Push(volume, volumeStock);
            Push(Price, priceStock);
            printf("Transaction profit: %d\n", tempprof);
        }
        else
        {
            tempvol = volumeStock;
            tempprof += (volumeStock * priceStock);

            /*An oi metoxes pou zitaei einai ligoteres apo autes pou exo sthn pano thesi
            afairo apo ekei me tin antistoixi timi tis korifis ths stoivas tis timis.
            An thelei perissoteres dino oti exo me tin pano timi
            kai tin diafora pou menei apo tis pio kato theseis me tis antoistoixes times*/

            if(volumeStock < volume->Element[volume->Top])
            {
                volume->Element[volume->Top] -= volumeStock; //Meiono tis metoxes stin thesi
                tempprof -= (tempvol * Price->Element[Price->Top]);
            }
            else
            {
                while(tempvol > 0) //Mporei na min ftanei oute to amesos epomeno keli kai na pao pio kato ara to kano mexri na midenistoun autes pou thelei
                {
                    if(tempvol - volume->Element[volume->Top] < 0) //An exo na doso dino kai afairo
                    {
                        tempprof -= (tempvol * Price->Element[Price->Top]);
                        volume->Element[volume->Top] -= tempvol;
                        tempvol = 0; //Pira oti ithela ara midenizo
                    }
                    else if(tempvol - volume->Element[volume->Top] == 0)//An den exo proxorao sta epomena kelia
                    {
                        Pop(volume, &remainvol);
                        Pop(Price, &remainprice);
                        tempprof -= (remainvol * remainprice);
                        tempvol = 0;//To idio
                    }
                    else
                    {
                        tempprof -= (volume->Element[volume->Top] * Price->Element[Price->Top]);
                        tempvol -= volume->Element[volume->Top];
                        Pop(volume, &remainvol);
                        Pop(Price, &remainprice);
                    }
                }
            }

            printf("Transaction profit: %d\n", tempprof);
        }
        *profit += tempprof;
    }
}


