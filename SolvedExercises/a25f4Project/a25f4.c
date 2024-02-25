#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NumberOfNodes 10    /*όριο μεγέθους της συνδεδεμένης λίστας,
                            ενδεικτικά τέθηκε ίσο με 50*/
#define NilValue -1          // ειδική μεδενικη τιμη δείχνει το τέλος της Συνδ.λίστας

typedef struct
{
    char name[21];
    int weight;
    int cost;
} ListElementType; /*τύπος δεδομένων για τα στοιχεία της συνδεδεμένης λίστας,
                                ενδεικτικά επιλέχθηκε ο τύπος int */
typedef int ListPointer;

typedef struct {
    ListElementType Data;
    ListPointer  Next;
} NodeType;

typedef enum {
    FALSE, TRUE
} boolean;


//Function prototypes
void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr);
void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
boolean FullList(ListPointer FreePtr);
void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]);
void ReleaseNode(NodeType Node[NumberOfNodes], ListPointer P, ListPointer *FreePtr);
void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item);
void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr);
void TraverseLinked(ListPointer List, NodeType Node[]);
void menu(int *choice);
void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[]);
void switch_positions (ListPointer PrevPtr, ListPointer CurrentPtr,ListPointer NextPtr, NodeType Node[],ListPointer *List);
void sort_list(ListPointer *List, NodeType Node[], boolean Ascending, int ByFeature);

//Main function
int main()
{
    ListPointer AList;
    NodeType Node[NumberOfNodes];
    ListPointer FreePtr,PredPtr;
    //ListPointer tmp1;

    ListElementType AnItem;

    int n,i;
    boolean Ascending;
    int ByFeature;

    InitializeStoragePool(Node, &FreePtr);
    CreateList(&AList);
    printAll(AList, FreePtr, Node);
    TraverseLinked(AList, Node);

    do
    {
        printf("Give objects number:");
        scanf("%d", &n);
    }while(n < 0 || n > 10);

    for(i = 0; i < n; i++)
    {
        printf("Give name: ");
        scanf("%s", AnItem.name);
        getchar();
        printf("Give weight: ");
        scanf("%d", &AnItem.weight);
        printf("Give cost: ");
        scanf("%d", &AnItem.cost);
        getchar();

        PredPtr = NilValue;
        Insert(&AList, Node, &FreePtr, PredPtr, AnItem);
    }

    printAll(AList, FreePtr, Node);
    TraverseLinked(AList, Node);

    Ascending = TRUE;
    ByFeature = 1;
    printf("Name Ascending:\n");
    sort_list(&AList, Node, Ascending, ByFeature); //True gia auksousa seira
    TraverseLinked(AList, Node);

    ByFeature++;
    printf("Weight Ascending:\n");
    sort_list(&AList, Node, Ascending, ByFeature);
    TraverseLinked(AList, Node);

    ByFeature++;
    printf("Cost Ascending:\n");
    sort_list(&AList, Node, Ascending, ByFeature);
    TraverseLinked(AList, Node);

    Ascending = FALSE;
    ByFeature = 1;
    printf("Name Ascending:\n");
    sort_list(&AList, Node, Ascending, ByFeature);  //fALSE GIA FTHINOUSA SEIRA
    TraverseLinked(AList, Node);

    ByFeature++;
    printf("Weight Ascending:\n");
    sort_list(&AList, Node, FALSE, ByFeature);
    TraverseLinked(AList, Node);

    ByFeature++;
    printf("Cost Ascending:\n");
    sort_list(&AList, Node, FALSE, ByFeature);
    TraverseLinked(AList, Node);


    return 0;
}

//Function definition
void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr)
/* Δέχεται:   Τον πίνακα Node και τον δείκτη FreePtr που δείχνει στον
                πρώτο διαθέσιμο κόμβο.
  Λειτουργία: Αρχικοποιεί τον πίνακα Node ως συνδεδεμένη λίστα συνδέοντας μεταξύ
                τους διαδοχικές εγγραφές του πίνακα,
                και αρχικοποιεί τον δείκτη FreePtr .
  Επιστρέφει: Τον τροποποιημένο πίνακα Node και τον
                δείκτη FreePtr του πρώτου διαθέσιμου κόμβου
*/
{
    int i;

    ListElementType tmp;

    tmp.name[0] = '\0';
    tmp.cost = 0;
    tmp.weight = 0;

    for (i=0; i<NumberOfNodes-1;i++)
    {
        Node[i].Next=i+1;
        Node[i].Data.name[0] = tmp.name[0];    /* δεν είναι αναγκαίο η απόδοση αρχικής τιμής στο πεδίο των δεδομένων, βοηθάει στην εκτύπω
        ση */
        Node[i].Data.weight = tmp.weight;
        Node[i].Data.cost = tmp.cost;
    }
    Node[NumberOfNodes-1].Next=NilValue;
    Node[NumberOfNodes - 1].Data.name[0] = tmp.name[0];    /* δεν είναι αναγκαίο η απόδοση αρχικής τιμής στο πεδίο των δεδομένων, βοηθάει στην εκτύπω
        ση */
    Node[NumberOfNodes - 1].Data.weight = tmp.weight;
    Node[NumberOfNodes - 1].Data.cost = tmp.cost;
    //Node[NumberOfNodes-1].Data=-1;
    *FreePtr=0;
}


