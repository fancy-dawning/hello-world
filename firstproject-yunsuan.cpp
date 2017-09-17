#include<stdio.h>
#include <stdlib.h> 
#include <iostream.h>
#include <conio.h> 
#include <time.h> 
#include <windows.h>
int a;    //第一个数
int b;    //第二个数 
int d;    //中间变量
int f,g;  //用于分数
int mode;//0:加  1:减   2:乘 3:除   4:真分数   
int c;    //输入答案 
int result;  //正确答案
int x;     //答题方式
float p,q;
double score = 0;  //成绩   
int m;//题数目
int e;//随机数生成的范围

int main() { 
	void menu();
	void online();
	void offline();
	menu();
	return 0;
}
void offline()
{
	int i=0;
	char t,t1;
	char s[100];
	FILE *f;
	printf("请输入需要的题目数目：");
	scanf("%d",&m);
	printf("请输入生成随机数的范围：");
	scanf("%d",&e);
	f=fopen("d:\\tencent\\jisuan.txt","w");
	if(f==NULL)
	{
		printf("文件打开出错！");
	}
	else
	{
		for(i=0;i<m;i++)
		{
			s[i]=rand() % e;
			s[i+1]=rand() % e;
			mode = rand() % 5; //生成一个0~3之间的随机数，代表运算符         
			switch(mode)
			{
			case 0:
				t='+';
				fprintf(f,"%d",s[i]);
				fputc(t,f);
				fprintf(f,"%d",s[i+1]);
				fputs("=\n",f);
				break;
			case 1:
				if(s[i]<s[i+1])
				{
					d=s[i];
					s[i]=s[i+1];
					s[i+1]=d;
				}  
				t='-';
				fprintf(f,"%d",s[i]);
				fputc(t,f);
				fprintf(f,"%d",s[i+1]);
				fputs("=\n",f);
				break;
			case 2:
				t='*';
				fprintf(f,"%d",s[i]);
				fputc(t,f);
				fprintf(f,"%d",s[i+1]);
				fputs("=\n",f);
				break;
			case 3:
				while(s[i+1]==0)   //除法保证除数不为零
				{
					s[i+1]=rand()%e;
				}
				t='/';
				fprintf(f,"%d",s[i]);
				fputc(t,f);
				fprintf(f,"%d",s[i+1]);
				fputs("=\n",f);
				break;
			case 4:
				t1='/';
				s[i+2] = rand() % e;
				s[i+3] = rand() % e;
				mode = rand() % 4 ;
				while (s[i+1] == 0)   //   分母不为零
				{
					s[i+1] = rand() % e;
				}
				while (s[i+3] == 0)  //分母不为零
				{
					s[i+3] = rand() % e;
				}
				if(s[i]>s[i+1])    //保证分子小于分母
				{
					d=s[i];
					s[i]=s[i+1];
					s[i+1]=d;
				}  
				if(s[i+2]>s[i+3])
				{
					d=s[i+2];
					s[i+2]=s[i+3];
					s[i+3]=d;
				}  
				switch (mode)
				{
				case 0:
					t='+';
					break;
				case 1:
					p = (float)s[i] / (float)s[i+1];
					q = (float)s[i+1] / (float)s[i+3];
					if (p < q)
					{
						d = s[i];
						s[i] = s[i+2];
						s[i+2] = d;
						d = s[i+1];
						s[i+1] = s[i+3];
						s[i+3] = d;
					}
					t='-';
					break;
				case 2:
					t='*';
					break;
				case 3:
					while (s[i+2]== 0)
					{
						s[i+2] = rand() % 100;
					}
					t='/';
					break;
				default:              
					printf("未知错误!\n");               
					break;
				}
				fprintf(f,"%d",s[i]);
				fputc(t1,f);
				fprintf(f,"%d",s[i+1]);
				fputs(" ",f);
				fputc(t,f);
				fputs(" ",f);
				fprintf(f,"%d",s[i+2]);
				fputc(t1,f);
				fprintf(f,"%d",s[i+3]);
				fputs("=\n",f);
			}
		}
	}
	printf("题目已成功保存到d:\\tencent\\jisuan.txt！\n");
	fclose(f);
}
void online(){
	time_t t1,t2;
	printf("请输入需要的题目数目：");
	scanf("%d",&m);
	printf("请输入生成随机数的范围：");
	scanf("%d",&e);
	srand((unsigned)time( NULL ) ); //初始化随机数发生器，使得每次运行生成的随机数不同
	printf("\n\n\n\t\t\t\t答题即将开始，建议答题时间为%0.1f分钟（结果为非整数时取整数）!\n",m*0.5);
	system("pause");
	system("cls");
	time(&t1);
	for(int i=0;i<m;i++)
	{
		a = rand() % e; //生成一个随机数         
		b = rand() % e;  //生成另一个随机数         
		mode = rand() % 5; //生成一个0~4之间的随机数，代表运算符         
		switch(mode) //确定运算符         
		{ 
		case 0:               
			printf("%d + %d = ",a,b);
			result= a + b;   //选择了+运算的正确答案            
			break;          
		case 1:  
			if(a<b)
			{
				d=a;
				a=b;
				b=d;
			}     //减法保证结果不为负数
			printf("%d + %d = ", a,b);
			result= a - b;   //选择了-运算的正确答案             
			break;          
		case 2:               
			printf("%d * %d = ", a,b);
			result= a * b;   //选择了*运算的正确答案            
			break;          
		case 3:  
			while(b==0)   //除法保证除数不为零
			{
				b=rand()%e;
			}
			printf("%d / %d = ", a,b);
			result= a / b;   //选择了/运算的正确答案 
			break;
		case 4:
			f = rand() % e;
			g = rand() % e;
			mode = rand() % 4 ;
            while (b == 0)   //   分母不为零
            {
				b = rand() % e;
			}
			while (g == 0)  //分母不为零
			{
				g = rand() % e;
			}
			if (a > b)
			{
				d = a;
				a = b;
				b = d;
			}
            if (f > g)
			{
				d = f;
				f = g;
				g = d;
			}
			switch (mode)
			{
			case 0:
				printf("%d/%d + %d/%d =", a, b, f, g);
				result = a/b + f/g;
				break;
			case 1:
				p = (float)a / (float)b;
				q = (float)f / (float)g;
				if (p < q)
				{
                    d = a;
                    a = f;
                    f = d;
					d = b;
					b = g;
					g = d;
				}
				printf("%d/%d - %d/%d =", a,b,f,g);
				result = a/b - f/g;
				break;
			case 2:printf("%d/%d * %d/%d =", a, b, f, g);
				result = (a/b) * (f/g);
				break;
			case 3:
				while (f == 0)
				{
					f = rand() % 100;
                }
				printf("%d/%d / %d/%d =", a, b, f, g);
				result = (a/b) / (f/g);
				break;
			default:              
				printf("未知错误!\n");               
				break;
			}   
		}    
		scanf("%d", &c); //输入答案        
		if(c == result) //与正确答案一致        
		{             
			score+= 100.0/m;  //加分             
			printf("正确！\n\n");         
		}         
		else         
		{              
			printf("错误！正确答案为%d\n\n",result); //错      
		}     
	}  
	printf("你的得分是: %0.1f\n\n\n", score);//显示得分   
	time(&t2);
	Sleep(1000);
	printf("答题所用时间为：%d:%d分钟\n",(t2-t1)/60,(t2-t1)%60);
	
}
void menu()
{
	int x;
	printf("请选择答题方式：1、线下答题  2、线上答题\n");
	scanf("%d",&x);
	switch(x)
	{
	case 1:
		offline();
		break;
	case 2:
		online();
		break;
	default:
		printf("输入错误！");
		break;
	}
	
}
