#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

char Usrinput[100];
char Usrcmd[20];
char Usrbuf1[10];
char Usrbuf2[10];
char Usrbuf3[10];


void INPUT_TIME(char *current);
void USER_INPUT();
int CLASSIFY_INPUT(char *buf,int i);
void MY_LS();
void MY_CAT();
void MY_SHOWFILE();
void MY_PWD();//
void MY_CD();//
void MY_CP();
void MY_CPTO();
void MY_CPFROM();
void MY_MKDIR();//
void MY_RMDIR();//
void MY_RM();
void MY_MV();
void MY_TOUCH();
void MY_SHOWINODE();
void MY_SHOWBLOCK();
void MY_STATE();
void MY_TREE();//
void COMMAND();
union type{
	 unsigned long long index[16];
	 char file[128];
};
typedef struct Block{
	 union type iorf;
}Block;
typedef struct{

}File;
typedef struct Dir{
	 struct Dir *pPrevDir; //상위 디렉토리
	 struct Dir *pSimilDir;//동위 디렉토리
	 struct Dir *pNextDir;//하위 디렉토리

	 File *pFileData;	 
}Dir;
typedef struct{
	 int inodenum;
	 _Bool ForD;
	 char time[20];
	 int File_size;
	 short direct;
	 short indirect;
	 short double_indirect;
}Inode;
int main()
{
	 int INcase=0;

	 USER_INPUT();
	 //	 while(1)
	 //	 {
	 //		  printf("[%s$]",directory);//now dir(pwd)
	 //		  scanf("%s",&Usrint);
	 switch(INcase)
	 {
		  case 1 : MY_LS();break;
		  case 2 : MY_CAT();break;
		  case 3 : MY_SHOWFILE();break;
		  case 4 : MY_PWD();break;
		  case 5 : MY_CD();break;
		  case 6 : MY_CP();break;
		  case 7 : MY_CPTO();break;
		  case 8 : MY_CPFROM();break;
		  case 9 : MY_MKDIR();break;
		  case 10 : MY_RMDIR();break;
		  case 11 : MY_RM();break;
		  case 12 : MY_MV();break;
		  case 13 : MY_TOUCH();break;
		  case 14 : MY_SHOWINODE();break;
		  case 15 : MY_SHOWBLOCK();break;
		  case 16 : MY_STATE();break;
		  case 17 : MY_TREE();break;
		  case 18 : COMMAND();break;
defalut : printf("myfs : %s : command not found.\n",Usrcmd);break;
	 }
	 //	 }
	 return 0;
}
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
{}
void MY_CD()
{}
void MY_CP()
{}
void MY_CPTO()
{}
void MY_CPFROM()
{}
void MY_MKDIR()
{}
void MY_RMDIR()
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
void MY_TREE()
{}
void COMMAND()
{}
