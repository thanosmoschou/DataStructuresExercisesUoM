#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NumberOfNodes 10    /*όριο μεγέθους της συνδεδεμένης λίστας,
                            ενδεικτικά τέθηκε ίσο με 50*/
#define NilValue -1          // ειδική μεδενικη τιμη δείχνει το τέλος της Συνδ.λίστας

typedef struct
{
    int classItem;
    int freq;
} ListElementType1; /*τύπος δεδομένων για τα στοιχεία της συνδεδεμένης λίστας,
                                ενδεικτικά επιλέχθηκε ο τύπος int */
typedef int ListPointer;

typedef struct {
    ListElementType1 Data;
    ListPointer  Next;
} NodeType1;


typedef struct
{
    int classItem;
} ListElementType2;


typedef struct {
    ListElementType2 Data;
    ListPointer  Next;
} NodeType2;


typedef enum {
    FALSE, TRUE
} boolean;


//Function prototypes
void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
boolean FullList(ListPointer FreePtr);
void Delete2(ListPointer *List, NodeType2 Node[], ListPointer *FreePtr, ListPointer PredPtr);
void Delete1(ListPointer *List, NodeType1 Node[], ListPointer *FreePtr, ListPointer PredPtr);
void Insert2(ListPointer *List, NodeType2 Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType2 Item);
void Insert1(ListPointer *List, NodeType1 Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType1 Item);
void ReleaseNode2(NodeType2 Node[], ListPointer P, ListPointer *FreePtr);
void ReleaseNode1(NodeType1 Node[], ListPointer P, ListPointer *FreePtr);
void GetNode2(ListPointer *P, ListPointer *FreePtr, NodeType2 Node[]);
void GetNode1(ListPointer *P, ListPointer *FreePtr, NodeType1 Node[]);
void InitializeStoragePool1(NodeType1 Node[], ListPointer *FreePtr);
void InitializeStoragePool2(NodeType2 Node[], ListPointer *FreePtr);
void TraverseLinked(ListPointer List, NodeType1 Node[]);
void menu(int *choice);
void fillTheLists(ListPointer *AList, ListPointer *BList, NodeType1 Node1[], NodeType2 Node2[], ListPointer *FreePtr1, ListPointer *FreePtr2, ListPointer *PredPtr1, ListPointer *PredPtr2, int *obserNum);
void getFrequency(ListPointer *AList, ListPointer *BList, NodeType1 Node1[], NodeType2 Node2[], ListPointer *FreePtr1, ListPointer *FreePtr2, ListPointer *PredPtr1, ListPointer *PredPtr2, int *obserNum);
void sortList(ListPointer *AList, NodeType1 Node[], ListPointer *FreePtr, ListPointer *PredPtr);
void switch_positions (ListPointer PrevPtr, ListPointer CurrentPtr,ListPointer NextPtr, NodeType1 Node[],
ListPointer *List);


//Main function
int main()
{
    ListPointer AList, BList;
    NodeType1 Node1[NumberOfNodes];
    NodeType2 Node2[NumberOfNodes];
    ListPointer FreePtr1, PredPtr1, FreePtr2, PredPtr2;

    int obserNum;

    CreateList(&AList);
    CreateList(&BList);
    InitializeStoragePool1(Node1, &FreePtr1);
    InitializeStoragePool2(Node2, &FreePtr2);

    fillTheLists(&AList, &BList, Node1, Node2, &FreePtr1, &FreePtr2, &PredPtr1, &PredPtr2, &obserNum);
    getFrequency(&AList, &BList, Node1, Node2, &FreePtr1, &FreePtr2, &PredPtr1, &PredPtr2, &obserNum);
    sortList(&AList, Node1, &FreePtr1, &PredPtr1);

    TraverseLinked(AList, Node1);

    return 0;
}

