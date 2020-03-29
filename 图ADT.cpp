//ͼ�Ĵ�����ɾ�����㡢���Ӷ��㡢���ӱߡ�ɾ���ߡ����Ҷ��㡢�޸ı߻򶥵�
//ͼ�Ĵ洢�ṹ������ƣ�ͬʱ���ʵ��һ�����Ӳ�������֤����������������˵���ɸô洢�ṹʵ��������Ӳ����Ƿ����
#include<stdio.h>
#include<vector>
#include<iostream>
#include<stdlib.h>
#include<queue>
#include<stdlib.h>
#define N 100
using namespace std;
queue<int>Q;
int nv[N][N];

typedef struct deg{
	int w;                         //����Ȩ 
	int id;                        //������
}Ver; 

typedef struct vdeg{
	int id;                       //������������ 
	int w;                        //����Ȩ 
	struct vdeg *nextarc;         //��һ�ڽӱ�         
}Vdeg;

typedef struct ver{
	int id;                        //������ 
	Vdeg *firstarc;                //�ڽ�ͷ��� 
	struct ver *nextVer;           //��һ�ڵ�         
}vertex;

vertex *head;//�ڽ�����ͷ��� 
Ver V[N];//����Ȩ�� 
int VerNum=0;

void CreateGraph(){
	printf("���������붥�㼰��Ȩ,��0 0����\n");
	int v=0,w,i,vv;
	scanf("%d %d",&v,&w);
	while(v!=0&&w!=0){
		V[VerNum].id=v;
		V[VerNum].w=w; 
		scanf("%d %d",&v,&w);
		VerNum++;
	}
	printf("���������붥��������������-1����");
	scanf("%d",&vv);
	vertex *p,*lp;
	Vdeg *q,*lq;
	p=(vertex *)malloc(sizeof(vertex));
	p->id=vv; p->nextVer=NULL;
	lp=p;
	head=p; 
	while(vv!=-1){
		p=(vertex *)malloc(sizeof(vertex));
		p->id=vv; p->nextVer=NULL;
		lp->nextVer=p;
		lp=p;
		printf("�����������������ͱ�Ȩ����0 0����");
		scanf("%d %d",&v,&w);
		q=(Vdeg *)malloc(sizeof(Vdeg));
		q->id=v; q->w=w; q->nextarc=NULL;
		p->firstarc=q;
		lq=q;
		while(v!=0&&w!=0){
		    q=(Vdeg *)malloc(sizeof(Vdeg));
		    q->id=v; q->w=w; q->nextarc=NULL;
		    lq->nextarc=q;
		    lq=q;
		    scanf("%d %d",&v,&w);
	    }
	    scanf("%d",&vv);
	} 
	getchar();
	system("cls");
}

void ReavelGraph(){//��ʾͼ
    int i,k=0;
    printf("����Ȩֵ:\n");
    for(i=0;k<VerNum;i++)
        if(V[i].w!=0){
            printf("id:%d weight:%d\n",V[i].id,V[i].w);
            k++;
		}
	printf("�����������:\n");
	vertex *p=head->nextVer;
	Vdeg *q;
	for(;p!=NULL;p=p->nextVer){
		printf("����%d���ߣ�",p->id);
		for(q=p->firstarc->nextarc;q!=NULL;q=q->nextarc)
		    printf("id:%d weight:%d ",q->id,q->w);
		printf("\n");
	}
}

int DeleteVer(){//ɾ������ (����Ȩ���㣬���Ȩ����)
    printf("��������ɾ���Ķ�����:");
	int i,k=0,vnum,flag=1;
	scanf("%d",&vnum);
	for(i=0;k<VerNum;i++){
		if(V[i].id!=0){
			if(V[i].id==vnum){
		        V[i].id=0;
		        V[i].w=0;
		        VerNum--;
		        flag=0;
		        break;
		    }
			k++;
		}
	}//�Ӷ���������ɾ��
	if(flag){
		printf("�ö��㲻����!");
		return -1;
	}
	vertex *p=head->nextVer,*lp=head;
	Vdeg *q=p->firstarc,*lq=p->firstarc;
	for(;p!=NULL;lp=p,p=p->nextVer)
		if(p->id==vnum){
			lp->nextVer=p->nextVer; 
			free(p);
	    }
	for(p=head->nextVer;p!=NULL;p=p->nextVer){
		q=p->firstarc->nextarc;
		if(q->id==vnum){
			p->firstarc->nextarc=q->nextarc;
		}
		else
	        for(q=p->firstarc->nextarc,lq=p->firstarc->nextarc;q!=NULL;){
	    	    if(q->id==vnum){
	    	    	printf("ads");
	    		    lq->nextarc=q->nextarc;
	    		    q=q->nextarc;
	    		}
			    else{
			        lq=q;
				    q=q->nextarc;
			    }
		    }
	}
	return 1;
} 

