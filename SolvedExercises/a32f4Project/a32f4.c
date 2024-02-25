#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define STRLIM 21
#define NumberOfNodes 10    /*όριο μεγέθους της συνδεδεμένης λίστας,
                            ενδεικτικά τέθηκε ίσο με 50*/
#define NilValue -1          // ειδική μεδενικη τιμη δείχνει το τέλος της Συνδ.λίστας

typedef struct
{
    int gymnasio;
    char name[STRLIM];
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
void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr, ListElementType *Item);
void TraverseLinked(ListPointer List, NodeType Node[]);
void menu(int *choice);
void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[]);
void Filling(NodeType Node1[], ListPointer *FreePtr1, ListPointer *AList, ListPointer PredPtr1, FILE *infile);
void Lottery(int Lott[], int dim);
void MoveStudents(NodeType Node1[],NodeType Node2[], ListPointer *AList, ListPointer *BList, ListPointer *FreePtr1, ListPointer *FreePtr2,ListPointer PredPtr1,ListPointer PredPtr2, int lott[], int dim);
void IsSick(NodeType Node1[],NodeType Node2[], ListPointer *AList, ListPointer *BList, ListPointer *FreePtr1, ListPointer *FreePtr2,ListPointer PredPtr1 , ListPointer PredPtr2);



//Main function
int main()
{
    FILE *infile;
    ListPointer AList, BList;
    NodeType Node1[NumberOfNodes], Node2[NumberOfNodes];
    ListPointer FreePtr1, FreePtr2, PredPtr1, PredPtr2;
    //ListElementType AnItem;
    int lott[4];

    infile = fopen("students.dat", "r");
    if(infile == NULL)
    {
        printf("Error with file %s\n", "students.dat");
        exit(1);
    }

    CreateList(&AList);
    CreateList(&BList);

    InitializeStoragePool(Node1, &FreePtr1);
    InitializeStoragePool(Node2, &FreePtr2);
    //printAll(BList, FreePtr2, Node2);

    PredPtr1 = NilValue;
    Filling(Node1, &FreePtr1, &AList, PredPtr1, infile);

    printf("Question a:\n");
    printAll(AList, FreePtr1, Node1);
    printf("Lista A\n");
    TraverseLinked(AList, Node1);

    Lottery(lott, 4);
    MoveStudents(Node1, Node2, &AList, &BList, &FreePtr1, &FreePtr2, PredPtr1 = NilValue, PredPtr2 = NilValue, lott, 4);

    printf("Question b:\n");
    printAll(AList, FreePtr1, Node1);
    printf("Lista A\n");
    TraverseLinked(AList, Node1);

    printAll(BList,FreePtr2,Node2);
    printf("Lista B\n");
    TraverseLinked(BList, Node2);

    printf("Question c:\n");
    IsSick(Node1, Node2, &AList, &BList, &FreePtr1, &FreePtr2, PredPtr1 = NilValue, PredPtr2 = NilValue);
    printAll(AList, FreePtr1, Node1);
    printf("Lista A\n");
    TraverseLinked(AList, Node1);

    printAll(BList,FreePtr2,Node2);
    printf("Lista B\n");
    TraverseLinked(BList, Node2);

    fclose(infile);
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

    for (i=0; i<NumberOfNodes-1;i++)
    {
        Node[i].Next=i+1;
        Node[i].Data.name[0] = '\0';
        Node[i].Data.gymnasio =-1;    /* δεν είναι αναγκαίο η απόδοση αρχικής τιμής στο πεδίο των δεδομένων, βοηθάει στην εκτύπωση */
    }
    Node[NumberOfNodes-1].Next=NilValue;
    Node[NumberOfNodes-1].Data.gymnasio =-1;
    Node[NumberOfNodes - 1].Data.name[0] = '\0';
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
  Node[P].Data.gymnasio = -1; /* Οχι αναγκαία εντολή, βοηθητική για να φαίνονται στην εκτύπωση οι διαγραμμένοι κόμβοι */
  Node[P].Data.name[0] = '\0';
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


void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr, ListElementType *Item)
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
        *Item = Node[TempPtr].Data;
        *List =Node[TempPtr].Next;
        ReleaseNode(Node,TempPtr,FreePtr);
    }
    else
      {
        TempPtr =Node[PredPtr].Next;
        *Item = Node[TempPtr].Data;
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
          printf("(%d: <%s,%d> ->%d) ",CurrPtr,Node[CurrPtr].Data.name,Node[CurrPtr].Data.gymnasio, Node[CurrPtr].Next);
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
        printf("(%d: <%s,%d> ->%d) ",i,Node[i].Data.name,Node[i].Data.gymnasio, Node[i].Next);
    printf("\n");
}


