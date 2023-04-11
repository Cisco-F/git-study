/*使用凯撒加密法，将每个字母向后移动一定位数，位数由用户指定*/
#include<stdio.h>
int main()
{
    char a[1000]={32};
    int i=0;
    int t=0;
    int p=0;
    printf("Enter message to be encrypted: ");
    do{
        i=0;
        a[i]=getchar();
        i++;
        p++;
    }while(a[i-1]!='\n');
    printf("Enter shift amount (1-25): "); 
    scanf("%d",&t);
    
    printf("Encrypted message: ");
    for(i=0;i<p;i++){
        if(65<=(int)a[i]&&(int)a[i]<=90){
            if(a[i]+t>90)
                putchar(a[i]+t-26);
            else
                putchar(a[i]+t);
        }
        else if(97<=a[i]&&a[i]<=122){
             if(a[i]+t>122)
                putchar(a[i]+t-26);
             else
                putchar(a[i]+t);
        }
        else
            printf("%c",a[i]);
    }
    return 0;
}