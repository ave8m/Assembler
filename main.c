//�z��̐��͓K���Ɍ��߂Ă���    TODO:hack computer�n�[�h�E�F�A�̎d�l�ɏ]���Č��߂�
//�׋��p�Ȃ̂ŃV���v���ɂ��Ă���

#include <stdio.h>
//#include <stdlib.h>
#include "Code.c"

int main(int argc, char *argv[])
{
    char* asmName = argv[1];        //���e�����Ȃ̂�char�|�C���^
    char hackName[64];               //���s������������̂�char�z��
    FILE *File;                     //.hack�p��File�X�g���[��������

    //asm�t�@�C�����J��
    openAsm(asmName);

    //����.hack��p��
    char *dot = strrchr(asmName,'.');
    strncpy(hackName, asmName, dot - asmName);
    hackName[dot - asmName] = '\0';
    strcat(hackName, ".hack");
    File = fopen(hackName,"w");

    while(hasMoreCommands()){

        char * p;                       //�����Ȏ��Ɏg��char�|�C���^

        advance();
        //printf("%s\n",advanceNow);    //���݂�1�s��\��
        commandNow = commandType();
        //printf("%d\n",commandNow);    //A�R�}���h��0 C�R�}���h��1�ƕ\��

        if(commandNow == A_COMMAND) {   //���̃��[�`����commandType()��C_COMMAND�̂Ƃ������ĂԂ悤�ɂ���

            p = symbol();
            p = decToBinary(p);

            //printf("bin:%s\n", p);    //@�̎��̐�����\��

            fputs("0", File);
            fputs(p, File);
            fputs("\n", File);


        }
        else if(commandNow = C_COMMAND) {   //���̃��[�`����commandType()��A_COMMAND�̂Ƃ������ĂԂ悤�ɂ���
            p = comp();
            p = code_comp(p);

            //printf("comp:%s\n", p);       //A=D��A��\��

            fputs("111", File);
            fputs(p, File);

            p = dest();
            p = code_dest(p);

            //printf("dest:%s\n", p);       //A=D��D��\��

            fputs(p, File);
            fputs("000", File);             //JMP�͂܂��������̈�
            fputs("\n", File);

        }
    }

    closeAsm();
    fclose(File);
 
    printf("finish\n");
}