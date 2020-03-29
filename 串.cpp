#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ERROR -1
#define OK 1
#define MAX_STRLEN 256

typedef struct{
	char str[MAX_STRLEN];
	int length=0;
}StringType;

StringType S[10];

StringType StrAssign1(char chars[]){
	StringType t;
	int i;
	for(i=0;chars[i]!='\0';i++){
		t.length++;
		t.str[i]=chars[i];
	}
	return t;
}

int StrConcat1(int s,int t){
	int i;
	if((S[s].length+S[t].length)>MAX_STRLEN)
	    return ERROR;
	for(i=0;i<S[t].length;i++)
	    S[s].str[S[s].length+i]=S[t].str[i];
	S[s].length+=S[t].length;
	return OK;
}

int SubString1(int s,int pos,int len,int sub){
	int k,j;
	if(pos<0||pos>S[s].length||len<0||len>(S[s].length-pos+1))
	    return ERROR;
	S[sub].length=len;
	for(j=0,k=pos;j<len;k++,j++)
	    S[sub].str[j]=S[s].str[k];
	return OK;
}

int Strcopy1(int s,int t){//��t��copy��s�� 
	int i;
	for(i=0;i<256;i++)
	    S[s].str[i]=0;
	for(i=0;i<=S[t].length;i++)
	    S[s].str[i]=S[t].str[i];
	S[s].length=S[t].length;
	return OK; 
}

int Strcmp1(int s,int t){
	int i,min=(S[s].length>S[t].length?S[t].length:S[s].length);
	for(i=0;i<min;i++)
	    if(S[s].str[i]!=S[t].str[i])
	        return S[s].str[i]-S[t].str[i];
	if(S[s].length>S[t].length) return S[s].str[i];
	if(S[s].length<S[t].length) return -S[t].str[i];
    return 0; 
}

void Reveal1(StringType s){
	int i;
	if(s.str[0]=='\0') printf("NULL");
	else
	    for(i=0;i<s.length;i++)
	        printf("%c",s.str[i]);
	printf(" ");
}

int Replace1(int s,int t,int v){
	int i,j,flag,pos;
	for(pos=0;pos<S[s].length-S[t].length+1;pos++){
		flag=1;
		for(j=pos;j<S[t].length+pos;j++)
		    if(S[s].str[j]!=S[t].str[j-pos]) flag=0;
		if(flag){
			if(S[t].length==S[v].length)
			   for(i=pos;i<S[t].length+pos;i++)
			       S[s].str[i]=S[v].str[i-pos];
			if(S[t].length>S[v].length){
				for(i=pos+S[v].length;i<S[s].length-S[t].length+S[v].length;i++)
					S[s].str[i]=S[s].str[i+S[t].length-S[v].length]; 
				for(i=S[s].length-S[t].length+S[v].length;i<S[s].length;i++)
				    S[s].str[i]=0;
				for(i=pos;i<S[v].length+pos;i++)
				    S[s].str[i]=S[v].str[i-pos]; Reveal1(S[s]);
				S[s].length-=(S[t].length-S[v].length);
			}
			if(S[t].length<S[v].length){
				for(i=S[s].length+S[v].length-S[t].length;i>pos+S[v].length;i--)
					S[s].str[i]=S[s].str[i+S[t].length-S[v].length];
				for(i=pos;i<S[v].length+pos;i++)
				    S[s].str[i]=S[v].str[i-pos];
				S[s].length+=(S[v].length-S[t].length);
			}
			pos+=S[v].length-1;
		}
	}
}

int StrDestroy1(int s){
	int i;
	for(i=0;i<S[s].length;i++)
	    S[s].str[i]=0;
}

int StrClear1(int s){
	int i;
	for(i=0;i<S[s].length;i++)
	    S[s].str[i]=0;
	S[s].length=0;
}

void Strnext1(StringType t,int next[]){
    int i=0;   // P ���±�
    int j=-1;  
    next[0]=-1;
    while (i<t.length){
        if (j==1||t.str[i]==t.str[j]){
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];
    }
}

int KMP1(int s,int t){
	int next[S[t].length+5];
	Strnext1(S[t],next);
    int i = 0;  //S���±�
    int j = 0;  //P���±�
    while (i<S[s].length&& j<S[t].length){
        if (j==-1||S[s].str[i]==S[t].str[j]){//P�ĵ�һ���ַ���ƥ��� S[i]==T[j]
            i++;
            j++;
        }
        else
            j=next[j];//��ǰ�ַ�ƥ��ʧ�ܣ�������ת
    }
    if (j==S[t].length)//ƥ��ɹ�
        return i - j;
    return -1;
}

#define BLOCK_SIZE 4
typedef struct Blstrtype{ 
    char data[BLOCK_SIZE]={}; 
    struct Blstrtype *next=NULL; 
}BNODE,*Blstring;//���㶨�� 

Blstring B[10];

