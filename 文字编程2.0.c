#include<stdio.h>
#include<string.h>
#include<math.h>
//定义结构体数组 name存放变量名 n则记录变量的大小
struct people
{
	char name[10];
	double n;
}peop[10];

//全局变量，其中x用来记录变量名的个数
char inter[11][5]={"零","一","二","三","四","五","六","七","八","九","十"};
int i,j,k,x=0;
char s[1001];


//一个数字汉字转为数字类型
int number(char *num)
{
	for(i=0;i<11;i++)
		if ( strcmp(inter[i],num)==0 )
			return i;
	if ( strcmp(num,"两")==0 )
		return 2;
	return -1;
}

//小数位数字转汉字
void to_dot(int d)
{
	int t=10000; //最多打印小数点后五位
	printf("点");
	while( t && d)
	{
		printf("%s",inter[d/t]);
		d=d%t;
		t=t/10;
	}
	printf("\n");
}

//数字转换成汉字
void ntc( double a )
{
	int n1;
	double c;
	//printf("%lf\n",a);
	if(a<0)
	{
		printf("负");
		a=-a;
	}
	n1=(int)a;
	c=a-(int)a;
	if( (c-0.999995) >= 0) 
	{
		n1++;
		c=0;
	}
	if(n1 == 0) 
		printf("%s",inter[n1]);
	else
		while(n1)
		{
			if(n1<=10)
			{
				printf("%s",inter[n1]);
			    break;
			}
		    else if(n1<100)
			{
			    printf("%s",inter[n1/10]);
			    printf("十");
			    n1%=10;
			}
		    else if(n1>=100)
			{
			    printf("%s",inter[n1/100]);
			    printf("百");
			    if( n1%100 < 10 && n1%100 != 0)
					printf("零");
			    n1%=100;
			}	
	}
	if(c!=0)
	{
		c=c*100000; 
	    if(c+0.5>=(int)c+1) c++; //四舍五入
	    to_dot(c);
	}
	else
		printf("\n");
}

//小数位汉字转数字
double dot(char *d)
{
	char num[5];
	double sum=0,v=1;
	int i;
	for(i=2;d[i];i+=2)
	{
		v=v*10;
		strncpy(num,d+i,2);
	    num[2]='\0';
		sum=sum+number(num)/v;
	}
	return sum;
}

//汉字转换成数字
double ctn( char *a )
{
    char num[5];
	int i=0,sum=0,m=0,flag=0;
	double con=0;
	strncpy(num,a+i,2);
	num[2]='\0';
	if ( strcmp(num,"负")==0 )
	{
		flag=1;
		i=2;
	}
	for(;a[i];i+=2)
	{
		strncpy(num,a+i,2);
		num[2]='\0';
		if ( strcmp(num,"十")==0 )
			if(sum==0) sum=10;
			else sum*=10;
		else if ( strcmp(num,"百")==0 )
		{
			m=sum*100;
			sum=0;
		}
		else if ( strcmp(num,"点")==0 ) break;
		else
		{
			//if(number(num)==-1) return -1;
			sum+=number(num);
		}
	}
	if( strstr(a,"点") == NULL )
		con=sum+m;
	else
		con=sum+m+dot(strstr(a,"点"));
	
	if(flag==1) con=-con;
	//printf("%lf\n",con);
	return con;
}

//根据变量名查找对应位置
int look(char *na)
{
	for(i=0;i<5;i++)
		if( strcmp(peop[i].name,na)==0 ) return i;
	return -1;
}

//打印 看看 后要求的内容
void disp(char *p)
{
	char str1[2][50]={0};
	p=strstr(p,"看看");
	for(i=0,j=0;j<2;i++)
		if(p[i]!=' ')
		{
			k=i;
			while( p[i]!=' '&&p[i]!='\0' ) i++;
			strncpy(str1[j++],p+k,i-k);
		}
	if(str1[1][0]!='"')
	{
		k=look(str1[1]);
		if(k == -1)
		{
			printf("变量:%s 不存在\n", str1[1]);
			return ;
		} 
		ntc(peop[k].n);
		return ;
	}
	for(i=1;str1[1][i]!='"';i++)
		printf("%c",str1[1][i]);
	printf("\n");
}

