#include <stdio.h>
#include <stdbool.h>

static FILE *asmFile;   //Todo:*Fileにする

void openAsm(char* asmName)
{
    asmFile = fopen(asmName, "r");
    if(asmFile == NULL) {
        perror("ファイルが存在しません\n");
    }
}

void printAsm()    //デバッグ用 fgetする
{
    int c = getc(asmFile);
    printf("%d\n",c);
}


bool IgnoreSpace()  //空白や改行はポインタを進める　他はポインタを元に戻す
{
    
    int c;
    c = fgetc(asmFile);
    if(c == ' '|| c == '\t' || c == '\n') {
        printf("detected space\n");
        return true;
    }
    else if(c == '/') {
        c = fgetc(asmFile);
        if(c== '/') {
            printf("detected Comment\n");
            while ((c = fgetc(asmFile)) != EOF && c != '\n'){}
            return true;
        }
        ungetc(c,asmFile);
    }
    ungetc(c,asmFile);
}

bool hasMoreCommands()
{
    int c;
    c = fgetc(asmFile);
    if (c == EOF) {
        printf("detected EOF\n");
        return false;
    }
    ungetc(c, asmFile);
    return true;
}