void StrAssign2(Blstring s,char *chars){
	int i,j,k,l,pos=0;
	BNODE *p,*q;
	q=s;
	i=strlen(chars);
	s->data[0]=i;
	j=i/BLOCK_SIZE;
	if(i%BLOCK_SIZE) j++;
	for(k=0;k<j;k++){
		p=(BNODE *)malloc(sizeof(BNODE));
		if(!p) exit(0);
		for(l=0;l<BLOCK_SIZE&&chars[pos]!='\0';l++,pos++)
		    p->data[l]=chars[pos];
		q->next=p;
		q=q->next;
	}
	if(i%BLOCK_SIZE) for(k=i%BLOCK_SIZE;k<BLOCK_SIZE;k++) p->data[k]='@';
	p->next=NULL;
}

int StrConcat2(Blstring s,Blstring t){
	BNODE *p;
	p=s->next;
	while(p->next!=NULL)
	    p=p->next;
	p->next=t->next;
	s->data[0]+=t->data[0];
}

int SubString2(Blstring s,int pos,int len,Blstring t){
	int poss=-1,l=0,i,j,k;
	if(len<0||pos<0||len+pos>s->data[0]) return -1;
	BNODE *p=s->next,*q=t,*r;
	for(i=0;poss!=pos;i++){
		if(i%4==0&&i!=0) p=p->next;
		if(p->data[i%4]!='@') poss+=1;
	}
	i=i-1;//i��λ 
	t->data[0]=len;
	j=len/4;
	if(len%4) j++;
	for(k=0;k<j;k++){
		r=(BNODE *)malloc(sizeof(BNODE));
		for(l=0;l!=4&&k*4+l<len;i++){
			if(i!=0&&i%4==0) p=p->next;
			if(p->data[i%4]!='@') r->data[l++]=p->data[i%4];
		}
		q->next=r;
		q=q->next;
	}
	if(len%BLOCK_SIZE) for(k=len%BLOCK_SIZE;k<BLOCK_SIZE;k++) r->data[k]='@';
	r->next=NULL;
}

int Strcopy2(Blstring s,Blstring t){//��t��copy��s�� 
	SubString2(t,0,t->data[0],s);
}

int Strcmp2(Blstring s,Blstring t){
	Strcopy2(B[5],s);Strcopy2(s,B[5]);Strcopy2(B[5],t);Strcopy2(t,B[5]);
	int min=(s->data[0]>t->data[0]?t->data[0]:s->data[0]),pos;
	BNODE *p=s->next,*q=t->next;
	for(pos=0;pos<min;pos++){
		if(pos!=0&&pos%4==0){
			p=p->next;
			q=q->next;
		}
		if(p->data[pos%4]!=q->data[pos%4]) return p->data[pos%4]-q->data[pos%4];
	}
	if(s->data[0]>t->data[0]){
		if(pos%4==0) p=p->next;
		return p->data[pos%4];
	}
	if(s->data[0]<t->data[0]){
		if(pos%4==0) q=q->next;
		return -q->data[pos%4];
	}
	return 0;
}

int Replace2(Blstring s,int i){
	StrAssign2(s,S[i].str);
}

void next2(Blstring s,int next[]){
	
}

int KMP2(Blstring s,Blstring t){
}

int StrDestroy2(Blstring s){
	s->next=NULL;
	s->data[0]=0;
} 

int StrClear2(Blstring s){
	int i;
	BNODE *p=s->next;
	while(p!=NULL){
		for(i=0;i<BLOCK_SIZE;i++)
		    p->data[i]=0;
		p=p->next;
	}
}

void Reveal2(int s){
	int i,j; 
	BNODE *p=B[s]->next;
	if(B[s]->next==NULL) printf("NULL");
	else{
	    for(;p!=NULL;){
		    for(j=0;j<BLOCK_SIZE;j++)
		        if(p->data[j]!='@') {
		        	printf("%c",p->data[j]);
				}
			p=p->next;
	    } 
	}
	printf(" ");
}

