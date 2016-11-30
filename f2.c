#include"func.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

void INPUT_TIME(Inode test){
	struct tm *t;
	time_t timer;
	timer = time(NULL);
	t = localtime(&timer);

	test.Timed.year = t -> tm_year + 1900;
	test.Timed.mon = t -> tm_mon + 1;
	test.Timed.day = t -> tm_mday;
	test.Timed.hour = t -> tm_hour;
	test.Timed.min = t -> tm_min;
	test.Timed.sec = t -> tm_sec;

	return;
}

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
void INSERT(Dir *pParentDir, Dir *pSonDir, Dir *pTmpDir, char *inp_name)
{
	strcpy(pTmpDir -> name, inp_name);
	if(pParentDir -> pNextDir == NULL)
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
Dir *MY_CD(Dir *pParentDir, char *inp_name)
{
	Dir *pSonDir;
	pSonDir = (Dir *)malloc(sizeof(Dir));
	pSonDir = pParentDir -> pNextDir;


	if(inp_name[0] == '/')
	{

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
	return pParentDir;
}
void MY_MKDIR(Dir *pParentDir, char *inp_name)
{
	Dir *pTmpDir, *pSonDir;
	pTmpDir = (Dir *)malloc(sizeof(Dir));
	pSonDir = (Dir *)malloc(sizeof(Dir));
	pTmpDir = MAKEDIR();
	pSonDir = pParentDir -> pNextDir;

	if(inp_name != NULL)
	INSERT(pParentDir, pSonDir,pTmpDir, inp_name);
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
}
void MY_TREE(Dir *pRootDir)
{
	Dir *pTmpDir;
	pTmpDir = (Dir *)malloc(sizeof(Dir));
	//pTmpDir = pRootDir -> pNext;

	printf("/\n");
	while(1)
	{

	}

}
void MY_LS(Dir *pParentDir)
{
	File_List *pTmp_File;
//	pTmp_File = (File_List *)malloc(sizeof(File_List));??
	pTmp_File = pParentDir -> pFileData;
	//while(pTmp_File != NULL)
	short x=pParentDir->num_file;
	for(;x>0;x--)
	{
		printf("%s ", pTmp_File -> file_name);
		pTmp_File = pTmp_File -> Next;
	}
	printf("\n");
}
