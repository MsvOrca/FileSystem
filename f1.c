#include"func.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
//block start at 54
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
	 char cases[18][20]= {"myls" , "mycat" , "myshowfile","mypwd","mycd","mycp","mycpto","mycpfrom","mymkdir","myrmdir","myrm","mymv","mytouch", "myshowinode","myshowblock","mystate","mytree","byebye"};

	 int x;
	 for(x=0;x<18;x++)
	 {
		  if(strcmp(Usrcmd,cases[x])==0)
		  {
				return x+1;
		  }
	 }
	 if(x==18)
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
{

}
void MY_CPFROM(char Source_File[],char Dest_File[])
{
	 FILE *sorce_file;
//sorce_file=fopen(Source_File,r);

}
void MY_RM()
{

}
void MY_MV()
{}
void MY_TOUCH(Dir *pndir,char name[])
{
	 Dir *temp;
	 temp=pndir;
	 if(strlen(name)>0)
	 {
		  int i,EXF=0;
		  int x;
		  File_List *temp;
		  temp=pndir->pFileData;
		  for(x=0;x<pndir->num_file;x++)
		  {
				if(!strcmp(temp->file_name,name))
				{
					 EXF=1;
					 break;
				}
				temp=temp->Next;

		  }
		  if(EXF==1)
		  {
				i=temp->Inode_Num;
		//cng		INPUT_TIME(*L_Inode[i]);
		  }
		  else
		  {
				i=INODECHECK();
				MAKEFILE(i,name,pndir,0,0);
		  }
	 }

	 else
		  printf("mytouch: missing file operand\n");
}
void MY_SHOWINODE(int inode_num)
{
	if(0<=inode_num && inode_num<=511)
	{
		FILE *ifp=fopen("mymkfs.bin", "rb");

		Inode I_node={0};

		// 인다이렉트 아이노드 (데이터블록)

		unsigned long long indirectinode[16]={0};
		unsigned long long indirectinode2[16]={0};


		// 아이노드 사용여부 체크

		fseek(ifp, 128, 0);
		fread(sb_inode, sizeof(unsigned long long), 8, ifp);

		int i=1;

		if((sb_inode[inode_num/64]&(i<<=(inode_num%64)))==0)
		{
			printf("사용중인 아이노드가 아닙니다.");
			return;
		}
		else
		{
			// 지정된 번호의 아이노드 출력

			fseek(ifp, 128+64+128+sizeof(Inode)*inode_num, 0);  // 0,1,2번의 데이터블록의 크기 : 128, 64, 128
			fread(&I_node, sizeof(Inode), 1, ifp);

			if(I_node.ForD==0)
				printf("file type : regular file\n");
			else
				printf("file type : directory file\n");

			printf("file size : %d byte\n", I_node.File_size);
			printf("modified time : %d/%02hd/%02hd/ %02hd:%02hd:%02hd\n", I_node.Timed.year, I_node.Timed.mon, I_node.Timed.day, I_node.Timed.hour, I_node.Timed.min, I_node.Timed.sec);
			printf("data block list : %d", I_node.direct);


			// 싱글 인다이렉트 블록

			if(I_node.indirect!=0)
			{
				fseek(ifp, 0, 0);       // 파일 지시자 위치 초기화

				fseek(ifp, 128+64+128+sizeof(Inode)*512+128*(I_node.indirect-131), 0);
				fread(indirectinode, sizeof(unsigned long long), 16, ifp);

				int i=0x3FF;            // 000...0011 1111 1111
				int j=0;
				int block_num[96]={0};

				for(j=0; j<96; j++)
				{
					block_num[j]=(indirectinode[j/6]>>((j%6)*10))&i;

					if(block_num[j]==0)
						break;
				}
				for(int k=0; k<j; k++)
					printf(", %d", block_num[k]);
			}
			else
				;

			// 더블 인다이렉트 블록 

			if(I_node.double_indirect!=0)
			{
				fseek(ifp, 0, 0);

				fseek(ifp, 128+64+128+sizeof(Inode)*512+128*(I_node.double_indirect-131), 0);
				fread(indirectinode, sizeof(unsigned long long), 16, ifp);

				int i=0x3FF; // 000...0011 1111 1111
				int j=0;  
				int block_num[96]={0};

				for(j=0; j<96; j++)
				{
					block_num[j]=(indirectinode[j/6]>>((j%6)*10))&i;

					if(block_num[j]==0)
						break;
				}
				for(int k=0; k<j; k++)
				{
					fseek(ifp, 0, 0);

					fseek(ifp, 128+64+128+sizeof(Inode)*512+128*(block_num[k]-131), 0);
					fread(indirectinode2, sizeof(unsigned long long), 16, ifp);

					int i=0x3FF;
					int h=0;
					int block_num2[96]={0};

					for(h=0; h<96; h++)
					{
						block_num2[h]=(indirectinode2[h/6]>>((h%6)*10))&i;

						if(block_num2[h]==0)
							break;
					}
					for(int k=0; k<h; k++)
						printf(", %d", block_num2[k]);
				}
			}
			else
				;

		}
	}
	else
		printf("오류 : 입력 가능한 아이노드의 번호는 0번부터 511번까지 입니다.\n");

	return;
}

