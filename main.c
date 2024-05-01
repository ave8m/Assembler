//配列の数は適当に決めた
//勉強用のためシンプルに
//バグ処理はあまり書かない


#include <stdio.h>
#include "Parser.c"

static FILE *file;

int main(int argc, char *argv[])
{
    char* asmName = argv[1];        //リテラルなのでポインタを使用
    char hackName[64];               //実行中書き換えるので配列を使用

    openAsm(asmName);


    while(hasMoreCommands()){
        IgnoreSpace();
        if( !hasMoreCommands() ) {
            break;
        }
        printAsm();
    }

    //fprintf(file, "test\n");
    fclose(file);
    printf("Program finished\n");
}