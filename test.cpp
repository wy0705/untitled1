//
// Created by wy on 2020/12/9.
//

#include "test.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "conredis.cpp"
//定义顺序串
#define MaxSize 100
typedef struct
{
    char data[MaxSize];//存放串字符
    int len;//串长
}SqString;
void menus();
void Scanf(char cstrr[]){//输入字符串
    cstrr[100];
    printf("Enter a string:\n");//提示用户输入字符串
    int j=0;
    while((cstrr[j]=getchar())!='\n')
        j++;
    cstrr[j]='\n';
}
//串赋值
void StrAssign(SqString s,char cstr[])
{
    Scanf(cstr);
    int i;
    for(i=0;cstr[i]!='\0';i++)
        s.data[i]=cstr[i];
    s.len=i;
}
//判断串是否相等
int StrEqual(SqString s,SqString t)
{
    int same=1,i;
    if(s.len!=t.len)//长度不相等时返回
        same=0;
    else {
        for(i=0;i<s.len;i++)
            if(s.data[i]!=t.data[i])//有一个对应字符不相同时返回
                same=0;
    }
    return same;
}
//将串t复制给串s
void StrCopy(SqString &s,SqString t)
{
    int i;
    for(i=0;i<t.len;i++)
        s.data[i]=t.data[i];
    s.len=t.len;
}
//求串长
int StringLength(SqString s)
{
    return s.len;
}
//求子串
SqString SubStr(SqString s,int i,int j)
{
    SqString str;
    int k;
    str.len=0;
    if(i<=0||i>s.len||j<0||i+j-1>s.len)
        return str;//参数不正确时返回空串
    for(k=i-1;k<i+j-1;k++){//将s.data[i..i+j]复制发str
        str.data[k-i+1]=s.data[k];
        str.len=j;
    }
    return str;
}
//串的联接；返回有两个串连接在一起的新串
SqString Concat(SqString s,SqString t)
{
    SqString str;
    int i;
    str.len=s.len+t.len;
    for(i=0;i<s.len;i++)//将s复制到str
        str.data[i]=s.data[i];
    for(i=0;i<t.len;i++)//将t复制到str
        str.data[s.len+i]=t.data[i];
    return str;
}
//串的替换
SqString RepStr(SqString s,int i,int j,SqString t)
{
    int k;
    SqString str;
    str.len=0;
    if(i<=0||i>s.len||i+j-1>s.len)//参数不正确时返回空串
        return str;
    for(k=0;k<i-1;k++) //将s.data[0..i-2]复制到str
        str.data[k]=s.data[k];
    for(k=i+j-1;k<s.len;k++) //将s.data[i+j-1..s.len-1]复制到str
        str.data[t.len+k-j]=s.data[k];
    str.len=s.len+t.len;
    return str;
}
//串的删除
SqString DelStr(SqString s,int i,int j)
{
    int k;
    SqString str;
    str.len=0;
    if(i<=0||i>s.len||i+j>s.len+1)//参数不正确时返回空串
    {
        printf("参数不正确\n");
        return str;
    }
    for(k=0;k<i-1;k++)//将s.data[0]~s.data[i-2]复制到str
        str.data[k-j]=s.data[k];
    for(k=i+j-1;k<s.len;k++)//将s.data[i+j-1]~data[s.length-1]复制到str
        str.data[k-j]=s.data[k];
    str.len=s.len-j;
    return str;
}
//串比较
int Strcmp(SqString s,SqString t)
{
    int i ,comlen;
    if(s.len<t.len)
        comlen=s.len;//求s和t的共同长度
    else
        comlen=t.len;
    for(i=0;i<comlen;i++){//在共同长度内逐个字符比较
        if(s.data[i]<t.data[i])
            return -1;
        else if(s.data[i]>t.data[i])
            return 1;
    }
    if(s.len==t.len)
        return 0; //s==t
    else if(s.len<t.len)
        return -1; //s<t
    else
        return 1; //s>t
}
//输出串

void DispStr(SqString str)
{
    int i;
    if(str.len>0)
    {
        for(i=0;i<str.len;i++)
            printf("%c",str.data[i]);
        printf("\n");
    }
}
int mains()
{
//    menus();
}
char cstr1[80],cstr2[80];
SqString str1,str2,s1,s2,s3;
//菜单函数
void menus(){
    int i,j,m,x,y;
    char n;
    printf("**********************************************\n");
    printf("*******A 赋值     E 判相等     C 联接*********\n");
    printf("*******L 求长度   S 求子串     I 子串定位*****\n");
    printf("*******R 串替换   P 显示       D 删除*********\n");
    printf("*******            Q 退出              *******\n");
    scanf("&c",&n);
    getchar();
    switch(n)
    {
        case 'A':
        case 'a':
            printf("A 请输入需要赋值的串 \n");
            StrAssign(str1,cstr1);
            printf("输出 str1=");
            DispStr(str1);
            menus();
            break;
        case 'E':
        case 'e':
            printf("E 判断串str1和str2是否相等: \n");
            StrAssign(str1,cstr1);
            StrAssign(str2,cstr2);
            m=StrEqual(str1,str2);
            if(m==1)
                printf("EQUAL\n");
            else
                printf("NUEQUAL\n");
            menus();
            break;
        case'C':
        case'c':
            printf("输入要连接的两个串: \n");
            printf("将串str1和str2连接起来形成串s1: \n");
            StrAssign(str1,cstr1);
            StrAssign(str2,cstr2);
            s1=Concat(str1,str2);
            DispStr(s1);
            menus();
            break;
        case'L':
        case'l':
            printf("输入要求长度的串: \n");
            StrAssign(str1,cstr1);
            printf("str1的长度为: %d\n",StringLength(str1));
            menus();
            break;
        case'S':
        case's':
            printf("提取串str1的第a个字符开始的b个字符而产生的串s2\n");
            StrAssign(str1,cstr1);
            int a,b;
            scanf("%d %d",&a,&b);
            s2=SubStr(str1,a,b);
            DispStr(s2);
            menus();
            break;
        case'R':
        case'r':
            printf("在串str1中，将第p个字符开始的q个字符构成的子串用str2替换，形成s3: \n");
            StrAssign(str1,cstr1);
            int p,q;
            scanf("%d %d",&p,&q);
            StrAssign(str2,cstr2);
            s3=RepStr(str1,p,q,str2);
            DispStr(s3);
            menus();
            break;
        case'D':
        case'd':
            printf("从串str1中删去第i个字符开始的长度为j的子串，形成串s3: \n");
            StrAssign(str1,cstr1);
            int x,y;
            scanf("%d %d",&x,&y);
            s3=DelStr(str1,x,y);
            DispStr(s3);
            menus();
            break;
        case'Q':
        case'q':
            break;
    }
}
