#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<queue>
//读懂代码框架中的代码，二叉链表实现二叉树
//先序/中序/后序/层序遍历算法的实现
//给定二叉树中序和后序序列（存在两个数组中），构造二叉树
//编写递归算法，求二叉树节点中最大的value和最小的value之差
typedef struct btree{
	char id;
	int data=0;
	struct btree *lchild=NULL;
	struct btree *rchild=NULL;
}BNode,*BiTree;

int max=0,min=100;

BiTree BiT;

BiTree structBiTree(BNode a[],BNode b[],int n){//中序序列与后序序列构建二叉树 
	BNode r,*p;
	int k;
	if(n<=0||a==0||b==0) return NULL;
	r=a[n-1];
	BNode *root=(BNode *)malloc(sizeof(BNode));
	root->data=r.data;
	root->id=r.id;
	for(p=b;p<b+n;p++)
	    if((*p).id==r.id) break;
	k=p-b;//左子树节点数
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

struct qNode{ //队列结点 
	BNode *ptr;  //队列的节点包括的数据域是二叉树结点的指针 
	struct qNode *next; //队列的下一个结点，队列是单链表 
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
	printf("请输入后序及中序序列（小写字母序列），以0 0结尾：\n");
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
	printf("\n先序序列为：\n");
	firsttraverse(BiT);
	printf("\n中序序列为：\n");
	middletraverse(BiT);
	printf("\n后序序列为：\n");
	lasttraverse(BiT);
	printf("\n层序序列为：\n");
	layertraverse(BiT);
	maxmin(BiT);
	minus=max-min;
	printf("\n最大值与最小值之差为：%d",minus);
	return 0;
}

