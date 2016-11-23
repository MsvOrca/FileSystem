#include <stdio.h>
#include <string.h>
#define INDIRECTINODE 0
#define DATA 1

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
		_Bool i_d;
	};
	union file_data file[1024]={0};




	// BOOT BLOCK

	fwrite("             \n", strlen("             \n"), 1, ifp);




	// 슈퍼블록 아이노드 사용여부 이진파일 출력
	fwrite(super_block.inode_use, sizeof(unsigned long long), 16, ifp);
	fwrite("\n", sizeof("\n"), 1, ifp);




	// 슈퍼블록 데이터블록 사용여부 이진파일 출력
	fwrite(super_block.data_block_use, sizeof(unsigned long long), 32, ifp);
	fwrite("\n", sizeof("\n"), 1, ifp);




	// 아이노드 리스트 : 파일 종류, 파일 생성 날짜, 파일 크기 , 저장 data block 이진파일 출력

	for(int i=0; i<512; i++)
	{
		fwrite(&inode[i], sizeof(inode[i]), 1, ifp);
		fwrite("\n", sizeof("\n"), 1, ifp);
	}




	// 데이터블록 : 파일 데이터 이진파일 출력

	for(int i=0; i<1024; i++)
	{
		if(file[i].i_d)
			fwrite(file[i].data, sizeof(char), sizeof(file[i].data), ifp); //파일에 대한 정보 저장
		else
			fwrite(file[i].indirectinode, sizeof(unsigned long long), 16, ifp); //인다렉트 블록일 경우 블록의 주소 저장

		fwrite("\n", sizeof("\n"), 1, ifp);
	}


	fclose(ifp);

	return 0;
}
