#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Queue */
#define QueueLimit 3  //το όριο μεγέθους της ουράς
#define SERVICELIM 30


typedef int QueueElementType;   /* ο τύπος δεδομένων των στοιχείων της ουράς
                                  ενδεικτικά τύπος int */

typedef struct {
	int Front, Rear, clien;
	QueueElementType Start[QueueLimit];
	QueueElementType End[QueueLimit];
	QueueElementType Arrival[QueueLimit];
	QueueElementType Stay[QueueLimit];
} QueueType;

typedef enum {FALSE, TRUE} boolean;

//Function prototypes
void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
boolean FullQ(QueueType Queue);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void AddQ(QueueType *Queue, QueueElementType Item);
void TraverseQ(QueueType Queue);
void show(QueueType Hold, QueueType Service);
QueueType TimesInQueue(QueueType *Queue);
void ReadData(QueueType *Hold);


//Main function
int main()
{
    QueueType Hold, Service;


    CreateQ(&Hold);
    CreateQ(&Service);

    ReadData(&Hold);
    show(Hold, Service);
    printf("\n");

    Service = TimesInQueue(&Hold);
    show(Hold, Service);

    return 0;
}


//Function definition
void CreateQ(QueueType *Queue)
/*  Λειτουργία:  Δημιουργεί μια κενή ουρά.
    Επιστρέφει:  Κενή ουρά
*/
{
	Queue->Front = 0;
	Queue->Rear = 0;
	Queue->clien = 0;
}


boolean EmptyQ(QueueType Queue)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Ελέγχει αν η ουρά είναι κενή.
   Επιστρέφει: True αν η ουρά είναι κενή, False διαφορετικά
*/
{
	return Queue.clien == 0;
}


boolean FullQ(QueueType Queue)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Ελέγχει αν η ουρά είναι γεμάτη.
   Επιστρέφει: True αν η ουρά είναι γεμάτη, False διαφορετικά
*/
{
	return Queue.clien == QueueLimit;
}


void ReadData(QueueType *Hold)
{
    QueueElementType arr,stay;

    for(QueueElementType i = 0; i < QueueLimit; i++)
    {
        //Epeidi h domi mou exei pollous pinakes mesa ego tha kano thn eisagogi xeirokinhta kai oxi me tin etoimi synartisi
        printf("Give: arrival time,stay time for client %d:", i + 1);
        scanf("%d,%d",&arr, &stay);
        getchar();
        if(!FullQ(*Hold))
        {
            Hold->Start[Hold->Rear] = -1;
            Hold->End[Hold->Rear] = -1;
            Hold->Arrival[Hold->Rear] = arr;
            Hold->Stay[Hold->Rear] = stay;
            Hold->Rear = (Hold->Rear + 1);
            Hold->clien++;
        }
        else
            printf("Full queue...\n");
    }
}


QueueType TimesInQueue(QueueType *Queue)
{
    QueueType temp;
    //QueueElementType start,end;

    CreateQ(&temp);

    for(QueueElementType i = 0; i < Queue->Rear; i++)
    {
        if(!EmptyQ(*Queue))
        {
            temp.Arrival[temp.Rear] = Queue->Arrival[Queue->Front];
            temp.Stay[temp.Rear] = Queue->Stay[Queue->Front];

            if(i == 0)
            {
                temp.Start[temp.Rear] = Queue->Arrival[Queue->Front];
                temp.End[temp.Rear] = Queue->Arrival[Queue->Front] + Queue->Stay[Queue->Front];
            }
            else
            {
                temp.Start[temp.Rear] = temp.End[temp.Rear - 1];
                temp.End[temp.Rear] = temp.Start[temp.Rear] + Queue->Stay[Queue->Front];
            }
            Queue->Front = (Queue->Front + 1);
            temp.Rear = (temp.Rear + 1);
            Queue->clien--;
            temp.clien++;

        }
    }

    return temp;
}


void show(QueueType Hold, QueueType Service)
{

    if(!EmptyQ(Hold))
    {
        printf("Waiting Queue:\n");
        printf("%-25s%-10s%-8s%-8s%-4s\n", "Client", "Start","End", "Arrival", "Stay");

        for(QueueElementType i = 0; i < Hold.Rear; i++)
        {
            printf("%-6s%-19d%-10d%-8d%-8d%-4d\n", "Client", i+1, Hold.Start[i],Hold.End[i], Hold.Arrival[i], Hold.Stay[i]);
        }
    }
    else
    {
        printf("Waiting Queue is empty\n");

    }

    if(!EmptyQ(Service))
    {
        printf("Service Queue:\n");
        printf("%-25s%-10s%-8s%-8s%-4s\n", "Client", "Start","End", "Arrival", "Stay");

        for(QueueElementType i = 0; i < Service.Rear; i++)
        {
            printf("%-6s%-19d%-10d%-8d%-8d%-4d\n", "Client", i+1, Service.Start[i], Service.End[i], Service.Arrival[i], Service.Stay[i]);
        }
    }
    else
        printf("Service Queue is empty\n");

}
