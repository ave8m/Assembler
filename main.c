//char配列の数は適当に決定している
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
    printAsm(asmName);

    //file = fopen(argv[1], "r");
    //if(file == NULL)
    //{
    //    perror("ファイルが存在しません");
    //    return 1;
    //}

    //fprintf(file, "test\n");
    fclose(file);
    printf("debug message");
}