#include<stdio.h>
#include<stdlib.h>
#define n 100
#include<math.h>

char a[n]={},b[n]={},c[n]={};//ԭʼ���� (����λ.С��λ) 
int num1[n]={},num2[n]={},num3[225]={};//ת�����ʮ�������� (0Ϊ����λ��1Ϊ����λ��2-21Ϊ����λ��22-83ΪС��λ,����λ-����λ-��-1��-����-С��-��-1��)
int Num[225]={};//����ת����� 
 
typedef struct pnode{
	int coe[n];
	int exp;
	struct pnode *next=NULL;
}PNode; 
 
PNode *P;

PNode *initPolyn(){
	PNode *s;
	s=(PNode *)malloc(sizeof(PNode));
	if(!s){
		printf("����ʧ�ܣ�\n");
		exit(0);
	}
	return s;
} 
 
void initChange(char A[],int num[]){
	int i=0,j=0,k;//iΪ��ȡָ�� 
	for(i=0;i<100;i++) num[i]=-1; i=0;
	int numnum[25]={};
	if(A[0]=='-') {num[0]=0;i=1;} else num[0]=1;
	num[1]=10;
	for(;A[i]!='.'&&A[i]!='\0';i++)
		numnum[j++]=A[i]-48;
	numnum[j]=-1;
	for(j=22-j,k=0;numnum[k]!=-1;k++)
	    num[j++]=numnum[k];
	for(i++,j=22;A[i]!='\0';i++)
	    num[j++]=A[i]-48;
}

void Reveal(int num[]){
	int flag=1;
	if(num[1]==0) printf("=NULL");
	else{
	    int i;
	    printf("(%d����:)",num[1]);
	    if(num[0]==0) printf("-");
	    if(num[1]<=10){
	        for(i=2;i<22;i++) if(num[i]!=-1) {
		        printf("%d",num[i]);
		        flag=0;
		    }
	        if(flag) printf("0");
	        if(num[22]!=-1)
	            printf(".");
	        for(i=22;num[i]!=-1&&i<225;i++) printf("%d",num[i]);
	    }
	    if(num[1]>10){
            for(i=2;i<22;i++) if(num[i]!=-1) {
		        printf("%d ",num[i]);
		        flag=0;
		    }
	        if(flag) printf("0");
	        if(num[22]!=-1)
	            printf(".");
	        for(i=22;num[i]!=-1&&i<225;i++) printf("%d ",num[i]);
		}
}
}
 
int Demicalchange(int N,int nnum[]){
	int zsw=0,i,j,k;
	int num[100]={};
	for(i=0;i<100;i++) num[i]=nnum[i];
	for(i=0;i<225;i++) Num[i]=-1;
	int NumNum[25]={};
	printf("ת��ǰΪ%d����",num[1]);
	printf("ת����Ϊ:");
	Num[1]=N; Num[0]=num[0];
	for(i=21;num[i]!=-1;i--)  zsw+=num[i]*(int)(pow(10,21-i));//����zsw������ֵ 
	for(j=0;zsw!=0;j++){
		NumNum[j]=zsw%N;
		zsw=zsw/N;
	}
	for(i=21,k=0;k<j;i--)
	    Num[i]=NumNum[k++];//����λת�����
	
	int jw=0,aa;
	for(i=22;i<225&&num[22]!=-1;i++){
		jw=0;
		for(j=22;num[j]!=-1;) j++; j--;
		for(;num[j]==0&&j>21;) {
		    num[j]=-1;
			j--;
		}
		for(;j>21;j--){
			aa=num[j];
		    num[j]=(num[j]*N+jw)%10;
		    jw=(aa*N+jw)/10;
		}
		Num[i]=jw;
	}//С��λת����� 
	
	Reveal(Num);
} 

