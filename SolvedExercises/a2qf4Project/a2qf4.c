#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef int ListElementType;           /* ο τύπος των στοιχείων της συνδεδεμένης λίστας
                                        ενδεικτικά τύπου int */
typedef struct ListNode *ListPointer;   //ο τύπος των δεικτών για τους κόμβους

typedef struct ListNode
{
	ListElementType Data;
    ListPointer Next;
} ListNode;


typedef enum {
    FALSE, TRUE
} boolean;


//Function prototypes
void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr);
void LinkedDelete(ListPointer *List, ListPointer PredPtr);
void LinkedTraverse(ListPointer List);
void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
void OrderedLinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
void menu(int *choice);
void list_insertion(ListPointer *List, int choice1);
void Filling(ListPointer *AList,int sumNum,ListPointer PredPtr);
void UniqueList(ListPointer InList, ListPointer *OutList);


//Main function
int main()
{
	 ListPointer AList, BList, PredPtr1;
	//int choice, choice1;
	//ListElementType item;
	//boolean Found;
    int sumNum1;


   	/*CreateList(&AList);
	list_insertion(&AList, choice1);
   	LinkedTraverse(AList);
	LinearSearch(AList, item, &PredPtr, &Found);
	LinkedDelete(&AList, PredPtr);
	OrderedLinearSearch(AList, item, &PredPtr, &Found);*/

    CreateList(&AList);
    CreateList(&BList);

    //Fill the 1st List
    printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS: ");
    do
    {
        scanf("%d", &sumNum1);
        if(sumNum1 < 0)
            printf("Please give valid data.\n");
    }while(sumNum1 < 0);

    if(sumNum1 > 0)
        Filling(&AList, sumNum1, PredPtr1 = NULL);

    //Printing
    if(!EmptyList(AList))
    {
        printf("1h lista\n");
        LinkedTraverse(AList);

        UniqueList(AList, &BList);

        printf("\nTeliki lista\n");
        LinkedTraverse(BList);
        printf("\n");
    }
    else
    {
        printf("1h lista\n");
        LinkedTraverse(AList);

        printf("\nTeliki lista\n");
        LinkedTraverse(BList);
        printf("\n");
    }

	return 0;
}


//Function definition
void CreateList(ListPointer *List)
/* Λειτουργία: Δημιουργεί μια κενή συνδεδεμένη λίστα.
  Επιστρέφει:  Τον μηδενικό δείκτη List
*/
{
	*List = NULL;
}


boolean EmptyList(ListPointer List)
/* Δέχεται:   Μια συνδεδεμένη λίστα με τον List να δείχνει στον πρώτο κόμβο.
  Λειτουργία: Ελέγχει αν η συνδεδεμένη λίστα είναι κενή.
  Επιστρέφει: True αν η λίστα είναι κενή και false διαφορετικά
*/
{
	return (List==NULL);
}


void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr)
/* Δέχεται:    Μια συνδεδεμένη λίστα με τον List να δείχνει στον πρώτο κόμβο,
                ένα στοιχείο δεδομένων Item και έναν δείκτη PredPtr.
   Λειτουργία: Εισάγει έναν κόμβο, που περιέχει το Item, στην συνδεδεμένη λίστα
                μετά από τον κόμβο που δεικτοδοτείται από τον PredPtr
                ή στην αρχή  της συνδεδεμένης λίστας,
                αν ο PredPtr είναι μηδενικός(NULL).
  Επιστρέφει:  Την τροποποιημένη συνδεδεμένη λίστα με τον πρώτο κόμβο της
                να δεικτοδοτείται από τον List.
*/
{
	ListPointer TempPtr;

   TempPtr= (ListPointer)malloc(sizeof(struct ListNode));
   TempPtr->Data = Item;
	if (PredPtr==NULL) {
        TempPtr->Next = *List;
        *List = TempPtr;
    }
    else {
        TempPtr->Next = PredPtr->Next;
        PredPtr->Next = TempPtr;
    }
}


void LinkedDelete(ListPointer *List, ListPointer PredPtr)
/* Δέχεται:    Μια συνδεδεμένη λίστα με τον List να δείχνει στον πρώτο κόμβο της
                 και έναν δείκτη PredPtr.
   Λειτουργία: Διαγράφει από τη συνδεδεμένη λίστα τον κόμβο που έχει
                για προηγούμενό του αυτόν στον οποίο δείχνει ο PredPtr
                ή διαγράφει τον πρώτο κόμβο, αν ο PredPtr είναι μηδενικός,
                εκτός και αν η λίστα είναι κενή.
   Επιστρέφει: Την τροποποιημένη συνδεδεμένη λίστα με τον πρώτο κόμβο
                να δεικτοδοτείται από τον List.
   Έξοδος:     Ένα μήνυμα κενής λίστας αν η συνδεδεμένη λίστα ήταν κενή .
*/
{
    ListPointer TempPtr;

    if (EmptyList(*List))
   	    printf("EMPTY LIST\n");
   else
   {
   	    if (PredPtr == NULL)
        {
      	      TempPtr = *List;
              *List = TempPtr->Next;
        }
        else
        {
      	     TempPtr = PredPtr->Next;
             PredPtr->Next = TempPtr->Next;
        }
        free(TempPtr);
    }
}