int AddVer(){//���Ӷ��� 
    int i,k=0,v,w;
    printf("�����붥��ı�ź�Ȩֵ:");
    scanf("%d %d",&v,&w);
    for(i=0;k<VerNum;i++)
    	if(V[i].id!=0) k++;
    VerNum++;
    V[i].id=v; V[i].w=w;
    vertex *p,*q=head->nextVer;
    Vdeg *lq;
    lq=(Vdeg *)malloc(sizeof(Vdeg));
    p=(vertex *)malloc(sizeof(vertex));
    p->id=v;
    p->firstarc=lq;
    p->firstarc->nextarc=NULL;
    p->nextVer=NULL;
    for(;q->nextVer!=NULL;q=q->nextVer);
    q->nextVer=p;
    return 1;
}

int DeleteArc(){//ɾ���� 
    printf("������ߵ�ͷ�����β�����:");
    int c,r,flag=1;
    scanf("%d %d",&c,&r);
    vertex *p=head->nextVer;
    Vdeg *q=p->firstarc,*lq=p->firstarc;
    for(;p!=NULL;p=p->nextVer)
	    if(p->id==c) flag=0;
	if(flag) {
	    printf("ERROR");
		return -1;
    }
    p=head->nextVer;
    for(;p->id!=c;p=p->nextVer) p=p;
    q=p->firstarc->nextarc; lq=p->firstarc;
    flag=1;
    for(;q!=NULL;q=q->nextarc)
	    if(q->id==r) flag=0;
	if(flag) {
	    printf("ERROR");
		return -1;
    }
    q=p->firstarc->nextarc;
    for(;q->id!=r;lq=q,q=q->nextarc);
    lq->nextarc=q->nextarc;
}

int AddArc(){//���ӱ� 
    printf("���������ߵ�Ȩֵ��ͷ��㣬β���");
    int w,c,r;
    scanf("%d %d %d",&w,&c,&r);
    vertex *p=head->nextVer;
	Vdeg *q,*lq;
	q=(Vdeg *)malloc(sizeof(Vdeg));
    q->id=r;
    q->w=w;
    q->nextarc=NULL;
    for(;p->id!=c;p=p->nextVer);
    for(lq=p->firstarc;lq->nextarc!=NULL;lq=lq->nextarc);
    lq->nextarc=q;
    return 1;
}

int SearchVer(){//���Ҷ��� 
    printf("����������ҵĶ���:");
    int v,i,k=0,flag=1;
    scanf("%d",&v);
    /*for(i=0;k<VerNum;i++){
    	if(V[i].id!=0){
    	    if(V[i].id==v)
    	        flag=0;
    	        k++;
    	    }
	}
	if(flag){
	    printf("�����ڣ�");
	    getchar();
	    getchar();
	    return 0;
	}*/
    vertex *p=head->nextVer;
    for(;p->id!=v;p=p->nextVer);
    Vdeg *q=p->firstarc->nextarc;
    for(;q!=NULL;q=q->nextarc)
        printf("������������:%d Ȩֵ:%d\n",q->id,q->w);
    p=head->nextVer;
	for(;p!=NULL;p=p->nextVer)
		for(q=p->firstarc->nextarc;q!=NULL;q=q->nextarc)
		    if(q->id==v)
		        printf("�����������:%d Ȩֵ:%d\n",p->id,q->w);
	return 0;
}

int CorrectVer(){//�޸Ķ��� 
    printf("��������Ҫ�޸ĵĶ���:");
    int i,v,w,k=0;
    scanf("%d",&v);
    printf("�������޸ĵ�Ȩֵ:");
    scanf("%d",&w);
    for(i=0;k<VerNum;i++)
       if(V[i].id!=0){
       	    if(V[i].id==v)
       	        V[i].w=w;
       	    k++;
	   }
	return 0;
}

