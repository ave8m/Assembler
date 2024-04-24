#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    if(file == NULL)
    {
        perror("ƒtƒ@ƒCƒ‹‚ª‘¶İ‚µ‚Ü‚¹‚ñ");
        return 1;
    }

    //fprintf(file, "test\n");
    fclose(file);



    printf("debug message");
}