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
void DoTheWork(StackType *StacT, boolean *flag1, boolean *flag2, boolean *ret, boolean *ctim);


//Main function
int main()
{
    StackType StacT;
    boolean flag1=FALSE, flag2=TRUE, ret=FALSE, ctimes=FALSE;

    CreateStack(&StacT);

    DoTheWork(&StacT,  &flag1, &flag2 ,&ret, &ctimes);

    if(ret)//Edoses # apo tin arxi
        return 0;

    if(!flag2) //Den iparxei simmetria
        printf("FALSE\n");
    else if(!flag1 || !flag2) //Den edoses C kai edoses meta apo liga insert # h edoses C apo tin arxi
        printf("FALSE\n");
    else if(flag2 && !ctimes) //Yparxei summetria
        printf("TRUE\n");

    return 0;
}


//Function prototypes
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


void DoTheWork(StackType *StacT, boolean *flag1, boolean *flag2, boolean *ret, boolean *ctim)
{
    char ch;
    StackElementType element, CheckLetter;
    int Cpos, ctr=0, i;
    StackType temp;
   // StackElementType limit=0;

    CreateStack(&temp);

    printf("Enter string:(1st character is not allowed to be C or \n.If you want to terminate the process enter #\nIf you want to give C character you are allowed to do it once)");
    while(1)
    {
        scanf("%c", &ch);
        getchar();

        if(ch == '#' && EmptyStack(*StacT))
        {
            *ret = TRUE; //Edo to exo gia na do an dosei apo tin arxi #
            //*flag2 = FALSE;
            return ;
        }
        else if(ch == '#')
            return ;

        if(ch != 'C')
        {
            if(*flag1)//Dosame C gia na mpei edo
            {
                if(ctr > Cpos) //Xalase i summetria os pros ton arithmo grammaton
                {
                    *flag2=FALSE;
                    return ;
                }

               /* d d s x C x s d d
                  0 1 2 3 4 5 6 7 8 */

                Push(StacT, ch);
                ctr++; //An dosame C arxizei o counter na metraei oste na sugkrino to top me to Cpos-ctr giati to C einai aksonas symmetrias...
                //Episis to ctr auksanetai parallila me to top
                //limit=StacT->Top;
                for(i = 0; i < 2*ctr+1; i++) //Edo pairno kathe fora to antistoixo stoixeio kato apo to C afinontas stin synexeia tin stoiba analoioti
                {                              // Exo 2*ctr+1 giati an doso C kai meta gramma exo 1 gramma apo deksia 1 apo aristera kai to C na paro
                    Pop(StacT, &element);     //gia na elegkso auta ta 2 grammata deksia kai aristera tou C. An doso kai deutero gramma exo 2 deksia 2 aristera kai to C
                    Push(&temp, element);
                }

                CheckLetter=element;
               // printf("Check: %c\n", CheckLetter);

                for(i = temp.Top; i > -1; i--)
                {
                    Pop(&temp, &element);
                    Push(StacT, element);
                }

                if(StacT->Element[StacT->Top] != CheckLetter)//Xalase i summetria dioti evales lathos gramma
                {
                    *flag2=FALSE;
                    return ;
                }
            }
            else
                Push(StacT, ch);
        }
        else
        {
            if(ctr==0 && EmptyStack(*StacT))
            {
                printf("Do not insert C for your first letter.\n");
                *flag1=FALSE;
                return ;
            }

            if(*flag1)
            {
                *ctim=TRUE;
                printf("Invalid format.You can't insert C more than once...\n"); // 2 fores i perissoteres na doseis C den ginetai
                return ;
            }
            *flag1=TRUE; //Dosame proti fora C
            Push(StacT, ch);
            Cpos=StacT->Top;
        }
    }
}
