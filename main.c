//�z��̐��͓K���Ɍ��߂�
//�׋��p�̂��߃V���v����
//�o�O�����͂��܂菑���Ȃ�


#include <stdio.h>
#include "Parser.c"

static FILE *file;

int main(int argc, char *argv[])
{
    char* asmName = argv[1];        //���e�����Ȃ̂Ń|�C���^���g�p
    char hackName[64];               //���s������������̂Ŕz����g�p

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