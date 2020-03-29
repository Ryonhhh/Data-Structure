//图的创建、删除顶点、增加顶点、增加边、删除边、查找顶点、修改边或顶点
//图的存储结构自行设计，同时设计实现一个复杂操作，验证上述基本操作，并说明采该存储结构实现这个复杂操作是否合适
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
	int w;                         //顶点权 
	int id;                        //顶点编号
}Ver; 

typedef struct vdeg{
	int id;                       //出边所连顶点 
	int w;                        //出边权 
	struct vdeg *nextarc;         //下一邻接边         
}Vdeg;

typedef struct ver{
	int id;                        //顶点编号 
	Vdeg *firstarc;                //邻接头结点 
	struct ver *nextVer;           //下一节点         
}vertex;

vertex *head;//邻接链表头结点 
Ver V[N];//顶点权表 
int VerNum=0;

void CreateGraph(){
	printf("请依次输入顶点及其权,以0 0结束\n");
	int v=0,w,i,vv;
	scanf("%d %d",&v,&w);
	while(v!=0&&w!=0){
		V[VerNum].id=v;
		V[VerNum].w=w; 
		scanf("%d %d",&v,&w);
		VerNum++;
	}
	printf("请依次输入顶点的连边情况，以-1结束");
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
		printf("请输入出边所连顶点和边权，以0 0结束");
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

void ReavelGraph(){//显示图
    int i,k=0;
    printf("顶点权值:\n");
    for(i=0;k<VerNum;i++)
        if(V[i].w!=0){
            printf("id:%d weight:%d\n",V[i].id,V[i].w);
            k++;
		}
	printf("顶点连边情况:\n");
	vertex *p=head->nextVer;
	Vdeg *q;
	for(;p!=NULL;p=p->nextVer){
		printf("顶点%d连边：",p->id);
		for(q=p->firstarc->nextarc;q!=NULL;q=q->nextarc)
		    printf("id:%d weight:%d ",q->id,q->w);
		printf("\n");
	}
}

int DeleteVer(){//删除顶点 (顶点权置零，入边权置零)
    printf("请输入想删除的顶点编号:");
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
	}//从顶点数组中删除
	if(flag){
		printf("该顶点不存在!");
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

int AddVer(){//增加顶点 
    int i,k=0,v,w;
    printf("请输入顶点的编号和权值:");
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

int DeleteArc(){//删除边 
    printf("请输入边的头结点与尾结点编号:");
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

int AddArc(){//增加边 
    printf("请输入加入边的权值，头结点，尾结点");
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

int SearchVer(){//查找顶点 
    printf("请输入想查找的顶点:");
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
	    printf("不存在！");
	    getchar();
	    getchar();
	    return 0;
	}*/
    vertex *p=head->nextVer;
    for(;p->id!=v;p=p->nextVer);
    Vdeg *q=p->firstarc->nextarc;
    for(;q!=NULL;q=q->nextarc)
        printf("出边所连顶点:%d 权值:%d\n",q->id,q->w);
    p=head->nextVer;
	for(;p!=NULL;p=p->nextVer)
		for(q=p->firstarc->nextarc;q!=NULL;q=q->nextarc)
		    if(q->id==v)
		        printf("入边所连顶点:%d 权值:%d\n",p->id,q->w);
	return 0;
}

int CorrectVer(){//修改顶点 
    printf("请输入想要修改的顶点:");
    int i,v,w,k=0;
    scanf("%d",&v);
    printf("请输入修改的权值:");
    scanf("%d",&w);
    for(i=0;k<VerNum;i++)
       if(V[i].id!=0){
       	    if(V[i].id==v)
       	        V[i].w=w;
       	    k++;
	   }
	return 0;
}

int CorrectArc(){//修改边 
    printf("请输入边的出顶点和入顶点:");
    int cv,rv,flag=0,w;
    scanf("%d %d",&cv,&rv);
    vertex *p=head->nextVer; Vdeg *q=p->firstarc;
    for(;p!=NULL;p=p->nextVer){
    	if(p->id==cv){
    		for(q=p->firstarc->nextarc;q!=NULL;q=q->nextarc){
    			if(q->id==rv){
    			    flag=1;
    			    printf("请输入想要修改的权值:");
    			    scanf("%d",&w);
    			    q->w=w;
    			    return 1;
    			}
			}
		}
	}
	if(!flag) printf("无此边！");
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

void wildtraverse(){//广度优先遍历 
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

int traverse(){//图的遍历 
    printf("研究图的遍历时将其视为无向图\n");
    reveal2();
    printf("\n广度优先遍历序列为:"); 
    wildtraverse();
    getchar();
    getchar();
}

int main(){
	int chose,arc,ver;
	printf("/***图操作器***/\n");
	CreateGraph();
	printf("1.显示图\n2.删除顶点\n3.增加顶点\n4.删除边\n5.增加边\n6.查找顶点\n7.修改顶点\n8.修改边\n9.图的遍历\n0.退出"); 
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
		printf("1.显示图\n2.删除顶点\n3.增加顶点\n4.删除边\n5.增加边\n6.查找顶点\n7.修改顶点\n8.修改边\n9.图的遍历\n0.退出"); 
		scanf("%d",&chose);
	} 
	return 0;
}
