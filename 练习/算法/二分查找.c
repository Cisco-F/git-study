#include <stdio.h>
int main()
{
    int arr[8] = {-1, 0, 3, 4, 6, 7, 9, 11};
    int size = 8;
    int target;
    printf("Please enter the number you wish to search:");
    scanf("%d", &target);

    int left = 0;
    int right = size-1;
    int isFound = -1;

    while(left <= right)
    {
        int mid = (left+right)/2;
        int temp = arr[mid];
        if(target < temp){
            right = mid-1;
        }
        else if(target > temp){
            left = mid+1;
        }
        else{
            isFound = mid;
            break;
        }
    }

    printf("%d",isFound);

    return 0;
}