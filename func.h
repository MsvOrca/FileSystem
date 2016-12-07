#include<stdio.h>
//global virable

char Usrinput[100];
char Usrcmd[20];
char Usrbuf1[10];
char Usrbuf2[10];
char Usrbuf3[10];
int CurrentDir_Inumber;//have to fix
unsigned int sb_inode[16];
unsigned int sb_block[32];

//structures
union type{
	 unsigned long long index[16];
	 char file[128];
};
typedef struct Block{
	 _Bool blockuse;
	 union type iorf;
}Block;
typedef struct{//시간에 대한 구조체
	 int year;
	 short mon;
	 short day;
	 short hour;
	 short min;
	 short sec;
}Touched;
typedef struct file{
	 struct file *Next;
}File;
typedef struct file_list{
	 struct file_list *Next;
	 char file_name[5];
	 short Inode_Num;
}File_List;

typedef struct Dir{
	 struct Dir *pPrevDir; //상위 디렉토리
	 struct Dir *pSimilDir;//동위 디렉토리
	 struct Dir *pNextDir;//하위 디렉토리
	 int inode_num;
	 char name[5];
	 short num_file;
	 File_List *pFileData;	 
}Dir;
typedef struct{
//	 int inodenum;//
	 _Bool ForD;
	 Touched Timed;
	 int File_size;
	 short direct;
	 short indirect;
	 short double_indirect;
}Inode;

//function

void INPUT_TIME(Inode *test);
void USER_INPUT();
int CLASSIFY_INPUT(char *buf,int i);
int CLASSIFY_INCASE();
void INSERT(Dir *pParentDir, Dir *pSonDir, Dir *pTmpDir, char *inp_name);
Dir *MAKEDIR(void);
void MY_LS(Dir *pParentDir);
void MY_CAT();
void MY_SHOWFILE();
void MY_PWD(Dir *pRootDir, Dir *pParentDir);//
Dir *MY_CD(Dir *pParentDir, char *inp_name);//
void MY_CP();
void MY_CPTO();
void MY_CPFROM();
void MY_MKDIR();//
void MY_RMDIR(Dir *pParentDir, char *inp_name);//
void MY_RM();
void MY_MV();
void MY_TOUCH(Dir *pndir,char name[]);
void MY_SHOWINODE(int);
void MY_SHOWBLOCK(int);
void MY_STATE();
void MY_TREE();//
File_List *PASS_FILELIST_NODE(Dir *Target_dir);
void MAKEFILE(int Inode_Num,char fname[],Dir *Target_Dir,_Bool F_D,int fsize);
int INODECHECK();
int BLOCKCHECK();
Inode *GOTOINODE(int a, char mode,FILE* ifp);
void CHANGE_SBINODE(int Inode_Num,FILE* ifp);
void CHANGE_SBBLOCK(int Block_Num,FILE* ifp);
File_List *CMPNAME(Dir *pndir, char name[]);