//处理 如果 语句
void fun(char *p)
{
	char str1[10][50]={0};
	for(i=0,j=0;p[i];i++)
		if(p[i]!=' ')
		{
			k=i;
			while( p[i]!=' '&&p[i]!='\0' ) i++;
			strncpy(str1[j++],p+k,i-k);
		}
	if ( strcmp(str1[1],"无")==0 )
		return ;
	else if ( strcmp(str1[1],"整数")==0  || strcmp(str1[1],"小数")==0 )
		{
			strcpy(peop[x].name, str1[2]);
			peop[x].n=ctn(str1[4]);
			x++;
		}
	else if ( strcmp(str1[1],"看看")==0 )
		disp(p);
	else if ( strcmp(str1[2],"等于")==0 )
	{
		k=look(str1[1]);
		if(k == -1)
			printf("变量:%s 不存在\n", str1[1]);
		else
			peop[k].n=ctn(str1[3]);
	}
	else if ( strcmp(str1[2],"增加")==0 )
	{
		k=look(str1[1]);
		if(k == -1)
			printf("变量:%s 不存在\n", str1[1]);
		else
		    peop[k].n=peop[k].n+ctn(str1[3]);
	}
    else if ( strcmp(str1[2],"减少")==0 )
	{
		k=look(str1[1]);
		if(k == -1)
			printf("变量:%s 不存在\n", str1[1]);
		else
		    peop[k].n=peop[k].n-ctn(str1[3]);
	}
	else if ( strcmp(str1[2],"乘")==0 || strcmp(str1[2],"乘以")==0 )
	{
		k=look(str1[1]);
		if(k == -1)
			printf("变量:%s 不存在\n", str1[1]);
		else
		{
			peop[k].n=peop[k].n * ctn(str1[3]);
		    printf("%d\n",peop[k].n);
		}
	}
	else if ( strcmp(str1[2],"除")==0 )
	{
		k=look(str1[1]);
		if(k == -1)
			printf("变量:%s 不存在\n", str1[1]);
		else
		{
			if( peop[k].n == 0 )
			{
				printf("%s的值为零,不能作为除数！\n",peop[k].name);
				return ;
			}
		    peop[k].n=ctn(str1[3])/peop[k].n;
		}
	}
	else if ( strcmp(str1[2],"除以")==0 )
	{
		if( ctn(str1[3]) == 0 )
			{
				printf("零不能作为除数，请重新输入！\n");
				return ;
			}
		k=look(str1[1]);
		if(k == -1)
			printf("变量:%s 不存在\n", str1[1]);
		else
		    peop[k].n=peop[k].n/ctn(str1[3]);
	}
	else
		printf("您输入的格式有问题！");
}

//程序入口
int main()
{
	int t=5;
	gets(s);
	while(strcmp(s,"0"))//输入0终止程序
	{
		char str[15][50]={0};
		//gets(s);
		for(i=0,j=0;s[i]!='\0';i++)
			if(s[i]!=' ')
			{
				k=i;
				while( s[i]!=' '&&s[i]!='\0' ) i++;
			    strncpy(str[j++],s+k,i-k);
			} 
		if ( strcmp(str[0],"整数")==0 || strcmp(str[0],"小数")==0 )  //两个字符串相等时，strcmp返回0
		{
			if( look(str[1])!= -1 )
				printf("变量%s已存在！",str[1]);
			else
			{
				strcpy(peop[x].name, str[1]);
			    peop[x].n=ctn(str[3]);
			    x++;
			}
		}
	    else if ( strcmp(str[0],"看看")==0 )
			disp(s);
		else if ( strcmp(str[1],"等于")==0 )  
		{
			k=look(str[0]);
			if(k == -1)
				printf("变量:%s 不存在\n", str[0]);
			else
				peop[k].n=ctn(str[2]);
		}
	    else if ( strcmp(str[1],"增加")==0 )
		{
			k=look(str[0]);
			if(k == -1)
				printf("变量:%s 不存在\n", str[0]);
			else
		        peop[k].n=peop[k].n+ctn(str[2]);
		}
		else if ( strcmp(str[1],"减少")==0 )
		{
			k=look(str[0]);
			if(k == -1)
				printf("变量:%s 不存在\n", str[0]);
			else
		        peop[k].n=peop[k].n-ctn(str[2]);
		}
		else if ( strcmp(str[1],"乘")==0 || strcmp(str[1],"乘以")==0 )
		{
			k=look(str[0]);
			if(k == -1)
				printf("变量:%s 不存在\n", str[0]);
			else
		        peop[k].n=peop[k].n*ctn(str[2]);
		}
        else if ( strcmp(str[1],"除以")==0 )
		{
			k=look(str[0]);
			if(k == -1)
				printf("变量:%s 不存在\n", str[0]);
			else
				if( ctn(str[2]) == 0 )
					printf("零不能作为除数，请重新输入！\n");
			
			    else
				    peop[k].n=peop[k].n/ctn(str[2]);
		}
		else if ( strcmp(str[1],"除")==0 )
		{
			k=look(str[0]);
			if( peop[k].n == 0 )
				printf("%s的值为零,不能作为除数！\n",peop[k].name);
			else
				if(k == -1)
					printf("变量:%s 不存在\n", str[0]);
			    else
				peop[k].n=ctn(str[2])/peop[k].n;
		}
		else if ( strcmp(str[0],"如果")==0 )
		{
			k=look(str[1]);
			if(k == -1)
				printf("变量:%s 不存在\n", str[1]);
			else
				if( (strcmp(str[2],"大于")==0 && peop[k].n>ctn(str[3])) || 
					(strcmp(str[2],"小于")==0 && peop[k].n<ctn(str[3])) || 
					(strcmp(str[2],"大于等于")==0 && peop[k].n>=ctn(str[3])) || 
					(strcmp(str[2],"小于等于")==0 && peop[k].n<=ctn(str[3])) || 
					(strcmp(str[2],"等于")==0 && peop[k].n==ctn(str[3])) )
					fun(strstr(s,"则"));
			    else
			        fun(strstr(s,"否则"));
		}
		else
			printf("您输入的格式有问题，请重新输入\n");
		gets(s);
	}
}
