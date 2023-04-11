#include<stdio.h>
int main()
{
    printf("Enter a message: ");
    
    int i=0;
    char ch[100];
    for(i=0;;){
    	ch[i]=getchar();
    	if(ch[i]=='\n'){
	    	i--;
	    	break;
	    }
    	i++;
    }
 
    printf("Reversal is: ");
    for(;i>=0;i--){
        printf("%c\n",ch[i]);
    }
}