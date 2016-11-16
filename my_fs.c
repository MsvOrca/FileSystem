#include<stdio.h>
#include<time.h>a

union type 
{
	 block *indirectnodei[16];
	 char body[128];
}

typedef struct{
	 union type;
}block;
typedef struct{
	 
}Dir;
typedef struct{
	 _Bool ForD;
	// time
	 int File_size;
	 block *direct;
	 block *indirect;
	 block *double_indirect
}Inode;
