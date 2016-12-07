#include <stdio.h>
void mystate(void);

int main(void)
{
	mystate();

	return 0;
}

void mystate(void)
{
	FILE *ifp=fopen("mymkfs.bin", "rb");

	int sb_inode[16]={0};                // 슈퍼블록 아이노드 & 데이터블록
	int sb_block[32]={0}; 

	int inode_num=0;
	int block_num=0;

	int free_inode=0;                    // 사용 가능한 아이노드 & 데이터블록 개수
	int free_block=0;

	int i=1;


	// 아이노드 사용여부 체크

	fseek(ifp, 2, 0);
	fread(sb_inode, sizeof(int), 16, ifp);



	for(inode_num=0; inode_num<512; inode_num++)
	{
		if((sb_inode[inode_num/32]&(i<<(inode_num%32)))==0)
			free_inode++;
		else
			;
	}


	// 데이터블록 사용여부 체크

	fseek(ifp, 2+64, 0);
	fread(sb_block, sizeof(int), 32, ifp);


	for(block_num=0; block_num<1024; block_num++)
	{
		if((sb_block[block_num/32]&(i<<(block_num%32)))==0)
			free_block++;
		else
			;
	}


	// 사용 가능한 아이노드, 데이터블록의 개수 출력

	printf("free inode : %d\n", free_inode);
	printf("free data block : %d\n", free_block);

	return;
}
