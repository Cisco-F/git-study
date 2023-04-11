#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MaxSubString(char *str1, char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int start = 0;
    int i, j;   i = j = 0;
    while(i < len1 && j < len2){
        if(str1[i] == str2[j]){
            i++;    j++;
        }
        else{
            start++;
            i = start;
            j = 0;
        }
    }
    if(j >= len2)   return start;
    else{
        // printf
    }
}

int main()
{
    char *str1, *str2;
    printf("Please enter str1:\n");
    gets(str1);
    printf("Please enter str2:\n");
    gets(str2);

}