void CreateList(ListPointer *List)
/* Λειτουργία: Δημιουργεί μια κενή συνδεδεμένη λίστα.
   Επιστρέφει: Έναν (μηδενικό) δείκτη που δείχνει σε κενή λίστα
*/
{
  *List=NilValue;
}


boolean EmptyList(ListPointer List)
/* Δέχεται:    Έναν δείκτη List που δείχνει σε μια συνδεδεμένη λίστα.
   Λειτουργία: Ελέγχει αν η συνδεδεμένη λίστα είναι κενή.
   Επιστρέφει: True αν η συνδεδεμένη λίστα είναι κενή και false διαφορετικά
*/
{
  return (List==NilValue);
}


boolean FullList(ListPointer FreePtr)
/* Δέχεται:    Μια συνδεδεμένη λίστα.
   Λειτουργία: Ελέγχει αν η συνδεδεμένη λίστα είναι γεμάτη.
   Επιστρέφει: True αν η συνδεδεμένηλίστα είναι γεμάτη, false διαφορετικά
*/
{
  return (FreePtr == NilValue);
}


void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[])
/* Δέχεται:   Τον πίνακα Node και τον δείκτη FreePtr.
  Λειτουργία: Αποκτά έναν "ελεύθερο" κόμβο που τον δείχνει ο δείκτης P.
  Επιστρέφει: Τον δείκτη P και τον τροποποιημένο  δείκτη FreePtr
                που δεικτοδοτεί στο πρώτο διαθέσιμο κόμβο
*/
{
  *P = *FreePtr;
  if (!FullList(*FreePtr))
    *FreePtr =Node[*FreePtr].Next;
}


void ReleaseNode(NodeType Node[], ListPointer P, ListPointer *FreePtr)
/* Δέχεται:    Τον πίνακα Node, που αναπαριστά τη δεξαμενή των διαθέσιμων κόμβων,
                έναν δείκτη TempPtr και τον δείκτη FreePtr.
   Λειτουργία: Επιστρέφει στη δεξαμενή τον κόμβο στον οποίο δείχνει ο TempPtr.
   Επιστρέφει: Τον τροποποιημένο πίνακα Node και τον δείκτη FreePtr
*/
{
  Node[P].Next =*FreePtr;
 // Node[P].Data = -1; /* Οχι αναγκαία εντολή, βοηθητική για να φαίνονται στην
                        //εκτύπωση οι διαγραμμένοι κόμβοι */
  *FreePtr =P;
}


void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item)
/* Δέχεται:    Μια συνδεδεμένη λίστα, τον πίνακα Node, τον δείκτη PredPtr και
                ένα στοιχείο Item.
  Λειτουργία: Εισάγει στη συνδεδεμένη λίστα, αν δεν είναι γεμάτη, το στοιχείο
                Item μετά από τον κόμβο στον οποίο δείχνει ο δείκτης PredPtr.
  Επιστρέφει: Την τροποποιημένη συνδεδεμένη λίστα, τον τροποποιημένο πίνακα Node
                και τον δείκτη FreePtr.
  Εξοδος:     Μήνυμα γεμάτης λίστας, αν η συνδεδεμένη λίστα είναι γεμάτη
*/
{
  ListPointer TempPtr;
  GetNode(&TempPtr,FreePtr,Node);
  if (!FullList(TempPtr)) {
    if (PredPtr==NilValue)
    {
        Node[TempPtr].Data =Item;
        Node[TempPtr].Next =*List;
        *List =TempPtr;
    }
    else
      {
        Node[TempPtr].Data =Item;
        Node[TempPtr].Next =Node[PredPtr].Next;
        Node[PredPtr].Next =TempPtr;
      }
}
  else
    printf("Full List ...\n");
}


void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr)
/* Δέχεται:   Μια συνδεδεμένη λίστα και τον δείκτη PredPtr που δείχνει
                στον προηγούμενο κόμβο από αυτόν που θα διαγραφεί.
  Λειτουργία: Διαγράφει από τη συνδεδεμένη λίστα, αν δεν είναι κενή,
                τον προηγούμενο κόμβο από αυτόν στον οποίο δείχνει ο PredPtr.
  Επιστρέφει: Την τροποποιημένη λίστα και το δείκτη FreePtr.
  Έξοδος:     Μήνυμα κενής λίστας, αν η συνδεδεμένη λίστα είναι κενή
*/
{
  ListPointer TempPtr ;

  if (!EmptyList(*List))
    if (PredPtr == NilValue)
    {
        TempPtr =*List;
        *List =Node[TempPtr].Next;
        ReleaseNode(Node,TempPtr,FreePtr);
    }
    else
      {
        TempPtr =Node[PredPtr].Next;
        Node[PredPtr].Next =Node[TempPtr].Next;
        ReleaseNode(Node,TempPtr,FreePtr);
      }
  else
    printf("Empty List ...\n");
}


