#include <stdio.h>
#include <stdbool.h>

static FILE *asm;   //Todo:*File�ɂ���

void openAsm(char* name) {
    asm = fopen(name, "r");
    if(asm == NULL) {
        perror("�t�@�C�������݂��܂���\n");
    }
}

void closeAsm(char* name) {
    fclose(asm);
}

void printAsm()    //�t�@�C���|�C���^��1�i�߃R���\�[���ɕ\��
{
    int c = getc(asm);
    printf("%d\n",c);
}

void IgnoreSpace()  //�󔒁A���s�A�R�����g�������Ȃ�܂Ńt�@�C���|�C���^��i�߂�
{
    while(1)
    {
        int c;
        c = fgetc(asm);

        if(c == ' '|| c == '\n') {
            printf("detected space\n");
            continue;
        }

        else if(c == '/') {
            c = fgetc(asm);
            if(c== '/') {
                printf("detected Comment\n");
                while ((c = fgetc(asm)) != EOF && c != '\n'){}
                continue;
            }
            ungetc(c,asm);
        }
        ungetc(c,asm);
        break;
    }
}

bool hasMoreCommands()
{
    int c;
    c = fgetc(asm);
    if (c == EOF) {
        printf("detected EOF\n");
        return false;
    }
    ungetc(c, asm);
    return true;
}