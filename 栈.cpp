#include<stdio.h> 
#include<stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

//顺序整数栈的静态结构 
unsigned int_stacksize;  //预分配空间大小 
int *int_stacktop_ptr;   //栈顶指针 
int *int_stackbase_ptr;  //栈底指针 

//下面用宏定义操作来实现链表 
//##用于连接前后两个字符串 
//初始化给栈底分配空间
//若分配成功则将栈的大小初始化 
//时间复杂度 O（1） 
#define initStack(stack) stack ## _stackbase_ptr = (stack *)malloc(sizeof(stack)*STACK_INIT_SIZE);\ 
                         if (stack ## _stackbase_ptr){\ 
                             stack ## _stacktop_ptr = stack ## _stackbase_ptr;\
                             stack ## _stacksize = STACK_INIT_SIZE;\
						 }else exit(0)
						 
//判断栈是否为空，是则返回1，否则返回0 
//时间复杂度 O（1）
#define stackEmpty(stack) stack ## _stackbase_ptr == stack ## _stacktop_ptr ? 1:0

//读栈顶元素，用e返回 
//时间复杂度 O（1）
#define getTop(stack,e) stack ## _stackbase_ptr == stack ## _stacktop_ptr ? 0:(e = *(stack ## _stacktop_ptr-1),1)

//将栈清空，栈底指针等于栈顶指针 
//时间复杂度 O（1）
#define clearStack(stack) stack ## _stacktop_ptr = stack ## _stackbase_ptr

//销毁链表，将栈底指针free 
//时间复杂度 O（1）
#define destoryStack(stack) free(stack ## _stackbase_ptr)

//求栈的长度，栈顶指针减去栈底指针 
//时间复杂度 O（1）
#define stackLength(stack) stack ## _stacktop_ptr - stack ## _stackbase_ptr

//将栈顶元素弹出，若栈空则返回0 
#define pop(stack,e) (stack ## _stackbase_ptr == stack ## _stacktop_ptr)? 0:(e =*(--stack ## _stacktop_ptr),1)

//将一个元素压入栈
//若栈的空间不够，则多申请STACKINCREMENT个空间 ，将原栈用realloc函数扩充空间 
//时间复杂度 O（1）
#define push(stack,e) if (stack ## _stacktop_ptr - stack ## _stackbase_ptr >= stack ## _stacksize){\
                      stack ## _stackbase_ptr = (stack *)realloc(stack ## _stackbase_ptr,\
					    (stack ## _stacksize + STACKINCREMENT)*sizeof(stack));\
					  if(! stack ## _stackbase_ptr) exit(0);\
					  stack ## _stacktop_ptr = stack ## _stackbase_ptr + stack ## _stacksize;\
					  stack ## _stacksize += STACKINCREMENT;}\
					  *(stack ## _stacktop_ptr++) = e
					  
//忽略栈的遍历操作（只能对栈顶元素进行操作）					  
					  
//定义字符型和结构体型的栈，只需静态定义结构					  
unsigned char_stacksize;  //预分配空间大小  
char *char_stacktop_ptr;  //栈顶指针 
char *char_stackbase_ptr; //栈底指针 

typedef struct node{
	int data[10];
	float x,y;
}tnode;//定义结构体 

unsigned tnode_stacksize;   //预分配空间大小 
tnode *tnode_stacktop_ptr;  //栈顶指针 
tnode *tnode_stackbase_ptr; //栈底指针 

int main(){
	initStack(int);
	initStack(char);
	initStack(tnode);
	
	int x;
	if(pop(int,x))
	    printf("出栈成功 %d\n",x);
	else
	    printf("栈空，不能出栈\n");//栈空时弹出栈顶元素 
	    
	printf("栈中有%d个元素\n",stackLength(int));//栈空时求栈长 
	
	if(stackEmpty(int))
	    printf("栈空，无法取栈顶\n");
	else
	    if(getTop(int,x))
	        printf("栈顶元素是%d\n",x);//判断栈是否空，若不是则读取栈顶元素 
	        
	push(int,3);
	printf("栈中有%d个元素\n",stackLength(int));//压进一个元素后计算栈长 
	
	push(int,4);
	push(int,5);
	
	printf("栈中有%d个元素\n",stackLength(int));
	
	if(pop(int,x))
	    printf("出栈成功%d\n",x);
	else 
	    printf("栈空，不能出栈\n");//将栈顶元素弹出 
	    
	printf("栈中有%d个元素\n",stackLength(int));
	
	if(stackEmpty(int))
	    printf("栈空，无法取栈顶\n");
	else
	    if(getTop(int,x))
	        printf("栈顶元素是%d\n",x);
	
	clearStack(int);
	
	
}
