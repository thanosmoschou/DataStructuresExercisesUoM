#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define megisto_plithos 256       //������� ������ ��������� ������� //10
#define DIMSUM 256
#define DIGSIZ 10
/*#define CHARSET 2*/
/*#define NUMSET 10*/
#define LETTSET 26

typedef enum {
    FALSE, TRUE
} boolean;

typedef boolean typos_synolou[megisto_plithos];
typedef int stoixeio_synolou;

//Function prototypes
void Dimiourgia(typos_synolou synolo);
void Katholiko(typos_synolou synolo);
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo);
void Diagrafi(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean KenoSynolo(typos_synolou synolo);
boolean IsaSynola(typos_synolou s1, typos_synolou s2);
boolean Yposynolo(typos_synolou s1, typos_synolou s2);
void EnosiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou enosi);
void TomiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou tomi);
void DiaforaSynolou(typos_synolou s1, typos_synolou s2, typos_synolou diafora);
void menu(int *choice);
void displayset(typos_synolou set);
void createSets(typos_synolou CharacterSet, typos_synolou DigitSet,typos_synolou LetterSet, int row);
boolean isValidInteger(int row, char str[], typos_synolou DigitSet,typos_synolou CharacterSet);
boolean isValidIdentifier(int row, char str[], typos_synolou DigitSet,typos_synolou CharacterSet, typos_synolou LetterSet );

//Main function
int main()
{
    stoixeio_synolou i;
	char str[DIMSUM]={'\0'},decision;
	typos_synolou DigitSet;
	typos_synolou LetterSet;
	typos_synolou CharacterSet;

	createSets(CharacterSet,DigitSet,LetterSet, DIMSUM);

	while(1) //Checking integers
	{

		printf("Please enter an integer: ");

		for(i=0; i<DIMSUM; i++) //Initialize every time my table with terminating characters in order to avoid bugs and wrong input from previous insert
			str[i]='\0';

		fgets(str, DIMSUM, stdin); //Reading my number with string format
		str[strlen(str)-1]='\0';

		if(isValidInteger(DIMSUM,  str, DigitSet, CharacterSet))
			printf("Correct integer\n");
		else
			printf("Wrong integer\n");

		do
		{
			printf("Continue with more integers?(Y or N):");
			scanf(" %c", &decision);
			getchar();
		//	printf("\n");
		}while(decision!='Y' && decision!='y' && decision!='N' && decision!='n');


		if(decision=='N' || decision=='n')
			break;

		//printf("\n\n");
	}

	//printf("\n");

	while(1)//Check identifiers
	{
		printf("Please enter an identifier: ");

		for(i=0; i<DIMSUM; i++) //Initialize every time my table with terminating characters in order to avoid bugs and wrong input from previous insert
			str[i]='\0';

		fgets(str, DIMSUM, stdin); //Read my identifier
		str[strlen(str)-1]='\0';

		if(isValidIdentifier(DIMSUM, str,DigitSet, CharacterSet,LetterSet ))
			printf("Correct identifier\n");
		else
			printf("Wrong identifier\n");

		do
		{
			printf("Continue with more identifiers?(Y or N):");
			scanf(" %c", &decision);
			getchar(); //if you give wrong info the \n won't be absorved and scanf will take it as an input for the next time
		//	printf("\n");
		}while(decision!='Y' && decision!='y' && decision!='N' && decision!='n');

		if(decision=='N' || decision=='n')
			break;

		//printf("\n\n");

	}

	return 0;
	system("PAUSE");
}

void menu(int *choice)
{
  printf("\nXRHSIMOPOIHSE TIS PARAKATW ENTOLES GIA NA ELEGJEIS TO unit SetADT\n");
  printf("1 ---- DHMIOYRGIA SYNOLOU\n");
  printf("2 ---- KA8OLIKO\n");
  printf("3 ---- EISAGWGH\n");
  printf("4 ---  DIAGRAFH\n");
  printf("5 ---  MELOS\n");
  printf("6 ---- KENO SYNOLO\n");
  printf("7 ---- ISA SYNOLA\n");
  printf("8 ---- YPOSYNOLO\n");
  printf("9 ---- ENOSH 2 SYNOLWN\n");
  printf("10 ---- TOMH 2 SYNOLWN\n");
  printf("11 ---- DIAFORA SYNOLOU\n");
  printf("12 ---- EXIT\n");
  printf("\nChoice 1-12: ");
  do
    {
    	scanf("%d", choice);
    } while (*choice<1 && *choice>12);
}


void displayset(typos_synolou set)
{
	stoixeio_synolou i;

	for (i=0;i < megisto_plithos;i++)
	{
		if(Melos(i,set))
			printf(" %d",i);
	}
	printf("\n");
}

void Dimiourgia(typos_synolou synolo)
/* ����������: ���������� ��� ������ ����� ��������, ������ �� ���� ������.
   ����������: �� ���� ������
*/
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        synolo[i] = FALSE;
}

void Katholiko(typos_synolou synolo)
/* �������:     ��� ������.
   ����������: ���������� ��� ������ �� ��� �� �������� �������,
                ���� ���� �������� ��� ����� �������� ��� ������������.
   ����������: �� �������� ������ ��� �������������
*/
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        synolo[i] = TRUE;
}

void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo)
/* �������:    ��� ������ ��� ��� ��������.
   ����������: ������� �� �������� ��� ������.
   ����������: �� ������������� ������
*/
{
    synolo[stoixeio] = TRUE;
}

