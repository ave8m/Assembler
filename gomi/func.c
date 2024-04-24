#include "func.h"

void test(int* x)
{
    *x += 10;
    if(x != NULL)
    {
    printf("%d",*x);
    }
}