#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "a2f4p1Protot.h"

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


void ReleaseNode(NodeType Node[], ListPointer P, ListPointer *FreePtr)
/* Δέχεται:    Τον πίνακα Node, που αναπαριστά τη δεξαμενή των διαθέσιμων κόμβων,
                έναν δείκτη TempPtr και τον δείκτη FreePtr.
   Λειτουργία: Επιστρέφει στη δεξαμενή τον κόμβο στον οποίο δείχνει ο TempPtr.
   Επιστρέφει: Τον τροποποιημένο πίνακα Node και τον δείκτη FreePtr
*/
{
  Node[P].Next =*FreePtr;
  Node[P].Data = -1; /* Οχι αναγκαία εντολή, βοηθητική για να φαίνονται στην
                        εκτύπωση οι διαγραμμένοι κόμβοι */
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
          printf("(%d: %d->%d) ",CurrPtr,Node[CurrPtr].Data, Node[CurrPtr].Next);
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
        printf("(%d: %d->%d) ",i,Node[i].Data, Node[i].Next);
    printf("\n");
}


void FillAtTheEnd(ListPointer *AList,NodeType Node[], ListPointer *FreePtr,ListPointer PredPtr, ListElementType Item)
{
    ListPointer Curr, PrevP, Tempfree;

    Curr = *AList;
    PrevP = NilValue;
    Tempfree = *FreePtr;

    while(Curr != NilValue)
    {
        PrevP = Curr;
        Curr = Node[Curr].Next;
    }

    *FreePtr = Node[*FreePtr].Next;
    Node[Tempfree].Data = Item;
    Node[Tempfree].Next = NilValue;
    Node[PrevP].Next = Tempfree;
}


void CopyList(ListPointer *AList, ListPointer *FreePtr, ListPointer *ListCop,
ListPointer *FreeCop, ListPointer PredPtr,ListPointer PredCop,NodeType Node[],NodeType Cop[])
{
    ListPointer Curr;

    Curr = *AList;

    while(Curr != NilValue)
    {
        Insert(ListCop, Cop, FreeCop, PredCop, Node[Curr].Data);
        Curr = Node[Curr].Next;
    }

}


void UniteList(ListPointer *AList, ListPointer *ListCop, ListPointer *ListUnit, ListPointer *FreePtr, ListPointer *FreeCop,ListPointer *FreeUnit, ListPointer PredPtr,ListPointer PredCop, ListPointer PredUnit,
NodeType Node[],NodeType Cop[],NodeType Unit[])
{
    ListPointer Curr;

    if(!FullList(*FreeUnit))
    {
        Curr = *ListCop;
        while(Curr != NilValue)
        {
            PredUnit = NilValue;
            Insert(ListUnit, Unit, FreeUnit, PredUnit, Cop[Curr].Data);
            Curr = Cop[Curr].Next;
        }
    }
    else
        printf("Full List\n");

    if(!FullList(*FreeUnit))
    {
        Curr = *AList;
        while(Curr != NilValue)
        {
            PredUnit = NilValue;
            FillAtTheEnd(ListUnit, Unit, FreeUnit, PredUnit, Node[Curr].Data);
            Curr = Node[Curr].Next;
        }
    }
    else
        printf("Full List\n");

}


void DeleteNodes(ListPointer *ListUnit,ListPointer *FreeUnit,ListPointer PredUnit,NodeType Unit[])
{
    ListPointer Curr;

    Curr = *ListUnit;

    while(Curr != NilValue)
    {
        *ListUnit = Unit[Curr].Next;
        Curr = Unit[Curr].Next;
    }
}


void ReverseNodes(ListPointer *List, NodeType Node[])
{
    ListPointer Curr, tmpcurr, tmpprev, tmplast, tmpmove;
    int ctr = 0, rep;

    Curr = *List;

    while(Curr != NilValue)
    {
        Curr = Node[Curr].Next;
        ctr++;
    }

    //Vrika thn thesi tou teleutaiou tora prepei na allakso tis theseis...na ta antistrepso

    tmpcurr = Curr = *List;
    tmpprev = NilValue;

    rep = 0;
    while(rep <= ctr/2)
    {
        Curr = Node[Curr].Next;
        tmplast = tmpcurr;

        while(tmplast != NilValue) //vrisko tin thesi tou teleutaiou kai afou kratisa thn thesi tou arxiko ta allazo
        {
            tmpprev = tmplast;
            tmplast = Node[tmplast].Next;
        }

        //klassiko switch positions
        tmpmove = tmpprev;
        Node[tmpprev].Next = tmpcurr;
        Node[tmpcurr].Next = tmpmove;
        rep++;
        tmpcurr = Curr;
    }
}


void DeleteLast(ListPointer *List, NodeType Node[], ListPointer *FreePtr)
{
    ListPointer prev, curr, prevprev;

    curr = *List;
    prev = NilValue;
    prevprev = NilValue;

    while(curr != NilValue)
    {
        prevprev = prev; //gia tin thesi tou proteleutaiou stoixeiou oste na ginei teleutaio
        prev = curr;
        curr = Node[curr].Next;
    }

    //Vrika tin thesi tou teleutaiou stoixeiou
    Node[prev].Data = -1;
    Node[prev].Next = *FreePtr;
    *FreePtr = prev;
    Node[prevprev].Next = NilValue;

}
