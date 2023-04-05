#include <stdio.h>

int fun(int N)
{
    if(N == 0)
        return 1;
    else
        return (N * fun(N-1));
}

int main()
{
    int N;
    scanf("%d", &N);
    printf("%d", fun(N));

    return 0;
}