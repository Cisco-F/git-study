#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct node{
    char data;
    struct node *next;
}Node, *pStack;

//Enter Stack;
void Push(pStack S, char x)
{
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = x;
    p->next = S->next;
    S->next = p;
}

//Delete From Stack
void Pop(pStack S)
{
    Node *p = S->next;
    S->next = p->next;
    free(p);
}

//Get The Top Mumber
char GetTop(pStack S)
{    
    char ch;
    ch = (S->next)->data;
    return ch;
}

//Match Function
bool Match(char a, char b)
{
    if((a == '[' && b == ']') || (b == '[' && a == ']'))
        return true;
    else if((a == '(' && b == ')') || (b == '(' && a == ')'))
        return true;
    else if((a == '{' && b == '}') || (b == '{' && a == '}'))
        return true;
    else return false;
}

int main()
{
    pStack top;
    top = (pStack)malloc(sizeof(Node));
    top->next = NULL;

    printf("请输入括号表达式:\n");
    char a, tmp;
    while((a = getchar())!='\n'){
        switch(a){
            case '{':
            case '[':
            case '(':
                Push(top, a);
                // {
                //     printf("%c", top->next->data);
                //     if(top->next != NULL)
                //         printf("1");
                // }
                break;
            
            case '}':
            case ']':
            case ')':
                if(top->next == NULL){
                    printf("surplus right\n");
                }
                else{
                    tmp = GetTop(top);
                    if(Match(a, tmp)){
                        // printf("%c %c", a, tmp);
                        Pop(top);
                    }
                    else{
                        printf("Left dose not match right!\n");
                    }
                }
        }
    }
    if(top->next == NULL)
        printf("Left match right!\n");
    else
        printf("surplus left!\n");
    
    return 0;
}