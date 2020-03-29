//遗传算法：求解优化问题的通用算法
//将问题的解x表示为0-1串，然后搜索最优的二进制串，使得目标函数值f(x)达到最小
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/** 算法参数设置 **/
//定义0-1串的长度，可用于表示解的精度
#define SLEN 101

//定义进化最大代数
#define MAXGEN 200

//变异概率
#define mProb 1/SLEN

//群体大小，假设所有群体大小都一样（可以不一样）
#define PSIZE 10

//一个解的定义
typedef struct {
	int x[SLEN];   //x:解的自变量，0-1串
	double y;      //y=f(x),要优化问题的目标函数值
} Solution;

//定义一个解集/解数组：称之为群体population
Solution pop[PSIZE*2];     //解集，父代和子代都存储在这里，前PSIZE个是父代，后面PSIZE个是子代
Solution *current = pop;             //当前代，也就是父代
Solution *offspring = pop + PSIZE;   //子代解集

//函数声明
void printPop(Solution *p,const char *str);

//将0-1串x解码为实数*xo ,假定整数4bits，SLEN-4bits为小数部分长度
void decode(int *x, double *xo){
    //todo
//整数部分换成10进制
    *xo=x[1]*8+x[2]*4+x[3]*2+x[4];
//小数部分换成10进制
    int i; 
    for(i=5;i<SLEN-5;i++)
        *xo+=x[i]/pow(10,i-4);
    if(x[0]==1) *xo=-*xo; 
    //done
}

//计算y=f(x) ,  0-1串x的长度 SLEN
//例子：求y=x*x-3x+2的最小值 ，假设整数部分4bits，小数部分SLEN-4bits
double func1(int *x){
	double xo;
	decode(x,&xo);  //将0-1串x解码成真正的解xo
	return xo*xo-3*xo+2;	 //计算目标函数值
}

//计算一个群体的所有解的目标函数值y ，给出了函数指针，支持个函数的优化
void evaluate(Solution *P, double (*ptrf)(int *ptr)){
    //todo
    int i=0;
    for(;i<PSIZE;i++)
        P[i].y=func1(P[i].x); 
    //y=f(x)
    //done
}

//算法初始化：分配两个解集所需的空间，随机生成currentPop中的解，并计算其y值
void initialize(){
	for(int i=0;i<PSIZE;++i)      //遍历currentPop.pop中每个解
		for(int j=0;j<SLEN;++j)  //对每个解的0-1串，随机生成
			current[i].x[j] = rand()%2;
	evaluate(current,func1);
}

//从父代中选择两个解，通过杂交生成两个子代个体
//父代两个解通过PK选择出来（锦标选择）
void crossover(){ //交叉算子
	int k1,k2,f1,f2,k=0,i,divide;
	while (k<PSIZE){   //逐步生成子代，一次两个
        //todo
        //随机选择两个父代个体
        k1=rand()%PSIZE; k2=rand()%PSIZE;
        //随机确定父代个体染色体交换位点
        //交换交叉位点前面的两个子串
        divide=rand()%SLEN;
        for(i=0;i<divide;i++){
        	offspring[k].x[i]=current[k1].x[i];
        	offspring[k+1].x[i]=current[k2].x[i];
		}
        for(i=divide;i<SLEN;i++){
        	offspring[k].x[i]=current[k2].x[i];
        	offspring[k+1].x[i]=current[k1].x[i];
		}
		k = k+2;
		//done
	}
}

//对offspring中的个体进行变异：变异概率为mProb
//所谓变异就是x[j]的取值 0-1互换： 0 <--> 1
void mutate(){ //变异算子
	for(int i=0;i<PSIZE;++i)
		for(int j=0;j<SLEN;++j)
			if ((rand()%10000)/10000.0<mProb)
				(offspring[i].x[j]==0)?offspring[i].x[j]=1:offspring[i].x[j]=0;
}

//从currentPop和offspring中选择下一代个体，有多种选择算法，但是通常都是先把两个群体中最好的保留下来 ，然后
//方法1：选择最好的PSIZE个为下一代（截断选择）
//方法2：给每个个体一个选择概率，y值小（好）的被选择的概率就高，然后依据此概率分布随机采样PSIZE个
//方法3：锦标选择，随机选择k个，相互pk，留下最好的放入下一代，依次选择PSIZE个 （不删除被选择了的）
void select(int k){ //选择算子 ：采用锦标选择
	double besty;   //锦标赛选出来的子代的y值
	int best;       //锦标赛选择出来的子代下标
	Solution tmp[PSIZE];
	for(int i=0;i<PSIZE;++i){ //一个一个子代选择
        //todo: 从pop[2*psize]中用方法1或2或3选择一个适应度值（y值）好的
        best=(current[i].y>current[i+PSIZE].y)?i+PSIZE:i;
        //done
		memcpy(&(tmp[i]),&(pop[best]),sizeof(Solution)); //选择出来的解，复制到临时解集中
	}
	memcpy(current,tmp,sizeof(Solution)*PSIZE);
}

//输出群体的信息
void printPop(Solution *p,const char *str){
	printf("%s/解集信息如下: \n",str);
	for (int i=0;i<PSIZE;++i){
		printf("个体 %3d : y=%10.6lf=f(",i,p[i].y);
		for (int j=0;j<SLEN;++j)
			printf("%d",p[i].x[j]);
		printf(")\n");
	}
}

int main(){
	int seed = 991;
	srand(seed); //设置随机数种子，使得算法结果可以重现
	initialize();
	printf("第 %d 代 ",0);
	printPop(current,"当前群体");
	for(int gen=1;gen<MAXGEN;gen++){
		crossover();
		mutate();
		evaluate(offspring,func1);
		select(2);
		//printf("第 %d 代 ",gen);
		//printPop(current,"当前群体");
	}
	printf("第 %d 代 ", MAXGEN);
	printPop(current,"最终群体");
	return 1;
}
