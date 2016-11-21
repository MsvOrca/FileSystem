#include<stdio.h>
#include<time.h>

void INPUT_TIME(char *current);
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
