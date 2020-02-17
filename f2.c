#include"func.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
void INPUT_TIME(Inode *test){//시간을 넣는 함수
	 struct tm *t;
	 time_t timer;
	 timer = time(NULL);
	 t = localtime(&timer);
	 test->Timed.year = t -> tm_year + 1900;//time 헤더에서 부터 가져와서 Inode 구조체에 Timed라는 구조체를 선언하여 값을 입력해//time 헤더에서 부터 가져와서 Inode 구조체에 Timed라는 구조체를 선언하여 값을 입력해줌
	 test->Timed.mon = t -> tm_mon + 1;
	 test->Timed.day = t -> tm_mday;
	 test->Timed.hour = t -> tm_hour;
	 test->Timed.min = t -> tm_min;
	 test->Timed.sec = t -> tm_sec;

	 return;
}
void OUTPUT_TIME(File_List *pFileData)//시간을 출력하는 함수
{
	 Inode *Tmp_Inode;
	 FILE *ifp;
	 ifp = fopen("mymkfs.bin", "r");
	 Tmp_Inode = (Inode *)malloc(sizeof(Inode));
	 Tmp_Inode = GOTOINODE(pFileData -> Inode_Num, 'r', ifp);


	 switch((int)Tmp_Inode -> ForD)//디렉토리인지 파일인지 타입을 알려줌
	 {
		  case 1 :
				printf("d ");
				break;
		  default :
				printf("- ");
				break;
	 }

	 printf("%4d ", Tmp_Inode -> File_size);//파일 사이즈를 출력해줌

	 printf("%d/", Tmp_Inode -> Timed.year);//시간들을 10을 넘을 경우 11이런식으로 아니면 08 이런식으로 출력하게 설정
	 if(Tmp_Inode -> Timed.mon < 10)
		  printf("0");
	 printf("%d/", Tmp_Inode -> Timed.mon);
	 if(Tmp_Inode -> Timed.day < 10)
		  printf("0");
	 printf("%d ", Tmp_Inode -> Timed.day);
	 if(Tmp_Inode -> Timed.hour < 10)
		  printf("0");
	 printf("%d:", Tmp_Inode -> Timed.hour);
	 if(Tmp_Inode -> Timed.min < 10)
		  printf("0");
	 printf("%d:", Tmp_Inode -> Timed.min);
	 if(Tmp_Inode -> Timed.sec < 10)
		  printf("0");
	 printf("%d", Tmp_Inode -> Timed.sec);
}
void MY_TREE(Dir *pParentDir, Dir *pRootDir, char *inp_name)//트리를 출력하게 하는 함수
{
	 Dir *pSonDir;
	 pSonDir = (Dir *)malloc(sizeof(Dir));
	 pSonDir = pParentDir -> pNextDir ;//하위  디렉토리를 임시 디렉토리에 복사
	 int cnt = 0;
	 if(inp_name[0] != '\0')
		  pSonDir = MY_CD(pParentDir, inp_name, pRootDir);
	 if(strcmp(pParentDir -> name, "ROOT") == 0)//루트디렉토리일 경우 루트라는 이름대신 /출력
		  printf("/\n");
	 else{
		  printf("%s\n", pParentDir -> name);//현재 디렉토리 출력하게 해줌
		 	pSonDir = pSonDir -> pNextDir;
	 }
	 while(1)
	 {
		  if(pSonDir == NULL)//하위 디렉토리가 존재하지 않으면 리턴
				return ;
		  printf("--");
		  for(int a = 0; a < cnt; a++)//cnt를 루프가 돌때마다 증가시켜 루프만큼 ---를 출력하게함
				printf("---");
		  printf("* %s\n", pSonDir -> name);//트리의 디렉토리 이름 출력
		  if(pSonDir -> pNextDir == NULL && pSonDir -> pSimilDir == NULL)
		  {
				while(pSonDir -> pPrevDir -> pSimilDir != NULL || pSonDir -> pPrevDir != pParentDir)
				{
					 pSonDir = pSonDir -> pPrevDir;
					 cnt--;
				}
				if(pSonDir -> pPrevDir == pParentDir && pSonDir -> pSimilDir == NULL)
				{
					 return;
				}
				pSonDir = pSonDir -> pSimilDir;
		  }
		  else if(pSonDir -> pNextDir == NULL)
		  {
				pSonDir = pSonDir -> pSimilDir;
		  }
		  else
		  {
				pSonDir = pSonDir -> pNextDir;
				cnt++;
		  }
	 }
}
Dir *RELATIVE_PATH(Dir *pParentDir, char *pDir, Dir *pRootDir)//상대 경로 리턴하는 함수
{
	 char Tmp_name[4];
	 Dir *pSonDir;
	 pSonDir = (Dir *)malloc(sizeof(Dir));
	 pSonDir = pParentDir; 
	 int x=0;
	 int i = 0;
	 int cnt = 0;
	 while(1)
	 {
		  x = 0;
		  while(i < 30)
		  {
				Tmp_name[x] = 0;
				if(pDir[i]=='/' || pDir[i] == '\0')// /나 널문자가 나올때까지 받음
				{
					 Tmp_name[x] = 0;// /나 널문자가 나오면 루프를 깨면서 나옴
					 i++;
					 break;
				}
				Tmp_name[x] = pDir[i];// /나 널문자가 아닐 경우 Tmp_name에 저장함
				x++;
				i++;
		  }
		  if(strcmp(Tmp_name, ".") == 0)//저장된 문자가 현재 디렉토리를 가리키면 컨티뉴로 루프 초기로 돌아감
		  {
				continue;
		  }
		  else if(Tmp_name[0] == 0)//저장된 문자가 없으면 입력 종료로 판단하고 리턴값을 주면서 함수 종료 시킴
		  {
				return pSonDir;
		  }
		  else if(strcmp(Tmp_name, "..") == 0)//저장된 문자가 상위디렉토리를 가리키면 상위 디렉토리로감
		  {
				if(pSonDir != pRootDir)
					 pSonDir = pSonDir -> pPrevDir;
				else//현재 디렉토리가 루트디렉토리이면 그냥 유지
					 pSonDir = pRootDir;
		  }
		  else//저장된 문자가 상위 현재, 혹은 널문자가아닌 그냥 일반적인 경로  판단
		  {
				while(1)
				{
					 if(pSonDir -> pNextDir == NULL && pDir[i] != '\0')
						  return NULL;
					 pSonDir = pSonDir -> pNextDir;
					 if(strcmp(pSonDir -> name, Tmp_name) == 0)
					 {
						  if(pSonDir -> pNextDir != NULL)
						  {
								break;
						  }
						  else
								if(pDir[i] == '\0')
									 return pSonDir;
								else
									 return NULL;
					 }
					 else
						  if(pSonDir -> pSimilDir != NULL)
						  {
								pSonDir = pSonDir -> pSimilDir;
						  }
						  else
						  {
								return NULL;
						  }
				}
		  }
	 }
}
Dir *ABSOLUTE_PATH(Dir *RootDir, char *pDir)//리턴값이 절대경로타겟 디렉토리인  함수
{
	 char Tmp_name[4];
	 Dir *pSonDir;
	 pSonDir = (Dir *)malloc(sizeof(Dir));
	 pSonDir = RootDir -> pNextDir;//루트 디렉토리의 하위 디렉토리로 초기화
	 int x=0;
	 int i = 1;
	 while(1)
	 {
		  x = 0;
		  while(i < 30)
		  {
				if(pDir[i]=='/' || pDir[i] == '\0')//상대랑마찬가지
				{
					 Tmp_name[x] = 0;
					 i++;
					 break;
				}
				Tmp_name[x] = pDir[i];
				x++;
				i++;
		  }
		  while(1)
		  {
				if(strcmp(pSonDir -> name, Tmp_name) == 0)
				{
					 if(pSonDir -> pNextDir != NULL)
						  pSonDir = pSonDir -> pNextDir;
					 else
						  if(pDir[i] == '\0')
								return pSonDir;
						  else
								return NULL;
					 break;
				}
				else
					 if(pSonDir -> pSimilDir != NULL)
						  pSonDir = pSonDir -> pSimilDir;
					 else
					 {
						  return NULL;
					 }
		  }
	 }
	 if(pSonDir -> pNextDir == NULL)
	 {
		  return NULL;
	 }
}
//
Dir *MAKEDIR()//디렉토리를 만드는 함수
{
	 Dir *pTmpDir;
	 pTmpDir = (Dir *)malloc(sizeof(Dir));
	 pTmpDir -> pFileData = (File_List *)malloc(sizeof(File));
	 pTmpDir -> pPrevDir = NULL;
	 pTmpDir -> pSimilDir = NULL;
	 pTmpDir -> pNextDir = NULL;

	 pTmpDir -> pFileData = NULL;

	 return pTmpDir;
}

