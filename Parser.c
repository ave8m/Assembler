#include <stdio.h>
#include <stdbool.h>

static FILE *asmFile;

void openAsm(char* asmName)
{
    asmFile = fopen(asmName, "r");
    if(asmFile == NULL)
    {
        perror("ƒtƒ@ƒCƒ‹‚ª‘¶İ‚µ‚Ü‚¹‚ñ");
    }
}

void printAsm(char* asmName)
{
    int c = fgetc(asmFile);
    printf("%d‚Å‚·",c);
}



//bool hasMoreCommands()
//{
//    if
//}