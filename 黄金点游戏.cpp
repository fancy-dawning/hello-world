#include <stdio.h>
#include <conio.h>
#include<iostream>
#include "stdlib.h"
#include "windows.h"
#include "math.h"
typedef struct gameplayer //������ҽṹ��
{
	int name;
	int score;
	float number; 
	int win;
	int fail;
	int b;
}PLAYER; //������ҵ���������������ţ�������Ϣ

void gamerule(); //��Ϸ����
void  startgame(); //��Ϸ�ĳ�ʼ��
void suan_score(PLAYER *p,float ave,int num);//��������÷ֵĺ���

int main()
{
	
	system("color 3B");
	int choice;
	while(1)
	{
		printf("\n\n\t\t\t\t\t\t�ƽ����Ϸ \n\n");
		printf(" \t\t\t\t\t\t1. ��Ϸ����\n\n");
		printf(" \t\t\t\t\t\t2. ��ʼ��Ϸ\n\n");
		printf(" \t\t\t\t\t\t3. �˳���Ϸ\n\n");
		printf("\t\t\t\t\t����������ѡ��");
		scanf("%d",&choice);
		printf("\n");
		switch(choice)
		{
		case 1: gamerule(); break;
		case 2: startgame(); break;
		case 3: exit(0); break;
		default: 
			{
				printf("\t\t\t\t\t����������������������\n"); 
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
	p=(PLAYER *)malloc(10*sizeof(PLAYER)); //��̬����ṹ������
	printf("\t\t\t\t\t���������������(����10�����ϣ���");
	scanf("%d",&playernum);
	printf("\n");
	if(playernum>10)
	{
		p=(PLAYER *)realloc(p,playernum*sizeof(PLAYER));//�ռ䲻�����Ҫ���ӿռ�
	}
	printf("\t\t\t\t\t����������ִΣ�");
	scanf("%d",&gamenum);
	printf("\n");
	system("cls");
	for(j=0;j<gamenum;j++)
	{
		printf("��%d�ֱ�����\n",j+1);
		for(i=0,sum=0 ;i<playernum;i++)//sum��Ϊ������
		{
			if(flag==1)
			{
				p[i].name=i+1;
				p[i].score=0; 
				p[i].win=0;
				p[i].fail=0;
			} //��ʼ����ֵΪ0
			printf("���%d: ",p[i].name);
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
		printf("���������ֵΪ��");
		for(i=0;i<playernum;i++) //�����������ɼ�
		printf("���%d: %d\t",p[i].name,a[i]);
		printf("\n");
		ave=sum/playernum; //����ƽ��ֵ
		ave=(float)(ave*0.618); //����ƽ���ֵ
		printf("�ƽ��G��ֵΪ��%f\n",ave);
		suan_score(p,ave,playernum); 
		flag=0;
	}
	printf("��Ϸ����!\n");
	system("pause");
	system("cls");
	
}
void suan_score(PLAYER *p,float ave,int num)
{
	int i;
	char ch;
	float max=(float)fabs(p[0].number-ave);
	float min=(float)fabs(p[0].number-ave);
	
	for(i=0;i<num;i++) //ͳ�Ƴ��������ֵ����Сֵ
	{
		p[i].b=(float)fabs(p[i].number-ave); 
		if(max<p[i].b)
			max=p[i].b; 
		if(min>p[i].b)
			min=p[i].b; 
	}
	
	for(i=0;i<num;i++) //������Ҹ���ɼ�
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
	printf("�ۼƱ����ĵ÷֣�\n");
	for(i=0;i<num;i++) //�����������ɼ�
		printf("\t\t���%d: %d\n",p[i].name,p[i].score);
}
void gamerule()
{
	printf(" N��ͬѧ��Nͨ������10����ÿ��дһ��0~100֮�����������������0��100),��������������ֵ�ƽ��ֵ��Ȼ�����0.618����ν�ƽ�ָ�������õ�Gֵ���ύ���������G��ȡ����ֵ����ͬѧ�õ�N�֣���G��Զ��ͬѧ�õ���2��,����ͬѧ��0�֡�\n\n"); 
}