void Diagrafi(stoixeio_synolou stoixeio, typos_synolou synolo)
/* �������:     ��� ������ ��� ��� ��������.
   ����������:  ��������� �� �������� ��� �� ������.
   ����������:  �� ������������� ������
*/
{
    synolo[stoixeio] = FALSE;
}

boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo)
/* �������:    ��� ������ ��� ��� ��������.
   ����������: ������� �� �� �������� ����� ����� ��� �������.
   ����������: ���������� TRUE �� �� �������� ����� ����� ��� ��� FALSE �����������
*/
{
    return synolo[stoixeio];
}

boolean KenoSynolo(typos_synolou synolo)
/*
�������: ��� ������.
 ����������: ������� �� �� ������ ����� ����.
 ����������: ���������� TRUE �� �� ������ ����� ���� ��� FALSE �����������
*/
{
    stoixeio_synolou i;
    boolean keno;

    keno=TRUE;
    i = 0;

    while (i < megisto_plithos  && keno) {
        if (Melos(i, synolo))
            keno = FALSE;
        else
            i++;
    }
    return keno;
}

boolean IsaSynola(typos_synolou s1, typos_synolou s2)
/* �������:     ��� ������ s1 ��� s2.
   ����������: ������� �� �� ��� ������ ����� ���.
   ����������: ���������� TRUE �� �� ��� ������ ����� �� ���� �������� ��� FALSE �����������
*/
{
    stoixeio_synolou i;
    boolean isa;

    isa = TRUE;
    i=0;
    while (i < megisto_plithos && isa)
        if (Melos(i,s1) != Melos(i,s2))
            isa = FALSE;
        else
            i++;
    return isa;
}

boolean Yposynolo(typos_synolou s1, typos_synolou s2)
/* �������:     ��� ������ s1 ��� s2.
   ����������: ������� �� �� ������ s1 ����� ��������� ��� s2.
   ����������: ���������� true �� �� ������ s1 ����� ��� ��������� ��� s2,
                ������ �� ���� �������� ��� s1 ����� ��� �������� ��� s2
*/
{
    stoixeio_synolou i;
    boolean yposyn;

    yposyn = TRUE;
    i=0;
    while (i < megisto_plithos && yposyn)
        if (Melos(i, s1) && !Melos(i, s2))
            yposyn = FALSE;
        else
            i++;
    return yposyn;
}

void EnosiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou enosi)
/* �������:     ��� ������ s1 ��� s2.
   ����������: ���������� ��� ��� ������ �� �� �������� ��� ������� � ��� s1 �
                ��� s2 � ��� ��� ��� ������.
   ����������: ���������� �� ������ enosi ��� ��������� ��� ��� ����� ��� ������� s1 ��� s2
*/
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        enosi[i] = Melos(i, s1) || Melos(i, s2);
}

void TomiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou tomi)
/* �������:     ��� ������ s1 ��� s2.
   ����������: ���������� ��� ��� ������ �� �� �������� ��� ������� ��� ��� ��� ������ s1 ��� s2.
   ����������: ���������� �� ������ tomi ��� ��������� ��� ��� ���� ��� ������� s1 ��� s2
*/
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        tomi[i] = Melos(i, s1) && Melos(i, s2);
}

void DiaforaSynolou(typos_synolou s1, typos_synolou s2, typos_synolou diafora)
/* �������: ��� ������ s1 ��� s2.
 ����������: ���������� ��� ��� ������ �� �� �������� ��� ������� ��� ������ s1 ��� ��� ������� ��� s2.
 ����������: ���������� �� ������ diafora ��� ��������� ��� ��� ������� ��� ������� s1-s2.
*/
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        diafora[i] = Melos(i, s1) && (!Melos(i, s2));
}


void createSets(typos_synolou CharacterSet, typos_synolou DigitSet,typos_synolou LetterSet, int row)
{
	stoixeio_synolou i;

	//Create void sets(initialization)
	Dimiourgia(CharacterSet);
	Dimiourgia(LetterSet);
	Dimiourgia(DigitSet);


	Eisagogi('+', CharacterSet);
	Eisagogi('-', CharacterSet);


	for(i=0; i<DIGSIZ; i++)
		Eisagogi('0'+i,DigitSet); //'0'+0='0', '0'+1='1' and so on

	for(i=0; i<LETTSET; i++)
		Eisagogi('A'+i, LetterSet); // 'A' +0='A', 'A'+1='B' ...this continue for the uppercase and  lowercase letters

	for(i=0; i<LETTSET; i++)
		Eisagogi('a'+i, LetterSet);
}


boolean isValidInteger(int row, char str[], typos_synolou DigitSet,typos_synolou CharacterSet )
{
	stoixeio_synolou i=0;
	boolean res=TRUE;

	while(i<strlen(str) && res)
	{
		if(i==0 &&(!Melos(str[i], CharacterSet) && !Melos(str[i], DigitSet)))
			res=FALSE;
		else if(i>0 && !Melos(str[i], DigitSet))
			res=FALSE;
		else
			i++;
	}

	if(i == 1)
		res = FALSE; //Tote exei mono - h +
		
	return res;
}


boolean isValidIdentifier(int row, char str[], typos_synolou DigitSet,typos_synolou CharacterSet, typos_synolou LetterSet )
{
	stoixeio_synolou i=0;
	boolean res=TRUE;

	while(i<strlen(str) && res)
	{
		if(i==0 && (Melos(str[i], DigitSet) || !Melos(str[i], LetterSet) || str[i]=='_'))
			res=FALSE;
		else if(i>0 &&( !Melos(str[i], DigitSet) && !Melos(str[i], LetterSet) && str[i]!='_'))
			res=FALSE;
		else
			i++;
	}

	return res;
}
