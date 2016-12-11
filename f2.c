#include"func.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
//fixed it
void INPUT_TIME(Inode *test){
	 struct tm *t;
	 time_t timer;
	 timer = time(NULL);
	 t = localtime(&timer);

	 test->Timed.year = t -> tm_year + 1900;
	 test->Timed.mon = t -> tm_mon + 1;
	 test->Timed.day = t -> tm_mday;
	 test->Timed.hour = t -> tm_hour;
	 test->Timed.min = t -> tm_min;
	 test->Timed.sec = t -> tm_sec;

	 return;
}
void OUTPUT_TIME(File_List *pFileData)
{
	 Inode *Tmp_Inode;
	 FILE *ifp;
	 ifp = fopen("mymkfs.bin", "r");
	 Tmp_Inode = (Inode *)malloc(sizeof(Inode));
	 Tmp_Inode = GOTOINODE(pFileData -> Inode_Num, 'r', ifp);


	 switch((int)Tmp_Inode -> ForD)
	 {
		  case 1 :
				printf("d ");
				break;
		  default :
				printf("- ");
				break;
	 }

	 printf("%4d ", Tmp_Inode -> File_size);

	 printf("%d/", Tmp_Inode -> Timed.year);
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
Dir *RELATIVE_PATH(Dir *pParentDir, char *pDir)
{
	 char Tmp_name[4];
	 Dir *pSonDir;
	 pSonDir = (Dir *)malloc(sizeof(Dir));
	 pSonDir = pParentDir;
	 int x=0;
	 int i = 0;
	 while(1)
	 {
		  x = 0;
		  while(i < 10)
		  {
				Tmp_name[x] = 0;
				printf("INPUT LETTER :%c\n", pDir[i]);
				if(pDir[i]=='/' || pDir[i] == '\0')
				{
					 Tmp_name[x] = 0;
					 i++;
					 break;
				}
				Tmp_name[x] = pDir[i];
				x++;
				i++;
		  }
		  printf("STACKED DATA: %s\n", Tmp_name);
		  if(strcmp(Tmp_name, ".") == 0)
		  {
				printf("WORKING\n");
				printf("CurrentNAME: %s\n", pSonDir -> name);
				continue;
		  }
		  else if(Tmp_name[0] == 0)
		  {
				printf("END\n");
				return pSonDir;
		  }
		  else if(strcmp(Tmp_name, "..") == 0)
		  {
				if(pSonDir -> pPrevDir != NULL)
				{
					 printf("2WORKING\n");
					 pSonDir = pSonDir -> pPrevDir;
					 continue;
				}
				else
					 return pSonDir;
		  }
		  else
				while(pSonDir -> pNextDir != NULL)
				{
					 if(strcmp(pSonDir -> pNextDir -> name, Tmp_name) == 0)
					 {
						  pSonDir = pSonDir -> pNextDir;
						  if(pDir[i] == '\0')
								return pSonDir;
						  break;
					 }
					 else
						  if(pSonDir  -> pNextDir!= NULL)
						  {
								if(pSonDir -> pNextDir -> pSimilDir != NULL)
								{
									 pSonDir -> pNextDir = pSonDir -> pNextDir -> pSimilDir;
									 break;
								}
								else
								{
									 return NULL;
								}
						  }
				}
	 }
}
Dir *ABSOLUTE_PATH(Dir *RootDir, char *pDir)
{
	 char Tmp_name[4];
	 Dir *pSonDir;
	 pSonDir = (Dir *)malloc(sizeof(Dir));
	 pSonDir = RootDir;
	 int x=0;
	 int i = 1;
	 while(1)
	 {
		  x = 0;
		  while(i < 10)
		  {
				if(pDir[i]=='/' || pDir[i] == '\0')
				{
					 Tmp_name[x] = 0;
					 i++;
					 break;
				}
				Tmp_name[x] = pDir[i];
				x++;
				i++;
		  }
		  while(pSonDir -> pNextDir != NULL)
		  {
				if(strcmp(pSonDir -> pNextDir -> name, Tmp_name) == 0)
				{
					 pSonDir = pSonDir -> pNextDir;
					 if(pDir[i] == '\0')
						  return pSonDir;
					 break;
				}
				else
					 if(pSonDir  -> pNextDir!= NULL)
					 {
						  if(pSonDir -> pNextDir -> pSimilDir != NULL)
								pSonDir -> pNextDir = pSonDir -> pNextDir -> pSimilDir;
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
}
//
Dir *MAKEDIR()
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

int INSERT(Dir *pParentDir, Dir *pSonDir, Dir *pTmpDir, char *inp_name)
{
	 int i;
	 i=INODECHECK();
	 strcpy(pTmpDir -> name, inp_name);
	 if(pSonDir == NULL)
	 {
		  pTmpDir -> pPrevDir = pParentDir;
		  pParentDir -> pNextDir = pTmpDir;
	 }
	 else
	 {
		  pTmpDir -> pPrevDir = pParentDir;
		  while(pSonDir -> pSimilDir != NULL)
		  {
				pSonDir = pSonDir -> pSimilDir;
		  }
		  pSonDir -> pSimilDir = pTmpDir;
	 }
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
void MY_PWD(Dir *pRootDir, Dir *pParentDir)
{
	 Dir *pTmpDir;
	 pTmpDir = (Dir *)malloc(sizeof(Dir));
	 pTmpDir = pRootDir;
	 if(pParentDir == pRootDir)
		  printf("/");

	 else{
		  printf("/");
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
Dir *MY_CD(Dir *pParentDir, char *inp_name, Dir *RootDir)
{
	 Dir *pSonDir;
	 pSonDir = (Dir *)malloc(sizeof(Dir));
	 pSonDir = pParentDir -> pNextDir;

	 if(inp_name[0] == '/' && inp_name[1] != '\0')
	 {
		  pSonDir = ABSOLUTE_PATH(RootDir, inp_name);
		  if(ABSOLUTE_PATH(RootDir, inp_name) != NULL)
				pParentDir = pSonDir;
	 }
	 else if(inp_name[0] == '/' && inp_name[1] == '\0')
		  pParentDir = pSonDir = RootDir;
	 else if(inp_name[0] == '.')
	 {
		  pSonDir = RELATIVE_PATH(pParentDir, inp_name);
		  if(pSonDir != NULL)
				pParentDir = pSonDir;
	 }
	 else
	 {
		  while(pSonDir != NULL)
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
	 if(pSonDir == NULL)
		  printf("No Directory Found\n");
	 CurrentDir_Inumber=pParentDir->inode_num;
	 return pParentDir;
}
void MY_MKDIR(Dir *pParentDir, char *inp_name)
{
	 if(inp_name != NULL)
	 {
		  if(CMPNAME(pParentDir,inp_name,'n')==NULL)
		  {
				Dir *pTmpDir, *pSonDir;
				pTmpDir = (Dir *)malloc(sizeof(Dir));
				pSonDir = (Dir *)malloc(sizeof(Dir));
				pTmpDir = MAKEDIR();
				pSonDir = pParentDir -> pNextDir;


				INSERT(pParentDir, pSonDir, pTmpDir, inp_name);
		  }
		  else
				printf("mymkdir: cannot create directory '%s': File exists\n",inp_name);
	 }
	 else
		  printf("mymkdir : missing file operand\n");
}
void MY_RMDIR(Dir *pParentDir, char *inp_name)
{
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
void OUTPUT_LIST(File_List *pTmp_File, char *inp_name, char *inp_name2, short x)
{
	if(strcmp(inp_name, "-i") == 0)
		for(x;x>0;x--)
		{
			printf("%hd ", pTmp_File -> Inode_Num);
			printf(" %s\n", pTmp_File -> file_name);
			pTmp_File = pTmp_File -> Next;
		}
	else if(strcmp(inp_name, "-l") == 0)
		for(x;x>0;x--)
		{
			OUTPUT_TIME(pTmp_File);
			printf(" %s\n", pTmp_File -> file_name);
			pTmp_File = pTmp_File -> Next;
		}
	else if(strcmp(inp_name, "-li") == 0 || strcmp(inp_name, "-il") == 0)
		for(x;x>0;x--)
		{
			printf("%hd  ", pTmp_File -> Inode_Num);
			OUTPUT_TIME(pTmp_File);
			printf(" %s\n", pTmp_File -> file_name);
			pTmp_File = pTmp_File -> Next;
		}
	else
		for(x;x>0;x--)
		{
			printf("%s\n", pTmp_File -> file_name);
			pTmp_File = pTmp_File -> Next;
		}
}
//i
void MY_LS(Dir *pParentDir, char *inp_name, char *inp_name2, Dir *RootDir)
{
	File_List *pTmp_File;
	Dir *pSonDir;
	pSonDir = (Dir *)malloc(sizeof(Dir));
	short x=pParentDir->num_file;
	pSonDir = pParentDir -> pNextDir;
	pTmp_File = pParentDir -> pFileData;
	/**
	for(int a = 0 ; a < x; a++)
	{
		if(a == 0)
			pTmp_File[a] = pParentDir -> pFileData;
		else
			pTmp_File[a] = pTmp_File[a-1] -> Next;
		printf("TMP : %s\n", pTmp_File[a] -> file_name);
	}
	qsort(*pTmp_File, x, sizeof(File_List *), compare);
	for(int a = 0; a < x; a++)
		printf("2TMP : %s\n", pTmp_File[a] -> file_name);
	x = pParentDir -> num_file;
	**/
	if((inp_name[0] == '-' && inp_name2[0] == '\0') || inp_name[0] == '\0')
		OUTPUT_LIST(pTmp_File, inp_name, inp_name2, x);
	else
	{	
		if(inp_name2[0] =='\0')
			strcpy(inp_name2, inp_name);
		{
			pSonDir = MY_CD(pParentDir, inp_name2, RootDir);
			x = pSonDir -> num_file;
			pTmp_File = pSonDir -> pFileData;
			for(x-1; x > 0; x--)
			{
				pTmp_File = pTmp_File -> Next;
			}
		}
		OUTPUT_LIST(pTmp_File, inp_name, inp_name2, x);
	}
	free(pSonDir);
}
void MY_TREE(Dir *pRootDir)
{
	Dir *pSonDir;
	pSonDir = (Dir *)malloc(sizeof(Dir));
	pSonDir = pRootDir -> pNextDir;
	int cnt = 0;
	printf("/\n");
	while(1)
	{
		printf("--");
		for(int a = 0; a < cnt; a++)
			printf("---");
		printf("* %s\n", pSonDir -> name);
		if(pSonDir == NULL)
			return ;
		if(pSonDir -> pNextDir == NULL && pSonDir -> pSimilDir == NULL)
		{
			while(pSonDir -> pPrevDir -> pSimilDir != NULL || pSonDir -> pPrevDir != pRootDir)
			{
				pSonDir = pSonDir -> pPrevDir;
				cnt--;
			}
			if(pSonDir -> pPrevDir == pRootDir && pSonDir -> pSimilDir == NULL)
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
int compare(const void*first, const void *second)
{
	File_List *First_Name = (File_List *)first;
	File_List *Second_Name = (File_List *)second;
	printf("\nF: %s\nS: %s\n%d\n\n",First_Name -> file_name, Second_Name -> file_name, strcmp((First_Name -> file_name),(Second_Name -> file_name)));

	return strcmp((First_Name -> file_name),(Second_Name -> file_name));
}
void LOAD_DATA()
{
	File *head;
}
