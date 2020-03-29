#include<stdio.h> 
#include<stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

//˳������ջ�ľ�̬�ṹ 
unsigned int_stacksize;  //Ԥ����ռ��С 
int *int_stacktop_ptr;   //ջ��ָ�� 
int *int_stackbase_ptr;  //ջ��ָ�� 

//�����ú궨�������ʵ������ 
//##��������ǰ�������ַ��� 
//��ʼ����ջ�׷���ռ�
//������ɹ���ջ�Ĵ�С��ʼ�� 
//ʱ�临�Ӷ� O��1�� 
#define initStack(stack) stack ## _stackbase_ptr = (stack *)malloc(sizeof(stack)*STACK_INIT_SIZE);\ 
                         if (stack ## _stackbase_ptr){\ 
                             stack ## _stacktop_ptr = stack ## _stackbase_ptr;\
                             stack ## _stacksize = STACK_INIT_SIZE;\
						 }else exit(0)
						 
//�ж�ջ�Ƿ�Ϊ�գ����򷵻�1�����򷵻�0 
//ʱ�临�Ӷ� O��1��
#define stackEmpty(stack) stack ## _stackbase_ptr == stack ## _stacktop_ptr ? 1:0

//��ջ��Ԫ�أ���e���� 
//ʱ�临�Ӷ� O��1��
#define getTop(stack,e) stack ## _stackbase_ptr == stack ## _stacktop_ptr ? 0:(e = *(stack ## _stacktop_ptr-1),1)

//��ջ��գ�ջ��ָ�����ջ��ָ�� 
//ʱ�临�Ӷ� O��1��
#define clearStack(stack) stack ## _stacktop_ptr = stack ## _stackbase_ptr

//����������ջ��ָ��free 
//ʱ�临�Ӷ� O��1��
#define destoryStack(stack) free(stack ## _stackbase_ptr)

//��ջ�ĳ��ȣ�ջ��ָ���ȥջ��ָ�� 
//ʱ�临�Ӷ� O��1��
#define stackLength(stack) stack ## _stacktop_ptr - stack ## _stackbase_ptr

//��ջ��Ԫ�ص�������ջ���򷵻�0 
#define pop(stack,e) (stack ## _stackbase_ptr == stack ## _stacktop_ptr)? 0:(e =*(--stack ## _stacktop_ptr),1)

//��һ��Ԫ��ѹ��ջ
//��ջ�Ŀռ䲻�����������STACKINCREMENT���ռ� ����ԭջ��realloc��������ռ� 
//ʱ�临�Ӷ� O��1��
#define push(stack,e) if (stack ## _stacktop_ptr - stack ## _stackbase_ptr >= stack ## _stacksize){\
                      stack ## _stackbase_ptr = (stack *)realloc(stack ## _stackbase_ptr,\
					    (stack ## _stacksize + STACKINCREMENT)*sizeof(stack));\
					  if(! stack ## _stackbase_ptr) exit(0);\
					  stack ## _stacktop_ptr = stack ## _stackbase_ptr + stack ## _stacksize;\
					  stack ## _stacksize += STACKINCREMENT;}\
					  *(stack ## _stacktop_ptr++) = e
					  
//����ջ�ı���������ֻ�ܶ�ջ��Ԫ�ؽ��в�����					  
					  
//�����ַ��ͺͽṹ���͵�ջ��ֻ�農̬����ṹ					  
unsigned char_stacksize;  //Ԥ����ռ��С  
char *char_stacktop_ptr;  //ջ��ָ�� 
char *char_stackbase_ptr; //ջ��ָ�� 

typedef struct node{
	int data[10];
	float x,y;
}tnode;//����ṹ�� 

unsigned tnode_stacksize;   //Ԥ����ռ��С 
tnode *tnode_stacktop_ptr;  //ջ��ָ�� 
tnode *tnode_stackbase_ptr; //ջ��ָ�� 

int main(){
	initStack(int);
	initStack(char);
	initStack(tnode);
	
	int x;
	if(pop(int,x))
	    printf("��ջ�ɹ� %d\n",x);
	else
	    printf("ջ�գ����ܳ�ջ\n");//ջ��ʱ����ջ��Ԫ�� 
	    
	printf("ջ����%d��Ԫ��\n",stackLength(int));//ջ��ʱ��ջ�� 
	
	if(stackEmpty(int))
	    printf("ջ�գ��޷�ȡջ��\n");
	else
	    if(getTop(int,x))
	        printf("ջ��Ԫ����%d\n",x);//�ж�ջ�Ƿ�գ����������ȡջ��Ԫ�� 
	        
	push(int,3);
	printf("ջ����%d��Ԫ��\n",stackLength(int));//ѹ��һ��Ԫ�غ����ջ�� 
	
	push(int,4);
	push(int,5);
	
	printf("ջ����%d��Ԫ��\n",stackLength(int));
	
	if(pop(int,x))
	    printf("��ջ�ɹ�%d\n",x);
	else 
	    printf("ջ�գ����ܳ�ջ\n");//��ջ��Ԫ�ص��� 
	    
	printf("ջ����%d��Ԫ��\n",stackLength(int));
	
	if(stackEmpty(int))
	    printf("ջ�գ��޷�ȡջ��\n");
	else
	    if(getTop(int,x))
	        printf("ջ��Ԫ����%d\n",x);
	
	clearStack(int);
	
	
}
