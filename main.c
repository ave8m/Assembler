//�z��̐��͓K���Ɍ��߂Ă���
//�׋��p�̂��߃V���v���ɂ��Ă���


#include <stdio.h>
#include "Parser.c"

static FILE *file;

int main(int argc, char *argv[])
{
    char* asmName = argv[1];        //���e�����Ȃ̂Ń|�C���^���g�p
    char hackName[64];               //���s������������̂Ŕz����g�p

    openAsm(asmName);

    while(hasMoreCommands()){
        printAsm();
    }

    closeAsm(asmName);

    printf("Program finished\n");
}