int main(){
	int i,j,k,flag,l,pos;
	for(i=0;i<10;i++) {
	    B[i]=(BNODE *)malloc(sizeof(BNODE));
		B[i]->next=NULL;
	}
	char chars[256];
	printf("��ӭ��������������\n�����������ж���˳��洢��0~4���Ϳ����洢��5~9��\n���漰�������Ĳ������������ͬ�洢�����½���\n1.������\n2.���ٴ�\n3.��մ�\n4.������\n5.�󴮳�\n6.��λ�����Ӵ�\n7.������\n8.���Ƚ�\n9.�Ӵ��滻\n10.KMPģʽƥ��\n11.��ʾ��ǰ��\n0.�˳�\n");
	scanf("%d",&flag);
	while(flag){
		switch(flag){
			case 1:
				printf("�������������λ�ã�\n0~4����˳��洢��len=256��\n5~9�����洢\n");
				scanf("%d",&i);
				printf("�������ַ�����");
				getchar();
				scanf("%s",chars);
				if(i>=0&&i<=4) S[i]=StrAssign1(chars);
				else if(i>=5&&i<=9) {
			 	    StrAssign2(B[i-5],chars);
			 	    S[i]=StrAssign1(chars);
			 	}
				else printf("ERROR");
				for(i=0;chars[i]!='\0';i++) chars[i]=0;
				break;
			case 2:
				printf("�����������ٵĴ���ţ�");
				scanf("%d",&i);
				if(i>=0&&i<=4) StrDestroy1(i);
				else if(i>=5&&i<=9) StrDestroy2(B[i-5]);
				else printf("ERROR");
				break;
			case 3:
				printf("����������յĴ���ţ�");
				scanf("%d",&i);
				if(i>=0&&i<=4) StrClear1(i);
				else if(i>=5&&i<=9) StrClear2(B[i-5]);
				else printf("ERROR");
				break;
			case 4:
				printf("�����������ӵ������������������Ĵ洢��ʽ��ͬ��\n");
				scanf("%d %d",&i,&j);
				if(i>=0&&i<=4&&j>=0&&j<=4) StrConcat1(i,j);
				else if(i>=5&&i<=9&&j>=5&&j<=9) StrConcat2(B[i-5],B[j-5]);
				else printf("ERROR");
				break;
			case 5:
				printf("���������󴮳�����ţ�");
				scanf("%d",&i);
				if(i>=0&&i<=4) printf("%d�Ŵ���Ϊ:%d",i,S[i].length);
				else if(i>=5&&i<=9) printf("%d�Ŵ���Ϊ:%d",i,B[i-5]->data[0]);
				else printf("ERROR");
				getchar();getchar();
				break;
			case 6:
				printf("������������Ӵ�λ�ڵ�������š���ʼλ�á��Ӵ������洢�Ӵ������");
				scanf("%d %d %d %d",&i,&pos,&l,&j);
				if(i>=0&&i<=4&&j>=0&&j<=4) SubString1(i,pos,l,j);
				else if(i>=5&&i<=9&&j>=5&&j<=9) SubString2(B[i-5],pos,l,B[j-5]);
				else printf("ERROR");
				break;
			case 7:
				printf("�������븴�ƵĴ�������Լ��븲�ǵĴ�����ţ�");
				scanf("%d %d",&j,&i);
				if(i>=0&&i<=4&&j>=0&&j<=4) Strcopy1(i,j);
				else if(i>=5&&i<=9&&j>=5&&j<=9) Strcopy2(B[i-5],B[j-5]);
				else printf("ERROR");
				break;
			case 8:
				printf("��������Ƚϵ������������");
				scanf("%d %d",&i,&j);
				if(i>=0&&i<=4&&j>=0&&j<=4) l=Strcmp1(i,j);
				else if(i>=5&&i<=9&&j>=5&&j<=9) l=Strcmp2(B[i-5],B[j-5]);
				else printf("ERROR");
				printf("�ȽϽ��Ϊ%d",l);
				getchar();getchar();
				break;
			case 9:
				printf("���������������滻���Ӵ����滻�Ӵ�����ţ�");
				scanf("%d %d %d",&i,&j,&k);
				if(i>=0&&i<=4&&j>=0&&j<=4&&k>=0&&k<=4) Replace1(i,j,k);
				else if(i>=5&&i<=9&&j>=5&&j<=9&&k>=5&&k<=9) {
				    Replace1(i,j,k);
					Replace2(B[i-5],i);
				}
				getchar();getchar();
				break;
			case 10:
				printf("������ģʽƥ����������Ӵ���ţ�");
				scanf("%d %d",&i,&j);
				if(i>=0&&i<=4&&j>=0&&j<=4) l=KMP1(i,j);
				else if(i>=5&&i<=9&&j>=5&&j<=9) l=KMP1(i,j);
				else printf("ERROR");
				printf("�Ӵ�λ��Ϊ��%d",l);
				getchar(); getchar();
				break;
			case 11:
				for(i=0;i<5;i++)
				    Reveal1(S[i]);
				for(i=5;i<10;i++)
				    Reveal2(i-5);
				getchar();
				getchar();
				break;
			case 0:
				break;
			default: 
			    printf("ERROR");
			    break;
		}
		system("cls");
		printf("��ӭ��������������\n�����������ж���˳��洢��0~4���Ϳ����洢��5~9��\n���漰�������Ĳ������������ͬ�洢�����½���\n1.������\n2.���ٴ�\n3.��մ�\n4.������\n5.�󴮳�\n6.��λ�����Ӵ�\n7.������\n8.���Ƚ�\n9.�Ӵ��滻\n10.KMPģʽƥ��\n11.��ʾ��\n0.�˳�\n");
	    scanf("%d",&flag);
	}
}
#include"pch.h"