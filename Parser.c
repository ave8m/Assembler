#include <stdio.h>
#include <stdbool.h>

static FILE *asmFile;

void openAsm(char* asmName)
{
    asmFile = fopen(asmName, "r");
    if(asmFile == NULL)
    {
        perror("�t�@�C�������݂��܂���");
    }
}

void printAsm(char* asmName)
{
    int c = fgetc(asmFile);
    printf("%d�ł�",c);
}



//bool hasMoreCommands()
//{
//    if
//}