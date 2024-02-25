#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#define NumberOfNodes 10    /*όριο μεγέθους της συνδεδεμένης λίστας,
                            ενδεικτικά τέθηκε ίσο με 50*/
#define NilValue -1          // ειδική μεδενικη τιμη δείχνει το τέλος της Συνδ.λίστας

typedef int ListElementType; /*τύπος δεδομένων για τα στοιχεία της συνδεδεμένης λίστας,
                                ενδεικτικά επιλέχθηκε ο τύπος int */
typedef int ListPointer;

typedef struct {
    ListElementType Data;
    ListPointer  Next;
} NodeType;

typedef enum {
    FALSE, TRUE
} boolean;


//Function prototypes
void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr);
void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
boolean FullList(ListPointer FreePtr);
void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]);
void ReleaseNode(NodeType Node[NumberOfNodes], ListPointer P, ListPointer *FreePtr);
void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item);
void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr);
void TraverseLinked(ListPointer List, NodeType Node[]);
void menu(int *choice);
void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[]);
void FillAtTheEnd(ListPointer *AList,NodeType Node[], ListPointer *FreePtr,ListPointer PredPtr, ListElementType Item);
void CopyList(ListPointer *AList, ListPointer *FreePtr, ListPointer *ListCop,
ListPointer *FreeCop, ListPointer PredPtr,ListPointer PredCop,NodeType Node[],NodeType Cop[]);
void UniteList(ListPointer *AList, ListPointer *ListCop, ListPointer *ListUnit, ListPointer *FreePtr, ListPointer *FreeCop,ListPointer *FreeUnit, ListPointer PredPtr,ListPointer PredCop, ListPointer PredUnit,
NodeType Node[],NodeType Cop[],NodeType Unit[]);
void DeleteNodes(ListPointer *ListUnit,ListPointer *FreeUnit,ListPointer PredUnit,NodeType Unit[]);
void ReverseNodes(ListPointer *List, NodeType Node[]);
void DeleteLast(ListPointer *List, NodeType Node[], ListPointer *FreePtr);
