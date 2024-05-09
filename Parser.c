#include <stdio.h>
#include <stdbool.h>

static FILE *file;
char advanceNow[256];


typedef enum{
    A_COMMAND,
    C_COMMAND,
    L_COMMAND
} Command;

Command commandNow;

void openAsm(char *name) {
    file = fopen(name, "r");
    if(file == NULL) {
        perror("�t�@�C�������݂��܂���\n");
    }
}

void closeAsm() {
    fclose(file);
}

void printAsm() {    //(�f�o�b�O�p) �t�@�C���|�C���^��1�i�߃R���\�[���ɕ\��
    int c = getc(file);
    printf("%d\n",c);
}

void advance() {     //���̃R�}���h��ǂݏo��
    int i = 0;
    char c;
    while((c = fgetc(file)) != '\n' && c != EOF){
        advanceNow[i] = c;
        i++;
    }
    advanceNow[i] = 0;
}

Command commandType() {
    if(advanceNow[0] == '@') {
        return A_COMMAND;
    }
    else if(advanceNow[0] == '(') {
        return L_COMMAND;
    }
    else {
        return C_COMMAND;
    }
}

void IgnoreSpace() {
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
            ungetc(c, file);
        }
        ungetc(c, file);
        break;
    }
}

bool hasMoreCommands(){ //�R�}���h�����݂��邩�H
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