void gjdAdd(int A[],int B[],int num[]){
	int jw=0,xws1,xws2,zsw1,zsw2,max,min,i;
	int AA[225]={},BB[225]={};
	for(i=0;i<225;i++) {
		AA[i]=-1;
		BB[i]=-1;
	} 
	for(i=0;i<100;i++){
		AA[i]=A[i];
		BB[i]=B[i];
	}//�����ӷ���ʱ���� 
	for(i=0;i<225;i++) num[i]=-1;//ˢ�´����� 
    num[1]=10;
	for(xws1=22;AA[xws1]!=-1;xws1++) i=i; xws1--;
	for(xws2=22;BB[xws2]!=-1;xws2++) i=i; xws2--;
	for(zsw1=21;AA[zsw1]!=-1;zsw1--) i=i; zsw1++;
	for(zsw2=21;BB[zsw2]!=-1;zsw2--) i=i; zsw2++;
	if(xws1>=xws2) for(i=xws2+1,max=xws1;i<xws1+1;i++) BB[i]=0;
	if(xws2>xws1) for(i=xws1+1,max=xws2;i<xws2+1;i++) AA[i]=0;
	if(zsw1<=zsw2) {
	    min=zsw1;
	    for(i=zsw2-1;i>zsw1-1;i--) BB[i]=0;
	}
	if(zsw2<zsw1){
		min=zsw2;
		for(i=zsw1-1;i>zsw2-1;i--) AA[i]=0;
	}
	if(AA[0]==BB[0]){
		num[0]=AA[0];jw=0;
	    for(i=max;i>min-1;i--){
		    num[i]=(AA[i]+BB[i]+jw)%10;
		    jw=(AA[i]+BB[i]+jw)/10;
	    }
	    if(jw!=0) num[i-1]=1;
	}
	if(AA[0]!=BB[0]){
		num[0]=AA[0];jw=0;
		for(i=max;i>min-1;i--){
			num[i]=(AA[i]-BB[i]+jw+10)%10;
			if((AA[i]-BB[i]+jw)<0) jw=-1;
			if((AA[i]-BB[i]+jw)>=0) jw=0;
		}
		if(jw!=0) {
			jw=0;
			for(i=0;i<100;i++){
		        AA[i]=A[i];
		        BB[i]=B[i];
	        }//�����ӷ���ʱ���� 
	        for(i=0;i<225;i++) num[i]=-1;num[0]=AA[0];num[1]=10;
	        if(xws1>=xws2) for(i=xws2+1,max=xws1;i<xws1+1;i++) BB[i]=0;
	        if(xws2>xws1) for(i=xws1+1,max=xws2;i<xws2+1;i++) AA[i]=0;
	        if(zsw1<=zsw2) for(i=zsw2-1,min=zsw1;i>zsw1-1;i--) BB[i]=0;
	        if(zsw2<zsw1) for(i=zsw1-1,min=zsw2;i>zsw2-1;i--) AA[i]=0;   //ˢ����Ӽ����� 
			for(i=max;i>min-1;i--){
			    num[i]=(10+BB[i]-AA[i]+jw)%10;
			    if((BB[i]-AA[i]+jw)<0) jw=-1;
			    if((BB[i]-AA[i]+jw)>=0) jw=0;
		    }
		    num[0]=1-num[0];
		}
	}
	for(i=2;i<22&&num[i]==-1;i++) i=i;
	for(;i<22&&num[i]==0;i++) num[i]=-1; 
}
 
void gjdMinus(int A[],int B[],int num[]){
	B[0]=1-B[0];
	gjdAdd(A,B,num);
	B[0]=1-B[0];
}

void gjdPlus(int A[],int B[],int num[]){
	int numans[225],numex[225];
	int zsw1,zsw2,xws1,xws2,i,j,l,jw=0;
	for(xws1=22;A[xws1]!=-1;xws1++) i=i; xws1--;
	for(xws2=22;B[xws2]!=-1;xws2++) i=i; xws2--;
	for(zsw1=21;A[zsw1]!=-1;zsw1--) i=i; zsw1++;
	for(zsw2=21;B[zsw2]!=-1;zsw2--) i=i; zsw2++;
	for(i=0;i<225;i++)
		numans[i]=-1;
	numans[0]=1;numans[1]=10;numans[21]=0; numex[1]=10; numex[0]=1;
	for(i=xws1;i>zsw1-1;i--){
		for(l=2;l<225;l++) numex[l]=-1;
		jw=0;
		for(j=xws2;j>zsw2-1;j--){
			numex[j+i-21]=(A[i]*B[j]+jw)%10;
			jw=(A[i]*B[j]+jw)/10;
		}
		gjdAdd(numans,numex,numans);
	}
	if(jw!=0) numans[zsw1+zsw2-22]=jw;
	numans[0]=(A[0]==B[0])?1:0;
	for(i=0;i<225;i++) num[i]=numans[i];
}

