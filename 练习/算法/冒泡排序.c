/*bubble.c*/
#include<stdio.h>
#define NUM 10
int main()
{
    int arr[NUM];
    int cnt=0;
    printf("Please enter an array with numbers divided by space:\n");

    for(int i=0;i<NUM;i++){
        scanf("%d",&arr[i]);
        cnt++;
    }
    for(int j=cnt;j>=0;j--){
        for(int i=0;i<j;i++){           //当前数字与最后一位比较
            if(arr[i]>arr[j-1]){
                int temp=arr[i];
                arr[i]=arr[j-1];
                arr[j-1]=temp;
            }
        }
    }
    for(int i=0;i<NUM;i++)
        printf("%d ",arr[i]);

    return 0;
}