//Function definition
void InitializeStoragePool1(NodeType1 Node[], ListPointer *FreePtr)
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

    for (i=0; i<NumberOfNodes-1;i++)
    {
        Node[i].Next=i+1;
        //Node[i].Data.freq = -0;
        //Node[i].Data.classItem=i;    /* δεν είναι αναγκαίο η απόδοση αρχικής τιμής στο πεδίο των δεδομένων, βοηθάει στην εκτύπωση */
    }
    Node[NumberOfNodes-1].Next=NilValue;
    //Node[NumberOfNodes - 1].Data.freq = 0;
    //Node[NumberOfNodes-1].Data.classItem= NumberOfNodes - 1;
    *FreePtr=0;
}


void InitializeStoragePool2(NodeType2 Node[], ListPointer *FreePtr)
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

    for (i=0; i<NumberOfNodes-1;i++)
    {
        Node[i].Next=i+1;
        //Node[i].Data.classItem=-1;    /* δεν είναι αναγκαίο η απόδοση αρχικής τιμής στο πεδίο των δεδομένων, βοηθάει στην εκτύπωση */
    }
    Node[NumberOfNodes-1].Next=NilValue;
    //Node[NumberOfNodes-1].Data.classItem=-1;
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


void GetNode1(ListPointer *P, ListPointer *FreePtr, NodeType1 Node[])
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


void GetNode2(ListPointer *P, ListPointer *FreePtr, NodeType2 Node[])
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


void ReleaseNode1(NodeType1 Node[], ListPointer P, ListPointer *FreePtr)
/* Δέχεται:    Τον πίνακα Node, που αναπαριστά τη δεξαμενή των διαθέσιμων κόμβων,
                έναν δείκτη TempPtr και τον δείκτη FreePtr.
   Λειτουργία: Επιστρέφει στη δεξαμενή τον κόμβο στον οποίο δείχνει ο TempPtr.
   Επιστρέφει: Τον τροποποιημένο πίνακα Node και τον δείκτη FreePtr
*/
{
  Node[P].Next =*FreePtr;
  Node[P].Data.freq = -1;
  Node[P].Data.classItem = -1; /* Οχι αναγκαία εντολή, βοηθητική για να φαίνονται στην
                        εκτύπωση οι διαγραμμένοι κόμβοι */
  *FreePtr =P;
}


void ReleaseNode2(NodeType2 Node[], ListPointer P, ListPointer *FreePtr)
/* Δέχεται:    Τον πίνακα Node, που αναπαριστά τη δεξαμενή των διαθέσιμων κόμβων,
                έναν δείκτη TempPtr και τον δείκτη FreePtr.
   Λειτουργία: Επιστρέφει στη δεξαμενή τον κόμβο στον οποίο δείχνει ο TempPtr.
   Επιστρέφει: Τον τροποποιημένο πίνακα Node και τον δείκτη FreePtr
*/
{
  Node[P].Next =*FreePtr;
  Node[P].Data.classItem = -1; /* Οχι αναγκαία εντολή, βοηθητική για να φαίνονται στην
                        εκτύπωση οι διαγραμμένοι κόμβοι */
  *FreePtr =P;
}


void Insert1(ListPointer *List, NodeType1 Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType1 Item)
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
  GetNode1(&TempPtr,FreePtr,Node);
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


void Insert2(ListPointer *List, NodeType2 Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType2 Item)
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
  GetNode2(&TempPtr,FreePtr,Node);
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

void Delete1(ListPointer *List, NodeType1 Node[], ListPointer *FreePtr, ListPointer PredPtr)
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
        ReleaseNode1(Node,TempPtr,FreePtr);
    }
    else
      {
        TempPtr =Node[PredPtr].Next;
        Node[PredPtr].Next =Node[TempPtr].Next;
        ReleaseNode1(Node,TempPtr,FreePtr);
      }
  else
    printf("Empty List ...\n");
}



void Delete2(ListPointer *List, NodeType2 Node[], ListPointer *FreePtr, ListPointer PredPtr)
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
        ReleaseNode2(Node,TempPtr,FreePtr);
    }
    else
      {
        TempPtr =Node[PredPtr].Next;
        Node[PredPtr].Next =Node[TempPtr].Next;
        ReleaseNode2(Node,TempPtr,FreePtr);
      }
  else
    printf("Empty List ...\n");
}


