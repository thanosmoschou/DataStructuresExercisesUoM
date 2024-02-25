#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "a2f4p1Protot.h"

#define NumberOfNodes 10

//Main function
int main()
{
    ListPointer AList, ListCop, ListUnit;
    NodeType Node[NumberOfNodes], Cop[NumberOfNodes], Unit[NumberOfNodes];
    ListPointer FreePtr,PredPtr, FreeCop, PredCop, FreeUnit, PredUnit;
    int i;

    CreateList(&AList);
    InitializeStoragePool(Node, &FreePtr);
    printAll(AList, FreePtr, Node);
    printf("Linked List\n");
    TraverseLinked(AList, Node);
    printf("\n");

    //Initial filling
    for(i = 0; i < NumberOfNodes / 2; i++)
    {
        PredPtr = NilValue;
        Insert(&AList, Node, &FreePtr, PredPtr, i+1);
    }

    printAll(AList, FreePtr, Node);
    TraverseLinked(AList, Node);
    printf("\n");

    printf("Question a:\n");
    srand(time(NULL));

    PredPtr = NilValue;
    FillAtTheEnd(&AList, Node, &FreePtr, PredPtr, rand()%11);
    printAll(AList, FreePtr, Node);
    printf("Linked List\n");
    TraverseLinked(AList, Node);
    printf("\n");

    printf("Question b\n");
    printf("Copy of Linked List:\n");
    CreateList(&ListCop);
    InitializeStoragePool(Cop, &FreeCop);
    PredCop = PredPtr = NilValue;
    CopyList(&AList, &FreePtr, &ListCop, &FreeCop, PredPtr, PredCop, Node, Cop);
    printAll(AList, FreePtr, Cop);
    printf("Linked List\n");
    TraverseLinked(ListCop, Cop);

    CreateList(&AList);
    InitializeStoragePool(Node, &FreePtr);

    for(i = 0; i < 3; i++)
    {
        PredPtr = NilValue;
        Insert(&AList, Node, &FreePtr, PredPtr, i+1);
    }

    printf("Question c\n");
    printAll(AList, FreePtr, Node);
    printf("\n");
    printAll(ListCop, FreeCop, Cop);
    printf("\n");

    printf("List A:\n");
    TraverseLinked(AList, Node);

    printf("List B:\n");
    TraverseLinked(ListCop, Cop);

    printf("United List:\n");
    CreateList(&ListUnit);
    InitializeStoragePool(Unit, &FreeUnit);
    TraverseLinked(ListUnit, Unit);

    PredUnit = NilValue;
    UniteList(&AList, &ListCop, &ListUnit, &FreePtr, &FreeCop,&FreeUnit, PredPtr, PredCop, PredUnit,
    Node, Cop, Unit);
    TraverseLinked(ListUnit, Unit);

    printf("Question d\n");
    PredUnit = NilValue;
    DeleteNodes(&ListUnit, &FreeUnit, PredUnit, Unit);
    TraverseLinked(ListUnit, Unit);

    printf("Question e\n");
    CreateList(&AList);
    InitializeStoragePool(Node, &FreePtr);

    for(i = 0; i < NumberOfNodes; i++)
    {
        PredPtr = NilValue;
        Insert(&AList, Node, &FreePtr, PredPtr, i+1);
    }

    printf("Linked List\n");
    TraverseLinked(AList, Node);

    printf("Reversed List\n");
    TraverseLinked(AList, Node);

    printf("Question f\n");
    printf("Linked List\n");
    DeleteLast(&AList, Node, &FreePtr);
    TraverseLinked(AList, Node);

    printf("Question g\n");

    NodeType Del[NumberOfNodes];
    ListElementType BList;
    ListPointer FreePtrDel, PredPtrDel,sum, num, curr, ctr;

    CreateList(&BList);
    InitializeStoragePool(Del, &FreePtrDel);

    printf("Dwse to plithos ton stoixeion tis listas(Plithos > 0 kai Plithos <= %d) ", NumberOfNodes);
    do
    {
        scanf("%d", &sum);
        if(sum < 0 || sum > NumberOfNodes)
            printf("Invalid Data\n");
    }while(sum < 0 || sum > NumberOfNodes);

    for(int i = 0; i < sum; i++)
    {
        printf("Dwse to %do stoixeio tis listas sou: ",i);
        scanf("%d", &num);

        Insert(&BList, Del, &FreePtrDel, PredPtrDel = NilValue, num);
    }

    printf("Linked List\n");
    TraverseLinked(BList, Del);

    curr = BList;
    ctr = 0;
    while(curr != NilValue)
    {
        ctr++;
        curr = Del[curr].Next;
    }

    printf("Poio stoixeio thes na sviseis? ");
    do
    {
        scanf("%d", &num);
        if(num < 0 || num > ctr)
            printf("ERROR\n");
    }while(num < 0 || num > ctr);

    curr = BList;
    while(curr != NilValue)
    {
        if(num == BList)
        {
            Delete(&BList, Del, &FreePtrDel, NilValue);
            break;
        }

        if(Del[curr].Next == num)
        {
            Delete(&BList, Del, &FreePtrDel, curr);
            break;
        }
        else
            curr = Del[curr].Next;
    }

    printf("Linked List without deleted item\n");
    TraverseLinked(BList, Del);


    return 0;
}



