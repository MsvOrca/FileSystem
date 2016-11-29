#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INDIRECTINODE 0
#define DATA 1


// 부트 블록

short boot_block={0};


// 슈퍼 블록

struct super_block{
	unsigned long long inode_use[8];             // 아이노드 사용여부
	unsigned long long data_block_use[16];       // 데이터블록 사용여부
};
struct super_block super_block={0}; 


// 파일 아이노드

	// 아이노드 시간
	
	struct time{
		unsigned int year;
		unsigned short month;
		unsigned short date;
		unsigned short hour;
		unsigned short min;
		unsigned short sec;
	};

	// 아이노드

	struct inode{
		_Bool ForD;                                   // 파일 종류
		struct time time;                             // 파일 생성 시간
		unsigned long long File_size;                       // 파일 크기
		unsigned short direct;                        // 다이렉트 블록
		unsigned short single;                        // 싱글 인다이렉트 블록
		unsigned short double_indirect;               // 더블 인다이렉트 블록
	};

struct inode Inode[512]={0};


// 파일 아이노드 패킹

struct packing{
	unsigned int typenblock;
	unsigned long long timensize;
};


// 파일 데이터

union file_data{
	unsigned long long sb[16];                 // 슈퍼블록
	struct packing packed_inode[10];           // 패킹된 아이노드 리스트 저장
	unsigned long long indirectinode[16];      // 데이터 블록 번호 저장 (인다이렉트 아이노드)
	char data[128];                            // 일반 데이터 저장
	_Bool i_d;                                 // 인다이렉트 아이노드 or 일반 데이터
};
union file_data file[1024]={0};                // 데이터블록 [0]       : 부트블록
                                               //            [1,2]     : 슈퍼블록
 											   //            [3~54]    : 아이노드 리스트
                                               //            [55~1023] : 데이터블록


void mymkfs(struct super_block, struct inode *, union file_data *);


// 메인 함수 : mymkfs함수 호출

int main(void)
{
	mymkfs(super_block, Inode, file);
	return 0;
}


// mymkfs 함수 : 파일시스템 정보 이진파일로 '패킹'하여 저장

void mymkfs(struct super_block super_block, struct inode *inode, union file_data *file)
{

	FILE *ifp;
	ifp=fopen("mymkfs.bin", "wb");


	// 아이노드 정보 패킹

	for(int i=3; i<55; i++)
	{
		static int k=0;

		for(int j=0; j<10; j++)
		{
			file[i].packed_inode[j].typenblock |= Inode[k].ForD << 18;
			file[i].packed_inode[j].typenblock |= Inode[k].direct << 17;
			file[i].packed_inode[j].typenblock |= Inode[k].single << 8;
			file[i].packed_inode[j].typenblock |= Inode[k].double_indirect;

			file[i].packed_inode[j].timensize |= Inode[k].File_size << 36;
			file[i].packed_inode[j].timensize |= Inode[k].time.year << 25;
			file[i].packed_inode[j].timensize |= Inode[k].time.month << 21;
			file[i].packed_inode[j].timensize |= Inode[k].time.date << 16;
			file[i].packed_inode[j].timensize |= Inode[k].time.hour << 11;
			file[i].packed_inode[j].timensize |= Inode[k].time.min << 5;
			file[i].packed_inode[j].timensize |= Inode[k].time.sec;

			k++;
		}
	}


	// 데이터블록 : 파일 시스템 정보 이진파일 출력

	{

		// 부트블록 : 0

		fwrite(file[0].data, sizeof(char), sizeof(file[0].data), ifp);
		fwrite("\n", sizeof(char), sizeof("\n"), ifp);


		// 슈퍼블록 : 1 ~ 2

		fwrite(file[1].data, sizeof(char), sizeof(file[1].data), ifp);
		fwrite("\n", sizeof(char), sizeof("\n"), ifp);

		fwrite(file[2].data, sizeof(char), sizeof(file[2].data), ifp);
		fwrite("\n", sizeof(char), sizeof("\n"), ifp);


		// 아이노드 리스트 : 3 ~ 54 

		for(int i=3; i<55; i++)
		{
			fwrite(file[i].packed_inode, sizeof(struct packing), 1, ifp);
			fwrite("\n", sizeof(char), sizeof("\n"), ifp);
		}



		// 일반 데이터 : 55 ~ 1023

		for(int i=55; i<1024; i++)
		{
			if(file[i].i_d)
				fwrite(file[i].data, sizeof(char), sizeof(file[i].data), ifp); //파일에 대한 정보 저장
			else
				fwrite(file[i].indirectinode, sizeof(unsigned long long), 16, ifp); //인다렉트 블록일 경우 블록의 주소 저장

			fwrite("\n", sizeof("\n"), 1, ifp);
		}
	}


	fclose(ifp);

	return;
}
