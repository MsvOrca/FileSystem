#include"func.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

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
Dir *MAKEDIR()
{
	Dir *pTmpDir;
	pTmpDir = (Dir *)malloc(sizeof(Dir));
	pTmpDir -> pFileData = (File *)malloc(sizeof(File));
	pTmpDir -> pPrevDir = NULL;
	pTmpDir -> pSimilDir = NULL;
	pTmpDir -> pNextDir = NULL;

	pTmpDir -> pFileData = NULL;

	return pTmpDir;
}
void INSERT(Dir *pParentDir, Dir *pSonDir, Dir *pTmpDir)
{
	if(pParentDir -> pNextDir == NULL)
	{
		pParentDir -> pNextDir = pTmpDir;
		pTmpDir -> pPrevDir = pParentDir;
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
void MY_PWD()
{}
void MY_CD()
{}
void MY_MKDIR(Dir *pParentDir)
{
	Dir *pTmpDir, *pSonDir;
	pTmpDir = (Dir *)malloc(sizeof(Dir));
	pSonDir = (Dir *)malloc(sizeof(Dir));
	pTmpDir = MAKEDIR();
	pSonDir = pParentDir -> pNextDir;

	INSERT(pParentDir, pSonDir,pTmpDir);

}
void MY_RMDIR()
{}
void MY_TREE()
{}
