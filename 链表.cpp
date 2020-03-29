#include<stdio.h>
#include<stdlib.h>

#define Elemtype int//�궨�����ݵ��������� 

#define _DEBUG_ 1//ѡ���Ƿ���_DEBUG_������ifdef-endif��� 


typedef struct Lnode{
	Elemtype data;
	struct Lnode *next;
}LinkNode,*LinkList;//��������Ľṹ���Լ��ṹ��ָ�� 


LinkNode *first;//����ȫ�ֱ����Ľṹ��ָ�� 

LinkNode *initList(){
	LinkNode *p= (LinkNode *)malloc(sizeof(LinkNode));
	if(!p){
		printf("��ʼ������ͷ���ʧ�ܣ�\n");
		exit(0); 
	}
	p->next = NULL;
	return p;
}
//��ʼ��һ��������ָ��p����һ���ռ䲢������Ϊ����ֵ����
//ʱ�临�Ӷ� O��1�� 

#ifdef _DEBUG_

LinkNode head;

void initListW(LinkNode *p){
	p = (LinkList)malloc(sizeof(LinkNode));
	if(!p){
		printf("��ʼ������ͷ���ʧ��\n");
		exit(0);
	}
	p->next = NULL;
}
//���ַ�����ʼ�������Ǵ���ģ���Ϊmain�����д�������ָ��ĵ�ֵַ��δ���޸ģ���pָ������˿ռ�֮���޷�����main���� 
//ʱ�临�Ӷ� O��1��

void initList2(){
	first = &head;
	first->next = NULL;
}
//��������ȫ�ֱ�������ʼ������ 
//ʱ�临�Ӷ� O��1��
#endif

int ListLength(LinkList p){
	int count = 0;
	while(p->next != NULL){
		count++;
		p=p->next;
	}
	return count;
}
//�����������pָ��ָ���nextΪ��ʱ�˳�ѭ����ʾ��������β�� 
//ʱ�临�Ӷ� O��n��

int ListEmpty(LinkList p){
	if(p->next != NULL)
	  return 1;
	return 0;
}
//�ж������Ƿ�Ϊ������������򷵻�1�����򷵻�0 
//ʱ�临�Ӷ� O��1��

void ClearList(LinkList p){
	LinkNode *q;
	while(p->next != NULL){
		q=p->next;
		p->next=q->next;
		free(q);
	}
}
//��������գ���������ָ�������֤ÿһ���ڵ㶼�ܱ�free 
//ʱ�临�Ӷ� O��n��

void DestroyList(LinkList p){
	ClearList(p);
	free(p);
}//���������ֽ�������գ��ٽ�ͷָ��free 
//ʱ�临�Ӷ� O��n��

int GetElem(LinkList p, int i, Elemtype *e){
	int k = 0;
	while(p=p->next){//��p->next == NULL��ѭ���������ʲ���дѭ������������ 
		k++;
		if(k==i){
			*e = p->data;
			return k;
		}
	}
	return 0;
}
//����һ���ص㣬��e��������ص�� dataֵ 
//ʱ�临�Ӷ� O��n��

LinkNode *LocateElem(LinkList p, Elemtype e){
	while(p=p->next){
		if(p->data == e)
		    return p;
	}
	return NULL;
}
//����һ��dataֵ�����������д����򷵻����ĵ�ַ�����������򷵻�NULL 
//ʱ�临�Ӷ� O��n��

LinkNode *PriorElem(LinkList p, LinkNode *cur_e){
	for(;p->next;p=p->next)
	    if(p->next == cur_e)
	        return p;
	return NULL;
}
//��һ������ڵ��ǰ����������ָ������¼��ǰ�ڵ����һ�ڵ� 
//ʱ�临�Ӷ� O��n��

LinkNode *NextElem(LinkList p, LinkNode *cur_e){
	return cur_e->next;
}
//���ظ����ڵ�ĺ�̽ڵ� 
//ʱ�临�Ӷ� O��1��

