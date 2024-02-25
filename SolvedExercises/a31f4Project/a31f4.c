#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NumberOfNodes 25
#define NumberOfNodes2 10    /*όριο μεγέθους της συνδεδεμένης λίστας,
                            ενδεικτικά τέθηκε ίσο με 50*/
#define NilValue -1          // ειδική μεδενικη τιμη δείχνει το τέλος της Συνδ.λίστας

//-----------------------gia tis parathrhseis-----------------------------
typedef int ListElementType; /*τύπος δεδομένων για τα στοιχεία της συνδεδεμένης λίστας,
                                ενδεικτικά επιλέχθηκε ο τύπος int */
typedef int ListPointer;

typedef struct {
    ListElementType Data;
    ListPointer  Next;
} NodeType;

//--------------------gia thn syxnothta----------------------------------
typedef struct
{
    int name;
    int freq;
} ListElementType2; /*τύπος δεδομένων για τα στοιχεία της συνδεδεμένης λίστας,
                                ενδεικτικά επιλέχθηκε ο τύπος int */

typedef struct {
    ListElementType2 Data;
    ListPointer  Next;
} NodeType2;

typedef enum {
    FALSE, TRUE
} boolean;


//Function prototypes
void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr);
void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
boolean FullList(ListPointer FreePtr);
void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]);
void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item);
void TraverseLinked(ListPointer List, NodeType Node[]);
void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[]);
//------------------------------------------------------------------------------------
void InitializeStoragePool2(NodeType2 Node[], ListPointer *FreePtr);
void GetNode2(ListPointer *P, ListPointer *FreePtr, NodeType2 Node[]);
void GetNode2(ListPointer *P, ListPointer *FreePtr, NodeType2 Node[]);
void Insert2(ListPointer *List, NodeType2 Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType2 Item);
void TraverseLinked2(ListPointer List, NodeType2 Node[]);
void Filling(NodeType Node1[],NodeType2 Node2[], ListPointer *FreePtr1, ListPointer *FreePtr2,ListPointer PredPtr1,ListPointer PredPtr2, ListPointer *AList, ListPointer *BList, int *sum);
void GetFrequencies(NodeType Node[], NodeType2 Node2[], ListElementType *FreePtr1, ListElementType *FreePtr2, ListElementType PredPtr1, ListElementType PredPtr2,
ListPointer *Alist, ListElementType *Blist);

//Main function
int main()
{
    ListPointer AList, BList;
    NodeType Node1[NumberOfNodes];
    NodeType2 Node2[NumberOfNodes2];
    ListPointer FreePtr1,PredPtr1, FreePtr2, PredPtr2;
    int sum;

    CreateList(&AList);
    CreateList(&BList);

    InitializeStoragePool(Node1, &FreePtr1);
    InitializeStoragePool2(Node2, &FreePtr2);

    PredPtr1 = PredPtr2 = NilValue;
    Filling(Node1, Node2, &FreePtr1, &FreePtr2, PredPtr1, PredPtr2, &AList, &BList, &sum);

    printf("1h Lista Parathrhsewn\n");
    TraverseLinked(AList, Node1);

    GetFrequencies(Node1,Node2, &FreePtr1, &FreePtr2, PredPtr1, PredPtr2, &AList, &BList);

    printf("2h Lista Syxnothtwn\n");
    TraverseLinked2(BList, Node2);

    return 0;
}


//Function definition

//------------------------------1st List functions-------------------------------------
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

    for (i=0; i<NumberOfNodes-1;i++)
    {
        Node[i].Next=i+1;
        Node[i].Data=-1;    /* δεν είναι αναγκαίο η απόδοση αρχικής τιμής στο πεδίο των δεδομένων, βοηθάει στην εκτύπωση */
    }
    Node[NumberOfNodes-1].Next=NilValue;
    Node[NumberOfNodes-1].Data=-1;
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
          printf("(%d) ",Node[CurrPtr].Data);
          CurrPtr=Node[CurrPtr].Next;
       }
       printf("\n");
   }
  else printf("Empty List ...\n");
}


//-------------------------------2nd List Functions-----------------------------------------------
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

    for (i=0; i<NumberOfNodes2-1;i++)
    {
        Node[i].Next=i+1;
        //Node[i].Data=-1;    /* δεν είναι αναγκαίο η απόδοση αρχικής τιμής στο πεδίο των δεδομένων, βοηθάει στην εκτύπωση */
    }
    Node[NumberOfNodes2-1].Next=NilValue;
    //Node[NumberOfNodes2-1].Data=-1;
    *FreePtr=0;
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


void TraverseLinked2(ListPointer List, NodeType2 Node[])
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
          printf("(%d: %d) ",Node[CurrPtr].Data.name, Node[CurrPtr].Data.freq);
          CurrPtr=Node[CurrPtr].Next;
       }
       printf("\n");
   }
  else printf("Empty List ...\n");
}


void Filling(NodeType Node1[],NodeType2 Node2[], ListPointer *FreePtr1, ListPointer *FreePtr2,ListPointer PredPtr1,ListPointer PredPtr2, ListPointer *AList, ListPointer *BList, int *sum)
{
    int i;
    ListElementType observ;
    ListElementType2 temp;

    printf("Give observations number: ");
    do
    {
        scanf("%d", sum);
        if(*sum <= 0 || *sum > NumberOfNodes)
            printf("Invalid Data.\n");
    }while(*sum <= 0 || *sum > NumberOfNodes);

    for(i = 0; i < *sum; i++)
    {
        printf("Enter an observation in [0,9]: ");
        do
        {
            scanf("%d", &observ);
            if(observ < 0 || observ > 9)
                printf("Invalid Data.\n");
        }while(observ < 0 || observ > 9);

        PredPtr1 = NilValue;
        Insert(AList, Node1, FreePtr1, PredPtr1, observ);
    }

    for(i = 0; i < NumberOfNodes2; i++)
    {
        temp.freq = 0;
        temp.name = i;

        PredPtr2 = NilValue;
        Insert2(BList, Node2, FreePtr2, PredPtr2, temp);
    }

}


void GetFrequencies(NodeType Node[], NodeType2 Node2[], ListElementType *FreePtr1, ListElementType *FreePtr2, ListElementType PredPtr1, ListElementType PredPtr2,
ListPointer *Alist, ListElementType *Blist)
{
    ListElementType curr,tmpcurr;

    if(!EmptyList(*Alist))
    {
        curr = *Alist;
        while(curr != NilValue)
        {
            tmpcurr = *Blist;

            while(tmpcurr != NilValue)
            {
                if(Node[curr].Data == Node2[tmpcurr].Data.name)
                {
                    Node2[tmpcurr].Data.freq++;
                    break;
                }
                else
                    tmpcurr = Node2[tmpcurr].Next;
            }
            curr = Node[curr].Next;
        }
    }
    else
        printf("Empty List\n");

}
