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
	 i=CLASSIFY_INPUT(Usrbuf3,i);
	 CLASSIFY_INPUT(Usrbuf4,i);
}
int CLASSIFY_INPUT(char buf[],int i)
{
	 int x=0;
	 for(;i<125;i++)
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
				return x+1;
	 }
	 if(x==18)
		  return 0;
}

void MY_CAT(char file1[],char file2[],char link,char targetfile[],Dir *pnowdir)//
{
	 FILE *ifp=fopen("mymkfs.bin","rb");
	 if(link=='>')
	 {
		  File *plinkfile;
		  if(CMPNAME(pnowdir,file1,'n')==NULL)
				printf("mycat: %s: No such file or directory\n",file1);
		  else
		  {
				File_List *pfile = CMPNAME(pnowdir,file1,'n');
		  }
		  if(CMPNAME(pnowdir,file2,'n')==NULL)
				printf("mycat: %s: No such file or directory\n",file1);
		  else
		  {
				File_List *pfile = CMPNAME(pnowdir,file2,'n');
		  }
	 }
	 else
	 { 
		  if(CMPNAME(pnowdir,file1,'n')==NULL)
				printf("mycat: %s: No such file or directory\n",file1);
		  else
		  {
				File_List *pfile = CMPNAME(pnowdir,file1,'n');
				Inode *pinode=GOTOINODE((int)pfile->Inode_Num,'r',ifp);
				int blocknum=pinode->File_size/128;
				if(pinode->File_size%128>0)
					 blocknum++;
				File *file1=ROADING_FILE((int)pfile->Inode_Num,'f',blocknum);
				File *temp;
				temp=file1;
				for(int x=0;x<blocknum;x++)
				{
					 printf("%s",temp->file_type.file);
					 temp=temp->Next;
				}
		  }
		  if(CMPNAME(pnowdir,file2,'n')==NULL)
				printf("mycat: %s: No such file or directory\n",file1);
		  else
		  {
				File_List *pfile = CMPNAME(pnowdir,file2,'n');
		  }
	 }
	 fclose(ifp);
}
void MY_SHOWFILE(int first, int end, char *Usrbuf3, Dir *pCurrentDir)//
{
	 FILE *ifp=fopen("mymkfs.bin", "rb");	

	 int h=0;
	 int inode_num=0;
	 _Bool ForD=0;
	 int block_num [18528];                         // 한 개의 파일이 가질 수 있는 최대 블록 개수 : 96x96 + 96 + 1 = 18528
	 char data[128]={0};

	 short direct;
	 short single;
	 short double_indirect;

	 unsigned long long indirectinode[16]={0};      // 데이터 블록 번호 패킹
	 unsigned long long indirectinode2[16]={0};

	 int i=0x3FF;                                   // 000...0011 1111 1111

	 File_List *showfile;

	 Inode I_node={0};


	 // 파일 찾기

	 showfile=CMPNAME(pCurrentDir, Usrbuf3, 'x');

	 if(showfile==NULL)
		  printf("오류 : 해당 파일을 찾을 수가 없습니다.\n");
	 else
	 {
		  inode_num=showfile->Inode_Num;

		  fseek(ifp, 2+64+128+(32*inode_num), 0);
		  fread(&I_node, 32, 1, ifp);


		  // 다이렉트 블록

		  block_num[0]=I_node.direct;


		  // 싱글 인다이렉트 블록

		  if(single!=1024)
		  {
				fseek(ifp, 2+64+128+(32*512)+(128*single), 0);
				fread(indirectinode, sizeof(unsigned long long), 16, ifp);


				for(h=1; h<96; h++)
				{
					 block_num[h]=(indirectinode[h/6]>>((h%6)*10))&i;

					 if(block_num[h]==0)
						  break;

					 h=h-1;                   
				}
		  }

		  // 더블 인다이렉트 블록

		  if(double_indirect!=1024)
		  {
				fseek(ifp, 2+64+128+(32*512)+(128*double_indirect), 0);
				fread(indirectinode, sizeof(unsigned long long), 16, ifp);

				int j=0;  
				int block_num1[96]={0};

				for(j=0; j<96; j++)
				{
					 block_num1[j]=(indirectinode[j/6]>>((j%6)*10))&i;

					 if(block_num1[j]==0)
						  break;
				}
				for(int k=0; k<j; k++)
				{
					 fseek(ifp, 2+64+128+(32*512)+(128*block_num1[k]), 0);
					 fread(indirectinode2, sizeof(unsigned long long), 16, ifp);

					 for(; h<18528; h++)
					 {
						  block_num[h]=(indirectinode2[h/6]>>((h%6)*10))&i;

						  if(block_num[h]==0)
								break;
					 }
				}
		  }


		  // 지정된 바이트 부터 바이트 까지의 데이터 출력

		  for(int i=first/128; i<end/128; i++)
		  {
				fseek(ifp, 128+64+128+(32*512)+128*(block_num[i]-131), 0);
				fread(data, sizeof(char), 128, ifp);

				if(i!=end/128)
				{
					 for(int i=first%128; i<128; i++)
					 {
						  if(data[i]='\0')
								return;
						  else
								printf("%c", data[i]);
					 }
				}
				else
				{
					 for(int i=0; i<end%128; i++)
					 {
						  if(data[i]='\0')
								return;
						  else
								printf("%c", data[i]);
					 }
				}
		  }
	 }
	 return;
}



