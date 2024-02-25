#include <stdio.h>
#include <ctype.h>

#define HMax 10             /*     το μέγεθος του πίνακα HashTable
                                ενδεικτικά ίσο με 5 */
#define VMax 30             /*το μέγεθος της λίστας,
                                ενδεικτικά ίσο με 30 */
#define EndOfList -1        /* σημαία που σηματοδοτεί το τέλος της λίστας
                                και της κάθε υπολίστας συνωνύμων */

#define CHARLIM 21

typedef struct
{
    int userCode;
    char username[CHARLIM];
    int role;
} ListElementType;  /*τύπος δεδομένων για τα στοιχεία της λίστας
                               * ενδεικτικά τύπου int */
typedef int KeyType;

typedef struct {
	KeyType key;
	ListElementType Data;
	int Link;
} ListElm;

typedef struct  {
	int HashTable[HMax];   // πίνακας δεικτών προς τις υπολίστες συνωνύμων
    int Size;                // πλήθος εγγραφών της λίστας List
	int SubListPtr;          // Dδείκτης σε μια υπολίστα συνωνύμων
    int StackPtr;           // δείκτης προς την πρώτη ελεύθερη θέση της λίστας List
	ListElm List[VMax];
} HashListType;

typedef enum {
    FALSE, TRUE
} boolean;


//Function prototypes
void CreateHashList(HashListType *HList);
int HashKey(KeyType key);
boolean FullHashList(HashListType HList);
void SearchSynonymList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred);
void SearchHashList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred);
void AddRec(HashListType *HList,ListElm InRec);
void DeleteRec(HashListType *HList,KeyType DelKey);
void Print_HashList(HashListType HList);
void menu(int *choice);
void PrintPinakes(HashListType HList);
void procedures(HashListType *HList);


//Main function
int main(){
   HashListType HList;

   procedures(&HList);

   return 0;
}


//Function definition
int HashKey(KeyType key)
/* Δέχεται:    Την τιμή key ενός κλειδιού.
   Λειτουργία: Βρίσκει την τιμή κατακερματισμού HValue για το κλειδί Key.
   Επιστρέφει: Την τιμή κατακερματισμού HValue
*/
{
	/*σε περίπτωση που το KeyType δεν είναι ακέραιος
	θα πρέπει να μετατρέπεται κατάλληλα το κλειδί σε αριθμό*/
	return (key%HMax) + 1;
}


void CreateHashList(HashListType *HList)
/* Λειτουργία: Δημιουργεί μια δομή HList.
   Επιστρέφει: Την δομή HList
*/
{
	int index;

	HList->Size=0;           //ΔΗΜΙΟΥΡΓΕΙ ΜΙΑ ΚΕΝΗ ΛΙΣΤΑ
	HList->StackPtr=0;       //ΔΕΙΚΤΗς ΣΤΗ ΚΟΡΥΦΗ ΤΗΣ ΣΤΟΙΒΑΣ ΤΩΝ ΕΛΕΥΘΕΡΩΝ ΘΕΣΕΩΝ

    /*ΑΡΧΙΚΟΠΟΙΕΙ ΤΟΝ ΠΙΝΑΚΑ HashTable ΤΗΣ ΔΟΜΗΣ HList ΩΣΤΕ ΚΑΘΕ ΣΤΟΙΧΕΙΟΥ ΤΟΥ
        ΝΑ ΕΧΕΙ ΤΗ ΤΙΜΗ EndOfList (-1)*/
    index=0;
	while (index<HMax)
	{
		HList->HashTable[index]=EndOfList;
		index=index+1;
    }

     //Δημιουργία της στοίβας των ελεύθερων θέσεων στη λίστα HList
    index=0;
	while(index < VMax-1)
	{
		HList->List[index].Link=index+1;
		index=index+1;
	}
	HList->List[index].Link=EndOfList;
}


boolean FullHashList(HashListType HList)
/* Δέχεται:    Μια δομή HList.
   Λειτουργία: Ελέγχει αν η λίστα List της δομής HList είναι γεμάτη.
   Επιστρέφει: TRUE αν η λίστα List είναι γεμάτη, FALSE διαφορετικά.
*/
{
	return(HList.Size==VMax);
}


