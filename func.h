#include<stdio.h>
///global virable

char Usrinput[125];
char Usrcmd[25];
char Usrbuf1[25];
char Usrbuf2[25];
char Usrbuf3[25];
char Usrbuf4[25];
int CurrentDir_Inumber;//have to fix
unsigned int sb_inode[16];
unsigned int sb_block[32];

//structures
typedef struct{
	 _Bool FD;
	 char name[5];
	 short inode;
}Sdir;
union type{
	 unsigned long long index[16];
	 char file[128];
	 Sdir dir[16];
};
typedef struct Block{
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
	 union type file_type;
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
int INSERT(Dir *pParentDir, Dir *pSonDir, Dir *pTmpDir, char *inp_name);
Dir *MAKEDIR(void);
void MY_LS(Dir *pParentDir,char *inp_name,char*inp_name2,Dir *RootDir);//not yet sort
void MY_CAT(char file1[],char file2[],char link,char targetfile[],Dir *pnowdir);//not yet
void MY_SHOWFILE(char *, char *, char *, Dir *);//ok
void MY_PWD(Dir *pRootDir, Dir *pParentDir);//ok
Dir *MY_CD(Dir *pParentDir, char *inp_name,Dir *RootDir);//ok
void MY_CP(char source_file[],char dest_file[],Dir *pndir);//not yet
void MY_CPTO();//not yet
void MY_CPFROM(char Source_File[],char My_Dest_File[],Dir *nowdir);//ok
void MY_MKDIR(Dir *pParentDir,char *inp_name);//ok but prevdir not
void MY_RMDIR(Dir *pParentDir, char *inp_name);//is ford not
void MY_RM(Dir *nowdir,char name[]);//ok
void MY_MV();//not yet
void MY_TOUCH(Dir *pndir,char name[]);//ok  problem is file more than 4
void MY_SHOWINODE(char*);//ok
void MY_SHOWBLOCK(char*);//ok
void MY_STATE();//ok
void MY_TREE();//ok
File_List *PASS_FILELIST_NODE(Dir *Target_dir);
void MAKEFILE(int Inode_Num,char fname[],Dir *Target_Dir,_Bool F_D,int fsize);
int INODECHECK();
int BLOCKCHECK();
Inode *GOTOINODE(int a, char mode,FILE* ifp);
File *GOTOBLOCK(int blocknum,char type,char mode,FILE* ifp);
void CHANGE_SBINODE(int Inode_Num,FILE* ifp);
void RM_SBINODE(int Inode_Num,FILE* ifp);
void CHANGE_SBBLOCK(int Block_Num,FILE* ifp);
void RM_SBBLOCK(int Block_Num,FILE* ifp);
File_List *CMPNAME(Dir *pndir, char name[],char prev);
int CHECK_INBLOCK(int inblock,int block_num[],FILE *ifp);
int CHECK_DINBLOCK(Inode I_node,int block_num[],FILE *ifp);
void STORE_INDIRECT(unsigned long long block_num[],int store,int num_block);
int *MAKE_BLOCKLIST(int inode_num);
File *ROADING_FILE(int inode_num,char type,int blocknum);
<<<<<<< HEAD
int compare(const void*first, const void*second);
=======
void ADD_SDIR(Dir *Target_DIr,char fname[],int inodenum,_Bool F_D,FILE *ifp);
void RM_SDIR();
>>>>>>> 200c3a2ed960c0e8b542fa629697fd14779493b6
