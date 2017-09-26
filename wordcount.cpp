#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <io.h>

void open_file(int a,int b,int c,int d,char data[]);
FILE *letter(FILE *fp1,char ch1);
FILE *message(FILE *fp1,char ch2);
FILE *null(FILE *fp1,char ch3);
void printDir( const char* path );
void index();

char str1[50],str3[50];
int word_N=0,line_N=0,ch_N=0;//��¼���������������ַ���
int null_h=0,code_h=0,mess_h=0;//��¼���С������С�ע����
int s_ch=0,s_word=0,s_line=0,hang_a=0,s_s=0;//��¼����Ĳ�ѯ����
int main ()
{
    char s[100];
	index();
    gets(s);
    
    while(1)
    {
        memset(str1, 0, sizeof(str1));     //��str1�����е�����Ԫ����Ϊ0
        memset(str3, 0, sizeof(str3));     //��str3�����е�����Ԫ����Ϊ0
        word_N=0,line_N=0,ch_N=0,null_h=0,code_h=0,mess_h=0;
        s_ch=0,s_word=0,s_line=0,hang_a=0,s_s=0;
        int length_s=0;
        length_s=strlen(s);
        
        int i=0;        
        for(i=7;i<length_s;++i)
        {
            if((s[i]=='-')&&(s[i+1]=='c')){
                s_ch=1;
            }
            if((s[i]=='-')&&(s[i+1]=='w')){
                s_word=2;
            }
            if((s[i]=='-')&&(s[i+1]=='l')){
                s_line=3;
            }
            if((s[i]=='-')&&(s[i+1]=='a')){
                hang_a=4;
            }
            if((s[i]=='-')&&(s[i+1]=='s'))
            {
                s_s=5;
            }
			//�޸�:��ԭ����·����Ϊ���Զ����·��
            if((s[i]>='A')&&(s[i]<='Z')){         
                strncpy(str1,s+i,length_s-i);
                strcpy(str3,str1);
                break;
            }//��ȡ�ļ���
        }
        if(s_s==5)
        {
            s_ch=1;
            s_word=2;
            s_line=3;
            hang_a=4;
            printDir(str1);
        }
        else open_file(s_ch,s_word,s_line,hang_a,str1);
        
        printf("\n");
        gets(s);
    }
    return 0;
}
void printDir( const char* path )
{
    struct _finddata_t data;

    long hnd = _findfirst( path, &data );    // �����ļ�����������ʽchRE��ƥ���һ���ļ�
    if ( hnd < 0 )
    {
        perror( path );
    }
    int  nRet = (hnd <0 ) ? -1 : 1;
    while ( nRet >= 0 )
    {
        if ( data.attrib == _A_SUBDIR )  // �����Ŀ¼
        {
            printf("�ļ�����[%s]*\n", data.name );
            open_file(s_ch,s_word,s_line,hang_a,data.name );
        }
        else
        {
            printf("�ļ�����[%s]\n", data.name );
            open_file(s_ch,s_word,s_line,hang_a,data.name);
        }
        nRet = _findnext( hnd, &data );
    }
    _findclose( hnd );     // �رյ�ǰ���
}
void open_file(int a,int b,int c,int d,char data[])
{
    word_N=0,line_N=0,ch_N=0,null_h=0,code_h=0,mess_h=0;
    int i=0,length_str3=0,j=0;
    length_str3=strlen(str3);
    char str2[50];
    memset(str1, 0, sizeof(str1));
    strcpy(str1,str3);
    for(i=0;i<length_str3;++i)
    {
        if(str3[0]==data[0])
        {
            strcpy(str2,str3);
            break;
        }//��δ����ָ��-sʱ��ֱ�Ӵ�str1
        else if(str3[i]=='*')
        {
            for(;i<length_str3;++i)
				str1[i]='\0';
            strcat(str1,data);
            printf("�ļ�λ�ã�%s\n", str1);
            strcpy(str2,str1);
            break;
        }
    }

    FILE *fp;
    fp=fopen(str2,"r");
    if(fp==NULL){
        printf("the file not found\n");
        exit(0);
    }//�򿪵�ַ�ļ�
    
    char ch;
    ch=fgetc(fp);
    ch_N++;
    if(ch==EOF)
        ch_N--;
    while(ch!=EOF)
    {
        switch(ch)
        {
        case ' ':fp=null(fp,ch);break;
        case '{':fp=null(fp,ch);break;
        case '}':fp=null(fp,ch);break;
        case '/': fp=message(fp,ch);break;
        default :fp=letter(fp,ch);break;
        }
        ch=fgetc(fp);
        ch_N++;
        if(ch==EOF)
            ch_N--;
    }
    
    if(a==1)
        printf("�ַ�����%d\n",ch_N);
    if(b==2)
        printf("��������%d\n",word_N);
    if(c==3)
        printf("��������%d\n",line_N);
    if(d==4)
    {
        printf("�����У�%d\n",code_h);
        printf("ע���У�%d\n",mess_h);
        printf("���У�%d\n",null_h);
    }
}
FILE *message(FILE *fp1,char ch2)
{
    char ch_2;
    ch_2=fgetc(fp1);
    ch_N++;
    if(ch_2=='/')
    {
        ch_2=fgetc(fp1);
        ch_N++;
        while((ch_2!='\n')&&(ch_2!=EOF))
        {
            ch_2=fgetc(fp1);
            ch_N++;
        }//����ʱ���
        ch_2=fgetc(fp1);
        ch_N++;
        mess_h++;
        line_N++;//ע����+1��������+1����ȡ\n֮�����һ���ַ���
        if(ch_2==EOF)
        {
            ch_N--;
            return fp1;
        }
    }
    fseek(fp1,-1,1);
    ch_N--;
    
    return fp1;
}//ע�ͺ���
FILE *null(FILE *fp1,char ch3)
{
    char ch_3;
    ch_3=ch3;

    if((ch_3=='{')||(ch_3=='}'))
    {
        ch_3=fgetc(fp1);
        ch_N++;
        if(ch_3=='\n')
        {
            null_h++;
            line_N++;
            ch_3=fgetc(fp1);
            ch_N++;
        }
    }
    if(ch_3==EOF)
    {
        ch_N--;
        null_h++;
        line_N++;
        return fp1;
    }

    while((ch_3==' '))
    {
        ch_3=fgetc(fp1);
        ch_N++;
    }
    if(ch_3=='\n')
    {
        null_h++;
        line_N++;
        ch_3=fgetc(fp1);
        ch_N++;
    }
    fseek(fp1,-1,1);
    ch_N--;

    return fp1;
}//���к���
FILE *letter(FILE *fp1,char ch1)
{
    char ch_1;
    ch_1=ch1;
    
    if(isalpha(ch_1))
    {
        ch_1=fgetc(fp1);
        ch_N++;
        while((isalpha(ch_1))||(isdigit(ch_1)))
        {
            ch_1=fgetc(fp1);
            ch_N++;
        }
        word_N++;
    }//��ĸ�͵���
    else if(isdigit(ch_1))
    {
        ch_1=fgetc(fp1);
        ch_N++;
        while((isdigit(ch_1))||(isalpha(ch_1)))
        {
            ch_1=fgetc(fp1);
            ch_N++;
        }
        word_N++;
    }//�����͵���
    else if(ch_1=='\n')
    {
        code_h++;
        line_N++;
        ch_1=fgetc(fp1);
        ch_N++;
    }
    else if(ch_1==EOF)
    {
        ch_N--;
        return fp1;
    }
    else
    {
        ch_1=fgetc(fp1);
        ch_N++;
    }
    fseek(fp1,-1,1);
    ch_N--;

    return fp1;
}//���ʼ�������
void index()
{
	printf("\t\t\t**        Wordcount        **\n\n");
    printf("\t\t\t**     -c:ͳ���ַ�         **\n\n");
    printf("\t\t\t**     -w:ͳ�Ƶ�����       **\n\n");
    printf("\t\t\t**     -l:ͳ������         **\n\n");
    printf("\t\t\t**     -a:���ظ߼�ѡ��     **\n\n");
    printf("\t\t\t**     -s:�ݹ鴦���ļ�     **\n\n");
	printf("������ͳ�ƹ��ܼ��ļ�λ�ã���wc.exe��ͷ���磺wc.exe -a -c D:/����/1.txt��:\n");
}//���ӣ���ʾ����