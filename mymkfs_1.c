#include <stdio.h>
int main(void)
{
	FILE *ifp;
	ifp=fopen("mymkfs.bin", "wb");


	//BOOT BLOCK
	
	fwrite("             \n", strlen("             \n"), 1, ifp);




	// SUPER BLOCK 아이노드 사용여부
	
	fwrite(&super_block.inode_use1, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.inode_use2, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.inode_use3, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.inode_use4, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.inode_use5, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.inode_use6, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.inode_use7, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.inode_use8, sizeof(unsigned long long), 1, ifp);

	fwrite("\n", sizeof("\n"), 1, ifp);




	// SUPER BLOCK 데이터블록 사용여부
	
	fwrite(&super_block.data_block_use1, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use2, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use3, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use4, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use5, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use6, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use7, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use8, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use9, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use10, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use11, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use12, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use13, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use14, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use15, sizeof(unsigned long long), 1, ifp);
	fwrite(&super_block.data_block_use16, sizeof(unsigned long long), 1, ifp);

	fwrite("\n", sizeof("\n"), 1, ifp);



	
	// INODE LIST : 파일 종류, 파일 생성 날짜, 파일 크기 , data block정보(문자? 숫자?)

	for(int i=0; i<512; i++)
	{
		fwrite(&file_ype, sizeof(char), 1, ifp);                                   //파일 종류 : 일반/디렉토리
		fwrite(&time_array, sizeof(char), sizeof(time_array)/sizeof(char), ifp);   //파일 생성시간
		fwrite(&size, sizeof(int), 1, ifp);                                        //파일 크기
		fwrite(&direct_block, sizeof(int), 1, ifp);                                //파일의 다이렉트 블록
		fwrite(&single_indirect_block, sizeof(int), 1, ifp);                       //파일의 인다이렉트 블록
		fwrite(&double_indirect_block, sizeof(int), 1, ifp);                       //파일의 더블인다이렉트 블록
		fwrite("\n", sizeof("\n"), 1, ifp);
	}



	// DATA BLOCK : 파일 데이터 저장

	for(int i=0; i<1024; i++)
	{
		if(     )
			fwrite(&file_data, sizeof(char), sizeof(file_data) / sizeof(char), ifp); //파일에 대한 정보 저장
		else
			fwrite(&block_num, sizeof(int), 1, ifp); //인다렉트 블록일 경우 블록의 주소 저장

		fwrite("\n", sizeof("\n"), 1, ifp);
	}



		

	fclose(ifp);

	return 0;
}
