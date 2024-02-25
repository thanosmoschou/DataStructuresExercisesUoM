#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LIMNAME 21
#define ELEMSCANFROMFILE 4
#define LIMFOREMPLOYEESINSERTION 3


typedef struct
{
    char name[LIMNAME];
    char code;
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
void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void BSTSearch2(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr, BinTreePointer *Parent);
void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void InorderTraversal(BinTreePointer Root);
void menu(int *choice);
void openAFile(FILE **filename);
void searchEmployee(BinTreePointer Root, BinTreeElementType employeeForSearch);
void InsertionToTrees(BinTreePointer *Root, FILE *filename);
void InorderTraversalEmployeesWithCriteria(BinTreePointer Root, BinTreeElementType criteria);
void showEmployeesViaCriteria(BinTreePointer *ARoot);


//Main function
int main()
{
    BinTreePointer ARoot;
    FILE *filename;

    openAFile(&filename);
    CreateBST(&ARoot);
    InsertionToTrees(&ARoot, filename);
    showEmployeesViaCriteria(&ARoot);

    fclose(filename);
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
        if (strncmp(Item.name, LocPtr->Data.name, strlen(LocPtr->Data.name)) < 0)
            LocPtr = LocPtr ->LChild;
        else if (strncmp(Item.name, LocPtr->Data.name, strlen(LocPtr->Data.name)) > 0)
            LocPtr = LocPtr ->RChild;
        else
            Found = TRUE;
    }
    if (Found)
        printf("TO STOIXEIO EINAI HDH STO DDA\n");
    else {
        LocPtr = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        strncpy(LocPtr ->Data.name, Item.name, strlen(Item.name));
        LocPtr->Data.code = Item.code;
        LocPtr ->LChild = NULL;
        LocPtr ->RChild = NULL;
        if (Parent == NULL)
            *Root = LocPtr;
        else if (strncmp(Item.name, Parent->Data.name, strlen(Parent->Data.name)) < 0)
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
        if (strncmp(KeyValue.name, (*LocPtr)->Data.name, strlen((*LocPtr)->Data.name)) < 0)
            (*LocPtr) = (*LocPtr)->LChild;
        else
            if (strncmp(KeyValue.name, (*LocPtr)->Data.name, strlen((*LocPtr)->Data.name)) > 0)
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
        if (strcmp(KeyValue.name, (*LocPtr)->Data.name) < 0) {
            *Parent=*LocPtr;
            *LocPtr = (*LocPtr)->LChild;
        }
        else
            if (strcmp(KeyValue.name, (*LocPtr)->Data.name) > 0) {
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
        printf("%-15s%-5c\n",Root->Data.name, Root->Data.code);
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


void openAFile(FILE **filename)
{
    *filename = fopen("i12f5.txt", "r");
    if(*filename == NULL)
    {
        printf("There is a problem with file: %s\n", "i12f5.txt");
        exit(1);
    }
}


void InsertionToTrees(BinTreePointer *Root, FILE *filename)
{
    BinTreeElementType anItem;
    int thingsScanned, lines = 0;
    char termch1, termch2;

    while(TRUE)
    {
        thingsScanned = fscanf(filename, "%20[^ ]%c%c%c", anItem.name, &termch1, &anItem.code, &termch2);
        if(thingsScanned != EOF && thingsScanned != ELEMSCANFROMFILE)
        {
            printf("Error in line %d\n", lines);
            exit(1);
        }

        lines++;

        if(thingsScanned == EOF)
            break;

        BSTInsert(Root, anItem);
    }
}


void searchEmployee(BinTreePointer Root, BinTreeElementType employeeForSearch)
{
    boolean Found = FALSE;
    BinTreePointer LocPtr;

    LocPtr = Root;

    printf("Employees with the same name:\n");
    printf("%-15s%-5s\n", "EMPLOYEES", "CODES");
    printf("--------------------\n");
    BSTSearch(Root, employeeForSearch, &Found, &LocPtr);

    if(Found)
        printf("%-15s%-5c\n", LocPtr->Data.name, LocPtr->Data.code);
    else
        printf("There are not employees with this name.\n");
}


void showEmployeesViaCriteria(BinTreePointer *ARoot)
{
    BinTreeElementType AnItem;
    char termch;
    int i;

    printf("%-15s%-5s\n", "EMPLOYEES", "CODES");
    printf("--------------------\n");
    InorderTraversal(*ARoot);

    for(i = 0; i < LIMFOREMPLOYEESINSERTION; i++)
    {
        printf("\nPlease enter the employee's name(MAX: %d CHARACTERS): ", LIMNAME - 1);
        scanf("%20[^\n]%c", AnItem.name, &termch);
        printf("Please enter the employee's code(1-3): ");
        scanf("%c%c", &AnItem.code, &termch);
        BSTInsert(ARoot, AnItem);
    }

    printf("\nList all employees:\n%-15s%-5s\n", "EMPLOYEES", "CODES");
    printf("--------------------\n");
    InorderTraversal(*ARoot);

    printf("\nPlease enter the name of the employee that you want to search: ");
    scanf("%20[^\n]%c", AnItem.name, &termch);
    searchEmployee(*ARoot, AnItem);

    printf("\nList all employees:\n%-15s%-5s\n", "EMPLOYEES", "CODES");
    printf("--------------------\n");
    InorderTraversal(*ARoot);

    printf("\nList office employees:\n%-15s%-5s\n", "EMPLOYEES", "CODES");
    printf("--------------------\n");
    AnItem.code = '1';
    InorderTraversalEmployeesWithCriteria(*ARoot, AnItem);

    printf("\nList sale employees:\n%-15s%-5s\n", "EMPLOYEES", "CODES");
    printf("--------------------\n");
    AnItem.code = '2';
    InorderTraversalEmployeesWithCriteria(*ARoot, AnItem);

    printf("\nList sale representatives:\n%-15s%-5s\n", "EMPLOYEES", "CODES");
    printf("--------------------\n");
    AnItem.code = '3';
    InorderTraversalEmployeesWithCriteria(*ARoot, AnItem);

    printf("\nEnter the name of the employee that you want to delete: ");
    scanf("%20[^\n]%c", AnItem.name, &termch);
    BSTDelete(ARoot, AnItem);

    printf("\nList all employees:\n%-15s%-5s\n", "EMPLOYEES", "CODES");
    printf("--------------------\n");
    InorderTraversal(*ARoot);
}


void InorderTraversalEmployeesWithCriteria(BinTreePointer Root, BinTreeElementType criteria)
/* Δέχεται:    Ένα δυαδικό δέντρο με το δείκτη Root να δείχνει στην ρίζα του.
   Λειτουργία: Εκτελεί ενδοδιατεταγμένη διάσχιση του δυαδικού δέντρου και
                επεξεργάζεται κάθε κόμβο ακριβώς μια φορά.
   Εμφανίζει: Το περιεχόμενο του κόμβου, και εξαρτάται από το είδος της επεξεργασίας
*/
{
    if(Root!=NULL ) {

        InorderTraversalEmployeesWithCriteria(Root->LChild, criteria);
        if(Root->Data.code == criteria.code)
            printf("%-15s%-5c\n",Root->Data.name, Root->Data.code);
        InorderTraversalEmployeesWithCriteria(Root->RChild, criteria);
    }
}
