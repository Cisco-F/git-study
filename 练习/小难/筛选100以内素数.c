#include<stdio.h>
#define N 100
int main()
{
    int arr[N];
    for(int i=0;i<N;i++){
        arr[i]=i+1;
    }

    for(int i=1;i<N;i++){
        if(arr[i]==0)
            continue;
        for(int j=i+1;j<N;j++){
            if(arr[j]%arr[i]==0)
                arr[j]=0;
        }
    }
    for(int i=0;i<N;i++){
        if(arr[i]!=0)
            printf("%d ",arr[i]);
    }
    return 0;
}