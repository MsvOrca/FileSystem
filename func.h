//global virable
 
char Usrinput[100];
char Usrcmd[20];
char Usrbuf1[10];
char Usrbuf2[10];
char Usrbuf3[10];

//structures

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

	 char name[10];
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

//function

void INPUT_TIME(char *current);
void USER_INPUT();
int CLASSIFY_INPUT(char *buf,int i);
int CLASSIFY_INCASE();
void INSERT(Dir *pParentDir, Dir *pSonDir, Dir *pTmpDir, char *inp_name);
Dir *MAKEDIR(void);
void MY_LS(Dir *pParentDir);
void MY_CAT();
void MY_SHOWFILE();
void MY_PWD(Dir *pParentDir);//
Dir *MY_CD(Dir *pParentDir, char *inp_name);//
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
