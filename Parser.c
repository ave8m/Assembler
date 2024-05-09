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
        perror("ファイルが存在しません\n");
    }
}

void closeAsm() {
    fclose(file);
}

void printAsm() {    //(デバッグ用) ファイルポインタを1つ進めコンソールに表示
    int c = getc(file);
    printf("%d\n",c);
}

void advance() {     //次のコマンドを読み出す
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

bool hasMoreCommands(){ //コマンドが存在するか？
    IgnoreSpace(); //空白、改行、コメントが無くなるまでファイルポインタを進める
    int c;
    c = fgetc(file);
    if (c == EOF) {
        printf("detected EOF\n");
        return false;
    }
    ungetc(c, file);
    return true;
}

