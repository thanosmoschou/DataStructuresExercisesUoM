#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LIMAM 9
#define LIMNAME 11
#define TXTELEMSCAN 7
#define MAXTRIES 3

typedef struct
{
    char AM[LIMAM];
    char name[LIMNAME];
    char surname[LIMNAME];
} BinTreeElementType;        /*ο τύπος των στοιχείων του ΔΔΑ ενδεικτικά τύπου int */

typedef struct BinTreeNode *BinTreePointer;
typedef struct BinTreeNode {
    BinTreeElementType Data;
    BinTreePointer LChild, RChild;
} BinTreeNode;

typedef enum {
    FALSE, TRUE
} boolean;


//Function prototypes
void CreateBST(BinTreePointer *Root);
boolean EmptyBST(BinTreePointer Root);
void BSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr, int *nodes);
void BSTSearch2(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr, BinTreePointer *Parent);
void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void InorderTraversal(BinTreePointer Root);
void menu(int *choice);
void BuildBST(BinTreePointer *Root);


//Main function
int main()
{
    BinTreePointer ARoot, LocPtr;
    BinTreeElementType AnItem;
    boolean Found;
    int i, nodes;
    char termch;

    CreateBST(&ARoot);
    BuildBST(&ARoot);
    //InorderTraversal(ARoot);

    for(i = 0; i < MAXTRIES; i++)
    {
        printf("Give am: ");
        scanf("%8[^\n]%c", AnItem.AM, &termch);

        BSTSearch(ARoot, AnItem, &Found, &LocPtr, &nodes);

        if(Found)
            printf("komboi=%d AM=%s Onoma=%s Epwnymo=%s\n", nodes, LocPtr->Data.AM, LocPtr->Data.name, LocPtr->Data.surname);
        else
            printf("komboi=%d o foithths den vrethike sto DDA\n", nodes);
    }


    return 0;
}


//Function definition
void CreateBST(BinTreePointer *Root)
/* Λειτουργία: Δημιουργεί ένα κενό ΔΔΑ.
   Επιστρέφει:  Τον μηδενικό δείκτη(NULL) Root
*/
{
    *Root = NULL;
}


boolean EmptyBST(BinTreePointer Root)
/* Δέχεται:   Ενα ΔΔα με το Root να δείχνει στη ρίζα του.
  Λειτουργία: Ελέγχει αν το ΔΔΑ είναι κενό.
  Επιστρέφει: TRUE αν το ΔΔΑ είναι κενό και FALSE διαφορετικά
*/
{   return (Root==NULL);
}


void BSTInsert(BinTreePointer *Root, BinTreeElementType Item)
/* Δέχεται:     Ένα ΔΔΑ με το δείκτη Root να δείχνει στη ρίζα του και ένα στοιχείο Item.
   Λειτουργία:  Εισάγει το στοιχείο Item στο ΔΔΑ.
   Επιστρέφει: Το τροποποιημένο ΔΔΑ με τον δείκτη Root να δείχνει στη ρίζα του
*/
{
    BinTreePointer LocPtr, Parent;
    boolean Found;

    LocPtr = *Root;
    Parent = NULL;
    Found = FALSE;
    while (!Found && LocPtr != NULL) {
        Parent = LocPtr;
        if (strcmp(Item.AM, LocPtr->Data.AM) < 0)
            LocPtr = LocPtr ->LChild;
        else if (strcmp(Item.AM, LocPtr->Data.AM) > 0)
            LocPtr = LocPtr ->RChild;
        else
            Found = TRUE;
    }
    if (Found)
        printf("TO STOIXEIO EINAI HDH STO DDA\n");
    else {
        LocPtr = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        LocPtr ->Data = Item;
        LocPtr ->LChild = NULL;
        LocPtr ->RChild = NULL;
        if (Parent == NULL)
            *Root = LocPtr;
        else if (strcmp(Item.AM, Parent->Data.AM) < 0)
            Parent ->LChild = LocPtr;
        else
            Parent ->RChild = LocPtr;
    }
}


void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
                BinTreePointer *LocPtr, int *nodes)
/* Δέχεται:    Ένα ΔΔΑ με το δείκτη Root να δείχνει στη ρίζα του και μια τιμή KeyValue.
   Λειτουργία: Αναζητά στο ΔΔΑ έναν κόμβο με τιμή KeyValue στο πεδίο κλειδί του.
   Επιστρέφει: Η Found έχει τιμή TRUE και ο δείκτης LocPtr δείχνει στον κόμβο που
                περιέχει την τιμή KeyValue, αν η αναζήτηση είναι επιτυχής.
                Διαφορετικά η Found έχει τιμή FALSE
*/
{

    (*LocPtr) = Root;
    (*Found) = FALSE;
    (*nodes) = 1;
    while (!(*Found) && (*LocPtr) != NULL)
    {
        if (strcmp(KeyValue.AM, (*LocPtr)->Data.AM) < 0)
        {
            (*LocPtr) = (*LocPtr)->LChild;
            (*nodes)++;
        }
        else
            if (strcmp(KeyValue.AM, (*LocPtr)->Data.AM) > 0)
            {
                (*LocPtr) = (*LocPtr)->RChild;
                (*nodes)++;
            }
            else (*Found) = TRUE;
        //(*nodes)++;
    }

    if((*LocPtr) == NULL)
        (*nodes)--; //An ftasei na elegksei fillo prepei na meioso ton arithmo nodes giati den uparxei
                    //allo epipedo na sugkrinei eno pio pano to nodes
                    //auksanetai giati pame se neo epipedo gia sigkrisi
}


void BSTSearch2(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
    BinTreePointer *LocPtr, BinTreePointer *Parent)