void MY_CP()
{}
void MY_CPTO(char My_Source_File[],char Dest_File[])
{
	 FILE *dest_file;
	 dest_file=fopen(Dest_File,"a");
	 fseek(dest_file,0,SEEK_END);
	 if(ftell(dest_file)>0)
	 {
		  char a;
		  printf("이미 파일이 존재합니다. 덮어쓰시겠습니까?[y/n]\n");
		  scanf("%c",&a);
		  if(a=='n')
		  {
				fclose(dest_file);
				dest_file=fopen("Dest_File","w");
				fclose(dest_file);
				return;
		  }
		  //파일구조체 로드


	 }
}
void MY_CPFROM(char Source_File[],char My_Dest_File[],Dir *nowdir)
{
	 if(strlen(My_Dest_File)>0)
	 {
		  FILE *source_file,*ifp;
		  ifp=fopen("mymkfs.bin","rb+");
		  int f_size,need_block;
		  if((source_file=fopen(Source_File,"r"))==NULL)
		  {
				printf("파일을 열 수 없습니다.\n");
				return;
		  }
		  if(CMPNAME(nowdir,My_Dest_File,'n')!=NULL)
		  {
				printf("현재디렉토리에 같은 이름의 파일이 있습니다.\n");
				return;
		  }
		  fseek(source_file,0,SEEK_END);
		  f_size=ftell(source_file);
		  need_block=f_size/128;
		  int need_inblock,need_dinblock;
		  if(need_block>=97)
		  {
				need_inblock=96;
				need_dinblock=(need_block-97)/96;
				if((need_block-97)%96>0)
					 need_dinblock++;
		  }
		  else
				need_inblock=need_block-1;


		  if(f_size%128>0)
				need_block++;
		  unsigned long long file_block[need_block];
		  memset(file_block,0,need_block);
		  unsigned long long file_dinblock[need_dinblock];
		  memset(file_dinblock,0,need_dinblock);
		  // 아이노드 기록 run
		  int inodenum;
		  inodenum=INODECHECK();
		  CHANGE_SBINODE(inodenum,ifp);
		  Inode new_inode;
		  new_inode.ForD=0;
		  INPUT_TIME(&new_inode);
		  new_inode.File_size=f_size;
		  //블록배정
		  new_inode.direct=(short)BLOCKCHECK();
		  CHANGE_SBBLOCK((int)new_inode.direct,ifp);
		  if(need_inblock==0)
				new_inode.indirect=1024;
		  if(need_inblock>0)
		  {
				new_inode.indirect=(short)BLOCKCHECK();
				CHANGE_SBBLOCK((int)new_inode.indirect,ifp);
		  }
		  if(need_dinblock>0)
		  {
				new_inode.double_indirect=(short)BLOCKCHECK();
				CHANGE_SBBLOCK((int)new_inode.double_indirect,ifp);
				for(int x=0;x<need_dinblock;x++)
				{
					 file_dinblock[x]=(unsigned long long)BLOCKCHECK();
					 CHANGE_SBBLOCK((int)file_dinblock[x],ifp);
				}
		  }
		  else
				new_inode.double_indirect=1024;
		  // run
		  GOTOINODE(inodenum,'w',ifp);
		  fwrite(&new_inode,sizeof(Inode),1,ifp);

		  file_block[0]=(unsigned long long)new_inode.direct;
		  for(int x=1;x<need_block;x++)
		  {
				file_block[x]=(unsigned long long)BLOCKCHECK();
				CHANGE_SBBLOCK((int)file_block[x],ifp);
		  }
		  //블록에다 쓰기

		  if(need_inblock>0)
		  {
				if(need_dinblock<0)
					 STORE_INDIRECT(&file_block[1],(int)new_inode.indirect,need_inblock);
				else
					 STORE_INDIRECT(&file_block[1],(int)new_inode.indirect,96);
		  }
		  if(need_dinblock>0)
		  {
				file_dinblock[need_dinblock]=0;
				STORE_INDIRECT(file_dinblock,(int)new_inode.double_indirect,need_dinblock+1);
				for(int x=0;x<need_dinblock;x++)
				{
					 file_block[need_block]=0;
					 STORE_INDIRECT(&file_block[97+96*x],(int)file_dinblock[x],96);
				}
		  }
		  for(int x=0;x<need_block-1;x++)
		  {
				GOTOBLOCK(file_block[x],'f','w',ifp);
				fseek(source_file,128*x,0);
				char tmpfile[128]={0};
				fread(tmpfile,sizeof(char),128,source_file);
				fwrite(tmpfile,sizeof(char),128,ifp);
		  }
		  GOTOBLOCK(file_block[need_block-1],'f','w',ifp);
		  fseek(source_file,128*(need_block-1),0);
		  char tmpfile[128]={0};
		  fread(tmpfile,sizeof(char),(f_size-(need_block*128)),source_file);
		  fwrite(tmpfile,sizeof(char),128,ifp);
		  fclose(source_file);
		  fclose(ifp);
		  //디렉토리에 추가
		  File_List *New_filelist;
		  New_filelist=(File_List*)calloc(1,sizeof(File_List));
		  strcpy(New_filelist->file_name,My_Dest_File);
		  New_filelist->Inode_Num=(short)inodenum;
		  int x;
		  File_List *temp;
		  temp=nowdir->pFileData;
		  for(x=0;x<nowdir->num_file-1;x++)
				temp=temp->Next;
		  temp->Next=New_filelist;
		  nowdir->num_file++;
	 }
	 else
		  printf("mycpfrom: missing file operand\n");

}
void MY_RM(Dir *nowdir,char name[])
{
	 int Target_inode;
	 int Target_block[1023]={0};
	 if(CMPNAME(nowdir,name,'n')!=0)
	 {
		  File_List *temp1,*temp2;
		  temp1=CMPNAME(nowdir,name,'p');
		  temp2=CMPNAME(nowdir,name,'n');
		  if(temp2->Next!=0)
				temp1->Next=temp2->Next;
		  else
				temp1->Next=0;
		  nowdir->num_file--;
		  Target_inode=(int)(temp2->Inode_Num);
		  free(temp2);
		  FILE *ifp;
		  ifp=fopen("mymkfs.bin","rb+");
		  Inode *temp_inode;
		  temp_inode=GOTOINODE(Target_inode,'r',ifp);
		  //블록 꺼내오기
		  int num_block=1;
		  Target_block[0]=temp_inode->direct;
		  if(temp_inode->indirect!=1024)
		  {
				num_block+=CHECK_INBLOCK(temp_inode->indirect,&Target_block[1],ifp);
				RM_SBBLOCK(temp_inode->indirect,ifp);
		  }
		  else
				RM_SBBLOCK(temp_inode->direct,ifp);
		  if(temp_inode->double_indirect!=1024)
		  {
				num_block+=CHECK_DINBLOCK(*temp_inode,&Target_block[num_block],ifp);
				int single[96];
				int temp,insingle;
				temp=temp_inode->File_size/128;
				if(temp_inode->File_size%128>0)
					 temp++;
				insingle=(temp-97)/96;
				if((temp-97)/96>0)
					 insingle++;
				CHECK_INBLOCK(temp_inode->double_indirect,single,ifp);
				for(int x=0;x<insingle;x++)
				{
					 RM_SBBLOCK(single[x],ifp);
				}
				RM_SBBLOCK(temp_inode->double_indirect,ifp);
		  }
		  num_block=temp_inode->File_size/128;
		  if(temp_inode->File_size%128>0)
				num_block++;
		  for(int x=0;x<num_block;x++)
		  {
				printf("rm block %d\n",Target_block[x]);
				RM_SBBLOCK(Target_block[x],ifp);
				//			char temp[128];
				//GOTOBLOCK  블럭으로 이동
		  }

		  //about inode
		  RM_SBINODE(Target_inode,ifp);
		  GOTOINODE(Target_inode,'w',ifp);
		  Inode tmp={0};
		  fwrite(&tmp,sizeof(Inode),0,ifp);
		  fclose(ifp);
	 }
	 else
		  printf("myrm : cannot remove '%s' : No such file or directory\n",name);
	 BLOCKCHECK();
}
void MY_MV(Dir *nowdir,char name[])
{
	 if(name[0]=='.' || name[0]=='/')
		  ;
	 else
	 {
		  File_List *temp;
		  temp=CMPNAME(nowdir,name,'n');
		  if(temp!=NULL)
		  {

				//경로 받으면 가능
		  }
		  else
				printf("myrm : cannot remove '%s' : No such file or directory",name);

		  //	  MY_TOUCH(nowdir,name);
		  //스캔 후 이름바꾸기
	 }
}
void MY_TOUCH(Dir *pndir,char name[])
{
	 File_List *temp;
	 int i;

	 if(strlen(name)>0)
	 {
		  temp=CMPNAME(pndir,name,'n');
		  if(temp!=NULL)
		  {
				i=temp->Inode_Num;
				Inode *tmp;
				Inode tmpnode={0};
				FILE *ifp=fopen("mymkfs.bin","rb+");
				tmp=GOTOINODE(i,'w',ifp);
				INPUT_TIME(tmp);
				fwrite(&tmpnode,sizeof(Inode),1,ifp);
				GOTOINODE(i,'w',ifp);
				fwrite(tmp,sizeof(Inode),1,ifp);
				fclose(ifp);
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
void MY_SHOWINODE(char *Usrbuf1)
{
	 // 아이노드 번호가 제대로 저장되었는지 확인

	 int index=0;  
	 while(Usrbuf1[index]!='\0')
	 {
		  if(48<=Usrbuf1[index]&&Usrbuf1[index]<=57)
				;
		  else
		  {
				printf("오류 : 아이노드의 번호를 다시 입력해주십시오.\n");
				return;
		  }

		  index++;
	 }


	 // 0을 포함한 양수가 저장되었다면 atoi를 사용하여 저장

	 int inode_num=atoi(Usrbuf1);


	 // 아이노드 번호가 제대로 저장되었는지 확인

	 if(0<=inode_num && inode_num<=511)
	 {
		  FILE *ifp=fopen("mymkfs.bin", "rb");

		  Inode I_node={0};

		  unsigned long long indirectinode[16]={0};
		  unsigned long long indirectinode2[16]={0};

		  int j=0;       // 지워도 되는건가?


		  // 아이노드 사용여부 체크

		  fseek(ifp, 2, 0);
		  fread(sb_inode, sizeof(unsigned int), 16, ifp);

		  int i=1;

		  if((sb_inode[inode_num/32]&(i<<(inode_num%32)))==0)
		  {
				printf("사용중인 아이노드가 아닙니다.\n");
				return;
		  }


		  // 사용중인 아이노드의 번호가 지정되었다면 지정된 번호의 아이노드 출력

		  else
		  {
				// mymkfs.bin으로 부터 아이노드 값을 읽어와 저장

				fseek(ifp, 2+64+128+sizeof(Inode)*inode_num, 0); 
				fread(&I_node, sizeof(Inode), 1, ifp);


				// 아이노드 정보 출력

				if(I_node.ForD==0)
					 printf("file type : regular file\n");
				else
					 printf("file type : directory file\n");

				printf("file size : %d byte\n", I_node.File_size);
				printf("modified time : %d/%02hd/%02hd/ %02hd:%02hd:%02hd\n", I_node.Timed.year, I_node.Timed.mon, I_node.Timed.day, I_node.Timed.hour, I_node.Timed.min, I_node.Timed.sec);
				int block_num[1023]={0};
				block_num[0]=I_node.direct;
				j=1;
				printf("data block list : %d", I_node.direct);


				// 싱글 인다이렉트 블록을 언패킹하여 블록번호 출력 (사용 안할시 1024 저장)

				int listnum;
				if(I_node.indirect!=1024)
				{
					 j=CHECK_INBLOCK(I_node.indirect,&block_num[1],ifp);
					 listnum=I_node.File_size/128;
					 if(I_node.File_size%128>0)
						  listnum++;
					 if(listnum>96)
						  listnum=97;
					 for(int k=1; k<listnum; k++)
						  printf(", %d", block_num[k]);
				}
				else
					 ;

				// 더블 인다이렉트 블록을 언패킹하여 블록번호 출력 (사용 안할시 1024 저장)

				if(I_node.double_indirect!=1024)
				{
					 int a=0;
					 a=CHECK_DINBLOCK(I_node,&block_num[listnum],ifp);
					 listnum=I_node.File_size/128;
					 if(I_node.File_size%128>0)
						  listnum++;
					 for(int k=1+j;k<listnum;k++)
						  printf(", %d", block_num[k]);
				}
				else
					 ;

		  }
		  printf("\n");
		  fclose(ifp);
	 }
	 else
		  printf("오류 : 입력 가능한 아이노드의 번호는 0번부터 511번까지 입니다.\n");
	 return;
}

void MY_SHOWBLOCK(char *Usrbuf1)
{
	 // 데이터블록의 번호가 제대로 입력되었는지 확인

	 int index=0;  
	 while(Usrbuf1[index]!='\0')
	 {
		  if(48<=Usrbuf1[index]&&Usrbuf1[index]<=57)
				;
		  else
		  {
				printf("오류 : 아이노드의 번호를 다시 입력해주십시오.\n");
				return;
		  }

		  index++;
	 }

	 // 0을 포함한 양수의 숫자가 입력되었다면 atoi를 사용해 저장

	 int a=atoi(Usrbuf1);


	 // 데이터블록의 번호가 제대로 입력되었는지 확인

	 if(0<=a&&a<=1023)
	 {
		  FILE *ifp=fopen("mymkfs.bin", "rb");

		  //Inode I_node={0};                          // 아이노드 -> 지워도 되는건가?

		  unsigned long long indirectinode[16]={0};    // 인다이렉트아이노드 -> 할지 안할지 아직 안 정함
		  char data[128]={0};                          // 일반 데이터


		  // 데이터블록 사용여부 체크

		  fseek(ifp, 2+64, 0);
		  fread(sb_block, sizeof(unsigned int), 32, ifp);

		  int i=1;
		  int check=0;

		  if((sb_block[a/32]&(i<<=(a%32)))==0)
		  {
				printf("사용중인 데이터블록이 아닙니다.\n");
				return;
		  }


		  // 사용중인 데이터블록의 번호가 입력되었다면 저장된 데이터 출력

		  else
		  {
				fseek(ifp, 2+64+128+sizeof(Inode)*512+128*(a), 0);
				fread(data, sizeof(char), 128, ifp);

				if(1)                   // 인다이렉트 아이노드인지 데이터인지 판별 -> 할지 안할지 아직 안 정함
					 printf("%s\n", data);
				else
					 printf("INDIRECT INODE\n");
				fclose(ifp);
		  }

	 }
	 else
		  printf("오류 : 입력 가능한 데이터블록의 번호는 0번부터 1023번까지 입니다.\n");
	 return;
}

// 데이터
void MY_STATE()//
{
	 FILE *ifp=fopen("mymkfs.bin","rb");
	 int inode_num=0;
	 int block_num=0;
	 int free_inode=0;
	 int free_block=0;
	 int i=1;
	 fseek(ifp,2,0);
	 fread(sb_inode,sizeof(int),16,ifp);
	 for(inode_num=0;inode_num<512;inode_num++)
	 {
		  if((sb_inode[inode_num/32]&(i<<(inode_num%32)))==0)
				free_inode++;
		  else
				;
	 }
	 fseek(ifp,2+64,0);
	 fread(sb_block,sizeof(int),32,ifp);
	 for(block_num=0;block_num<1024;block_num++)
	 {
		  if((sb_block[block_num/32]&(i<<(block_num%32)))==0)
				free_block++;
		  else
				;
	 }
	 printf("free inode : %d\n", free_inode);
	 printf("free data block : %d\n",free_block);
}

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
	 }

	 else
	 {
		  int x;
		  File_List *temp;
		  temp=Target_Dir->pFileData;
		  for(x=0;x<Target_Dir->num_file-1;x++)
				temp=temp->Next;
		  temp->Next=New_filelist;
	 }
	 Target_Dir->num_file++;
	 I_node->direct=(short)BLOCKCHECK();
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
	 I_node->indirect=1024;
	 I_node->double_indirect=1024;
	 fwrite(&tmpnode,sizeof(Inode),1,ifp);
	 GOTOINODE(Inode_Num,'w',ifp);
	 fwrite(I_node,sizeof(Inode),1,ifp);
	 fflush(ifp);
	 CHANGE_SBINODE(Inode_Num,ifp);

	 int Block_Num=BLOCKCHECK();
	 CHANGE_SBBLOCK(Block_Num,ifp);
	 //real block should change
	 int size,listnum;
	 File_List *tmp;
	 tmp=CMPNAME(Target_Dir,fname,'n');
	 listnum=Target_Dir->num_file-1;
	 Sdir temp;
	 temp.FD=F_D;
	 strcpy(temp.name,fname);
	 temp.inode=tmp->Inode_Num;
	 int *blocklist=MAKE_BLOCKLIST(CurrentDir_Inumber);
	 if(listnum<=16)
		  fseek(ifp,2+64+128+(32*512)+(128*blocklist[0])+(8*listnum),0);
	 else
		  fseek(ifp,2+64+128+(32*512)+(128*blocklist[(listnum/16)-1])+(8*((listnum%16)-1)),0);
					 fwrite(&temp,sizeof(Sdir),1,ifp);



	 fclose(ifp);

	 //parent direct have to increase size;
}
Inode *GOTOINODE(int a,char mode, FILE* ifp)
{

	 Inode *I_node;
	 I_node=(Inode*)calloc(1,sizeof(Inode));

	 // 지정된 번호의 아이노드 출력

	 fseek(ifp, 2+64+128+sizeof(Inode)*a, 0);  // 0,1,2번의 데이터블록의 크기 : 128, 64, 128
	 if(mode=='r')
		  fread(I_node, sizeof(Inode), 1, ifp);
	 else
		  free(I_node);
	 return I_node;
}
File *GOTOBLOCK(int blocknum,char type,char mode, FILE* ifp)
{
	 File *temp;
	 temp=(File *)calloc(1,sizeof(File));
	 fseek(ifp,2+64+128+(32*512)+(128*blocknum),0);
	 if(mode=='r')
	 {
		  if(type=='d')
				fread(temp->file_type.dir,sizeof(Sdir),16,ifp);
		  else if(type=='i')
				fread(temp->file_type.index,sizeof(unsigned long long),16,ifp);
		  else
				fread(temp->file_type.file,sizeof(char),128,ifp);
	 }
	 else
		  free(temp);
	 return temp;

}
int INODECHECK()
{
	 FILE *ifp=fopen("mymkfs.bin", "rb");

	 unsigned int i=1; 
	 int b=0;

	 fseek(ifp, 2, 0);   							       // 부트블록 크기만큼 지시자 이동
	 fread(sb_inode, sizeof(unsigned int), 16, ifp);   // sb_inode크기 만큼 읽어들인다
	 /*
	 //for bitcheck
	 printf ("------------SB_INODE CHECK------------\n");
	 int x;
	 int y;
	 for(y=15;y>=0;y--)
	 {
	 for(x=1;x<=32;x++)
	 {
	 if((sb_inode[y]>>(32-x)&1))
	 printf("1");
	 else
	 printf("0");
	 }
	 printf("\n");
	 }
	  */ //dd
	 for(;b<512;b++)
	 {

		  if((sb_inode[b/32]&(i<<(b%32)))==0)
				return b;
		  else{}
	 }
}
int BLOCKCHECK()
{
	 FILE *ifp=fopen("mymkfs.bin","rb");
	 fseek(ifp,2+64,0);
	 fread(sb_block,sizeof(unsigned int),32,ifp);

	 unsigned int i=1;
	 int a=0;
	 /*
	 //for block check
	 printf ("------------SB_BLOCK CHECK------------\n");
	 int x;
	 int y;
	 for(y=31;y>=0;y--)
	 {
	 for(x=1;x<=32;x++)
	 {
	 if((sb_block[y]>>(32-x)&1))
	 printf("1");
	 else
	 printf("0");
	 }
	 printf("\n");
	 }
	  */
	 for(;a<1024;a++)
	 {
		  if((sb_block[a/32]&(i<<(a%32)))==0)
				return a;
		  else
		  {}
	 }

}
void CHANGE_SBINODE(int Inode_Num,FILE* ifp)
{
	 fseek(ifp,2,0);
	 fread(sb_inode,sizeof(unsigned int),16,ifp);
	 unsigned int tmp=1;

	 int SBarry,SBdata;
	 SBarry=Inode_Num/32;
	 SBdata=Inode_Num%32;
	 //	 printf("SBarry : %d\nSBdata : %d\n",SBarry,SBdata);
	 sb_inode[SBarry]=(sb_inode[SBarry] | (tmp<<SBdata));
	 fseek(ifp,2,0);
	 fwrite(sb_inode,sizeof(unsigned int),16,ifp);
	 fflush(ifp);
	 //	 printf("Inodecheck : %d\n",INODECHECK());
}
void RM_SBINODE(int Inode_Num,FILE*ifp)
{
	 fseek(ifp,2,0);
	 fread(sb_inode,sizeof(unsigned int),16,ifp);
	 unsigned int tmp=1,tempSB;
	 int SBarry=Inode_Num/32;
	 int SBdata=Inode_Num%32;
	 tempSB=~sb_inode[SBarry];
	 sb_inode[SBarry]=~(tempSB | (tmp<<SBdata));
	 fseek(ifp,2,0);
	 fwrite(sb_inode,sizeof(unsigned int),16,ifp);
	 fflush(ifp);
}
void CHANGE_SBBLOCK(int Block_Num,FILE* ifp)
{
	 fseek(ifp,2+64,0);
	 fread(sb_block,sizeof(unsigned int),32,ifp);
	 unsigned int tmp=1;
	 int SBarry,SBdata;
	 SBarry=Block_Num/32;
	 SBdata=Block_Num%32;
	 sb_block[SBarry]=(sb_block[SBarry] | (tmp<<SBdata));
	 fseek(ifp,2+64,0);
	 fwrite(sb_block,sizeof(unsigned int),32,ifp);
	 fflush(ifp);
	 BLOCKCHECK();
	 // printf("Blockcheck : %d\n", BLOCKCHECK());
}
void RM_SBBLOCK(int Block_Num,FILE* ifp)
{
	 ifp=fopen("mymkfs.bin","rb+");
	 fseek(ifp,2+64,0);
	 fread(sb_block,sizeof(unsigned int),32,ifp);
	 unsigned int tmp=1,tempSB;
	 int SBarry,SBdata;
	 SBarry=Block_Num/32;
	 SBdata=Block_Num%32;
	 printf("SBarry  %d  SBdata  %d\n",SBarry,SBdata);
	 tempSB=~sb_block[SBarry];
	 sb_block[SBarry]=~(tempSB | (tmp<<SBdata));
	 printf("%u\n",sb_block[SBarry]);
	 fseek(ifp,2+64,0);
	 fwrite(sb_block,sizeof(unsigned int),32,ifp);
	 fflush(ifp);
	 fclose(ifp);
}
// 파일 스캔 함수  해당 디렉토리에서 이름같은 파일 있으면 그 리스트 리턴 아니면 NULL 리턴
File_List *CMPNAME(Dir *pndir, char name[],char prev)
{
	 int x;
	 File_List *prevtemp,*temp;
	 temp=pndir->pFileData;
	 for(x=0;x<pndir->num_file;x++)
	 {
		  //  printf("run");
		  if(!strcmp(temp->file_name,name))
		  {
				if(prev=='p')
					 return prevtemp;
				else
					 return temp;

		  }
		  prevtemp=temp;
		  temp=temp->Next;

	 }
	 return NULL;
}
int CHECK_INBLOCK(int inblock,int block_num[],FILE *ifp)
{
	 unsigned long long indirectinode[16]={0};
	 int point_num=0;
	 fseek(ifp,0,0);
	 fseek(ifp,2+64+128+sizeof(Inode)*512+128*(inblock),0);
	 fread(indirectinode, sizeof(unsigned long long),16,ifp);
	 int i=0x3FF;
	 unsigned long long j=0;
	 for(j=0;j<96;j++)
	 {
		  point_num++;
		  block_num[j]=(indirectinode[j/6]>>((j%6)*10))&i;
		  if(block_num[j]==0)
				break;

	 }
	 return point_num;
}
int CHECK_DINBLOCK(Inode I_node,int block_num[],FILE *ifp)//테스트 필요
{
	 fseek(ifp, 0, 0);
	 unsigned long long indirectinode[16]={0};
	 fseek(ifp, 2+64+128+sizeof(Inode)*512+128*(I_node.double_indirect), 0);
	 fread(indirectinode, sizeof(unsigned long long), 16, ifp);

	 int i=0x3FF; // 000...0011 1111 1111
	 unsigned long long j=0;  
	 int iblock_num[96]={0};
	 int z;
	 z=CHECK_INBLOCK(I_node.double_indirect,iblock_num,ifp);
	 int a=0;
	 for(int k=0; k<z; k++)
	 {
		  a+=CHECK_INBLOCK(iblock_num[k],&block_num[a],ifp);
	 }
	 return a;
}
void STORE_INDIRECT(unsigned long long block_num[], int store,int num_block)
{
	 FILE *ifp=fopen("mymkfs.bin", "rb+");

	 unsigned long long indirectinode[16]={0};
	 int k=0;
	 for(int i=0; i<16; i++)
		  for(int j=0; j<6; j++)
		  {
				indirectinode[i]|=(block_num[k]<<(j*10));
				k++;
		  }

	 fseek(ifp, 2+64+128+(32*512)+(128*store), 0);

	 fwrite(indirectinode, sizeof(unsigned long long), 16, ifp);

	 fflush(ifp);
	 fclose(ifp);
}
int *MAKE_BLOCKLIST(int inode_num)
{
	 FILE *ifp;
	 ifp=fopen("mymkfs.bin","rb");
	 Inode *temp_inode;
	 temp_inode=GOTOINODE(inode_num,'r',ifp);
	 int blocknum,inblocknum;
	 blocknum = temp_inode->File_size/128;
	 if(temp_inode->File_size%128>0)
		  blocknum++;
	 int *blocklist;
	 int templist[1023];
	 blocklist=(int*)calloc(blocknum,sizeof(int));
	 blocklist[0]=temp_inode->direct;
	 if(blocknum>1)
	 {
		  if(blocknum+1<=97)
		  {
				inblocknum=blocknum;
				CHECK_INBLOCK(temp_inode->indirect,&templist[1],ifp);
		  }
		  else
		  {
				inblocknum=96;
				CHECK_INBLOCK(temp_inode->indirect,&templist[1],ifp);
				CHECK_DINBLOCK(*temp_inode,&templist[inblocknum+1],ifp);
		  }
	 }
	 fclose(ifp);
	 for(int x=1;x<blocknum;x++)
	 {
		  blocklist[x]=templist[x];
		  printf("block %d",blocklist[x]);
	 }
	 return blocklist;
}

File *ROADING_FILE(int inode_num,char type,int blocknum)
{
	 FILE *ifp=fopen("mymkfs.bin","rb");
	 int *blocklist= MAKE_BLOCKLIST(inode_num);
	 File *head,*temp;
	 head=(File*)calloc(1,sizeof(File));
	 head=GOTOBLOCK(blocklist[0],type,'r',ifp);
	 temp=head;
	 for(int x=1;x<blocknum;x++)
	 {
		  printf("%d\n",(int)blocklist[x]);
		  temp->Next=GOTOBLOCK(blocklist[x],type,'r',ifp);
		  temp=temp->Next;
	 }
	 temp->Next=NULL;
	 return head;
}
