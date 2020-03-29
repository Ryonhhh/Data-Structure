#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<queue>
//�����������еĴ��룬��������ʵ�ֶ�����
//����/����/����/��������㷨��ʵ��
//��������������ͺ������У��������������У������������
//��д�ݹ��㷨����������ڵ�������value����С��value֮��
typedef struct btree{
	char id;
	int data=0;
	struct btree *lchild=NULL;
	struct btree *rchild=NULL;
}BNode,*BiTree;

int max=0,min=100;

BiTree BiT;

BiTree structBiTree(BNode a[],BNode b[],int n){//����������������й��������� 
	BNode r,*p;
	int k;
	if(n<=0||a==0||b==0) return NULL;
	r=a[n-1];
	BNode *root=(BNode *)malloc(sizeof(BNode));
	root->data=r.data;
	root->id=r.id;
	for(p=b;p<b+n;p++)
	    if((*p).id==r.id) break;
	k=p-b;//�������ڵ���
	root->lchild=structBiTree(a,b,k);
	root->rchild=structBiTree(a+k,p+1,n-k-1); 
	return root;
}

int firsttraverse(BiTree B){
	if(!B) return 0;
	printf("id:%c data:%d\n",B->id,B->data);
	firsttraverse(B->lchild);
	firsttraverse(B->rchild);
	return 1;
}

int middletraverse(BiTree B){
	if(!B) return 0;
	middletraverse(B->lchild);
	printf("id:%c data:%d\n",B->id,B->data);
	middletraverse(B->rchild);
	return 1;
}

int lasttraverse(BiTree B){
	if(!B) return 0;
    lasttraverse(B->lchild);
	lasttraverse(B->rchild);
	printf("id:%c data:%d\n",B->id,B->data);
	return 1;
}

struct qNode{ //���н�� 
	BNode *ptr;  //���еĽڵ�������������Ƕ���������ָ�� 
	struct qNode *next; //���е���һ����㣬�����ǵ����� 
};

typedef struct queue{
	struct qNode *front;
	struct qNode *rear;
}linkQueue;

int layertraverse(BiTree B){
	std::queue<BNode *>q;
	BNode *front;
	if(B==NULL) return 0;
	q.push(B);
	while(!q.empty()){
		front=q.front();
		q.pop();
		if(front->lchild)
		    q.push(front->lchild);
		if(front->rchild)
		    q.push(front->rchild);
		printf("id:%c data:%d\n",front->id,front->data);
	}
	return 1;
}

int maxmin(BiTree B){
	if(!B) return 0;
	if(B->data>max) max=B->data;
	if(B->data<min) min=B->data;
	maxmin(B->lchild);
	maxmin(B->rchild);
	return 1;
} 

int main(){
	BNode a[20]={},b[20]={};
	int e,minus,i=0;char c;
	printf("����������������У�Сд��ĸ���У�����0 0��β��\n");
	scanf("%c %d",&c,&e);
	while(c!='0'&&e!=0){
		a[i].data=e;
		a[i++].id=c;
		scanf(" %c %d",&c,&e);
	}
	getchar();
	i=0;
	scanf("%c %d",&c,&e);
	while(c!=0&&e!=0){
		b[i].data=e;
		b[i++].id=c;
		scanf(" %c %d",&c,&e);
	}
	BiT=structBiTree(a,b,i); 
	BNode *p=BiT->lchild;
	printf("\n��������Ϊ��\n");
	firsttraverse(BiT);
	printf("\n��������Ϊ��\n");
	middletraverse(BiT);
	printf("\n��������Ϊ��\n");
	lasttraverse(BiT);
	printf("\n��������Ϊ��\n");
	layertraverse(BiT);
	maxmin(BiT);
	minus=max-min;
	printf("\n���ֵ����Сֵ֮��Ϊ��%d",minus);
	return 0;
}

