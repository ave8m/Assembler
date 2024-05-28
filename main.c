//配列の数は適当に決めている    TODO:hack computerハードウェアの仕様に従って決める
//勉強用なのでシンプルにしている

#include <stdio.h>
#include <stdlib.h>
#include "Code.c"



char* decToBinary(char* str) {
    static char binary[16];
    memset(binary, '\0', sizeof(binary));

    // 2進数に変換
    int num = atoi(str);

    for (int i = 14; i >= 0; --i) {
        binary[i] = (num % 2) == 0 ? '0':'1';
        num /= 2;
    }

    // 負の値の場合2の補数  最も右側の'1'よりも左にある全ビットを反転する
    if (atoi(str) < 0) {
        for (int i = 14; i >= 0; --i) {
            if (binary[i] == '1') {
                while(i > 0) {
                    --i;
                    binary[i] = binary[i] == '0' ? '1':'0';
                }
                break;
            }
        }
    }
    return binary;
}


int main(int argc, char *argv[])
{
    char* asmName = argv[1];        //リテラルなのでcharポインタ
    char hackName[64];               //実行中書き換えるのでchar配列
    FILE *File;                     //.hack用のFileストリームを準備

    openAsm(asmName);

    char *dot = strrchr(asmName,'.');
    strncpy(hackName, asmName, dot - asmName);
    strcat(hackName, ".hack");
    
    File = fopen(hackName,"w");



    while(hasMoreCommands()){

        char * mnemonic;       //一時的な

        //printAsm();  (デバッグ用にASCIIコードでprint)
        advance();
        //printf("%s\n",advanceNow); //現在の1行を表示


        commandNow = commandType();
        //printf("%d\n",commandNow); //Aコマンドは0 Cコマンドは1と表示

        if(commandNow == A_COMMAND) {   //このルーチンはcommandType()がC_COMMANDのときだけ呼ぶようにする

            mnemonic = symbol();
            mnemonic = decToBinary(mnemonic);
            printf("bin:%s\n", mnemonic);     //@の次の数字を表示


        }
        else if(commandNow = C_COMMAND) {   //このルーチンはcommandType()がA_COMMANDのときだけ呼ぶようにする
            mnemonic = dest();
            mnemonic = code_dest(mnemonic);
            printf("dest:%s\n", mnemonic);  //A=DのAを表示

            mnemonic = comp();
            mnemonic = code_comp(mnemonic);
            printf("comp:%s\n", mnemonic);  //A=DのDを表示

        }
    }

    closeAsm();
 
    printf("finish\n");
}


