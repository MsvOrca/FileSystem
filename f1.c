#include"func.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

void USER_INPUT()
{
	int i=0;
	scanf("%[^\n]",Usrinput);
	getchar();
	i=CLASSIFY_INPUT(Usrcmd,i);
	i=CLASSIFY_INPUT(Usrbuf1,i);
	i=CLASSIFY_INPUT(Usrbuf2,i);
	CLASSIFY_INPUT(Usrbuf3,i);
}
int CLASSIFY_INPUT(char buf[],int i)
{
	int x=0;
	for(;i<100;i++)
	{
		if(Usrinput[i]==' ' || Usrinput[i]=='\0')
		{
			buf[x]=0;
			break;
		}
		buf[x]=Usrinput[i];
		x++;
	}
	return i+1;
}
int CLASSIFY_INCASE()
{
	char cases[19][20]= {"myls" , "mycat" , "myshowfile","mypwd","mycd","mycp","mycpto","mycpfrom","mymkdir","myrmdir","myrm","mymv","mytouch", "myshowinode","myshowblock","mystate","mytree","command","byebye"};
	int x;
	for(x=0;x<19;x++)
	{
		if(strcmp(Usrcmd,cases[x])==0)
		{
			return x+1;
		}
	}
	if(x==19)
	{
		return 0;
	}
}

void MY_CAT()
{}
void MY_SHOWFILE()
{}
void MY_CP()
{}
void MY_CPTO()
{}
void MY_CPFROM()
{}
void MY_RM()
{}
void MY_MV()
{}
void MY_TOUCH()
{}
void MY_SHOWINODE()
{}
void MY_SHOWBLOCK()
{}
void MY_STATE()
{}
void COMMAND()
{
	char cominput[100];
	printf("please input your command...\n");
	system("pwd");
	scanf("%[^\n]",cominput);
	getchar();
	system(cominput);
}
