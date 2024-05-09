//配列の数は適当に決めている
//勉強用のためシンプルにしている
#include <stdio.h>
#include "Parser.c"

int main(int argc, char *argv[])
{
    char* asmName = argv[1];        //リテラルなのでポインタを使用
    char hackName[64];               //実行中書き換えるので配列を使用

    openAsm(asmName);

    while(hasMoreCommands()){
        //printAsm();
        advance();
        commandNow=commandType();
        printf("%d\n",(int)commandNow);
    }

    closeAsm();
 
    printf("Program finished\n");
}