#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define HMax 31             /*     το μέγεθος του πίνακα HashTable
                                ενδεικτικά ίσο με 5 */
#define VMax 30             /*το μέγεθος της λίστας,
                                ενδεικτικά ίσο με 30 */
#define EndOfList -1        /* σημαία που σηματοδοτεί το τέλος της λίστας
                                και της κάθε υπολίστας συνωνύμων */

#define CHARLIM 6
#define LIMFORLOOPINSERTVARIABLES 4


typedef struct
{
    int varValue;
    char varName[CHARLIM];
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
	return key%HMax;
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

    /* printf("HASHLIST STRUCTURE with SYNONYM CHAINING\n");
     printf("========================================\n");

          printf("PINAKAS DEIKTWN STIS YPO-LISTES SYNWNYMWN EGGRAFWN:\n");
            for (i=0; i<HMax;i++)
              printf("%d| %d\n",i,HList.HashTable[i]);

          printf("OI YPO-LISTES TWN SYNWNYMWN EGGRAFWN:\n");*/

          for (i=0; i<HMax;i++)
          {
                SubIndex = HList.HashTable[i];
                if(SubIndex != EndOfList)
                {
                    while ( SubIndex != EndOfList )
                    {
                        printf("[%d, %s %d, %d]",HList.List[SubIndex].key,HList.List[SubIndex].Data.varName, HList.List[SubIndex].Data.varValue, HList.List[SubIndex].Link);
                        printf(" -> ");
                        SubIndex = HList.List[SubIndex].Link;
                    } //* while *)
                    printf("TELOS % dHS YPO-LISTAS\n", i);
                }
          }

          /*printf("H STOIBA TWN ELEY8ERWN 8ESEWN THS LISTAS:\n");
          SubIndex = HList.StackPtr;
          while ( SubIndex != EndOfList )
          {
                printf("%d <= ",SubIndex);
                SubIndex = HList.List[SubIndex].Link;
          }
          printf("TELOS\n");

          printf("MEGE8OS THS LISTAS = %d\n", HList.Size);
          printf("========================================\n"); */
}