void MY_SHOWBLOCK(int a)
{
	if(0<=a&&a<=1023)
	{
		FILE *ifp=fopen("mymkfs.bin", "rb");

		unsigned long long sb_inode[8]={0};          // 슈퍼블록 아이노드
		unsigned long long sb_block[16]={0};         // 슈퍼블록 데이터블록
		Inode I_node={0};                      // 아이노드
		unsigned long long indirectinode[16]={0};    // 인다이렉트아이노드
		char data[128]={0};                          // 일반 데이터


		// 데이터블록 사용여부 체크

		fseek(ifp, 128+64, 0);
		fread(sb_block, sizeof(unsigned long long), 16, ifp);

		int i=1;
		int check=0;

		if((sb_block[a/64]&(i<<=(a%64)))==0)
		{
			printf("사용중인 데이터블록이 아닙니다.");
			return;
		}
		else
		{
			fseek(ifp, 0, 0);

			//// 지정된 번호의 데이터블록의 데이터 출력

			// 부트블록

			if(a==0)
			{
				fread(data, sizeof(char), 128, ifp);

				printf("%s", data);
			}

			// 슈퍼블록 아이노드

			else if(a==1)
			{
				fseek(ifp, 128, 0);
				fread(sb_inode, sizeof(unsigned long long), 8, ifp);

				for(int i=0; i<8; i++)
					printf("%lld", sb_inode[i]);
			}

			// 슈퍼블록 데이터블록

			else if(a==2)
			{
				fseek(ifp, 128+64, 0);
				fread(sb_block, sizeof(unsigned long long), 16, ifp);

				for(int i=0; i<16; i++)
					printf("%lld", sb_block[i]);
			}

			// 아이노드

			else if(3<=a&&a<=130)
			{
				fseek(ifp, 128+64+128+sizeof(Inode)*(a-3), 0);
				fread(&I_node, sizeof(Inode), 1, ifp);

				printf("%d%d%hd%hd%hd%hd%hd%lld%hd%hd%hd", I_node.ForD, I_node.Timed.year, I_node.Timed.mon, I_node.Timed.day, I_node.Timed.hour, I_node.Timed.min, I_node.Timed.sec, I_node.File_size, I_node.direct, I_node.indirect, I_node.double_indirect);
			}

			// 데이터

			else if(a>=131)
			{
				fseek(ifp, 128+64+128+sizeof(Inode)*512+128*(a-131), 0);
				fread(data, sizeof(char), 128, ifp);

				if(1)                               // 인다이렉트 아이노드인지 데이터인지 판별
					printf("%s", data);
				else
					printf("INDIRECT INODE");
			}

		}
	}
	else
		printf("오류 : 입력 가능한 데이터블록의 번호는 0번부터 1023번까지 입니다.\n");

	return;
}

			// 데이터
void MY_STATE()
{}

