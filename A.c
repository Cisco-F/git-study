#include<stdio.h>
#include <stdlib.h>

int main()
{
	int a, i=0;
	scanf("%d",&a);	
    int *arr = (int *)malloc(sizeof(int)*a);
    
    while(i < a){
		scanf("%d", &arr[i]);			
		i++;
	}
    for(int cnt = 0; cnt < a; cnt++){
        if(arr[cnt]>=550 && arr[cnt]<=750)
            printf("Excellent!\n");
        if(arr[cnt]<550 && arr[cnt]>=425)
            printf("Passed!\n");
        if(arr[cnt]<425 && arr[cnt]>=0)
            printf("See you next year!\n");
    }
	return 0;
}