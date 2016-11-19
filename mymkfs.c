#include <stdio.h>
int main(void)
{
	FILE *ifp;
	ifp=fopen("mymkfs.txt", "w");


	//BOOT BLOCK
	fprintf(mymkfs,"          \n");




	// SUPER BLOCK 아이노드 사용여부
	fprintf(mymkfs,"%d %d %d %d %d %d %d %d\n", super_block.inode_use1, super_block.inode_use2, super_block.inode_use3, ... , super_block.inode_use8);




	// SUPER BLOCK 데이터블록 사용여부
	fprintf(mymkfs,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", super_block.data_block_use1, super_block.data_block_use2, super_block.data_block_use3, ... , super_block.data_block_use16);




	// INODE LIST : 파일 종류, 파일 생성 날짜, 파일 크기 , data block정보(문자? 숫자?)
	for(int i=0; i<512; i++)
		fprintf(mymkfs,"%d : %c %s %d %d %d %d\n", i, file_type, time, size, direct block, single indirect block, double indirect block);




	// DATA BLOCK : 파일 데이터 저장
	for(int i=0; i<1024; i++)
	{
		if( ) // 일반 데이터 저장
			fprintf(mymkfs, "%d : %s", i, 데이터);
		else // 인다이렉트 블록 ( 블록 번호/주소 저장)
			fprintf(mymkfs, "%d : %d/%p", i, 번호/주소);
	}

