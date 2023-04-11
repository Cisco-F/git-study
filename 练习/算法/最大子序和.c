// 动态排列
#include <stdio.h>
#include <malloc.h>
int main()
{
    int *arr = (int*)malloc(10000*sizeof(int));
    int cnt = 0;    int i = 0;
    do{
        scanf("%d", &arr[i]);
        cnt++;  i++;
    }while(getchar() != '\n');

    int pre = 0;
    int maxAns = arr[0];
    for(int j = 0; j < cnt; j++){
        pre = fmax(pre+arr[j], arr[j]);
        maxAns = fmax(pre, maxAns);
    }

    printf("The maximum subarray is %d\n", maxAns);

    return 0;
}