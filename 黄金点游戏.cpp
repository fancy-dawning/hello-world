#include <stdio.h>
#include <conio.h>
#include<iostream>
#include "stdlib.h"
#include "windows.h"
#include "math.h"
typedef struct gameplayer //定义玩家结构体
{
	int name;
	int score;
	float number; 
	int win;
	int fail;
	int b;
}PLAYER; //含有玩家的姓名，分数，编号，分数信息

void gamerule(); //游戏规则
void  startgame(); //游戏的初始化
void suan_score(PLAYER *p,float ave,int num);//计算比赛得分的函数

int main()
{
	
	system("color 3B");
	int choice;
	while(1)
	{
		printf("\n\n\t\t\t\t\t\t黄金点游戏 \n\n");
		printf(" \t\t\t\t\t\t1. 游戏规则\n\n");
		printf(" \t\t\t\t\t\t2. 开始游戏\n\n");
		printf(" \t\t\t\t\t\t3. 退出游戏\n\n");
		printf("\t\t\t\t\t请输入您的选择：");
		scanf("%d",&choice);
		printf("\n");
		switch(choice)
		{
		case 1: gamerule(); break;
		case 2: startgame(); break;
		case 3: exit(0); break;
		default: 
			{
				printf("\t\t\t\t\t您的输入有误，请重新输入\n"); 
				break;
			}
		}
	}
	return 0;
}
void startgame()
{
	PLAYER *p;
	int i,playernum,gamenum,j;
	int flag=1;
	float sum,ave;
	char choice;
	int a[20];
	p=(PLAYER *)malloc(10*sizeof(PLAYER)); //动态分配结构体数组
	printf("\t\t\t\t\t请输入参与的玩家数(建议10人以上）：");
	scanf("%d",&playernum);
	printf("\n");
	if(playernum>10)
	{
		p=(PLAYER *)realloc(p,playernum*sizeof(PLAYER));//空间不足而需要增加空间
	}
	printf("\t\t\t\t\t请输入比赛轮次：");
	scanf("%d",&gamenum);
	printf("\n");
	system("cls");
	for(j=0;j<gamenum;j++)
	{
		printf("第%d轮比赛：\n",j+1);
		for(i=0,sum=0 ;i<playernum;i++)//sum设为总数和
		{
			if(flag==1)
			{
				p[i].name=i+1;
				p[i].score=0; 
				p[i].win=0;
				p[i].fail=0;
			} //初始化初值为0
			printf("玩家%d: ",p[i].name);
			p[i].number=0;
			char c;
			char passwd[16] = "";
			int spx=0;
			while ((c=getch())!='\r')
			{
				if (spx<16 && isprint(c))
				{
					passwd[spx] = c;
					putchar('*');
					spx++;
				}
				else if (spx>0 && c=='\b')
				{
					--spx;
					putchar('\b');
					putchar(' ');
					putchar('\b');
				}
			}
			putchar('\n');
			passwd[spx] = '\0';
			spx=0;
			int flag=-1;
			float spxnum=0;
			
			while( passwd[spx] != '\0'){
				if( passwd[spx]!='.'&&flag==-1){
					p[i].number*=10;
					p[i].number+= float(passwd[spx] - '0');
					spx++;;
				}else {
					flag++;
					spxnum=0;
					if(flag>0)
						spxnum=float(passwd[spx] - '0');
					for(int j = flag;j--;j>0){
						spxnum*=0.1;
					}
					p[i].number+=spxnum;
					spx++;
				}
			}
			sum+=p[i].number;
			a[i]=p[i].number;
		}
		printf("各玩家输入值为：");
		for(i=0;i<playernum;i++) //挨个玩家输出成绩
		printf("玩家%d: %d\t",p[i].name,a[i]);
		printf("\n");
		ave=sum/playernum; //计算平均值
		ave=(float)(ave*0.618); //计算黄金点的值
		printf("黄金点G的值为：%f\n",ave);
		suan_score(p,ave,playernum); 
		flag=0;
	}
	printf("游戏结束!\n");
	system("pause");
	system("cls");
	
}
void suan_score(PLAYER *p,float ave,int num)
{
	int i;
	char ch;
	float max=(float)fabs(p[0].number-ave);
	float min=(float)fabs(p[0].number-ave);
	
	for(i=0;i<num;i++) //统计出本轮最大值，最小值
	{
		p[i].b=(float)fabs(p[i].number-ave); 
		if(max<p[i].b)
			max=p[i].b; 
		if(min>p[i].b)
			min=p[i].b; 
	}
	
	for(i=0;i<num;i++) //挨个玩家赋予成绩
	{
		if(p[i].b==max) 
		{
			p[i].score-=2;
		}
		if(p[i].b==min) 
		{
			p[i].score+=num;
		}
	}
	printf("累计比赛的得分：\n");
	for(i=0;i<num;i++) //挨个玩家输出成绩
		printf("\t\t玩家%d: %d\n",p[i].name,p[i].score);
}
void gamerule()
{
	printf(" N个同学（N通常大于10），每人写一个0~100之间的有理数（不包括0或100),裁判算出所有数字的平均值，然后乘以0.618（所谓黄金分割常数），得到G值。提交的数字最靠近G（取绝对值）的同学得到N分，离G最远的同学得到－2分,其他同学得0分。\n\n"); 
}