void TraverseLinked(ListPointer List, NodeType1 Node1[])
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
          printf("(%d: %d) ",Node1[CurrPtr].Data.classItem, Node1[CurrPtr].Data.freq);
          CurrPtr=Node1[CurrPtr].Next;
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


/*void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[])
{
    int i;
    printf("1o STOIXEIO LISTAS=%d, 1H FREE POSITION=%d\n", List, FreePtr);
    printf("H STORAGE POOL EXEI TA EJHS STOIXEIA\n");
    for (i=0;i<NumberOfNodes;i++)
        printf("(%d: %d->%d) ",i,Node[i].Data, Node[i].Next);
    printf("\n");
}*/


void fillTheLists(ListPointer *AList, ListPointer *BList, NodeType1 Node1[], NodeType2 Node2[], ListPointer *FreePtr1, ListPointer *FreePtr2, ListPointer *PredPtr1, ListPointer *PredPtr2, int *obserNum)
{
    ListElementType1 AItem;
    ListElementType2 BItem;

    printf("Give observations number: ");
    do
    {
        scanf("%d", obserNum);
        if(*obserNum <= 0 || *obserNum > NumberOfNodes)
            printf("Enter valid data [0...%d].\nGive observations number: ", NumberOfNodes);
    }while(*obserNum <= 0 || *obserNum > NumberOfNodes);

    for(int i = 0; i < *obserNum; i++)
    {
        printf("Enter an observation: ");
        scanf("%d", &BItem.classItem);
        Insert2(BList, Node2, FreePtr2, *PredPtr2 = NilValue, BItem);
    }

    for(int i = 0; i < NumberOfNodes; i++)
    {
        AItem.classItem = i;
        AItem.freq = 0;
        Insert1(AList, Node1, FreePtr1, *PredPtr1 = NilValue, AItem);
    }

}


void getFrequency(ListPointer *AList, ListPointer *BList, NodeType1 Node1[], NodeType2 Node2[], ListPointer *FreePtr1, ListPointer *FreePtr2, ListPointer *PredPtr1, ListPointer *PredPtr2, int *obserNum)
{
    ListPointer curr1, curr2;


    if(!EmptyList(*BList))
    {
        curr2 = *BList;
        while(curr2 != NilValue)
        {
            curr1 = *AList;
            while(curr1 != NilValue)
            {
                if(Node1[curr1].Data.classItem == Node2[curr2].Data.classItem)
                {
                    Node1[curr1].Data.freq++;
                    break;
                }
                else
                {
                    curr1 = Node1[curr1].Next;
                }
            }
            curr2 = Node2[curr2].Next;
        }
    }
    else
    {
        printf("Empty List\n");
    }
}


void sortList(ListPointer *AList, NodeType1 Node[], ListPointer *FreePtr, ListPointer *PredPtr)
{
    ListPointer OutPtr, CurrPtr, PrevPtr, NextPointer;
    boolean switchneed;


    if(!EmptyList(*AList))
    {
        OutPtr = *AList;

        while(OutPtr != NilValue)
        {
            CurrPtr = *AList;
            PrevPtr = NilValue;
            NextPointer = Node[CurrPtr].Next;

            while(NextPointer != NilValue) //Na min deixnei ektos listas
            {
                switchneed = FALSE;

                if(Node[CurrPtr].Data.freq < Node[NextPointer].Data.freq)
                    switchneed = TRUE;

                if(switchneed)
                {
                    /*tmpcur = CurrPtr;
                    tmpnext = NextPointer;
                    tmpprev = PrevPtr;  */

                    switch_positions(PrevPtr, CurrPtr, NextPointer, Node, AList);
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
}


void switch_positions (ListPointer PrevPtr, ListPointer CurrentPtr,ListPointer NextPtr, NodeType1 Node[],
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
