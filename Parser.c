#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//**FILE**//
static FILE *file;      //.asm用のファイルストリームを準備

void openAsm(char *name) {
    file = fopen(name, "r");
    if(file == NULL) {
        perror("ファイルが存在しないか引数忘れ\n");
    }
}

void closeAsm() {
    fclose(file);
}
//**FILE END**//

//**advance**//
char advanceNow[256];   //「@2」 , 「D=A」など 現コマンドである1行が入る

void advance() {        //fileから次のコマンドを読み出す advanceNowに入れる
    int i = 0;
    int c;
    while((c = fgetc(file)) != '\n' && c != EOF){
        advanceNow[i] = (char)c;
        i++;
    }
    advanceNow[i] = '\0';
}
//**advance END**//

//**コマンドタイプの判別**//
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
//**コマンドタイプの判別 END**//

//**文字列を返す関数**//
char* symbol() {                //@1234の1234部分を返す
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
//**文字列を返す関数 END**//

void IgnoreSpace() {    //空白、改行、コメントが無くなるまでファイルポインタを進める
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

bool hasMoreCommands(){     //コマンドが存在するか？
    IgnoreSpace();          //空白、改行、コメント無視
    int c;
    c = fgetc(file);
    if (c == EOF) {
        //printf("detected EOF\n");
        return false;
    }
    ungetc(c, file);
    return true;
}