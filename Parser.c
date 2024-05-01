#include <stdio.h>
#include <stdbool.h>

static FILE* file;   //Todo:*Fileにする

void openAsm(char* name) {
    file = fopen(name, "r");
    if(file == NULL) {
        perror("ファイルが存在しません\n");
    }
}

void closeAsm(char* name) {
    fclose(file);
}

void printAsm()    //デバッグ用 ファイルポインタを1つ進めコンソールに表示
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

bool hasMoreCommands() //コマンドが存在するか？
{
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