void LinkedTraverse(ListPointer List)
/* Δέχεται:    Μια συνδεδεμένη λίστα με τον List να δείχνει στον πρώτο κόμβο.
   Λειτουργία: Διασχίζει τη συνδεδεμένη λίστα και
                επεξεργάζεται κάθε δεδομένο ακριβώς μια φορά.
   Επιστρέφει: Εξαρτάται από το είδος της επεξεργασίας.
*/
{
	ListPointer CurrPtr;

   if (EmptyList(List))
   	    printf("EMPTY LIST\n");
   else
   {
   	    CurrPtr = List;
   	    //printf("%-16s\t%-4s\t%-16s\n", "CurrPtr","Data","Next");
         while ( CurrPtr!=NULL )
        {
             printf("%d ",(*CurrPtr).Data);
             CurrPtr = CurrPtr->Next;
        }
   }
}


void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found)
/* Δέχεται:   Μια συνδεδεμένη λίστα με τον List να δείχνει στον πρώτο κόμβο.
  Λειτουργία: Εκτελεί μια γραμμική αναζήτηση στην μη ταξινομημένη συνδεδεμένη
              λίστα για έναν κόμβο που να περιέχει το στοιχείο Item.
  Επιστρέφει: Αν η αναζήτηση είναι επιτυχής η Found είναι true, ο CurrPtr δείχνει
                στον κόμβο που περιέχει το Item και ο PredPtr στον προηγούμενό του
                ή είναι nil αν δεν υπάρχει προηγούμενος.
                Αν η αναζήτηση δεν είναι επιτυχής η Found είναι false.
*/
{
   ListPointer CurrPtr;
   boolean stop;

   CurrPtr = List;
    *PredPtr=NULL;
   stop= FALSE;
   while (!stop && CurrPtr!=NULL )
    {
         if (CurrPtr->Data==Item )
         	stop = TRUE;
         else
         {
         	*PredPtr = CurrPtr;
            CurrPtr = CurrPtr->Next;
         }
	}
	*Found=stop;
}


void OrderedLinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found)
/* Δέχεται:    Ένα στοιχείο Item και μια ταξινομημένη συνδεδεμένη λίστα,
                που περιέχει στοιχεία δεδομένων σε αύξουσα διάταξη και στην οποία
                ο δείκτης List δείχνει στον πρώτο  κόμβο.
   Λειτουργία: Εκτελεί γραμμική αναζήτηση της συνδεδεμένης ταξινομημένης λίστας
                για τον πρώτο κόμβο που περιέχει το στοιχείο Item ή για μια θέση
                για να εισάγει ένα νέο κόμβο που να περιέχει το στοιχείο Item.
   Επιστρέφει: Αν η αναζήτηση είναι επιτυχής η Found είναι true,
                ο CurrPtr δείχνει στον κόμβο που περιέχει το Item και
                ο PredPtr στον προηγούμενό του ή είναι nil αν δεν υπάρχει προηγούμενος.
                Αν η αναζήτηση δεν είναι επιτυχής η Found είναι false.
*/
{
   ListPointer CurrPtr;
   boolean DoneSearching;

   CurrPtr = List;
   *PredPtr = NULL;
   DoneSearching = FALSE;
   *Found = FALSE;
   while (!DoneSearching && CurrPtr!=NULL )
    {
         if (CurrPtr->Data>=Item )
         {
         	DoneSearching = TRUE;
         	*Found = (CurrPtr->Data==Item);
         }
         else
         {
         	*PredPtr = CurrPtr;
            CurrPtr = CurrPtr->Next;
         }
	}
}


void list_insertion(ListPointer *List,int choice1)
{
 	ListElementType Item;
    char ch;
    ListPointer PredPtr;
    boolean Found;

	do
    {
   	    printf("Enter a number for insertion in the list: ");
   	    scanf("%d", &Item);
   	    if (choice1==1)
   	        OrderedLinearSearch(*List, Item, &PredPtr, &Found);
   	    else
            PredPtr= NULL;
        LinkedInsert(List, Item, PredPtr);
        printf("\nContinue Y/N: ");
        do
        {
      	     scanf("%c", &ch);
        } while (toupper(ch)!= 'N' && toupper(ch)!= 'Y');
    } while (toupper(ch)!='N');
}


void Filling(ListPointer *AList,int sumNum,ListPointer PredPtr)
{
    int i,loopNum;
    for(i = 0; i < sumNum; i++)
    {
        printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS: ");
        scanf("%d", &loopNum);
        LinkedInsert(AList, loopNum, PredPtr = NULL);
    }
}


void UniqueList(ListPointer InList, ListPointer *OutList)
{
    ListPointer curr, PredPtr, tmpcurr, tmppred;

    PredPtr = NULL;
    curr = InList;
    LinkedInsert(OutList, curr->Data, PredPtr);

    //First i am gonna insert the 1st element manually,
    //and then everytime i compare the curr->data with the 1st element of my other
    //list and if it is the same i continue to the next element of curr
    //otherwise i insert it to the end of my list

    if(!EmptyList(InList))
    {
        PredPtr = curr;
        curr = curr->Next;
        while(curr != NULL)
        {
            if(curr->Data != PredPtr->Data)
            {
                tmppred = NULL;
                tmpcurr = *OutList;

                while(tmpcurr != NULL)
                {
                    tmppred = tmpcurr;
                    tmpcurr = tmpcurr->Next;
                }

                LinkedInsert(OutList, curr->Data, tmppred);
            }
            PredPtr = curr;
            curr = curr->Next;
        }
    }
    else
        printf("Empty List...\n");
}
