#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//int main()
//{

FILE *infile1;

infile1 = fopen("I5f6.txt", "r");
char name[50] = {'\0'};

fscanf(infile1, "%s", name);

return 0;
}
