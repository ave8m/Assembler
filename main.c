//�z��̐��͓K���Ɍ��߂Ă���    TODO:hack computer�n�[�h�E�F�A�̎d�l�ɏ]���Č��߂�
//�׋��p�Ȃ̂ŃV���v���ɂ��Ă���

#include <stdio.h>
#include <stdlib.h>
#include "Code.c"



char* decToBinary(char* str) {
    static char binary[16];
    memset(binary, '\0', sizeof(binary));

    // 2�i���ɕϊ�
    int num = atoi(str);

    for (int i = 14; i >= 0; --i) {
        binary[i] = (num % 2) == 0 ? '0':'1';
        num /= 2;
    }

    // ���̒l�̏ꍇ2�̕␔  �ł��E����'1'�������ɂ���S�r�b�g�𔽓]����
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
    char* asmName = argv[1];        //���e�����Ȃ̂�char�|�C���^
    char hackName[64];               //���s������������̂�char�z��
    FILE *File;                     //.hack�p��File�X�g���[��������

    openAsm(asmName);

    char *dot = strrchr(asmName,'.');
    strncpy(hackName, asmName, dot - asmName);
    strcat(hackName, ".hack");
    
    File = fopen(hackName,"w");



    while(hasMoreCommands()){

        char * mnemonic;       //�ꎞ�I��

        //printAsm();  (�f�o�b�O�p��ASCII�R�[�h��print)
        advance();
        //printf("%s\n",advanceNow); //���݂�1�s��\��


        commandNow = commandType();
        //printf("%d\n",commandNow); //A�R�}���h��0 C�R�}���h��1�ƕ\��

        if(commandNow == A_COMMAND) {   //���̃��[�`����commandType()��C_COMMAND�̂Ƃ������ĂԂ悤�ɂ���

            mnemonic = symbol();
            mnemonic = decToBinary(mnemonic);
            printf("bin:%s\n", mnemonic);     //@�̎��̐�����\��


        }
        else if(commandNow = C_COMMAND) {   //���̃��[�`����commandType()��A_COMMAND�̂Ƃ������ĂԂ悤�ɂ���
            mnemonic = dest();
            mnemonic = code_dest(mnemonic);
            printf("dest:%s\n", mnemonic);  //A=D��A��\��

            mnemonic = comp();
            mnemonic = code_comp(mnemonic);
            printf("comp:%s\n", mnemonic);  //A=D��D��\��

        }
    }

    closeAsm();
 
    printf("finish\n");
}


