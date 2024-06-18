//配列の数は適当に決めている    TODO:hack computerハードウェアの仕様に従って決める
//勉強用なのでシンプルにしている

#include <stdio.h>
//#include <stdlib.h>
#include "Code.c"

int main(int argc, char *argv[])
{
    char* asmName = argv[1];        //リテラルなのでcharポインタ
    char hackName[64];               //実行中書き換えるのでchar配列
    FILE *File;                     //.hack用のFileストリームを準備

    //asmファイルを開く
    openAsm(asmName);

    //同名.hackを用意
    char *dot = strrchr(asmName,'.');
    strncpy(hackName, asmName, dot - asmName);
    hackName[dot - asmName] = '\0';
    strcat(hackName, ".hack");
    File = fopen(hackName,"w");

    while(hasMoreCommands()){

        char * p;                       //いろんな事に使うcharポインタ

        advance();
        //printf("%s\n",advanceNow);    //現在の1行を表示
        commandNow = commandType();
        //printf("%d\n",commandNow);    //Aコマンドは0 Cコマンドは1と表示

        if(commandNow == A_COMMAND) {   //このルーチンはcommandType()がC_COMMANDのときだけ呼ぶようにする

            p = symbol();
            p = decToBinary(p);

            //printf("bin:%s\n", p);    //@の次の数字を表示

            fputs("0", File);
            fputs(p, File);
            fputs("\n", File);


        }
        else if(commandNow = C_COMMAND) {   //このルーチンはcommandType()がA_COMMANDのときだけ呼ぶようにする
            p = comp();
            p = code_comp(p);

            //printf("comp:%s\n", p);       //A=DのAを表示

            fputs("111", File);
            fputs(p, File);

            p = dest();
            p = code_dest(p);

            //printf("dest:%s\n", p);       //A=DのDを表示

            fputs(p, File);
            fputs("000", File);             //JMPはまだ未実装の為
            fputs("\n", File);

        }
    }

    closeAsm();
    fclose(File);
 
    printf("finish\n");
}