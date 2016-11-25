#include <stdio.h>
#include <string.h>
#define INDIRECTINODE 0
#define DATA 1

// 부트 블록

short boot_block={0};


// 슈퍼 블록

struct super_block{
	unsigned long long inode_use[16];            // 아이노드 사용여부
	unsigned long long data_block_use[32];       // 데이터블록 사용여부
};
struct super_block super_block={0}; 


// 파일 아이노드

struct inode{
	_Bool ForD;                          // 파일 종류
	char name[5];                        // 파일 이름
	char time[20];                       // 파일 생성 시간
	int File_size;                       // 파일 크기
	short direct;                        // 다이렉트 블록
	short single;                        // 싱글 인다이렉트 블록
	short double_indirect;               // 더블 인다이렉트 블록
};
struct inode Inode[512]={0};


// 파일 데이터

union file_data{
	_Bool i_d;
	unsigned long long indirectinode[16];      // 데이터 블록 번호 저장 (인다이렉트 아이노드)
	char data[128];                            // 일반 데이터 저장
};
union file_data file[1024]={0};


































void myrm(char *);
void mymkfs(struct super_block, struct inode *, union file_data *);


int main(void)
{
	myrm("abc");
	return 0;
}


void myrm(char *name)
{
	int i=0;
	int num=1;


	// 512개의 아이노드리스트 중 이름이 일치하는 것을 찾는다.

	for(; i<512; i++)
	{
		if((strcmp(name, Inode[i].name))==0)
			break;
	}


	// 슈퍼블록의 아이노드, 데이터블록 사용 여부 지우기
	// 원래의 아이노드 값에서 2^(아이노드 번호) 만큼 값을 빼주어 이진수로 나타냈을 때 원하는 부분이 0이 되도록 만들어 준다.

	for(int j=0; j<i; j++)
		num*=2;

	if(0<=i && i<=63)
		super_block.inode_use[0]-(num-64*0);
	else if(64<=i && i<=127)
		super_block.inode_use[1]-(num-64*1);
	else if(128<=i && i<=191)
		super_block.inode_use[2]-(num-64*2);
	else if(129<=i && i<=255)
		super_block.inode_use[3]-(num-64*3);
	else if(256<=i && i<=319)
		super_block.inode_use[4]-(num-64*4);
	else if(320<=i && i<=383)
		super_block.inode_use[5]-(num-64*5);
	else if(384<=i && i<=448)
		super_block.inode_use[6]-(num-64*6);
	else if(449<=i && i<=511)
		super_block.inode_use[7]-(num-64*7);


	// 데이터 블록 지우기
	// 1. 일반 데이터 값 지우기
	// 2. 싱글 또는 더블 인다이렉트 블록을 가질 경우 지워주기

	file[i].i_d=0;


	// 아이노드 지우기
	// 0으로 초기화 시켜준다.

	Inode[i].ForD=0;
	strcpy(Inode[i].name, "0");
	strcpy(Inode[i].time, "0");
	Inode[i].File_size=0;
	Inode[i].direct=0;
	Inode[i].single=0;
	Inode[i].double_indirect=0;


	mymkfs(super_block, Inode, file);
}


// mymkfs 함수 : 파일시스템 정보 이진파일로 저장

void mymkfs(struct super_block super_block, struct inode *inode, union file_data *file)
{
	FILE *ifp;
	ifp=fopen("mymkfs.bin", "wb");


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

	return;
}


