/* Δέχεται:    Ένα ΔΔΑ με το δείκτη Root να δείχνει στη ρίζα του και μια τιμή KeyValue.
   Λειτουργία: Αναζητά στο ΔΔΑ έναν κόμβο με τιμή KeyValue στο πεδίο κλειδί του
                και τον πατέρα του κόμβου αυτού.
   Επιστρέφει: Η Found έχει τιμή TRUE, ο δείκτης LocPtr δείχνει στον κόμβο που
                περιέχει την τιμή KeyValue και ο Parent δείχνει στον πατέρα
                αυτού του κόμβου, αν η αναζήτηση είναι επιτυχής.
                Διαφορετικά η Found έχει τιμή FALSE.
*/
{
    *LocPtr = Root;
    *Parent=NULL;
    *Found = FALSE;
    while (!(*Found) && *LocPtr != NULL)
    {
        if (strcmp(KeyValue.AM, (*LocPtr)->Data.AM) < 0) {
            *Parent=*LocPtr;
            *LocPtr = (*LocPtr)->LChild;
        }
        else
            if (strcmp(KeyValue.AM, (*LocPtr)->Data.AM) > 0) {
                *Parent=*LocPtr;
                *LocPtr = (*LocPtr)->RChild;
            }
            else *Found = TRUE;
    }

}


void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue)
/* Δέχεται:  Ένα ΔΔΑ με το δείκτη Root να δείχνει στη ρίζα του και μια τιμή KeyValue.
  Λειτουργία: Προσπαθεί να βρει έναν κόμβο στο ΔΔΑ που να περιέχει την τιμή
                KeyValue στο πεδίο κλειδί του τμήματος δεδομένων του και,
                αν τον βρει, τον διαγράφει από το ΔΔΑ.
  Επιστρέφει: Το τροποποιημένο ΔΔΑ με τον δείκτη Root να δείχνει στη ρίζα του.
*/
{

   BinTreePointer
   n,                   //δείχνει στον κόμβο που περιέχει την τιμή KeyValue *)
   Parent,              // πατέρας του n ή του nNext
   nNext,               // ενδοδιατεταγμένος επόμενος του n
   SubTree;             // δείκτης προς υποδέντρο του n
   boolean Found;       // TRUE AN TO ΣΤΟΙΧΕΙΟ KeyValue EINAI ΣΤΟΙΧΕΟ ΤΟΥ ΔΔΑ *)

     BSTSearch2(*Root, KeyValue, &Found , &n, &Parent);
     if (!Found)
        printf("TO STOIXEIO DEN EINAI STO DDA\n");
     else {
          if (n->LChild != NULL && n->RChild != NULL)
          {  // κόμβος προς διαγραφή με δύο παιδιά
                 //Βρες τον ενδοδιατεταγμένο επόμενο και τον πατέρα του
                 nNext = n->RChild;
                 Parent = n;
                 while (nNext->LChild !=NULL)  //* DIASXISH PROS TA ARISTERA *)
                 {
                      Parent = nNext;
                      nNext = nNext->LChild;
                 }
                /* Αντιγραφή των περιεχομένων του nNext στον n και
                αλλαγή του n ώστε να δείχνει στον επόμενο */
                n->Data = nNext->Data;
                n = nNext;
          } //Συνεχίζουμε με την περίπτωση που ο κόμβος έχει το πολύ 1 παιδί
          SubTree = n->LChild;
          if (SubTree == NULL)
             SubTree = n->RChild;
          if (Parent == NULL)                 //* 8A DIAGRAFEI H RIZA *)
             *Root = SubTree;
          else if (Parent->LChild == n)
                  Parent->LChild = SubTree;
               else
                   Parent->RChild = SubTree;
          free(n);
     }
}


void InorderTraversal(BinTreePointer Root)
/* Δέχεται:    Ένα δυαδικό δέντρο με το δείκτη Root να δείχνει στην ρίζα του.
   Λειτουργία: Εκτελεί ενδοδιατεταγμένη διάσχιση του δυαδικού δέντρου και
                επεξεργάζεται κάθε κόμβο ακριβώς μια φορά.
   Εμφανίζει: Το περιεχόμενο του κόμβου, και εξαρτάται από το είδος της επεξεργασίας
*/
{
    if (Root!=NULL) {
        InorderTraversal(Root->LChild);
        printf("%s %s %s\n",Root->Data.AM, Root->Data.name, Root->Data.surname);
        InorderTraversal(Root->RChild);
    }
}


void menu(int *choice)
{
    printf("                  MENOY                  \n");
    printf("-------------------------------------------------\n");
    printf("1. Insert an element to Binary Tree\n");
    printf("2. Inoder traverse of Binary TreeA\n");
    printf("3. Search for a element in Binary Tree\n");
    printf("4. Delete an element of Binary Tree\n");
    printf("5. Telos\n");
    printf("\nEpilogh: ");
    do
    {
    	scanf("%d", choice);
    } while (*choice<1 && *choice>4);
}


void BuildBST(BinTreePointer *Root)
{
    FILE *filename;
    BinTreeElementType anItem;
    char space1, space2, backslashR, endLine;
    int line = 0, elemScanned;

    filename = fopen("i31f5.txt", "r");
    if(filename == NULL)
    {
        printf("Problem with file: %s\n", "i31f5.txt");
        exit(1);
    }

    while(TRUE)
    {
        elemScanned = fscanf(filename, "%8[^ ]%c%10[^ ]%c%10[^\r]%c%c", anItem.AM, &space1, anItem.name, &space2, anItem.surname, &backslashR, &endLine);
        if(elemScanned != EOF && elemScanned != TXTELEMSCAN)
        {
            printf("Error in line %d\n", line);
            exit(1);
        }

        line++;

        if(elemScanned == EOF)
            break;

        BSTInsert(Root, anItem);
    }

    fclose(filename);
}


