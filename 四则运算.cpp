/*#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{

  return 0;
  }
  ��ӹ���  1��ѡ����ⷽʽ:���� ����(�ı��ĵ�)
            2���Ʒ�
            3����ʱ
            4��֧�ַ�������*/

#include<stdio.h>
#include <stdlib.h> 
#include <iostream.h>
#include <conio.h> 
#include <time.h> 
#include <windows.h>
int a;    //��һ����
int b;    //�ڶ����� 
int d;    //�м����
int f,g;  //���ڷ���
int mode;//0:��  1:��   2:�� 3:��   4:�����   
int c;    //����� 
int result;  //��ȷ��
int x;     //���ⷽʽ
float p,q;
double score = 0;  //�ɼ�   
int m;//����Ŀ
int e;//��������ɵķ�Χ

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
	printf("��������Ҫ����Ŀ��Ŀ��");
	scanf("%d",&m);
	printf("����������������ķ�Χ��");
	scanf("%d",&e);
	f=fopen("d:\\tencent\\jisuan.txt","w");
	if(f==NULL)
	{
		printf("�ļ��򿪳���");
	}
	else
	{
		for(i=0;i<m;i++)
		{
			s[i]=rand() % e;
			s[i+1]=rand() % e;
			mode = rand() % 5; //����һ��0~3֮�������������������         
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
				while(s[i+1]==0)   //������֤������Ϊ��
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
				while (s[i+1] == 0)   //   ��ĸ��Ϊ��
				{
					s[i+1] = rand() % e;
				}
				while (s[i+3] == 0)  //��ĸ��Ϊ��
				{
					s[i+3] = rand() % e;
				}
				if(s[i]>s[i+1])    //��֤����С�ڷ�ĸ
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
					printf("δ֪����!\n");               
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
	printf("��Ŀ�ѳɹ����浽d:\\tencent\\jisuan.txt��\n");
	fclose(f);
}
void online(){
	time_t t1,t2;
	printf("��������Ҫ����Ŀ��Ŀ��");
	scanf("%d",&m);
	printf("����������������ķ�Χ��");
	scanf("%d",&e);
	srand((unsigned)time( NULL ) ); //��ʼ���������������ʹ��ÿ���������ɵ��������ͬ
	printf("\n\n\n\t\t\t\t���⼴����ʼ���������ʱ��Ϊ%0.1f���ӣ����Ϊ������ʱȡ������!\n",m*0.5);
	system("pause");
	system("cls");
	time(&t1);
	for(int i=0;i<m;i++)
	{
		a = rand() % e; //����һ�������         
		b = rand() % e;  //������һ�������         
		mode = rand() % 5; //����һ��0~4֮�������������������         
		switch(mode) //ȷ�������         
		{ 
		case 0:               
			printf("%d + %d = ",a,b);
			result= a + b;   //ѡ����+�������ȷ��            
			break;          
		case 1:  
			if(a<b)
			{
				d=a;
				a=b;
				b=d;
			}     //������֤�����Ϊ����
			printf("%d + %d = ", a,b);
			result= a - b;   //ѡ����-�������ȷ��             
			break;          
		case 2:               
			printf("%d * %d = ", a,b);
			result= a * b;   //ѡ����*�������ȷ��            
			break;          
		case 3:  
			while(b==0)   //������֤������Ϊ��
			{
				b=rand()%e;
			}
			printf("%d / %d = ", a,b);
			result= a / b;   //ѡ����/�������ȷ�� 
			break;
		case 4:
			f = rand() % e;
			g = rand() % e;
			mode = rand() % 4 ;
            while (b == 0)   //   ��ĸ��Ϊ��
            {
				b = rand() % e;
			}
			while (g == 0)  //��ĸ��Ϊ��
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
				printf("δ֪����!\n");               
				break;
			}   
		}    
		scanf("%d", &c); //�����        
		if(c == result) //����ȷ��һ��        
		{             
			score+= 100.0/m;  //�ӷ�             
			printf("��ȷ��\n\n");         
		}         
		else         
		{              
			printf("������ȷ��Ϊ%d\n\n",result); //��      
		}     
	}  
	printf("��ĵ÷���: %0.1f\n\n\n", score);//��ʾ�÷�   
	time(&t2);
	Sleep(1000);
	printf("��������ʱ��Ϊ��%d:%d����\n",(t2-t1)/60,(t2-t1)%60);
	
}
void menu()
{
	int x;
	printf("��ѡ����ⷽʽ��1�����´���  2�����ϴ���\n");
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
		printf("�������");
		break;
	}
	
}
/*#include<stdio.h>
int main()
{
char t='+';
printf("%c\n",t);
return 0;
}

  #include <stdio.h>
  #include <time.h>
  #include <conio.h>
  #include <windows.h>
  int main()
  {
  time_t t1,t2;
  time(&t1);
  char  f;
  puts("��ʱ��ʼ���� S ����");
  while((t2-t1)/60!=1)
  { 
  time(&t2);
  printf("%d:%d\n",(t2-t1)/60,(t2-t1)%60);
  Sleep(1000);
  system("cls");
  }
  return 0;
}*/

