#include<stdio.h>
#include<string.h>
#include<math.h>
//����ṹ������ name��ű����� n���¼�����Ĵ�С
struct people
{
	char name[10];
	int n;
}peop[10];

//ȫ�ֱ���������x������¼�������ĸ���
char inter[11][5]={"��","һ","��","��","��","��","��","��","��","��","ʮ"};
int i,j,k,x=0;
char s[1001];


//һ�����ֺ���תΪ��������
int number(char *num)
{
	for(i=0;i<11;i++)
		if ( strcmp(inter[i],num)==0 )
			return i;
	if ( strcmp(num,"��")==0 )
		return 2;
}

//����ת���ɺ���
void ntc( int n1 )
{
	if(n1<0)
	{
		printf("��");
		n1=abs(n1);
	}
	while(n1)
	{
		if(n1<=10)
		{
			puts(inter[n1]);
			return ;
		}
		else if(n1<100)
		{
			printf("%s",inter[n1/10]);
			printf("ʮ");
			n1%=10;
		}
		else if(n1>=100)
		{
			printf("%s",inter[n1/100]);
			printf("��");
			if( n1%100 < 10 && n1%100 != 0)
				printf("��");
			n1%=100;
		}	
	}
	printf("\n");
}

//����ת��������
int ctn( char *a )
{
	char num[5];
	int i,sum=0,m=0;
	for(i=0;a[i];i+=2)
	{
		strncpy(num,a+i,2);
		num[2]='\0';
		if ( strcmp(num,"ʮ")==0 )
			if(sum==0) sum=10;
			else sum*=10;
		else if ( strcmp(num,"��")==0 )
		{
			m=sum*100;
			sum=0;
		}
		else
			sum+=number(num);
	}
	return sum+m;
}

//���ݱ��������Ҷ�Ӧλ��
int look(char *na)
{
	for(i=0;i<5;i++)
		if( strcmp(peop[i].name,na)==0 ) return i;
}

//��ӡ ���� ��Ҫ�������
void disp(char *p)
{
	char str1[2][50]={0};
	p=strstr(p,"����");
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
		ntc(peop[k].n);
		return ;
	}
	for(i=1;str1[1][i]!='"';i++)
		printf("%c",str1[1][i]);
	printf("\n");
}

//���� ��� ���
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
	if ( strcmp(str1[1],"��")==0 )
		return ;
	else if ( strcmp(str1[1],"����")==0 )
		{
			strcpy(peop[x].name, str1[2]);
			peop[x].n=ctn(str1[4]);
			x++;
		}
	else if ( strcmp(str1[1],"����")==0 )
		disp(p);
	else if ( strcmp(str1[2],"����")==0 )
	{
		k=look(str1[1]);
		peop[k].n=ctn(str1[3]);
	}
	else if ( strcmp(str1[2],"����")==0 )
	{
		k=look(str1[1]);
		peop[k].n=peop[k].n+ctn(str1[3]);
	}
    else if ( strcmp(str1[2],"����")==0 )
	{
		k=look(str1[1]);
		peop[k].n=peop[k].n-ctn(str1[3]);
	}
	else if ( strcmp(str1[2],"��")==0 || strcmp(str1[2],"����")==0 )
	{
		k=look(str1[1]);
		peop[k].n=peop[k].n * ctn(str1[3]);
		printf("%d\n",peop[k].n);
	}
	else if ( strcmp(str1[2],"��")==0 )
	{
		k=look(str1[1]);
		peop[k].n=ctn(str1[3])/peop[k].n;
	}
	else if ( strcmp(str1[2],"����")==0 )
	{
		k=look(str1[1]);
		peop[k].n=peop[k].n/ctn(str1[3]);
	}
	else
		printf("������ĸ�ʽ�����⣡");
}

//�������
int main()
{
	int t=5;
	gets(s);
	while(strcmp(s,"0"))//����0��ֹ����
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
		if ( strcmp(str[0],"����")==0 )  //�����ַ������ʱ��strcmp����0
		{
			strcpy(peop[x].name, str[1]);
			peop[x].n=ctn(str[3]);
			x++;
		}
	    else if ( strcmp(str[0],"����")==0 )
			disp(s);
		else if ( strcmp(str[1],"����")==0 )  
		{
			k=look(str[0]);
			peop[k].n=ctn(str[2]);
		}
	    else if ( strcmp(str[1],"����")==0 )
		{
			k=look(str[0]);
		    peop[k].n=peop[k].n+ctn(str[2]);
		}
		else if ( strcmp(str[1],"����")==0 )
		{
			k=look(str[0]);
		    peop[k].n=peop[k].n-ctn(str[2]);
		}
		else if ( strcmp(str[1],"��")==0 || strcmp(str[1],"����")==0 )
		{
			k=look(str[0]);
		    peop[k].n=peop[k].n*ctn(str[2]);
		}
        else if ( strcmp(str[1],"����")==0 )
		{
			k=look(str[0]);
		    peop[k].n=peop[k].n/ctn(str[2]);
		}
		else if ( strcmp(str[1],"��")==0 )
		{
			k=look(str[0]);
		    peop[k].n=ctn(str[2])/peop[k].n;
		}
		else if ( strcmp(str[0],"���")==0 )
		{
			k=look(str[1]);
			if( (strcmp(str[2],"����")==0 && peop[k].n>ctn(str[3])) || 
				(strcmp(str[2],"С��")==0 && peop[k].n<ctn(str[3])) || 
				(strcmp(str[2],"���ڵ���")==0 && peop[k].n>=ctn(str[3])) || 
				(strcmp(str[2],"С�ڵ���")==0 && peop[k].n<=ctn(str[3])) || 
				(strcmp(str[2],"����")==0 && peop[k].n==ctn(str[3])) )
				fun(strstr(s,"��"));
			else
			    fun(strstr(s,"����"));
		}
		else
			printf("������ĸ�ʽ�����⣬����������");
		gets(s);
	}
}
