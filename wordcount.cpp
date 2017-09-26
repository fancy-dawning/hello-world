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
int word_N=0,line_N=0,ch_N=0;//记录单词数、行数、字符数
int null_h=0,code_h=0,mess_h=0;//记录空行、代码行、注释行
int s_ch=0,s_word=0,s_line=0,hang_a=0,s_s=0;//记录输入的查询数据
int main ()
{
    char s[100];
	index();
    gets(s);
    
    while(1)
    {
        memset(str1, 0, sizeof(str1));     //将str1数组中的所有元素置为0
        memset(str3, 0, sizeof(str3));     //将str3数组中的所有元素置为0
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
			//修改:将原绝对路径改为可自定义的路径
            if((s[i]>='A')&&(s[i]<='Z')){         
                strncpy(str1,s+i,length_s-i);
                strcpy(str3,str1);
                break;
            }//获取文件名
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

    long hnd = _findfirst( path, &data );    // 查找文件名与正则表达式chRE的匹配第一个文件
    if ( hnd < 0 )
    {
        perror( path );
    }
    int  nRet = (hnd <0 ) ? -1 : 1;
    while ( nRet >= 0 )
    {
        if ( data.attrib == _A_SUBDIR )  // 如果是目录
        {
            printf("文件名：[%s]*\n", data.name );
            open_file(s_ch,s_word,s_line,hang_a,data.name );
        }
        else
        {
            printf("文件名：[%s]\n", data.name );
            open_file(s_ch,s_word,s_line,hang_a,data.name);
        }
        nRet = _findnext( hnd, &data );
    }
    _findclose( hnd );     // 关闭当前句柄
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
        }//当未输入指令-s时，直接打开str1
        else if(str3[i]=='*')
        {
            for(;i<length_str3;++i)
				str1[i]='\0';
            strcat(str1,data);
            printf("文件位置：%s\n", str1);
            strcpy(str2,str1);
            break;
        }
    }

    FILE *fp;
    fp=fopen(str2,"r");
    if(fp==NULL){
        printf("the file not found\n");
        exit(0);
    }//打开地址文件
    
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
        printf("字符数：%d\n",ch_N);
    if(b==2)
        printf("单词数：%d\n",word_N);
    if(c==3)
        printf("总行数：%d\n",line_N);
    if(d==4)
    {
        printf("代码行：%d\n",code_h);
        printf("注释行：%d\n",mess_h);
        printf("空行：%d\n",null_h);
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
        }//换行时输出
        ch_2=fgetc(fp1);
        ch_N++;
        mess_h++;
        line_N++;//注释行+1，总行数+1，获取\n之后的下一个字符；
        if(ch_2==EOF)
        {
            ch_N--;
            return fp1;
        }
    }
    fseek(fp1,-1,1);
    ch_N--;
    
    return fp1;
}//注释函数
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
}//空行函数
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
    }//字母型单词
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
    }//数字型单词
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
}//单词及代码行
void index()
{
	printf("\t\t\t**        Wordcount        **\n\n");
    printf("\t\t\t**     -c:统计字符         **\n\n");
    printf("\t\t\t**     -w:统计单词数       **\n\n");
    printf("\t\t\t**     -l:统计行数         **\n\n");
    printf("\t\t\t**     -a:返回高级选项     **\n\n");
    printf("\t\t\t**     -s:递归处理文件     **\n\n");
	printf("请输入统计功能及文件位置（以wc.exe开头，如：wc.exe -a -c D:/测试/1.txt）:\n");
}//增加：提示界面