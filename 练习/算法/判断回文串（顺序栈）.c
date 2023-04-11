/*本函数采用了自定义函数初始化栈的方式*/
/*在主函数中栈的定义为 Stack S */
/*后续使用S时应使用.访问S的元素*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

#define MAXSIZE 1000

typedef struct stack{
    char data[MAXSIZE];
    int top;
}Stack;

//初始化栈
void InitStack(Stack *S)
{
    S->top = -1;
}

//入栈
bool Push(Stack *S, char x)
{
    if(S->top == MAXSIZE-1){
        printf("The stack is full!\n");
        exit(0);
    }
    S->top++;
    S->data[S->top] = x;
}

//出栈
bool Pop(Stack *S, char *x)
{
    if(S->top == -1){
        printf("The stack is empty!\n");
        exit(0);
    }
    *x = S->data[S->top];
    S->top--;
}

int main()
{
    Stack S;
    InitStack(&S);

    char t, cmp;
    printf("请输入字符串:\n");
    while((t=getchar())!='&'){  //前半部分字符入栈
        Push(&S, t);
    }
    
    while((t=getchar())!='@' && S.top != -1){
        Pop(&S, &cmp);
        if(cmp != t){
            printf("不是回文串!\n");
            return 0;
        }
    }
    if(S.top == -1 && t == '@'){
        printf("是回文串!\n");
        return 0;
    }
    else{
        printf("不是回文串!\n");
        return 0;
    }
}