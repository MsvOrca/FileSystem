#include <stdio.h>
#include <string.h>
int main(void)
{
	FILE *ifp;
	ifp=fopen("mymkfs.bin", "wb");


	// 부트 블록
	
	short boot_block={0};
	

	// 슈퍼 블록
	
	struct super_block{
		unsigned long long inode_use[16];       // 아이노드 사용여부
		unsigned long long data_block_use[32];  // 데이터블록 사용여부
	};
	struct super_block super_block={0}; 


	// 파일 아이노드
	
	struct inode{
		char file_type;                 // 파일 종류
		char time[30];                  // 파일 생성 시간
		int size;                       // 파일 크기
		short direct_block;             // 다이렉트 블록
		short single_indirect_block;    // 싱글 인다이렉트 블록
		short double_indirect_block;    // 더블 인다이렉트 블록
	};
	struct inode inode[512]={0};


	// 파일 데이터
	
	union file_data{
			unsigned long long indirectinode[16];  // 데이터 블록 번호 저장 (인다이렉트 아이노드)
			char data[128];                        // 일반 데이터 저장
		};
	union file_data file[1024]={0};


	

	// BOOT BLOCK
	
	fwrite("             \n", strlen("             \n"), 1, ifp);




	// SUPER BLOCK 아이노드 사용여부
	
	for(int i=0; i<16; i++)
		fwrite(&super_block.inode_use[i], sizeof(unsigned long long), 1, ifp);

	fwrite("\n", sizeof("\n"), 1, ifp);




	// SUPER BLOCK 데이터블록 사용여부
	
	for(int i=0; i<32; i++)
		fwrite(&super_block.data_block_use[i], sizeof(unsigned long long), 1, ifp);

	fwrite("\n", sizeof("\n"), 1, ifp);



	
	// INODE LIST : 파일 종류, 파일 생성 날짜, 파일 크기 , 저장 data block

	for(int i=0; i<512; i++)
	{
		fwrite(&inode[i].file_type, sizeof(char), 1, ifp);                                   //파일 종류 : 일반/디렉토리
		fwrite(inode[i].time, sizeof(char), sizeof(inode[i].time), ifp);   //파일 생성시간
		fwrite(&inode[i].size, sizeof(int), 1, ifp);                                        //파일 크기
		fwrite(&inode[i].direct_block, sizeof(int), 1, ifp);                                //파일의 다이렉트 블록
		fwrite(&inode[i].single_indirect_block, sizeof(int), 1, ifp);                       //파일의 인다이렉트 블록
		fwrite(&inode[i].double_indirect_block, sizeof(int), 1, ifp);                       //파일의 더블인다이렉트 블록
		fwrite("\n", sizeof("\n"), 1, ifp);
	}


	

	// DATA BLOCK : 파일 데이터 저장

	for(int i=0; i<1024; i++)
	{
		if(1)
			fwrite(file[i].data, sizeof(char), sizeof(file[i].data), ifp); //파일에 대한 정보 저장
		else
			fwrite(file[i].indirectinode, sizeof(unsigned long long), 16, ifp); //인다렉트 블록일 경우 블록의 주소 저장

		fwrite("\n", sizeof("\n"), 1, ifp);
	}
	

	fclose(ifp);

	return 0;
}