void MAKEFILE(int Inode_Num,char fname[],Dir *Target_Dir, _Bool F_D,int fsize)//0-file 1-dir
{
	// load I_node
	 Inode *I_node;
	FILE *ifp=fopen("mymkfs.bin", "rb+");
	 I_node=GOTOINODE(Inode_Num,'r',ifp);

	 File_List *New_filelist;
	 New_filelist=(File_List*)calloc(1,sizeof(File_List));
	 strcpy(New_filelist->file_name,fname);
	 New_filelist->Inode_Num=(short)Inode_Num;
	 if(Target_Dir->num_file==0)//nowdir have no file
	 {
		  Target_Dir->pFileData=New_filelist;
		  Target_Dir->num_file++;
	 }

	 else
	 {
		  int x;
		  File_List *temp;
		  temp=Target_Dir->pFileData;
		  for(x=0;x<Target_Dir->num_file-1;x++)
		  {
				temp=temp->Next;

		  }

		  temp->Next=New_filelist;
		  Target_Dir->num_file++;
	 }
	 I_node->direct=(short)BLOCKCHECK();
//	 I_nodee.inodenum=Inode_Num;
	 if(F_D==0)
		  I_node->ForD=0;
	 else
	 {
		  I_node->ForD=1;
		  File_List *ParentDir,*NowDir;

	 }
	 INPUT_TIME(I_node);
	 I_node->File_size=fsize;
GOTOINODE(Inode_Num,'w',ifp);
Inode tmpnode={0};
fwrite(&tmpnode,sizeof(Inode),1,ifp);
GOTOINODE(Inode_Num,'w',ifp);
fwrite(I_node,sizeof(Inode),1,ifp);
CHANGE_SBINODE(Inode_Num,ifp);
fclose(ifp);

//	 L_Inode[Inode_Num]=&New_file;
//	 L_Inode[Target_Dir->inode_num]->inodenum+=2;
	 //parent direct have to increase size;
}
Inode *GOTOINODE(int a,char mode, FILE* ifp)
{

	Inode *I_node;
	I_node=(Inode*)calloc(1,sizeof(Inode));

	// 지정된 번호의 아이노드 출력

	fseek(ifp, 128+64+128+sizeof(Inode)*a, 0);  // 0,1,2번의 데이터블록의 크기 : 128, 64, 128
	if(mode=='r')
	fread(I_node, sizeof(Inode), 1, ifp);
	return I_node;
}
int INODECHECK()
{
	FILE *ifp=fopen("mymkfs.bin", "rb");

	int i=1,b=0;

	fseek(ifp, 128, 0);   							       // 부트블록 크기만큼 지시자 이동
	fread(sb_inode, sizeof(unsigned long long), 8, ifp);   // sb_inode크기 만큼 읽어들인다

for(;b<512;b++)
{
	if((sb_inode[b/64]&(i<<=(b%64)))==0)
return b;
		 //		printf("사용중인 아이노드가 아닙니다.");
	else{}
//		printf("사용중인 아이노드 입니다.");
}
}
int BLOCKCHECK()
{
	 FILE *ifp=fopen("mymkfs.bin","rb");
	 fseek(ifp,128+64,0);
	 fread(sb_block,sizeof(unsigned long long),16,ifp);
	 int i=1,a=0;
	 for(;a<1024;a++)
	 {
	 if((sb_block[a/64]&(i<<=(a%64)))==0)
		  return a;
	 else
	 {}
	 }

}
void LOADING_FS()
{
	 FILE *ifp=fopen("mymkfs.bin","rb");
	 fseek(ifp,128,0);
	 fread(sb_inode,sizeof(unsigned long long),8,ifp);
	 fread(sb_block,sizeof(unsigned long long),16,ifp);
}	
void CHANGE_SBINODE(int Inode_Num,FILE* ifp)
{
	 fseek(ifp,128,0);
	 fread(sb_inode,sizeof(unsigned long long),8,ifp);
	 unsigned long long tmp=1;
	 
	 int SBarry,SBdata;
	 SBarry=Inode_Num/64;
	 SBdata=Inode_Num%64;
	 sb_inode[SBarry]=sb_inode[SBarry] | tmp<<SBdata;
	 fseek(ifp,128,0);
	 fwrite(sb_inode,sizeof(unsigned long long),8,ifp);

}