void Polyn(int N){
	int i;
	int numadd[225]; numadd[0]=1; numadd[1]=10;
	int numplus[225]; numplus[0]=1; numplus[1]=10;
	for(i=2;i<225;i++) {
	    numadd[i]=-1;
	    numplus[i]=-1;
	}
	P=initPolyn();
	printf("�������������ʽϵ����������� 0 -1 ����\n");
	int e; char c[n];
	PNode *s=P,*t=P;
	printf("������ϵ����");
	scanf("%s",c);
	printf("�����������");
	scanf("%d",&e);
	while(e!=-1){
		s=(PNode *)malloc(sizeof(PNode));
		s->exp=e; s->next=NULL;
		t->next=s; t=s;
		initChange(c,s->coe);
		printf("\n");
		for(i=0;c[i]!='\0';i++) c[i]=0;
		printf("������ϵ����");
	    scanf("%s",c);
	    printf("�����������");
	    scanf("%d",&e);
	} 
	printf("����Ķ���ʽΪ��"); 
	for(s=P->next;s!=NULL;s=s->next){
		Reveal(s->coe);
		printf("*x^%d",s->exp);
		if(s->next!=NULL)
		    printf("+");
	}
	printf("\n");
	s=P->next;
	while(s!=NULL){
		for(i=2;i<225;i++)
	        numplus[i]=-1;
	    numplus[0]=1; numplus[1]=10;
		if(s->exp!=0){
		    gjdAdd(num1,numplus,numplus);
		    for(i=0;i<s->exp-1;i++){
			    gjdPlus(num1,numplus,numplus);
		    }
		    gjdPlus(numplus,s->coe,numplus);
		    gjdAdd(numadd,numplus,numadd);
		}
		if(s->exp==0){
			gjdAdd(s->coe,numadd,numadd);
		}
		s=s->next;
	}
	Reveal(numadd);
}


int main(){
	int choise,N,i;
	char x,c3;
	printf("��ӭ!\n1.���ĵ�ǰ��ֵ\n2.����ת��\n3.�Ӽ��˼���\n4.����ʽ��ֵ\n5.��ʾ��ǰ������\n0.�˳�\n");
    scanf("%d",&choise);
    while(choise){
	    switch(choise){
		    case 1:
		    	printf("ѡ��1��2����a��b��ֵ\n1.a\n2.b\n");
		    	scanf("%d",&x);
		    	printf("\n�����룺");
				switch(x){
					case 1:
						for(i=0;a[i]!='\0';i++) a[i]=0;
						scanf("%s",a);
						initChange(a,num1);
						break;
					case 2:
						for(i=0;b[i]!='\0';i++) b[i]=0;
						scanf("%s",b);
						initChange(b,num2);
						break;
					default:
						printf("ERROR");    
						break;
				}
		    	break;
		    case 2:
		    	printf("��������ת���Ľ��ƻ�����");
		    	scanf("%d",&N);
		    	Demicalchange(N,num1);
		    	Demicalchange(N,num2);
		    	getchar();
		    	break;
			case 3:
				printf("\n1.��\n2.��\n3.��\n");
				scanf("%d",&c3);
				switch(c3){
					case 1:
						printf("a+b=");
						gjdAdd(num1,num2,num3);
						Reveal(num3);
						getchar();
						break;
					case 2:
						printf("a-b=");
						gjdMinus(num1,num2,num3);
						Reveal(num3);
						getchar();
						break;
				    case 3:
				    	printf("a*b=");
						gjdPlus(num1,num2,num3);
					    Reveal(num3);
					    getchar();
				        break;
				    default:
				    	break;
				}
				break;
			case 4:
				Polyn(N);
				getchar();
				break;
			case 5:
				Reveal(num1);
				Reveal(num2);
				getchar();
				break;
			case 0:
				break;
			default: 
		 	    printf("ERROR");
			    break;
	    } 	
	    getchar();
	    system("cls");
	    printf("��ӭ!\n1.���ĵ�ǰ��ֵ\n2.����ת��\n3.�Ӽ��˼���\n4.����ʽ��ֵ\n5.��ʾ��ǰ������\n0.�˳�\n");
	    scanf("%d",&choise);
    }
    return 0;
} 
