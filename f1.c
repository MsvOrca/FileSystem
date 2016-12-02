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
void MY_TOUCH(Dir *pndir)
{
	 
	 int i,EXF=0;
	 for(i=54;i<512;i++)
	 {
		  if(L_Inode[i]!=0)
		  {
				printf("filein\n");
//		  if(strcmp(SB_Inode[i]->filename,Usrbuf1))
///		  {
	//			EXF=1;
	//			break;
	//	  }
	 }
	 }
	 if(EXF==1)
	 {
		 INPUT_TIME(*L_Inode[i]);
	 }
	 else
	 {
	 i=CHK_INODE();
	 printf("%d\n",i);
	 MAKEFILE(i,pndir,0,0);
	 }

}
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

int CHK_INODE()
{
	 int i;
	 for(i=54;i<512;i++)
	 {
		  if(L_Inode[i]==0)
				break;
	 }
	 return i;
}
void MAKEFILE(int Inode_Num,Dir *Target_Dir, _Bool F_D,int fsize)//0-file 1-dir
{
	 Inode New_file;
	 L_Inode[Inode_Num]=&New_file;
	 File_List New_filelist;
	 strcpy(New_filelist.file_name,Usrbuf1);
	 New_filelist.Inode_Num=(short)Inode_Num;
	 
	 if(Target_Dir->num_file=0)//nowdir have no file
	 {
	 Target_Dir->pFileData=&New_filelist;
	 }
	 /*
	 else
	 {
		  int x;
		  File_List *temp;
		  for(x=0;x<;x++)
		  {
				temp=L_Inode[Inode_Num]->next;
				
		  }
	 }
	 */
	 New_file.inodenum=Inode_Num;
	 if(F_D==0)
		  New_file.ForD=0;
	 else
		  New_file.ForD=1;
 INPUT_TIME(New_file);
	 New_file.File_size=fsize;
}


