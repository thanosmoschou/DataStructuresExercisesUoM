#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LIMCHAR 21
#define THINGSSCANNEDFROMFILE2 2

typedef struct
{
    char word[LIMCHAR];
}BinTreeElementType;        /*ο τύπος των στοιχείων του ΔΔΑ ενδεικτικά τύπου int */
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
void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void BSTSearch2(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr, BinTreePointer *Parent);
void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void InorderTraversal(BinTreePointer Root);
void menu(int *choice);
void CreateDictionary(BinTreePointer *Root, FILE *fp);
int SpellingCheck(BinTreePointer Root, FILE *fp);


//Main function
int main()
{
    BinTreePointer ARoot;
    int wordsNotInDictionary;
    FILE *filename1, *filename2;

    filename2 = fopen("i112f5.txt", "r");
    if(filename2 == NULL)
    {
        printf("Problem with file: %s\n", "i112f5.txt");
        exit(1);
    }

    CreateDictionary(&ARoot, filename2);

    printf("*********Dictionary************\n");
    InorderTraversal(ARoot);

    filename1 = fopen("i111f5.txt", "r");

    if(filename1 == NULL)
    {
        printf("Problem with file: %s\n", "i111f5.txt");
        exit(1);
    }

    printf("**************Not in dictionary**************\n");
    wordsNotInDictionary = SpellingCheck(ARoot, filename1);
    printf("Number of words not in dictionary: %d\n", wordsNotInDictionary);

    fclose(filename1);
    fclose(filename2);

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
    BinTreePointer LocPtr, Parent, RChild;
    boolean Found;

    LocPtr = *Root;
    Parent = NULL;
    Found = FALSE;
    RChild = LocPtr;
    while (!Found && LocPtr != NULL) {
        Parent = LocPtr;
        if (strncmp(Item.word, LocPtr->Data.word, strlen(LocPtr->Data.word)) < 0)
            LocPtr = LocPtr ->LChild;
        else if (strncmp(Item.word, LocPtr->Data.word, strlen(LocPtr->Data.word)) > 0)
            LocPtr = LocPtr ->RChild;
        else
            Found = TRUE;
    }
    if (Found)
        printf("TO STOIXEIO EINAI HDH STO DDA\n");
    else {
        LocPtr = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        strncpy(LocPtr ->Data.word, Item.word, strlen(Item.word));
        LocPtr ->LChild = NULL;
        LocPtr ->RChild = NULL;
        if (Parent == NULL)
            *Root = LocPtr;
        else if (strncmp(Item.word, Parent->Data.word, strlen(Parent->Data.word)) < 0)
            Parent ->LChild = LocPtr;
        else
            Parent ->RChild = LocPtr;
    }
}


void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
                BinTreePointer *LocPtr)
/* Δέχεται:    Ένα ΔΔΑ με το δείκτη Root να δείχνει στη ρίζα του και μια τιμή KeyValue.
   Λειτουργία: Αναζητά στο ΔΔΑ έναν κόμβο με τιμή KeyValue στο πεδίο κλειδί του.
   Επιστρέφει: Η Found έχει τιμή TRUE και ο δείκτης LocPtr δείχνει στον κόμβο που
                περιέχει την τιμή KeyValue, αν η αναζήτηση είναι επιτυχής.
                Διαφορετικά η Found έχει τιμή FALSE
*/
{

    (*LocPtr) = Root;
    (*Found) = FALSE;
    while (!(*Found) && (*LocPtr) != NULL)
    {
        if (strncmp(KeyValue.word, (*LocPtr)->Data.word, strlen(KeyValue.word)) < 0)
            (*LocPtr) = (*LocPtr)->LChild;
        else
            if (strncmp(KeyValue.word, (*LocPtr)->Data.word, strlen(KeyValue.word)) > 0)
                (*LocPtr) = (*LocPtr)->RChild;
            else (*Found) = TRUE;
    }
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
        if (strcmp(KeyValue.word, (*LocPtr)->Data.word) < 0) {
            *Parent=*LocPtr;
            *LocPtr = (*LocPtr)->LChild;
        }
        else
            if (strcmp(KeyValue.word, (*LocPtr)->Data.word) > 0) {
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
                strcpy(n->Data.word, nNext->Data.word);
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
        printf("%s\n",Root->Data.word);
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


void CreateDictionary(BinTreePointer *Root, FILE *fp)
{
    BinTreeElementType word;
    char termch;
    int scannedElements, line = 0;


    while(TRUE)
    {
        scannedElements = fscanf(fp, "%20[^\n]%c", word.word, &termch);

        if(scannedElements != EOF && scannedElements != THINGSSCANNEDFROMFILE2)
        {
            printf("Problem in line %d\n", line);
            exit(1);
        }

        line++;

        if(scannedElements == EOF)
            break;

        BSTInsert(Root, word);
    }
}


int SpellingCheck(BinTreePointer Root, FILE *fp)
{
    BinTreeElementType word;
    int wordsNotFound = 0;
    boolean Found;
    BinTreePointer LocPtr;


    while(fgets(word.word, LIMCHAR, fp) != NULL)
    {
        word.word[strlen(word.word) - 1] = '\0';
        BSTSearch(Root, word, &Found, &LocPtr);
        if(!Found)
        {
            printf("%s\n", word.word);
            wordsNotFound++;
        }
    }

    return wordsNotFound;
}
