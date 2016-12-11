#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include"func.h"
int main()
{
	CurrentDir_Inumber=0;
	Dir *pRootDir;
	Dir *pCurrentDir;
	pRootDir = (Dir *)malloc(sizeof(Dir));
	pCurrentDir = (Dir *)malloc(sizeof(Dir));
	pRootDir -> pNextDir = NULL;
	pRootDir -> pSimilDir = NULL;
	pRootDir -> pPrevDir = NULL;
	strcpy(pRootDir -> name, "ROOT");
	pCurrentDir = pRootDir;

	// 파일시스템의 존재 여부 확인

	FILE *ifp=fopen("mymkfs.bin", "r");
	if(ifp==NULL)
	{
		printf("오류 : 파일시스템이 존재하지 않습니다.\n");
		return 0;
	}

	/// 파일시스템이 존재한다면 쉘 생성
	
	while(1)
	{
		int INcase=0;
		printf("[");
		MY_PWD(pRootDir,pCurrentDir);
		printf("]");
		printf("$ ");
		USER_INPUT();
		INcase=CLASSIFY_INCASE();
		switch(INcase)
		{
			case 1 : MY_LS(pCurrentDir,Usrbuf1,Usrbuf2,pRootDir);break;
			case 2 : MY_CAT(Usrbuf1,Usrbuf2,Usrbuf3[0],Usrbuf4,pCurrentDir);break;
			case 3 : MY_SHOWFILE(Usrbuf1, Usrbuf2, Usrbuf3, pCurrentDir);break;
			case 4 : MY_PWD(pRootDir, pCurrentDir);printf("\n");break;
			case 5 : pCurrentDir = MY_CD(pCurrentDir, Usrbuf1,pRootDir);break;
			case 6 : MY_CP();break;
			case 7 : MY_CPTO();break;
			case 8 : MY_CPFROM(Usrbuf1,Usrbuf2,pCurrentDir);break;
			case 9 : MY_MKDIR(pCurrentDir, Usrbuf1);break;
			case 10 : MY_RMDIR(pCurrentDir, Usrbuf1);break;
			case 11 : MY_RM(pCurrentDir,Usrbuf1);break;
			case 12 : MY_MV();break;
			case 13 : MY_TOUCH(pCurrentDir,Usrbuf1);break;
			case 14 : MY_SHOWINODE(Usrbuf1);break;
			case 15 : MY_SHOWBLOCK(Usrbuf1);break;
			case 16 : MY_STATE();break;
			case 17 : MY_TREE();break;
			case 18 : return 0;
			case 0 : system(Usrinput);break;//nedd patch
		}
		memset(Usrinput,0,100);
		memset(Usrcmd,0,20);
		memset(Usrbuf1,0,10);
		memset(Usrbuf2,0,10);
		memset(Usrbuf3,0,10);
	}
	return 0;
}