void SearchSynonymList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred)
/* Δέχεται:     Μια δομή HList και μια τιμή κλειδιού KeyArg.
    Λειτουργία: Αναζητά μια εγγραφή με κλειδί KeyArg στην υπολίστα συνωνύμων.
    Επιστρέφει: Τη θέση Loc της εγγραφής και τη θέση Pred της προηγούμενης
                εγγραφής στην υπολίστα
*/
{
	int Next;
	Next=HList.SubListPtr;
	*Loc=-1;
	*Pred=-1;
	while(Next!=EndOfList)
	{
		if (HList.List[Next].key==KeyArg)
		{
			*Loc=Next;
			Next=EndOfList;
		}
		else
		{
			*Pred=Next;
			Next=HList.List[Next].Link;
		}
	}
}


void SearchHashList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred)
/* Δέχεται:     Μια δομή HList και μια τιμή κλειδιού KeyArg.
    Λειτουργία: Αναζητά μια εγγραφή με κλειδί KeyArg στη δομή HList.
    Επιστρέφει: Τη θέση Loc της εγγραφής και τη θέση Pred της
                προηγούμενης εγγραφής της υπολίστας στην οποία ανήκει.
                Αν δεν υπάρχει εγγραφή με κλειδί KeyArg τότε Loc=Pred=-1
*/
{
	int HVal;
	HVal=HashKey(KeyArg);
    if (HList.HashTable[HVal]==EndOfList)
	{
		*Pred=-1;
		*Loc=-1;
	}
	else
	{
		HList.SubListPtr=HList.HashTable[HVal];
		SearchSynonymList(HList,KeyArg,Loc,Pred);
	}
}


void AddRec(HashListType *HList,ListElm InRec)
/* Δέχεται:    Μια δομή HList και μια εγγραφή InRec.
   Λειτουργία: Εισάγει την εγγραφή InRec στη λίστα List, αν δεν είναι γεμάτη,
                και ενημερώνει τη δομή HList.
   Επιστρέφει: Την τροποποιημένη δομή HList.
   Έξοδος:     Μήνυμα γεμάτης λίστας, αν η List είναι γεμάτη, διαφορετικά,
                αν υπάρχει ήδη εγγραφή με το ίδιο κλειδί,
                εμφάνιση αντίστοιχου μηνύματος
*/
{
	int Loc, Pred, New, HVal;

   // New=0;
	if(!(FullHashList(*HList)))
	{
		Loc=-1;
		Pred=-1;
		SearchHashList(*HList,InRec.key,&Loc,&Pred);
		if(Loc==-1)
		{
			HList->Size=HList->Size +1;
			New=HList->StackPtr;
			HList->StackPtr=HList->List[New].Link;
			HList->List[New]=InRec;
			if (Pred==-1)
			{
			    HVal=HashKey(InRec.key);
                HList->HashTable[HVal]=New;
				HList->List[New].Link=EndOfList;
			}
			else
			{
                HList->List[New].Link=HList->List[Pred].Link;
				HList->List[Pred].Link=New;
			}
		}

		else
		{
			printf("YPARXEI HDH EGGRAFH ME TO IDIO KLEIDI \n");
		}
	}
	else
	{
		printf("Full list...");
	}
}


void DeleteRec(HashListType *HList,KeyType DelKey)
/* DEXETAI:    TH DOMH (HList) KAI To KLEIDI (DelKey) THS EGGRAFHS
               POY PROKEITAI NA DIAGRAFEI
   LEITOYRGIA: DIAGRAFEI, THN EGGRAFH ME KLEIDI (DelKey) APO TH
               LISTA (List), AN YPARXEI ENHMERWNEI THN DOMH HList
   EPISTREFEI: THN TROPOPOIHMENH DOMH (HList)
   EJODOS:     "DEN YPARXEI EGGRAFH ME KLEIDI" MHNYMA
*/
{
	int Loc, Pred, HVal;

	SearchHashList(*HList,DelKey,&Loc,&Pred);
	if(Loc!=-1)
	{
		if(Pred!=-1)
		{
			HList->List[Pred].Link=HList->List[Loc].Link;
		}
		else
		{
			HVal=HashKey(DelKey);
		    HList->HashTable[HVal]=HList->List[Loc].Link;
		}
		HList->List[Loc].Link=HList->StackPtr;
		HList->StackPtr=Loc;
		HList->Size=HList->Size -1;
	}
	else
	{
		printf("DEN YPARXEI  EGGRAFH ME KLEIDI %d \n",DelKey);
	}
}


