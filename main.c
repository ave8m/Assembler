//char�z��̐��͓K���Ɍ��肵�Ă���
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
    printAsm(asmName);

    //file = fopen(argv[1], "r");
    //if(file == NULL)
    //{
    //    perror("�t�@�C�������݂��܂���");
    //    return 1;
    //}

    //fprintf(file, "test\n");
    fclose(file);
    printf("debug message");
}