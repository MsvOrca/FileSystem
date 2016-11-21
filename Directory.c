#include <stdio.h>

typedef struct File{

}File;
typedef struct Dir{
	Dir *pPrevDir; //상위 디렉토리
	Dir *pSimilDir;
	Dir *pNextDir;

	File *pFileData;	 
}Dir;
typedef struct{
	 _Bool ForD;
	 char time[20];
	 int File_size;
	 Block *direct;
	 Block *indirect;
	 Block *double_indirect;
}Inode;
int main()
{

}
