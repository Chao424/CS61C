#include <stdio.h>
int test(int, int);
int main(int argc, char *argv[])
{
    int i;
    int count = 0;
    int *p = &count;
    int k;
    for (i = 0; i < 10; i++)
    {
        (*p)++; // Do you understand this line of code and all the other permutations of the operators? ;)
    }
    k = test(i, count);
    printf("Thanks for waddling through this program. Have a nice day.");
    return 0;
}

int test(int a, int b)
{
    int c;
    c = b + a;
    c++;
    return c;
}