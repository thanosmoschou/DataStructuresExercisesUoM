#include <stdio.h>
#include "a2f4p2.h"

//Main function
int main()
{

    ListPointer AList;
    NodeType Node[NumberOfNodes];
    ListPointer FreePtr,PredPtr;
    ListElementType AnItem;

    CreateList(&AList);
    InitializeStoragePool(Node, &FreePtr);
    printAll(AList, FreePtr, Node);
    printf("Linked List\n");
    TraverseLinked(AList, Node);

    PredPtr = NilValue;
    Filling(Node, &AList, &FreePtr, PredPtr);
    printAll(AList, FreePtr, Node);
    printf("Linked List\n");
    TraverseLinked(AList, Node);

    printf("Question h\n");
    DeleteEveryOtherNode(Node, &AList, NilValue, &FreePtr);
    printAll(AList, FreePtr, Node);
    printf("Linked List\n");
    TraverseLinked(AList, Node);

    //------------------------------
    ListElementType Blist, Clist,Dlist;
    NodeType Node2[NumberOfNodes], Node3[NumberOfNodes], Node4[NumberOfNodes];
    ListPointer FreeB, FreeC, FreeD, PredB, PredC, PredD;

    CreateList(&Blist);
    CreateList(&Clist);
    CreateList(&Dlist);

    InitializeStoragePool(Node2, &FreeB);
    InitializeStoragePool(Node3, &FreeC);
    InitializeStoragePool(Node4, &FreeD);

    for(int i = 0; i < NumberOfNodes; i++)
    {
        PredB = NilValue;
        Insert(&Blist, Node2, &FreeB, PredB, i);
    }

    for(int i = 0; i < NumberOfNodes; i+=2)
    {
        PredC = NilValue;
        Insert(&Clist, Node3, &FreeC, PredC, i);
    }


    Intersection(Node2, Node3, Node4, &FreeB, &FreeC, &FreeD, PredB, PredC, PredD, &Blist, &Clist, &Dlist);
    printf("Question i\n");

    printf("List 1\n");
    TraverseLinked(Blist, Node2);

    printf("List 2\n");
    TraverseLinked(Clist, Node3);

    printf("Intersection\n");
    TraverseLinked(Dlist, Node4);

    return 0;
}

