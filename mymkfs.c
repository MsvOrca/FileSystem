#include <stdio.h>
#include <time.h>
#include <string.h>

// 부트블록

short boot_block=0;


// 슈퍼블록

unsigned int sb_inode[16]={0};       // 아이노드 사용여부 저장
unsigned int sb_block[32]={0};       // 데이터블록 사용여부 저장


// 아이노드 리스트

typedef struct{                      // 파일 생성 시간
	int year;
	short mon;
	short day;
	short hour;
	short min;
	short sec;
}Touched;

typedef struct{
	_Bool ForD;                      // 파일 종류 
	Touched Timed;                   // 파일 생성 시간     
	int File_size;                   // 파일 크기           
	short direct;                    // 다이렉트 블록        
	short single;                    // 싱글 인다이렉트 블록  
	short double_indirect;           // 더블 인다이렉트 블록   
}Inode;                                                

Inode I_node[512]={0};


// 데이터 블록 	

typedef struct{                                // 디렉토리 파일 데이터
	_Bool FD;
	char name[5];
	short inode;
}sdir;

union file_data{
	unsigned long long indirectinode[16];      // 인다이렉트 아이노드
	char data[128];                            // 일반 파일 데이터
	sdir basedir[16];
};

union file_data file[1024]={0};            


void INPUT_TIME(Inode *test);


void main(void)
{
	// 읽기 모드로 열어 파일시스템이 이미 존재하는지 확인
	
	FILE *ifp=fopen("mymkfs.bin", "r");

	if(ifp==NULL)                              
	{
		ifp=fopen("mymkfs.bin", "wb");                        // 존재하지 않는다면 파일시스템을 새로 생성


		// 루트 디렉토리 생성

		sb_inode[0]=1;
		sb_block[0]=1;

		I_node[0].ForD=1;
		I_node[0].File_size=16;
		I_node[0].direct=0;
		I_node[0].single=1024;
		I_node[0].double_indirect=1024;

		INPUT_TIME(&I_node[0]);
		file[0].basedir[0].FD=1;
		strcpy(file[0].basedir[0].name,".");
		file[0].basedir[0].inode=0;
		file[0].basedir[1].FD=1;
		strcpy(file[0].basedir[1].name,"..");
		file[0].basedir[1].inode=0;


		//// 이진파일로 출력

		// 부트블록

		fwrite(&boot_block, sizeof(short), 1, ifp);


		// 슈퍼블록

		fwrite(sb_inode, sizeof(int), 16, ifp);        
		fwrite(sb_block, sizeof(int), 32, ifp);         


		// 아이노드 리스트

		fwrite(I_node, sizeof(Inode), 512, ifp);


		// 일반 데이터

		for(int i=0; i<1024; i++)
			fwrite(file[i].data, sizeof(char), 128, ifp);     


		fclose(ifp);
	}
	else                                                
		printf("파일시스템이 이미 존재합니다.");              // 파일시스템이 이미 존재한다면 오류 메시지 출력


	return;
}


// 파일 생성 시간 저장 함수

void INPUT_TIME(Inode *test){
	struct tm *t;
	time_t timer;
	timer = time(NULL);
	t = localtime(&timer);

	test->Timed.year = t -> tm_year + 1900;
	test->Timed.mon = t -> tm_mon + 1;
	test->Timed.day = t -> tm_mday;
	test->Timed.hour = t -> tm_hour;
	test->Timed.min = t -> tm_min;
	test->Timed.sec = t -> tm_sec;

	return;
}