int CorrectArc(){//�޸ı� 
    printf("������ߵĳ�������붥��:");
    int cv,rv,flag=0,w;
    scanf("%d %d",&cv,&rv);
    vertex *p=head->nextVer; Vdeg *q=p->firstarc;
    for(;p!=NULL;p=p->nextVer){
    	if(p->id==cv){
    		for(q=p->firstarc->nextarc;q!=NULL;q=q->nextarc){
    			if(q->id==rv){
    			    flag=1;
    			    printf("��������Ҫ�޸ĵ�Ȩֵ:");
    			    scanf("%d",&w);
    			    q->w=w;
    			    return 1;
    			}
			}
		}
	}
	if(!flag) printf("�޴˱ߣ�");
	getchar();
	getchar();
	return 0;
}

void reveal2(){
	vertex *p=head->nextVer; Vdeg *q=p->firstarc;
	int i=0,j=0,k=0,l=0;
	for(;i<N;i++)
	    for(;j<N;j++)
	        nv[i][j]=0;
	for(;p!=NULL;p=p->nextVer)
	    for(q=p->firstarc->nextarc;q!=NULL;q=q->nextarc){
	        nv[p->id][q->id]=1;
	        nv[q->id][p->id]=1;
	    }
	for(i=0;k<VerNum;i++){
		if(V[i].w!=0){
			k++;
			printf("%d :",V[i].id);
		    for(j=0,l=0;l<VerNum;j++)
			    if(V[j].w!=0){
			        printf("%d ",nv[V[i].id][V[j].id]);
			        l++;
			    }
		}
		printf("\n");
	}
}

void wildtraverse(){//������ȱ��� 
    int i,j,k,m,l;
    int visited[N];
    for(i=0;i<N;i++)
           visited[i] = 0; 
        for(i=1;k<VerNum-2;i++)
        {
        	if(V[i].id!=0){
			k++;
        if (!visited[V[i].id]) 
        {
            visited[V[i].id]=1;
            printf("%d ", V[i].id);
            Q.push(V[i].id);
            while(!Q.empty()) 
            {
                m=Q.front();
				Q.pop();
				for(l=0;l<N;l++) if(V[l].id==m) i=l;
                for(j=0;j<VerNum;j++) 
                { 
                    if(nv[V[i].id][V[j].id]==1 && !visited[V[j].id]) 
                    { 
                         visited[V[j].id]=1;
                        printf("%d ",V[j].id);
                        Q.push(V[j].id);
                    } 
                } 
            }
        }
    }
	}
}

int traverse(){//ͼ�ı��� 
    printf("�о�ͼ�ı���ʱ������Ϊ����ͼ\n");
    reveal2();
    printf("\n������ȱ�������Ϊ:"); 
    wildtraverse();
    getchar();
    getchar();
}

int main(){
	int chose,arc,ver;
	printf("/***ͼ������***/\n");
	CreateGraph();
	printf("1.��ʾͼ\n2.ɾ������\n3.���Ӷ���\n4.ɾ����\n5.���ӱ�\n6.���Ҷ���\n7.�޸Ķ���\n8.�޸ı�\n9.ͼ�ı���\n0.�˳�"); 
	scanf("%d",&chose);
	while(chose){
		switch(chose){
			case 1:
				ReavelGraph();
				getchar();
				getchar();
				break;
			case 2:
				DeleteVer();
				break;
			case 3:
				AddVer();
				break;
			case 4:
				DeleteArc();
				break;
			case 5:
				AddArc();
				break;
			case 6:
				SearchVer();
				getchar();
				getchar();
				break;
			case 7:
				CorrectVer();
				break;
			case 8:
				CorrectArc();
				break;
			case 9:
			    traverse();
				break;
			default:
				break;
			
		}
		system("cls");
		printf("1.��ʾͼ\n2.ɾ������\n3.���Ӷ���\n4.ɾ����\n5.���ӱ�\n6.���Ҷ���\n7.�޸Ķ���\n8.�޸ı�\n9.ͼ�ı���\n0.�˳�"); 
		scanf("%d",&chose);
	} 
	return 0;
}
