#include<stdio.h>
#include<string.h>
#include<math.h>
//����ṹ������ name��ű����� n���¼�����Ĵ�С
struct people
{
	char name[10];
	double n;
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
	return -1;
}

//С��λ����ת����
void to_dot(int d)
{
	int t=10000; //����ӡС�������λ
	printf("��");
	while( t && d)
	{
		printf("%s",inter[d/t]);
		d=d%t;
		t=t/10;
	}
	printf("\n");
}

//����ת���ɺ���
void ntc( double a )
{
	int n1;
	double c;
	//printf("%lf\n",a);
	if(a<0)
	{
		printf("��");
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
	if(c!=0)
	{
		c=c*100000; 
	    if(c+0.5>=(int)c+1) c++; //��������
	    to_dot(c);
	}
	else
		printf("\n");
}

//С��λ����ת����
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

//����ת��������
double ctn( char *a )
{
    char num[5];
	int i=0,sum=0,m=0,flag=0;
	double con=0;
	strncpy(num,a+i,2);
	num[2]='\0';
	if ( strcmp(num,"��")==0 )
	{
		flag=1;
		i=2;
	}
	for(;a[i];i+=2)
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
		else if ( strcmp(num,"��")==0 ) break;
		else
		{
			//if(number(num)==-1) return -1;
			sum+=number(num);
		}
	}
	if( strstr(a,"��") == NULL )
		con=sum+m;
	else
		con=sum+m+dot(strstr(a,"��"));
	
	if(flag==1) con=-con;
	//printf("%lf\n",con);
	return con;
}

//���ݱ��������Ҷ�Ӧλ��
int look(char *na)
{
	for(i=0;i<5;i++)
		if( strcmp(peop[i].name,na)==0 ) return i;
	return -1;
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
		if(k == -1)
		{
			printf("����:%s ������\n", str1[1]);
			return ;
		} 
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
	else if ( strcmp(str1[1],"����")==0  || strcmp(str1[1],"С��")==0 )
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
		if(k == -1)
			printf("����:%s ������\n", str1[1]);
		else
			peop[k].n=ctn(str1[3]);
	}
	else if ( strcmp(str1[2],"����")==0 )
	{
		k=look(str1[1]);
		if(k == -1)
			printf("����:%s ������\n", str1[1]);
		else
		    peop[k].n=peop[k].n+ctn(str1[3]);
	}
    else if ( strcmp(str1[2],"����")==0 )
	{
		k=look(str1[1]);
		if(k == -1)
			printf("����:%s ������\n", str1[1]);
		else
		    peop[k].n=peop[k].n-ctn(str1[3]);
	}
	else if ( strcmp(str1[2],"��")==0 || strcmp(str1[2],"����")==0 )
	{
		k=look(str1[1]);
		if(k == -1)
			printf("����:%s ������\n", str1[1]);
		else
		{
			peop[k].n=peop[k].n * ctn(str1[3]);
		    printf("%d\n",peop[k].n);
		}
	}
	else if ( strcmp(str1[2],"��")==0 )
	{
		k=look(str1[1]);
		if(k == -1)
			printf("����:%s ������\n", str1[1]);
		else
		{
			if( peop[k].n == 0 )
			{
				printf("%s��ֵΪ��,������Ϊ������\n",peop[k].name);
				return ;
			}
		    peop[k].n=ctn(str1[3])/peop[k].n;
		}
	}
	else if ( strcmp(str1[2],"����")==0 )
	{
		if( ctn(str1[3]) == 0 )
			{
				printf("�㲻����Ϊ���������������룡\n");
				return ;
			}
		k=look(str1[1]);
		if(k == -1)
			printf("����:%s ������\n", str1[1]);
		else
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
		if ( strcmp(str[0],"����")==0 || strcmp(str[0],"С��")==0 )  //�����ַ������ʱ��strcmp����0
		{
			if( look(str[1])!= -1 )
				printf("����%s�Ѵ��ڣ�",str[1]);
			else
			{
				strcpy(peop[x].name, str[1]);
			    peop[x].n=ctn(str[3]);
			    x++;
			}
		}
	    else if ( strcmp(str[0],"����")==0 )
			disp(s);
		else if ( strcmp(str[1],"����")==0 )  
		{
			k=look(str[0]);
			if(k == -1)
				printf("����:%s ������\n", str[0]);
			else
				peop[k].n=ctn(str[2]);
		}
	    else if ( strcmp(str[1],"����")==0 )
		{
			k=look(str[0]);
			if(k == -1)
				printf("����:%s ������\n", str[0]);
			else
		        peop[k].n=peop[k].n+ctn(str[2]);
		}
		else if ( strcmp(str[1],"����")==0 )
		{
			k=look(str[0]);
			if(k == -1)
				printf("����:%s ������\n", str[0]);
			else
		        peop[k].n=peop[k].n-ctn(str[2]);
		}
		else if ( strcmp(str[1],"��")==0 || strcmp(str[1],"����")==0 )
		{
			k=look(str[0]);
			if(k == -1)
				printf("����:%s ������\n", str[0]);
			else
		        peop[k].n=peop[k].n*ctn(str[2]);
		}
        else if ( strcmp(str[1],"����")==0 )
		{
			k=look(str[0]);
			if(k == -1)
				printf("����:%s ������\n", str[0]);
			else
				if( ctn(str[2]) == 0 )
					printf("�㲻����Ϊ���������������룡\n");
			
			    else
				    peop[k].n=peop[k].n/ctn(str[2]);
		}
		else if ( strcmp(str[1],"��")==0 )
		{
			k=look(str[0]);
			if( peop[k].n == 0 )
				printf("%s��ֵΪ��,������Ϊ������\n",peop[k].name);
			else
				if(k == -1)
					printf("����:%s ������\n", str[0]);
			    else
				peop[k].n=ctn(str[2])/peop[k].n;
		}
		else if ( strcmp(str[0],"���")==0 )
		{
			k=look(str[1]);
			if(k == -1)
				printf("����:%s ������\n", str[1]);
			else
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
			printf("������ĸ�ʽ�����⣬����������\n");
		gets(s);
	}
}
