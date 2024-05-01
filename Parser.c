#include <stdio.h>
#include <stdbool.h>

static FILE* file;   //Todo:*File�ɂ���

void openAsm(char* name) {
    file = fopen(name, "r");
    if(file == NULL) {
        perror("�t�@�C�������݂��܂���\n");
    }
}

void closeAsm(char* name) {
    fclose(file);
}

void printAsm()    //�f�o�b�O�p �t�@�C���|�C���^��1�i�߃R���\�[���ɕ\��
{
    int c = getc(file);
    printf("%d\n",c);
}

void IgnoreSpace()
{
    while(1)
    {
        int c;
        c = fgetc(file);

        if(c == ' '|| c == '\n') {
            printf("detected space\n");
            continue;
        }

        else if(c == '/') {
            c = fgetc(file);
            if(c== '/') {
                printf("detected Comment\n");
                while ((c = fgetc(file)) != EOF && c != '\n'){}
                continue;
            }
            ungetc(c,file);
        }
        ungetc(c,file);
        break;
    }
}

bool hasMoreCommands() //�R�}���h�����݂��邩�H
{
    IgnoreSpace(); //�󔒁A���s�A�R�����g�������Ȃ�܂Ńt�@�C���|�C���^��i�߂�
    int c;
    c = fgetc(file);
    if (c == EOF) {
        printf("detected EOF\n");
        return false;
    }
    ungetc(c, file);
    return true;
}