LinkNode *ListInsert(LinkList p, int i, Elemtype e){
	if(i<1)  return NULL;//������λ�ò������򷵻�NULL 
	for(;p;p=p->next)
	    if(--i<1){//������ָ��λ��ʱ 
	    	LinkNode *q = (LinkNode *)malloc(sizeof(LinkNode));//����ռ� 
	    	if(!q){
	    		printf("����ڵ�ʱ������ռ�ʧ��\n");
	    		exit(0);
			}
			q->next = p->next;
			p->next = q;
			q->data = e;//��������λ�õ�ǰ��ڵ��nextָ�벢���ز���Ľڵ� 
			return q;
		}
	return NULL;//������λ�ó�����ǰ������ 
}
//�ڸ���λ�ò���һ���½ڵ� 
//ʱ�临�Ӷ� O��n��

int ListDelete(LinkList p, int i, Elemtype *e){
	if (i<1) return 0;
	LinkNode *q=p;
	for(p=p->next;p;p=p->next){
		if(--i<1){//����ָ��λ�� 
			q->next = p->next;
			*e = p->data;//��e����ɾ����data 
			free(p);
			return 1;
		}
		q=p;
	}
	return 0;//������λ�ó�����ǰ������ 
}
//ɾ������λ�õĽڵ� 
//ʱ�临�Ӷ� O��n��

void PrintLinkNode(LinkNode *p){
	printf("%d,",p->data);
}
//��ӡ��ǰ�ڵ�dataֵ 
//ʱ�临�Ӷ� O��1��

void Add2(LinkNode *p){
	p->data += 2;
	printf("+2,");
}
//����ǰ�ڵ�data+2
//ʱ�临�Ӷ� O��1��

void DebugLinkNode(LinkNode *p){
	printf("���-(*addr)=value: ");
	printf("(*%lx)=%d\n",p,p->data); 
}
//��ӡ��ǰ�ڵ�ĵ�ֵַ��16���ƣ���dataֵ 
//ʱ�临�Ӷ� O��1��

void ListTraverse(LinkList p, void (*ptrFunc)(LinkNode *ptr)){
	printf("������=%d����\n",ListLength(p));
	while(p=p->next)
	    (*ptrFunc)(p);//ѭ�������������ptrFunc��ָ��ĺ������� 
	printf("\n");
}
//��ӡ����ı� 
//ʱ�临�Ӷ� O��n��

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
	printf("ȡ����֮ǰ %d --",ei);
	GetElem(first,10,&ei);
	printf("��ȡ������Ϊ %d\n",ei);
	
	LinkNode *q = LocateElem(first,888);
	if(!q)
	    printf("û���ҵ�ֵ����Ӧ�ĵ�\n");
	else{
		q = PriorElem(first,q);
		printf("�ҵ�����ǰ��Ϊ%d -- ",q->data);
		printf("�ҵ����Ϊ %d -- ",q->next->data);
		if(q->next->next)
		    printf("�ҵ����ĺ��Ϊ %d",NextElem(first,NextElem(first,q))->data);
		printf("\n");
	}
	
	printf("ɾ��ǰ��ֵ %d -- ",ei);
	if(ListDelete(first,15,&ei)>0)
	    printf("ɾ����ֵΪ %d\n",ei);
	else
	    printf("ɾ��ʧ�� %d \n",ei);
	    
	ListTraverse(first,ptrFunc);
	printf("ɾ��ǰ��ֵ %d --",ei);
	if (ListDelete(first,6,&ei)>0)
	    printf("ɾ����ֵΪ %d \n",ei);
	else 
	    printf("ɾ��ʧ�� %d\n",ei);
	ListTraverse(first,ptrFunc);
	
	ptrFunc = Add2;
	printf("ÿ������Ԫ��׼��+2\n");
	ListTraverse(first,ptrFunc);
	printf("���+2���µ�����");
	ListTraverse(first,PrintLinkNode);
	
	DestroyList(first);
	
	return 0; 
}