void Filling(NodeType Node1[], ListPointer *FreePtr1, ListPointer *AList, ListPointer PredPtr1, FILE *infile)
{
    char termch1, termch2;
    int  line, read, ctr = 0;
    ListElementType ins;

    line = 0;
    while(1)
    {
        char tmpname[STRLIM] = {'\0'};
        read = fscanf(infile, "%20[^\r]%c%c", tmpname, &termch1, &termch2);
        if(read != 3 && read != EOF)
        {
            printf("Problem in line %d\n", line);
            exit(1);
        }
        line++;

        if(read == EOF)
            break;

        if(tmpname[0] >= '0' && tmpname[0] <= '9')
        {
            int sum = 0; //Ksero oti exo mexri 2psifio noumero

            sum = atoi(tmpname);

            ctr++; //Kathe fora pou tha einai zugo tha eisago tin domi
            ins.gymnasio = sum;
        }
        else
        {
            strncpy(ins.name, tmpname, strlen(tmpname)+1); //thelo +1 giati tp strlen den metraei to \0
            ctr++;
        }

        if(ctr % 2 == 0) //Edo exo prolavei na valo stin temp domi mou kai to gymnasio kai to onoma
            Insert(AList, Node1, FreePtr1, PredPtr1 = NilValue, ins);
    }
}


void Lottery(int Lott[], int dim)
{
    int i;

    for(i = 0; i < dim; i++)
    {
        printf("Dwse thn thesh toy ma8hth poy klhrw8hke: ");
        do
        {
            scanf("%d", &Lott[i]);
            if(Lott[i] < 0 || Lott[i] > 10)
                printf("Give valid data\n");
        }while(Lott[i] < 0 || Lott[i] > 10);
    }
}


void MoveStudents(NodeType Node1[],NodeType Node2[], ListPointer *AList, ListPointer *BList, ListPointer *FreePtr1, ListPointer *FreePtr2,ListPointer PredPtr1,ListPointer PredPtr2, int lott[], int dim)
{
    int i;
    ListElementType temp;
    ListPointer tmpcurr,tmpprev;
    ListPointer ListP, curr;

    CreateList(&ListP);
    for(i = 0; i < dim; i++)
    {
        curr = *AList;
        while(curr != NilValue)
        {
            tmpprev = NilValue;
            tmpcurr = *BList;
            while(tmpcurr != NilValue)
            {
                tmpprev = tmpcurr;
                tmpcurr = Node2[tmpcurr].Next;
            }

            if(lott[i] == *AList)
            {
                Delete(AList, Node1, FreePtr1, NilValue, &temp);
                Insert(BList, Node2, FreePtr2, tmpprev , temp);
                break;
            }

            if(Node1[curr].Next == lott[i])
            {
                Delete(AList, Node1, FreePtr1, curr, &temp);
                Insert(BList, Node2, FreePtr2, tmpprev, temp);
                break;
            }
            else
            {
                curr = Node1[curr].Next;
            }
        }
    }
}


void IsSick(NodeType Node1[],NodeType Node2[], ListPointer *AList, ListPointer *BList, ListPointer *FreePtr1, ListPointer *FreePtr2,ListPointer PredPtr1 , ListPointer PredPtr2)
{
    ListElementType tmp;
    ListPointer curr;

    curr = *BList;

    Delete(BList, Node2, FreePtr2, PredPtr2 = curr, &tmp);
    Insert(AList, Node1, FreePtr1, PredPtr1=NilValue, tmp);

}