int INSERT(Dir *pParentDir, Dir *pSonDir, Dir *pTmpDir, char *inp_name, char mode)
{//디렉토리를 디렉토리 밑에 만들어주는 함수
	 int i;
	 i=INODECHECK();
	 strcpy(pTmpDir -> name, inp_name);
	 if(pSonDir == NULL)//하위 디렉토리가 없을 경우
	 {
		  pTmpDir -> pPrevDir = pParentDir;
		  pParentDir -> pNextDir = pTmpDir;
	 }
	 else//하위 디렉토리가 있을 경우
	 {
		  pTmpDir -> pPrevDir = pParentDir;
		  while(pSonDir -> pSimilDir != NULL)
		  {
				pSonDir = pSonDir -> pSimilDir;
		  }
		  pSonDir -> pSimilDir = pTmpDir;
	 }
	 if(mode == 'N')//로딩 하는 디렉토리가 아닐경우 파일에 저장
	 {
	 pTmpDir->inode_num=i;
	 MAKEFILE(i,inp_name,pParentDir,1,2);
	 File_List *pPdir,*pNdir;
	 pPdir=(File_List*)calloc(1,sizeof(File_List));
	 pNdir=(File_List*)calloc(1,sizeof(File_List));
	 strcpy(pPdir->file_name,"..");
	 strcpy(pNdir->file_name,".");
	 pPdir->Inode_Num=(short)CurrentDir_Inumber;
	 pNdir->Inode_Num=(short)i;
	 pParentDir->pNextDir->pFileData=pPdir;
	 pParentDir->pNextDir->pFileData->Next=pNdir;
	 pParentDir->pNextDir->num_file=2;
	 return i;
	 }
}
void MY_PWD(Dir *pRootDir, Dir *pParentDir)//현재 위치를 출력해주는 함수
{
	 Dir *pTmpDir;
	 pTmpDir = (Dir *)malloc(sizeof(Dir));
	 pTmpDir = pRootDir;
	 if(pParentDir == pRootDir)
		  printf("/");//루트 디렉토리일경우 /만출력

	 else{
		  printf("/");//루트가 아닐경우 / 이후에 위치를 찾아서 출력
		  while(pTmpDir != pParentDir -> pPrevDir)
		  {
				pTmpDir = pTmpDir -> pNextDir;
				printf("%s/", pTmpDir -> name);
		  }
		  pTmpDir = pTmpDir -> pNextDir;
		  while(strcmp(pTmpDir->name,pParentDir->name) != 0)
		  {
				pTmpDir = pTmpDir -> pSimilDir;
		  }
		  printf("%s", pTmpDir -> name);
	 }

}
Dir *MY_CD(Dir *pParentDir, char *inp_name, Dir *RootDir)//위치를 이동하는 함수
{
	 Dir *pSonDir;
	 pSonDir = (Dir *)malloc(sizeof(Dir));
	 pSonDir = pParentDir -> pNextDir;

	 if(inp_name[0] == '/' && inp_name[1] != '\0')//절대 경로로 가는 함수
	 {
		  pSonDir = ABSOLUTE_PATH(RootDir, inp_name);
		  if(ABSOLUTE_PATH(RootDir, inp_name) != NULL)
				pParentDir = pSonDir;
	 }
	 else if(inp_name[0] == '/' && inp_name[1] == '\0')//루트로 가는 함수
		  pParentDir = pSonDir = RootDir;
	 else if(inp_name[0] == '.')//상대경로일경우 처음에 .이나와서 판단
	 {
		  pSonDir = pParentDir;
		  pSonDir = RELATIVE_PATH(pSonDir, inp_name, RootDir);
		  if(pSonDir != NULL)
				pParentDir = pSonDir;
	 }
	 else
	 {
		  while(pSonDir != NULL)//절대 혹은 상대가 아닐경우
		  {
				if(strcmp(pSonDir -> name, inp_name) == 0)
				{
					 pParentDir = pSonDir;
					 return pParentDir;
				}
				else
					 pSonDir = pSonDir -> pSimilDir;
		  }
	 }
	 CurrentDir_Inumber=pParentDir->inode_num;
	 if(pSonDir == NULL)//디렉토리를 찾지 못할 경우 No Directory Found라고함
		  printf("No Directory Found\n");
	 return pParentDir;
}
void MY_MKDIR(Dir *pParentDir, char *in_name)
{//새로운 디렉토리 형성
	 char inp_name[5]={0,};
	 strncpy(inp_name,in_name,4);
	if(inp_name != NULL)
	{//이름이 널이 아니면 실행
		 File_List *temp;
		 temp=CMPNAME(pParentDir,inp_name,'n');
		if(temp==NULL)//같은 이름이 존재하지 않으면 실행
		{
			Dir *pTmpDir, *pSonDir;
			pTmpDir = (Dir *)malloc(sizeof(Dir));
			pSonDir = (Dir *)malloc(sizeof(Dir));
			pTmpDir = MAKEDIR();
			pSonDir = pParentDir -> pNextDir;

				INSERT(pParentDir, pSonDir, pTmpDir, inp_name, 'N');
				//filefeedback
				FILE *ifp=fopen("mymkfs.bin","rb+");
				int size,listnum;
				File_List *tmp;
				tmp=CMPNAME(pParentDir,inp_name,'n');
				listnum=pParentDir->num_file-1;
				Sdir temp;
				temp.FD=1;
				strcpy(temp.name,inp_name);
				temp.inode=tmp->Inode_Num;
				int *blocklist=MAKE_BLOCKLIST(CurrentDir_Inumber);
				if(listnum<=16)
				{
					 fseek(ifp,2+64+128+(32*512)+(128*blocklist[0])+(8*listnum),0);
				}
				else
				{
					 int cal=(listnum/16)-1;
					 fseek(ifp,2+64+128+(32*512)+(128*blocklist[cal])+(8*((listnum%16)-1)),0);
				}
				fwrite(&temp,sizeof(Sdir),1,ifp);
				fclose(ifp);
		  }
		  else//같은 이름이 존재하면 실행
				printf("mymkdir: cannot create directory '%s': File exists\n",inp_name);
	 }
	 else//이름이 널이면 실행되지않음
		  printf("mymkdir : missing file operand\n");
}
void MY_RMDIR(Dir *pParentDir, char *inp_name)
{//존재하는 디렉토리를 파일리스트에서 지움
	 Dir *pTmpDir;

	 pTmpDir = (Dir *)malloc(sizeof(Dir));
	 pTmpDir = pParentDir -> pNextDir;

	 while(1)
	 {
		  if(pTmpDir -> pSimilDir == NULL)
				break;
		  if(strcmp(pTmpDir -> name, inp_name) == 0)
		  {
				if(pTmpDir = pParentDir -> pNextDir)
					 pParentDir -> pNextDir = pTmpDir -> pSimilDir;
				else
					 pTmpDir -> pSimilDir = pTmpDir -> pSimilDir -> pSimilDir;
				break;
		  }
		  pTmpDir = pTmpDir -> pSimilDir;
	 }
	 MY_RM(pParentDir,inp_name);
}
void OUTPUT_LIST(File_List *pTmp_File, char *inp_name, char *inp_name2, short x, char *pTmp_LETTER)
{//LS의 정보를 출력하는 함수
	 File_List *pTmp2_File;
	 pTmp2_File = (File_List *)malloc(sizeof(File_List));
	 pTmp2_File = pTmp_File;
	 while(1)
	 {
		  if(strcmp(pTmp_LETTER, pTmp2_File -> file_name) == 0)//옵션에 따라서 출력
		  {
				if(strcmp(inp_name, "-i") == 0)
				{
					 printf("%hd ", pTmp2_File -> Inode_Num);
					 printf(" %s\n", pTmp2_File -> file_name);
				}
				else if(strcmp(inp_name, "-l") == 0)
				{
					 OUTPUT_TIME(pTmp2_File);
					 printf(" %s\n", pTmp2_File -> file_name);
				}
				else if(strcmp(inp_name, "-li") == 0 || strcmp(inp_name, "-il") == 0)
				{
					 printf("%hd  ", pTmp2_File -> Inode_Num);
					 OUTPUT_TIME(pTmp2_File);
					 printf(" %s\n", pTmp2_File -> file_name);
				}
				else
				{
					 printf("%s\n", pTmp2_File -> file_name);
				}
				break;
		  }
		  else
		  {
				if(pTmp2_File == NULL)
					 break;
				pTmp2_File = pTmp2_File -> Next;
		  }
	 }
}

