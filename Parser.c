#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//**FILE**//
static FILE *file;      //.asm�p�̃t�@�C���X�g���[��������

void openAsm(char *name) {
    file = fopen(name, "r");
    if(file == NULL) {
        perror("�t�@�C�������݂��Ȃ��������Y��\n");
    }
}

void closeAsm() {
    fclose(file);
}
//**FILE END**//

//**advance**//
char advanceNow[256];   //�u@2�v , �uD=A�v�Ȃ� ���R�}���h�ł���1�s������

void advance() {        //file���玟�̃R�}���h��ǂݏo�� advanceNow�ɓ����
    int i = 0;
    int c;
    while((c = fgetc(file)) != '\n' && c != EOF){
        advanceNow[i] = (char)c;
        i++;
    }
    advanceNow[i] = '\0';
}
//**advance END**//

//**�R�}���h�^�C�v�̔���**//
typedef enum{
    A_COMMAND,
    C_COMMAND,
    L_COMMAND
} Command;

Command commandNow;

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
//**�R�}���h�^�C�v�̔��� END**//

//**�������Ԃ��֐�**//
char* symbol() {                //@1234��1234������Ԃ�
    static char symbol[256];
    int i = 0;
    char c;

    while( (c = advanceNow[i+1]) != ')' && c != '\0'){
        symbol[i] = c;
        i += 1;
    }
    symbol[i] = '\0';

    return symbol;
}

char* comp() {
    static char * ptr;
    ptr = strchr(advanceNow, '=');
    ptr += 1;
    return ptr;
}

char* dest() {
    static char arr[2];
    int i = 0;
    while( advanceNow[i] != '=' && i != 2 ) {
        arr[i] = advanceNow[i];
        i++;
    }
    return arr;
}

char* jump() {  //
    static char * ptr;
    ptr = strchr(advanceNow, ';');
    ptr += 1;
    return ptr;
}
//**�������Ԃ��֐� END**//

void IgnoreSpace() {    //�󔒁A���s�A�R�����g�������Ȃ�܂Ńt�@�C���|�C���^��i�߂�
    while(1)
    {
        int c;
        c = fgetc(file);

        if(c == ' '|| c == '\n') {
            //printf("detected space\n");
            continue;
        }

        else if(c == '/') {
            c = fgetc(file);
            if(c== '/') {
                //printf("detected Comment\n");
                while ((c = fgetc(file)) != EOF && c != '\n'){}
                continue;
            }
            ungetc(c, file);
        }
        ungetc(c, file);
        break;
    }
}

bool hasMoreCommands(){     //�R�}���h�����݂��邩�H
    IgnoreSpace();          //�󔒁A���s�A�R�����g����
    int c;
    c = fgetc(file);
    if (c == EOF) {
        //printf("detected EOF\n");
        return false;
    }
    ungetc(c, file);
    return true;
}