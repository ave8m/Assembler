#include <stdio.h>
#include <stdbool.h>

static FILE *asmFile;

void openAsm(char* asmName)
{
    asmFile = fopen(asmName, "r");
    if(asmFile == NULL)
    {
        perror("ファイルが存在しません");
    }
}

void printAsm(char* asmName)
{
    int c = fgetc(asmFile);
    printf("%dです",c);
}



//bool hasMoreCommands()
//{
//    if
//}