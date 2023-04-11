/*OPTRΪ�����ջ��OVSΪ������ջ*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXSIZE 100

typedef struct stack{
    char data[MAXSIZE];
    int top;
}Stack, *pStack;

//��ʼ��OPTRջ
void Init_Stack(pStack S)
{
    S->top = -1;
}

//�жϽ��ĸ�ջ ����1��OVSջ������0��OPTRջ
bool catagory(char a)
{
    if(a >= '0' && a < '9')
        return true;
    else if(a == '+' || a == '-' || a == '*' || a == '/')
        return false;
    else{
        printf("�Ƿ��������ʽ!");
        exit(0);
    }
    
}

//��ջ
bool Push(pStack S, char a)
{
    if(S->top == -1)
        return false;
    S->top++;
    S->data[S->top] = a;
    return true;
}

//��ջ
bool Pop(pStack S, char *a)
{
    if(S->top == -1)
        return false;
    *a = S->data[S->top];
    S->top--;
}

//��ȡOPTRջ��Ԫ��
bool GetTop(pStack S, char *a)
{
    if(S->top == -1)
        return false;
    *a = S->data[S->top];
}

//��������ȼ��Ƚ� ջ�����������ȼ����򷵻�1
int Cmp(pStack S, char a)//aΪ���Ƚ��������bΪջ��������
{
    char *b;
    int cmp;
    GetTop(S, b);
    switch(*b)
    {
        case '+': case '-':
            if(a == '*' || a == '/')
                cmp = 0;
            else
                cmp = 1;
            break;
        case '*': case '/':
            cmp = 1;
            break;
    }
    return cmp;
}

int main()
{
    Stack OPTR;    Init_Stack(&OPTR);
    Stack OVS;      Init_Stack(&OVS);

    printf("�������������������ʽ:");
    char x;
    while(x = getchar() != '\n'){
        if(catagory(x)){
            Push(&OVS, x);
        }
        else
        {
            if(OPTR.top == -1)
                Push(&OPTR, x);
            else
            {
                switch(Cmp(&OPTR, x)){
                    case 0:
                        Push(&OPTR, x);

                }
            }
        }
    }
}