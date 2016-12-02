#include <stdio.h>
#include <stdlib.h>
void MY_SHOWBLOCK(int);


int main(void)
{
	int a=0;
	char Usrbuf1[20]={0};

	scanf("%s", Usrbuf1);
	a=atoi(Usrbuf1);

	MY_SHOWBLOCK(a);

	return 0;
}

void MY_SHOWBLOCK(int a)
{
	if(0<=a&&a<=1023)
	{
		FILE *ifp=fopen("mymkfs.bin", "rb");

		// 아이노드 시간

		struct time{
			int year;
			short month;
			short date;
			short hour;
			short min;
			short sec;
		};

		// 아이노드

		struct inode{
			_Bool ForD;                          // 파일 종류 
			struct time time;                    // 파일 생성 시간     
			int File_size;                 // 파일 크기           
			short direct;                        // 다이렉트 블록        
			short single;                        // 싱글 인다이렉트 블록  
			short double_indirect;               // 더블 인다이렉트 블록   
		};                                                

		unsigned long long sb_inode[8]={0};          // 슈퍼블록 아이노드
		unsigned long long sb_block[16]={0};         // 슈퍼블록 데이터블록
		struct inode Inode={0};                      // 아이노드
		unsigned long long indirectinode[16]={0};    // 인다이렉트아이노드
		char data[128]={0};                          // 일반 데이터


		// 데이터블록 사용여부 체크

		fseek(ifp, 128+64, 0);
		fread(sb_block, sizeof(unsigned long long), 16, ifp);

		int i=1;
		int check=0;

		if((sb_block[a/64]&(i<<=(a%64)))==0)
		{
			printf("사용중인 데이터블록이 아닙니다.");
			return;
		}
		else
		{
			fseek(ifp, 0, 0);

			//// 지정된 번호의 데이터블록의 데이터 출력

			// 부트블록

			if(a==0)
			{
				fread(data, sizeof(char), 128, ifp);

				printf("%s", data);
			}

			// 슈퍼블록 아이노드

			else if(a==1)
			{
				fseek(ifp, 128, 0);
				fread(sb_inode, sizeof(unsigned long long), 8, ifp);

				for(int i=0; i<8; i++)
					printf("%lld", sb_inode[i]);
			}

			// 슈퍼블록 데이터블록

			else if(a==2)
			{
				fseek(ifp, 128+64, 0);
				fread(sb_block, sizeof(unsigned long long), 16, ifp);

				for(int i=0; i<16; i++)
					printf("%lld", sb_block[i]);
			}

			// 아이노드

			else if(3<=a&&a<=130)
			{
				fseek(ifp, 128+64+128+sizeof(struct inode)*(a-3), 0);
				fread(&Inode, sizeof(struct inode), 1, ifp);

				printf("%d%d%hd%hd%hd%hd%hd%lld%hd%hd%hd", Inode.ForD, Inode.time.year, Inode.time.month, Inode.time.date, Inode.time.hour, Inode.time.min, Inode.time.sec, Inode.File_size, Inode.direct, Inode.single, Inode.double_indirect);
			}

			// 데이터

			else if(a>=131)
			{
				fseek(ifp, 128+64+128+sizeof(struct inode)*512+128*(a-131), 0);
				fread(data, sizeof(char), 128, ifp);

				if(1)                               // 인다이렉트 아이노드인지 데이터인지 판별
					printf("%s", data);
				else
					printf("INDIRECT INODE");
			}

		}
	}
	else
		printf("오류 : 입력 가능한 데이터블록의 번호는 0번부터 1023번까지 입니다.\n");

	return;
}
