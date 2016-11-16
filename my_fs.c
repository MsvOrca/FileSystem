#include<stdio.h>
#include<time.h>a

union type 
{
	 struct block *indirectnodei[16];
	 char body[128];
}

struct block{
	 union type;
}
struct Dir{
	 
}
struct Inode{
	 _Bool ForD;
	// time
	 int File_size;
	 struct block *direct;
	 struct block *indirect;
	 struct block *double_indirect
}
