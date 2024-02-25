#include <stdio.h>
#include "a2f4p3.h"

//Main function
int main()
{
    int ctr;
    ListPointer AList;
    NodeType Node[NumberOfNodes];
    ListPointer FreePtr,PredPtr;

    CreateList(&AList);
    InitializeStoragePool(Node, &FreePtr);
    printAll(AList, FreePtr, Node);
    printf("Linked List\n");
    TraverseLinked(AList, Node);

    PredPtr = NilValue;
    Filling(Node, &AList, &FreePtr, PredPtr);

    ctr = HowManyElements(Node, &AList);
    printf("Question j\nArxiki Lista\n");
    //printAll(AList, FreePtr, Node);
    //printf("Linked List\n");
    TraverseLinked(AList, Node);
    insert_list_m_elements(&AList, Node, &FreePtr, PredPtr = NilValue, ctr);

    printf("Teliki Lista\n");
    TraverseLinked(AList,Node);

    //--------------------------------
    NodeType Node2[NumberOfNodes], Node3[NumberOfNodes], Node4[NumberOfNodes];
    ListPointer BList, FreeB, PredB, CList,FreeC,PredC, DList, FreeD, PredD;
    int num1, sum, elements;

    CreateList(&BList);
    InitializeStoragePool(Node2, &FreeB);
    CreateList(&CList);
    InitializeStoragePool(Node3, &FreeC);
    CreateList(&DList);
    InitializeStoragePool(Node4, &FreeD);

    for(int i = 0; i < 6; i++)
    {
        printf("Dwse ena stoixeio pou na einai megalitero apo to proigoumeno: ");
        scanf("%d", &num1);
        PredPtr = NilValue;
        Insert(&BList, Node2, &FreeB, PredPtr, num1);
    }

    printf("Dwse ena stoixeio: ");
    scanf("%d", &num1);

    InsertSorted(Node2, &BList, &FreeB, PredB = NilValue, num1);

    printf("Question k\nFinal List with ypur element and sorted\n");
    TraverseLinked(BList, Node2);

    printf("Question l\n");
    for(int i = 0; i < 3; i++)
    {
        printf("Dwse ena stoixeio pou na einai megalitero apo to proigoumeno: ");
        scanf("%d", &num1);
        PredPtr = NilValue;
        Insert(&CList, Node3, &FreeC, PredPtr, num1);
    }

    TraverseLinked(CList, Node3);

    MergeLists(Node2,Node3, &BList, &CList, &FreeB, &FreeC, PredB, PredC, Node4, &DList, &FreeD, PredD, &sum, &elements);
    printf("Merged List\n");
    TraverseLinked(DList, Node4);

    printf("Question m\nSum = %d\n", sum);
    printf("Question n\nElements = %d\n", elements);

    return 0;
}


void MergeLists(NodeType Node2[], NodeType Node3[], ListPointer *BList, ListPointer *CList, ListPointer *FreeB, ListPointer *FreeC,
ListPointer PredB,ListPointer PredC,NodeType Node4[], ListPointer *DList, ListPointer *FreeD, ListPointer PredD, int *sum, int *elements)
{
    ListPointer curr1,prev1,curr2,prev2, curr3, prev3;


    curr1 = *BList;
    prev1 = NilValue;

    while(curr1 != NilValue)
    {
        Insert(DList, Node4, FreeD, PredD = NilValue, Node2[curr1].Data);
        prev1 = curr1;
        curr1 = Node2[curr1].Next;
    }

    curr2 = *CList;
    prev2 = NilValue;

    while(curr2 != NilValue)
    {
        curr3 = *DList;
        prev3 = NilValue;

        while(curr3 != NilValue)
        {
            if(Node4[curr3].Data < Node3[curr2].Data)
            {
                prev3 = curr3;
                curr3 = Node4[curr3].Next;
            }
            else if(Node4[curr3].Data > Node3[curr2].Data)
                break;
            else
            {
                prev3 = curr3;
                curr3 = Node4[curr3].Next;
            }
        }

        Insert(DList, Node4, FreeD, prev3, Node3[curr2].Data);
        prev2 = curr2;
        curr2 = Node3[curr2].Next;
    }

    (*sum) = 0;
    (*elements) = 0;
    curr1 = *DList;
    while(curr1 != NilValue)
    {
        (*elements)++;
        (*sum) += Node4[curr1].Data;
        curr1 = Node4[curr1].Next;
    }
}




