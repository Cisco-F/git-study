/*�������������Զ��庯����ʼ��ջ�ķ�ʽ*/
/*����������ջ�Ķ���Ϊ Stack S */
/*����ʹ��SʱӦʹ��.����S��Ԫ��*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

#define MAXSIZE 1000

typedef struct stack{
    char data[MAXSIZE];
    int top;
}Stack;

//��ʼ��ջ
void InitStack(Stack *S)
{
    S->top = -1;
}

//��ջ
bool Push(Stack *S, char x)
{
    if(S->top == MAXSIZE-1){
        printf("The stack is full!\n");
        exit(0);
    }
    S->top++;
    S->data[S->top] = x;
}

//��ջ
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
    printf("�������ַ���:\n");
    while((t=getchar())!='&'){  //ǰ�벿���ַ���ջ
        Push(&S, t);
    }
    
    while((t=getchar())!='@' && S.top != -1){
        Pop(&S, &cmp);
        if(cmp != t){
            printf("���ǻ��Ĵ�!\n");
            return 0;
        }
    }
    if(S.top == -1 && t == '@'){
        printf("�ǻ��Ĵ�!\n");
        return 0;
    }
    else{
        printf("���ǻ��Ĵ�!\n");
        return 0;
    }
}