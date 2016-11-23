#include"my_fs_function.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

void printTest(char *a)
{
	 int i = 0;
	 printf("PrintTest ====\n");
	 while(a[i] != 0)
	 {
		  printf("%d ",a[i]);
		  ++i;
	 }
	 printf("\nPrintfTestEnd =====\n");
}
void USER_INPUT()
{
	 int i=0;
	 scanf("%[^\n]",Usrinput);
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
void CLASSIFY_INCASE()
{
	 char cases[19][20]= {"myls" , "mycat" , "myshowfile","mypwd","mycd","mycp","mycpto","mycpfrom","mymkdir","myrmdir","myrm","mymv","mytouch", "myshowinode","myshowblock","mystate","mytree","command","byebye"};
}
void INPUT_TIME(char *current){
	 struct tm *t;
	 time_t timer;
	 int len;
	 timer = time(NULL);
	 t = localtime(&timer);

	 len = sprintf(current, "%d",t -> tm_year + 1900);
	 *(current + len) = '/';
	 len++;
	 len += sprintf(current + len, "%d", t -> tm_mon + 1);
	 *(current + len) = '/';
	 len++;
	 len += sprintf(current + len, "%d", t -> tm_mday);
	 *(current + len) = ' ';
	 len++;
	 len += sprintf(current + len, "%d", t -> tm_hour);
	 *(current + len) = ':';
	 len++;
	 len += sprintf(current + len, "%d", t -> tm_min);
	 *(current + len) = ':';
	 len++;
	 len += sprintf(current + len, "%d", t -> tm_sec);
}

void MY_LS()
{}
void MY_CAT()
{}
void MY_SHOWFILE()
{}
void MY_PWD()
{}//
void MY_CD()
{}//
void MY_CP()
{}
void MY_CPTO()
{}
void MY_CPFROM()
{}
void MY_MKDIR()
{}//
void MY_RMDIR()
{}//
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
void MY_TREE()
{}//
void COMMAND()
{}