void TraverseLinked(ListPointer List, NodeType Node[])
/* Δέχεται:    Μια συνδεδεμένη λίστα.
   Λειτουργία: Κάνει διάσχιση της συνδεδεμένης λίστας, αν δεν είναι κενή.
   Έξοδος:     Εξαρτάται από την επεξεργασία
*/
{
  ListPointer CurrPtr;

  if (!EmptyList(List))
  {
      CurrPtr =List;
      while (CurrPtr != NilValue)
      {
          printf("(%s, %d, %d)\n",Node[CurrPtr].Data.name, Node[CurrPtr].Data.weight,Node[CurrPtr].Data.cost );
          CurrPtr=Node[CurrPtr].Next;
       }
       printf("\n");
   }
  else printf("Empty List ...\n");
}


void menu(int *choice)
{
    printf("                  MENOY                  \n");
    printf("-------------------------------------------------\n");
    printf("1. Create List\n");
    printf("2. Insert an element to List\n");
    printf("3. Traverse List\n");
    printf("4. Delete an element from the List\n");
    printf("5. Check if List is empty\n");
    printf("6. Check if List is full\n");
    printf("7. Print storage pool\n");
    printf("8. Telos\n");
    printf("\nChoice 1-8 : ");
    do
    {
    	scanf("%d", choice);
    } while (*choice<1 && *choice>7);
}


void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[])
{
    int i;
    printf("1o STOIXEIO LISTAS=%d, 1H FREE POSITION=%d\n", List, FreePtr);
    printf("H STORAGE POOL EXEI TA EJHS STOIXEIA\n");
    for (i=0;i<NumberOfNodes;i++)
        printf("(%d:<%s,%d,%d> ->%d) ",i,Node[i].Data.name,Node[i].Data.weight,Node[i].Data.cost, Node[i].Next);
    printf("\n");
}


void sort_list(ListPointer *List, NodeType Node[], boolean Ascending, int ByFeature)
{
    ListPointer NextPointer,CurrPtr,PrevPtr, OutPtr;
    boolean switchneed;
    //ListPointer tmpcur,tmpnext,tmpprev;

    if(!EmptyList(*List))
    {
        OutPtr = *List; //Show to the 1st element of the list

        while(OutPtr != NilValue)
        {
            CurrPtr = *List;
            PrevPtr = NilValue;
            NextPointer = Node[CurrPtr].Next;

            while(NextPointer != NilValue) //Na min deixnei ektos listas
            {
                switchneed = FALSE;

                if(Ascending)
                {
                    switch(ByFeature)
                    {
                        case 1:
                            if(strcmp(Node[CurrPtr].Data.name, Node[NextPointer].Data.name) > 0) //The 1st is greater
                                switchneed = TRUE;
                            break;
                        case 2:
                            if(Node[CurrPtr].Data.weight > Node[NextPointer].Data.weight)
                                switchneed = TRUE;
                            break;
                        case 3:
                            if(Node[CurrPtr].Data.cost > Node[NextPointer].Data.cost)
                               switchneed = TRUE;
                            break;
                    }
                }
                else
                {
                    switch(ByFeature)
                    {
                        case 1:
                            if(strcmp(Node[CurrPtr].Data.name, Node[NextPointer].Data.name) < 0) //The 2nd is greater
                                switchneed = TRUE;
                            break;
                        case 2:
                            if(Node[CurrPtr].Data.weight < Node[NextPointer].Data.weight)
                                switchneed = TRUE;
                            break;
                        case 3:
                            if(Node[CurrPtr].Data.cost < Node[NextPointer].Data.cost)
                               switchneed = TRUE;
                            break;
                    }
                }

                if(switchneed)
                {
                    /*tmpcur = CurrPtr;
                    tmpnext = NextPointer;
                    tmpprev = PrevPtr;  */

                    switch_positions(PrevPtr, CurrPtr, NextPointer, Node, List);
                    if(OutPtr == CurrPtr)
                        OutPtr = NextPointer;
                    //PrevPtr = Node[PrevPtr].Next;

                    PrevPtr = NextPointer;
                    CurrPtr = Node[NextPointer].Next;
                    NextPointer = Node[CurrPtr].Next;
                }
                else
                {
                    PrevPtr = CurrPtr;
                    CurrPtr = Node[CurrPtr].Next;
                    NextPointer = Node[NextPointer].Next;
                }
            }

            OutPtr = Node[OutPtr].Next;
        }
    }
    else
        printf("Empty List...\n");

}


void switch_positions (ListPointer PrevPtr, ListPointer CurrentPtr,ListPointer NextPtr, NodeType Node[],
ListPointer *List)
{
    //ListPointer tmpcurr,tmpnext;

    //tmpcurr = CurrentPtr;
    //tmpnext = NextPtr;

    if(CurrentPtr == *List)
        *List = NextPtr;

    Node[CurrentPtr].Next = Node[NextPtr].Next;
    Node[NextPtr].Next = CurrentPtr;

    if(PrevPtr != NilValue)
        Node[PrevPtr].Next = NextPtr;
}