int compare(const void*first, const void *second)
{//이름 두개를 비교하는 함수
	 return strcmp((first),(second));
}
void MY_LS(Dir *pParentDir, char *inp_name, char *inp_name2, Dir *RootDir)
{//하위 디렉토리들 출력
	 File_List *pTmp_File;
	 char pTmp_LETTER[30][5];
	 Dir *pSonDir;
	 pSonDir = (Dir *)malloc(sizeof(Dir));
	 short x=pParentDir->num_file;
	 pSonDir = pParentDir -> pNextDir;
	 pTmp_File = pParentDir -> pFileData;
	 int b = 0;


	 if((inp_name[0] == '-' && inp_name2[0] == '\0') || inp_name[0] == '\0')
	 {
		  for(int a = 0 ; a < x; a++)
		  {
				strcpy(pTmp_LETTER[a], pTmp_File -> file_name);
				pTmp_File = pTmp_File -> Next;
				if(pTmp_File == NULL)
					 break;
		  }
		  qsort(pTmp_LETTER, x, sizeof(pTmp_LETTER[0]), compare);//사전식 배열을 위해 퀵소트 사용
		  pTmp_File = pParentDir -> pFileData;
		  for(int a = 0; a < x; a++)
		  {
				OUTPUT_LIST(pTmp_File, inp_name, inp_name2, x, pTmp_LETTER[a]);
		  }
	 }
	 else
	 {	//경로가 존재할경우 실행됨 절대or상대or 하위 디렉토리중 일부
		  if(inp_name2[0] =='\0')
				strcpy(inp_name2, inp_name);
		  pSonDir = MY_CD(pParentDir, inp_name2, RootDir);
		  x = pSonDir -> num_file;
		  pTmp_File = pSonDir -> pFileData;
		  for(int a = 0 ; a < x; a++)
		  {
				strcpy(pTmp_LETTER[a], pTmp_File -> file_name);
				pTmp_File = pTmp_File -> Next;
		  }
		  qsort(pTmp_LETTER, x, sizeof(pTmp_LETTER[0]), compare);
		  pTmp_File = pSonDir -> pFileData;
		  for(int a = 0; a < x; a++)
		  {
				OUTPUT_LIST(pTmp_File, inp_name, inp_name2, x, pTmp_LETTER[a]);
		  }
	 }
	 free(pSonDir);

}
int LOAD_DATA(int Inode_Num)
{//데이터를 로드함// 루트에 몇개가 있는지 비교
	 FILE *ifp = fopen("mymkfs.bin", "rb");
	 Inode *pTmp_Inode = GOTOINODE(Inode_Num, 'r', ifp);
	 int num = pTmp_Inode -> File_size/8;//숫자를 파일사이즈를 8로 나눠서 계산

	 return num;
}
void CONSTRUCT_BUILD(Dir *pCurrentDir)
{//파일리스트의 정보로 처음 구조를 빌드함
	 File_List *pTmp_File;
	 Inode *pTmp_Inode;
	 pTmp_File = (File_List *)malloc(sizeof(File_List));
	 FILE *ifp = fopen("mymkfs.bin", "rb");
	 Dir *pTmpDir, *pSonDir;
	 pTmpDir = (Dir *)malloc(sizeof(Dir));
	 pSonDir = (Dir *)malloc(sizeof(Dir));
	 pTmpDir = MAKEDIR();
	 pSonDir = pCurrentDir -> pNextDir;

	 int a;
	 pTmp_File = pCurrentDir -> pFileData;

	 for(a = 0; a < (pCurrentDir -> num_file); a++)
	 {
		  pTmp_Inode = GOTOINODE(pTmp_File -> Inode_Num, 'r', ifp);
		  if(pTmp_Inode -> ForD == 1)
		  {
				INSERT(pCurrentDir, pSonDir, pTmpDir, pTmp_File -> file_name, 'K');
		  }
		  pTmp_File = pTmp_File -> Next;
	 }
}