void Print_HashList(HashListType HList)
{
   int i, SubIndex;

     printf("HASHLIST STRUCTURE with SYNONYM CHAINING\n");
     printf("========================================\n");

          printf("PINAKAS DEIKTWN STIS YPO-LISTES SYNWNYMWN EGGRAFWN:\n");
            for (i=0; i<HMax;i++)
              printf("%d| %d\n",i,HList.HashTable[i]);

          printf("OI YPO-LISTES TWN SYNWNYMWN EGGRAFWN:\n");
          for (i=0; i<HMax;i++)
          {
              SubIndex = HList.HashTable[i];
              while ( SubIndex != EndOfList )
              {
                   printf("[%d, %d, %d]",HList.List[SubIndex].key,HList.List[SubIndex].Data,HList.List[SubIndex].Link);
                   printf(" -> ");
                   SubIndex = HList.List[SubIndex].Link;
               } //* while *)
              printf("TELOS % dHS YPO-LISTAS\n", i);
          }

          printf("H STOIBA TWN ELEY8ERWN 8ESEWN THS LISTAS:\n");
          SubIndex = HList.StackPtr;
          while ( SubIndex != EndOfList )
          {
                printf("%d <= ",SubIndex);
                SubIndex = HList.List[SubIndex].Link;
          }
          printf("TELOS\n");

          printf("MEGE8OS THS LISTAS = %d\n", HList.Size);
          printf("========================================\n");
}


void menu(int *choice)
{
    printf("                  MENOY                  \n");
    printf("-------------------------------------------------\n");
    printf("1. EISAGWGH EGGRAFHS\n");
    printf("2. DIAGRAFH EGGRAFHS\n");
    printf("3. ANAZHTHSH EGGRAFHS\n");
    printf("4. EMFANISH OLWN TWN XRHSTWN\n");
    //printf("5. EMFANISH PINAKWN (BOH8HTIKH\n");
    printf("5. EXIT\n");
    printf("\nCHOICE: ");
    do
    {
    	scanf("%d", choice);
    } while (*choice<1 && *choice>5);
}


void PrintPinakes(HashListType HList)
{
    int i;
	printf("Hash table\n");
	for (i=0; i<HMax;i++)
              printf("%d)%3d\n",i,HList.HashTable[i]);

	printf("Hash List\n");
    for (i=0;i<HList.Size;i++)
	   printf("%d) %d, %d\n",i,HList.List[i].key,HList.List[i].Link);
	printf("\n");
}


