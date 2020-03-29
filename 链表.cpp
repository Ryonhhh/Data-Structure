#include<stdio.h>
#include<stdlib.h>

#define Elemtype int//宏定义数据的数据类型 

#define _DEBUG_ 1//选择是否定义_DEBUG_来调试ifdef-endif语句 


typedef struct Lnode{
	Elemtype data;
	struct Lnode *next;
}LinkNode,*LinkList;//定义链表的结构体以及结构体指针 


LinkNode *first;//定义全局变量的结构体指针 

LinkNode *initList(){
	LinkNode *p= (LinkNode *)malloc(sizeof(LinkNode));
	if(!p){
		printf("初始化分配头结点失败！\n");
		exit(0); 
	}
	p->next = NULL;
	return p;
}
//初始化一个链表，给指针p分配一个空间并将它作为返回值返回
//时间复杂度 O（1） 

#ifdef _DEBUG_

LinkNode head;

void initListW(LinkNode *p){
	p = (LinkList)malloc(sizeof(LinkNode));
	if(!p){
		printf("初始化分配头结点失败\n");
		exit(0);
	}
	p->next = NULL;
}
//这种方法初始化链表是错误的，因为main函数中传进来的指针的地址值并未被修改，而p指针分配了空间之后无法传回main函数 
//时间复杂度 O（1）

void initList2(){
	first = &head;
	first->next = NULL;
}
//利用两个全局变量来初始化链表 
//时间复杂度 O（1）
#endif

int ListLength(LinkList p){
	int count = 0;
	while(p->next != NULL){
		count++;
		p=p->next;
	}
	return count;
}
//求链表表长，当p指针指向的next为空时退出循环表示到达链表尾端 
//时间复杂度 O（n）

int ListEmpty(LinkList p){
	if(p->next != NULL)
	  return 1;
	return 0;
}
//判断链表是否为空链表，如果是则返回1，否则返回0 
//时间复杂度 O（1）

void ClearList(LinkList p){
	LinkNode *q;
	while(p->next != NULL){
		q=p->next;
		p->next=q->next;
		free(q);
	}
}
//将链表清空，利用两个指针变量保证每一个节点都能被free 
//时间复杂度 O（n）

void DestroyList(LinkList p){
	ClearList(p);
	free(p);
}//销毁链表，现将链表清空，再将头指针free 
//时间复杂度 O（n）

int GetElem(LinkList p, int i, Elemtype *e){
	int k = 0;
	while(p=p->next){//若p->next == NULL则循环结束，故不用写循环结束的条件 
		k++;
		if(k==i){
			*e = p->data;
			return k;
		}
	}
	return 0;
}
//输入一个地点，用e返回这个地点的 data值 
//时间复杂度 O（n）

LinkNode *LocateElem(LinkList p, Elemtype e){
	while(p=p->next){
		if(p->data == e)
		    return p;
	}
	return NULL;
}
//输入一个data值，若在链表中存在则返回它的地址，若不存在则返回NULL 
//时间复杂度 O（n）

LinkNode *PriorElem(LinkList p, LinkNode *cur_e){
	for(;p->next;p=p->next)
	    if(p->next == cur_e)
	        return p;
	return NULL;
}
//求一个链表节点的前驱，用两个指针来记录当前节点和上一节点 
//时间复杂度 O（n）

LinkNode *NextElem(LinkList p, LinkNode *cur_e){
	return cur_e->next;
}
//返回给定节点的后继节点 
//时间复杂度 O（1）

LinkNode *ListInsert(LinkList p, int i, Elemtype e){
	if(i<1)  return NULL;//若给定位置不合理则返回NULL 
	for(;p;p=p->next)
	    if(--i<1){//当到达指定位置时 
	    	LinkNode *q = (LinkNode *)malloc(sizeof(LinkNode));//分配空间 
	    	if(!q){
	    		printf("插入节点时，分配空间失败\n");
	    		exit(0);
			}
			q->next = p->next;
			p->next = q;
			q->data = e;//调整插入位置的前后节点的next指针并返回插入的节点 
			return q;
		}
	return NULL;//若给定位置超过当前链表长度 
}
//在给定位置插入一个新节点 
//时间复杂度 O（n）

int ListDelete(LinkList p, int i, Elemtype *e){
	if (i<1) return 0;
	LinkNode *q=p;
	for(p=p->next;p;p=p->next){
		if(--i<1){//到达指定位置 
			q->next = p->next;
			*e = p->data;//用e返回删除的data 
			free(p);
			return 1;
		}
		q=p;
	}
	return 0;//若给定位置超过当前链表长度 
}
//删除给定位置的节点 
//时间复杂度 O（n）

void PrintLinkNode(LinkNode *p){
	printf("%d,",p->data);
}
//打印当前节点data值 
//时间复杂度 O（1）

void Add2(LinkNode *p){
	p->data += 2;
	printf("+2,");
}
//将当前节点data+2
//时间复杂度 O（1）

void DebugLinkNode(LinkNode *p){
	printf("结点-(*addr)=value: ");
	printf("(*%lx)=%d\n",p,p->data); 
}
//打印当前节点的地址值（16进制）和data值 
//时间复杂度 O（1）

void ListTraverse(LinkList p, void (*ptrFunc)(LinkNode *ptr)){
	printf("链表（表长=%d）：\n",ListLength(p));
	while(p=p->next)
	    (*ptrFunc)(p);//循环遍历链表进行ptrFunc所指向的函数操作 
	printf("\n");
}
//打印链表的表长 
//时间复杂度 O（n）

int main(){
	void (*ptrFunc)(LinkNode *p) = DebugLinkNode;
	
	first = initList();
	
	ListTraverse(first,ptrFunc);
	ListInsert(first,1,2);
	ListInsert(first,1,3);
	ListInsert(first,1,4);
	ListInsert(first,1,5);
	ListTraverse(first,ptrFunc);
	ListInsert(first,1,6);
	ListInsert(first,1,7);
	ListInsert(first,1,8);
	ListInsert(first,1,9);
	ListInsert(first,1,666);
	ListInsert(first,1,777);
	ListInsert(first,1,888);
	ListInsert(first,1,999);
	ListTraverse(first,ptrFunc);
	
	Elemtype ei;
	printf("取数据之前 %d --",ei);
	GetElem(first,10,&ei);
	printf("读取的数据为 %d\n",ei);
	
	LinkNode *q = LocateElem(first,888);
	if(!q)
	    printf("没有找到值所对应的点\n");
	else{
		q = PriorElem(first,q);
		printf("找到结点的前驱为%d -- ",q->data);
		printf("找到结点为 %d -- ",q->next->data);
		if(q->next->next)
		    printf("找到结点的后继为 %d",NextElem(first,NextElem(first,q))->data);
		printf("\n");
	}
	
	printf("删除前的值 %d -- ",ei);
	if(ListDelete(first,15,&ei)>0)
	    printf("删除的值为 %d\n",ei);
	else
	    printf("删除失败 %d \n",ei);
	    
	ListTraverse(first,ptrFunc);
	printf("删除前的值 %d --",ei);
	if (ListDelete(first,6,&ei)>0)
	    printf("删除的值为 %d \n",ei);
	else 
	    printf("删除失败 %d\n",ei);
	ListTraverse(first,ptrFunc);
	
	ptrFunc = Add2;
	printf("每个数据元素准备+2\n");
	ListTraverse(first,ptrFunc);
	printf("完成+2后，新的链表：");
	ListTraverse(first,PrintLinkNode);
	
	DestroyList(first);
	
	return 0; 
}