void menu(int *choice)
{
    printf("                  MENOY                  \n");
    printf("-------------------------------------------------\n");
    printf("1. DHLWSH METAVLHTHS KAI ANATHESI TIMHS SE AUTHN\n");
    printf("2. POLLAPLASIASMOS 2 METAVLHTWN\n");
    printf("3. PROSTHESI 2 METAVLHTWN\n");
    //printf("4. EMFANISH OLWN TWN XRHSTWN\n");
    //printf("5. EMFANISH PINAKWN (BOH8HTIKH\n");
    printf("4. EXIT\n");
    printf("\nCHOICE: ");
    do
    {
    	scanf("%d", choice);
    } while (*choice<1 && *choice>4);
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


int FoldKey(char name[CHARLIM])
{
    int hashValue = 0;

    /*Η υλοποίηση να γίνει χρησιμοποιώντας λίστα κατακερματισμού με συνώνυμα και η συνάρτηση κατακερματισμού να είναι
    η εξής:
    H(x)=x%p, p=31
    Όπου x είναι το άθροισμα των γραμμάτων του ονόματος της μεταβλητής, κωδικοποιημένα ως
    Α→1,Β→2…Ζ→26
    Και πολλαπλασιασμένα με τη θέση τους στο αλφαριθμητικό. Π.Χ. το αλφαριθμητικό NICK έχει ως άθροισμα το
    1∙14+2∙9+3∙3+4∙11.
    Ara ego afou to A=1 klp na ksero thn seira tou kathe grammatos. To A apo ta alla kefalaia grammata me
    vasi ton kwdika ASCII exoun mia diafora. An apo to gramma pou thelo afaireso ton kwdiko ASCII tou A
    pairno thn apostasi tous ara kai thn seira tou grammatos pou thelo sto alfavito , sthn opoia an prostheso 1
    pairnw thn timh pou thelo me vasi tin arithmisi mou. Meta me
    vasi thn thesi ston pinaka pollaplasiazo analoga afou exo prosthesei 1 sthn thesi giati ksekiname apo 0*/

    for(int i = 0; name[i] != '\0'; i++)
        hashValue += ((1 + (name[i] - 'A')) * (i + 1));

    return hashValue;
}


void procedures(HashListType *HList)
{
    int i;
    ListElm AnItem1, AnItem2;
    int Loc1, Pred1, Loc2, Pred2, mulRes, addRes;
    //char var1, var2;
    boolean flag1 = TRUE, flag2 = TRUE;

    CreateHashList(HList);

    printf("Declare variables\n");
    for(i = 1; i <= LIMFORLOOPINSERTVARIABLES; i++) //Skopima ksekinaw apo 1 kai oxi apo 0 gia na dieukolunomai stin euresi ths thesis sto alfarithmitiko
    {
        printf("Enter the variable name: ");
        /*scanf("%5[^\n]", AnItem1.Data.varName);
        while(getchar() != '\n');*/
        scanf("%s", AnItem1.Data.varName);

        /*for(int i = 0; AnItem1.Data.varName[i] != '\0'; i++)
            AnItem1.Data.varName[i] = toupper(AnItem1.Data.varName[i]);*/

        printf("Enter variable value: ");
        scanf("%d", &AnItem1.Data.varValue);
        //getchar(); //gia na fygei to \n apo thn eisagwgi arithmou

        AnItem1.key = FoldKey(AnItem1.Data.varName);
        AddRec(HList, AnItem1);
    }
    Print_HashList(*HList);

    for(i = 0; i < 2; i++)
    {
        flag1 = flag2 = TRUE;
        if(i == 0)
            printf("Multiply Variables\n");
        else
            printf("Add Variables\n");

        printf("Enter the first variable: ");
        scanf("%s", AnItem1.Data.varName);
        //scanf("%5[^\n]", AnItem1.Data.varName);
        /*for(int i = 0; AnItem1.Data.varName[i] != '\0'; i++)
            AnItem1.Data.varName[i] = toupper(AnItem1.Data.varName[i]);*/
        //while(getchar() != '\n');
        AnItem1.key = FoldKey(AnItem1.Data.varName);

        printf("Enter the second variable: ");
        scanf("%s", AnItem2.Data.varName);
        //scanf("%5[^\n]", AnItem2.Data.varName);
        /*for(int i = 0; AnItem2.Data.varName[i] != '\0'; i++)
            AnItem2.Data.varName[i] = toupper(AnItem2.Data.varName[i]);*/
        //while(getchar() != '\n');
        AnItem2.key = FoldKey(AnItem2.Data.varName);

        SearchHashList(*HList, AnItem1.key, &Loc1, &Pred1);
        SearchHashList(*HList, AnItem2.key, &Loc2, &Pred2);

        if(Loc1 == EndOfList)
            printf("Undeclared variable %s\n", AnItem1.Data.varName);
        else if(Loc2 == EndOfList)
            printf("Undeclared variable %s\n", AnItem2.Data.varName);
        else
        {
            if(strncmp(HList->List[Loc1].Data.varName, AnItem1.Data.varName, strlen(HList->List[Loc2].Data.varName)) != 0)
            {
                printf("Undeclared variable %s\n", AnItem1.Data.varName);
                flag1 = FALSE;
            }

            if(strncmp(HList->List[Loc2].Data.varName, AnItem2.Data.varName, strlen(HList->List[Loc2].Data.varName)) != 0)
            {
                printf("Undeclared variable %s\n", AnItem2.Data.varName);
                flag2 = FALSE;
            }

            if(flag1 && flag2)
            {
                if(i == 0)
                {
                    mulRes = HList->List[Loc1].Data.varValue * HList->List[Loc2].Data.varValue;
                    printf("%s*%s=%d\n", AnItem1.Data.varName, AnItem2.Data.varName, mulRes);
                }
                else
                {
                    addRes = HList->List[Loc1].Data.varValue + HList->List[Loc2].Data.varValue;
                    printf("%s+%s=%d\n", AnItem1.Data.varName, AnItem2.Data.varName, addRes);
                }
            }
        }
    }
}