void procedures(HashListType *HList)
{
    int choice, i, j;
    char termch, decision;
    ListElm AnItem;
    KeyType AKey;
    int Loc, Pred;

    CreateHashList(HList);

    while(TRUE)
    {
        menu(&choice);
        while(getchar() != '\n');

        switch(choice)
        {
            case 1:
                printf("EISAGWGH:\n");
                while(TRUE)
                {
                    printf("DWSE TO ONOMATEPONYMO: ");
                    scanf("%20[^\n]%c", AnItem.Data.username, &termch);
                    if(termch != '\n') //fflush gia to stdin
                        while(getchar() != '\n');

                    printf("DWSE TON KWDIKO TOU %s: ", AnItem.Data.username);
                    scanf("%d", &AnItem.Data.userCode);

                    printf("DWSE THN IDIOTHTA TOU %s (1 = student, 2 = postgraduate student, 3 = teacher,\
4 = visitor): ", AnItem.Data.username);

                    do
                    {
                        scanf("%d", &AnItem.Data.role);
                        if(AnItem.Data.role < 1 || AnItem.Data.role > 4)
                            printf("Please enter valid data.\nDWSE THN IDIOTHTA TOU %s (1 = student, 2 = postgraduate student, 3 = teacher,\
4 = visitor)", AnItem.Data.username);
                    }while(AnItem.Data.role < 1 || AnItem.Data.role > 4);

                    AnItem.key = AnItem.Data.userCode;
                    AddRec(HList, AnItem);

                    printf("SYNEXEIA ME THN EISAGWGH XRHSTWN (Y/N)? ");
                    do
                    {
                        scanf(" %c", &decision);
                        while(getchar() != '\n');

                        if(toupper(decision) != 'Y' && toupper(decision) != 'N')
                            printf("Please enter valid data.\nSYNEXEIA ME THN EISAGWGH XRHSTWN (Y/N)? ");
                    }while(toupper(decision) != 'Y' && toupper(decision) != 'N');

                    if(toupper(decision) == 'N')
                        break; //gia thn while
                }
                break; //gia to case ths switch
            case 2:
                printf("DIAGRAFH:\n");
                while(TRUE)
                {
                    printf("\nEMFANISH OLWN TWN XRHSTWN:\n\n");

                    for(i = 0; i < HMax; i++)
                    {
                        if(HList->HashTable[i] != EndOfList)
                        {
                            printf("SYNWNYMA, SYGKROUSI STHN THESI: %d\n", i);
                            j = HList->HashTable[i];
                            while(j != EndOfList)
                            {
                                printf("%d:[%d, %s, %s]\n", j, HList->List[j].Data.userCode, HList->List[j].Data.username,
                                HList->List[j].Data.role == 1 ? "student" :
                                HList->List[j].Data.role == 2 ? "postgraduate student" :
                                HList->List[j].Data.role == 3 ? "teacher" :
                                "visitor");
                                j = HList->List[j].Link;
                            }
                        }
                    }

                    printf("DWSE TON KWDIKO TOU XRHSTH POU THES NA DIAGRAPSEIS: ");
                    scanf("%d", &AKey);
                    DeleteRec(HList, AKey);

                    printf("\nEMFANISH OLWN TWN XRHSTWN:\n\n");

                    for(i = 0; i < HMax; i++)
                    {
                        if(HList->HashTable[i] != EndOfList)
                        {
                            printf("SYNWNYMA, SYGKROUSI STHN THESI: %d\n", i);
                            j = HList->HashTable[i];
                            while(j != EndOfList)
                            {
                                printf("%d:[%d, %s, %s]\n", j, HList->List[j].Data.userCode, HList->List[j].Data.username,
                                HList->List[j].Data.role == 1 ? "student" :
                                HList->List[j].Data.role == 2 ? "postgraduate student" :
                                HList->List[j].Data.role == 3 ? "teacher" :
                                "visitor");
                                j = HList->List[j].Link;
                            }
                        }
                    }

                    printf("SYNEXEIA ME THN DIAGRAFH XRHSTWN (Y/N)? ");
                    do
                    {
                        scanf(" %c", &decision);
                        while(getchar() != '\n');

                        if(toupper(decision) != 'Y' && toupper(decision) != 'N')
                            printf("Please enter valid data.\nSYNEXEIA ME THN DIAGRAFH XRHSTWN (Y/N)? ");
                    }while(toupper(decision) != 'Y' && toupper(decision) != 'N');

                    if(toupper(decision) == 'N')
                        break; //gia thn while
                }
                break; //gia to case ths switch
            case 3:
                printf("ANAZHTHSH XRHSTH:\n");
                while(TRUE)
                {
                    printf("DWSE TON KWDIKO TOU XRHSTH POU THES NA ANAZHTHSEIS: ");
                    scanf("%d", &AKey);

                    SearchHashList(*HList, AKey, &Loc, &Pred);

                    if(Loc != EndOfList) //H endiamesa vrethike h stin arxi
                        printf("ONOMATEPWNYMO: %s, KWDIKOS: %d, IDIOTHTA: %s\n", HList->List[Loc].Data.username, HList->List[Loc].Data.userCode,
                            HList->List[j].Data.role == 1 ? "student" :
                            HList->List[j].Data.role == 2 ? "postgraduate student" :
                            HList->List[j].Data.role == 3 ? "teacher" :
                            "visitor");
                    else
                        printf("DEN YPARXEI XRHSTHS ME KWDIKO: %d\n", AKey);

                    printf("SYNEXEIA ME THN ANAZHTHSH XRHSTWN (Y/N)? ");
                    do
                    {
                        scanf(" %c", &decision);
                        while(getchar() != '\n');

                        if(toupper(decision) != 'Y' && toupper(decision) != 'N')
                            printf("Please enter valid data.\nSYNEXEIA ME THN ANAZHTHSH XRHSTWN (Y/N)? ");
                    }while(toupper(decision) != 'Y' && toupper(decision) != 'N');

                    if(toupper(decision) == 'N')
                        break; //gia thn while
                }
                break; //gia thn switch
            case 4:
                printf("EMFANISH OLWN TWN XRHSTWN:\n\n");

                for(i = 0; i < HMax; i++)
                {
                    if(HList->HashTable[i] != EndOfList)
                    {
                        printf("SYNWNYMA, SYGKROUSI STHN THESI: %d\n", i);
                        j = HList->HashTable[i];
                        while(j != EndOfList)
                        {
                            printf("%d:[%d, %s, %s]\n", j, HList->List[j].Data.userCode, HList->List[j].Data.username,
                            HList->List[j].Data.role == 1 ? "student" :
                            HList->List[j].Data.role == 2 ? "postgraduate student" :
                            HList->List[j].Data.role == 3 ? "teacher" :
                            "visitor");
                            j = HList->List[j].Link;
                        }
                    }
                }
                break;
            default:
                break;
        }

        if(choice == 5)
            break;
    }
}

