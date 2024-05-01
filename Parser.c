#include <stdio.h>
#include <stdbool.h>

static FILE *asm;   //Todo:*Fileにする

void openAsm(char* name) {
    asm = fopen(name, "r");
    if(asm == NULL) {
        perror("ファイルが存在しません\n");
    }
}

void closeAsm(char* name) {
    fclose(asm);
}

void printAsm()    //ファイルポインタを1つ進めコンソールに表示
{
    int c = getc(asm);
    printf("%d\n",c);
}

void IgnoreSpace()  //空白、改行、コメントが無くなるまでファイルポインタを進める
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