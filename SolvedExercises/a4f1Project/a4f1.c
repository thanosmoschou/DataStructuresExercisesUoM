#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define megisto_plithos 60       //������� ������ ��������� �������

typedef enum {
    FALSE, TRUE
} boolean;

typedef boolean typos_synolou[megisto_plithos];
typedef int stoixeio_synolou;

//Function prototypes
void Dimiourgia(typos_synolou synolo);
void EnosiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou enosi);
void TomiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou tomi);
void DiaforaSynolou(typos_synolou s1, typos_synolou s2, typos_synolou diafora);
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean isOdd(stoixeio_synolou num);
boolean isPrime(stoixeio_synolou num);
void displayset(typos_synolou set);
void createSets(typos_synolou Odds, typos_synolou Prime, typos_synolou Enos,typos_synolou TomiS,typos_synolou Diafor,typos_synolou Simplirom);

//Main function
int main()
{
	typos_synolou Odds, Prime, Enos, TomiS, Diafor, Simplirom;

	createSets(Odds, Prime, Enos, TomiS, Diafor, Simplirom);

	printf("Odds:\n");
	displayset(Odds);

	printf("Prime:\n");
	displayset(Prime);

	printf("Tomi:\n");
	displayset(TomiS);

	printf("Enosi:\n");
	displayset(Enos);

	printf("Diafora:\n");
	displayset(Diafor);

	printf("Sympliroma:\n");
	displayset(Simplirom);

	system("pause");
	return 0;
}

//Function definition
void Dimiourgia(typos_synolou synolo)
/* ����������: ���������� ��� ������ ����� ��������, ������ �� ���� ������.
   ����������: �� ���� ������
*/
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        synolo[i] = FALSE;
}

boolean isOdd(stoixeio_synolou num)
{
	return (num % 2);
}

boolean isPrime(stoixeio_synolou num)
{
	stoixeio_synolou ctr=2; //Numbers to check if my num is divided with them.Start from 2 because 1 is already divide my num

	while(ctr<=num)
	{
		if(num % ctr == 0) //If my mod equals to 0 i must stop because i found a number that divides my num
			break;
		else
			ctr++; //If the mod of division is different than 0 i must check the next number if it divides my num
	}

	if(ctr>=2 && ctr<num) //If the loop stopped i check if there is a number within my limits that divides my num. If that happens my num is not a primary
		return FALSE;
	else
		return TRUE;
}

void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo)
/* �������:    ��� ������ ��� ��� ��������.
   ����������: ������� �� �������� ��� ������.
   ����������: �� ������������� ������
*/
{
    synolo[stoixeio] = TRUE;
}

boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo)
/* �������:    ��� ������ ��� ��� ��������.
   ����������: ������� �� �� �������� ����� ����� ��� �������.
   ����������: ���������� TRUE �� �� �������� ����� ����� ��� ��� FALSE �����������
*/
{
    return synolo[stoixeio];
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

void createSets(typos_synolou Odds, typos_synolou Prime, typos_synolou Enos,typos_synolou TomiS,typos_synolou Diafor,typos_synolou Simplirom)
{
	stoixeio_synolou i;

	Dimiourgia(Odds);
	Dimiourgia(Prime);
	Dimiourgia(TomiS);
	Dimiourgia(Enos);
	Dimiourgia(Diafor);
	Dimiourgia(Simplirom);

	for(i=1; i< megisto_plithos; i++)
	{
		Odds[i]=isOdd(i);
		Prime[i]= isPrime(i);
	}

	TomiSynolou(Odds, Prime, TomiS);
	EnosiSynolou(Odds, Prime, Enos);
	DiaforaSynolou(Odds, Prime, Diafor);

	for(i=1; i< megisto_plithos; i++)
		Simplirom[i]= !Prime[i];
}
