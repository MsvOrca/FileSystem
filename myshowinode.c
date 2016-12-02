#include <stdio.h>
#include <stdlib.h>
void MY_SHOWINODE(int);


int main(void)
{
	int a=0;
	char Usrbuf1[20]={0};

	scanf("%s", Usrbuf1);
	a=atoi(Usrbuf1);

	MY_SHOWINODE(a);

	return 0;
}

void MY_SHOWINODE(int a) 
{
	if(0<=a && a<=511)
	{
		FILE *ifp=fopen("mymkfs.bin", "rb");

		// 파일 아이노드

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
			int File_size;                       // 파일 크기
			short direct;                        // 다이렉트 블록
			short single;                        // 싱글 인다이렉트 블록
			short double_indirect;               // 더블 인다이렉트 블록
		};
		struct inode Inode={0};

		// 인다이렉트 아이노드 (데이터블록)

		unsigned long long indirectinode[16]={1,40,};
		unsigned long long indirectinode2[16]={1,40,};

		// 아이노드 사용여부

		unsigned long long sb_inode[8]={0};  


		// 아이노드 사용여부 체크

		fseek(ifp, 128, 0);
		fread(sb_inode, sizeof(unsigned long long), 8, ifp);

		int i=1;

		if((sb_inode[a/64]&(i<<=(a%64)))==0)
		{
			printf("사용중인 아이노드가 아닙니다.");
			return;
		}
		else
		{
			// 지정된 번호의 아이노드 출력

			fseek(ifp, 128+64+128+sizeof(struct inode)*a, 0);  // 0,1,2번의 데이터블록의 크기 : 128, 64, 128
			fread(&Inode, sizeof(struct inode), 1, ifp);

			if(Inode.ForD==0)
				printf("file type : regular file\n");
			else
				printf("file type : directory file\n");

			printf("file size : %lld byte\n", Inode.File_size);
			printf("modified time : %d/%02hd/%02hd/ %02hd:%02hd:%02hd\n", Inode.time.year, Inode.time.month, Inode.time.date, Inode.time.hour, Inode.time.min, Inode.time.sec);
			printf("data block list : %d", Inode.direct);


			// 싱글 인다이렉트 블록

			if(Inode.single!=0)
			{
				fseek(ifp, 0, 0);       // 파일 지시자 위치 초기화

				fseek(ifp, 128+64+128+sizeof(struct inode)*512+128*(Inode.single-131), 0);
				fread(indirectinode, sizeof(unsigned long long), 16, ifp);

				int i=0x3FF;            // 000...0011 1111 1111
				int j=0;
				int block_num[96]={0};

				for(j=0; j<96; j++)
				{
					block_num[j]=(indirectinode[j/6]>>((j%6)*10))&i;

					if(block_num[j]==0)
						break;
				}
				for(int k=0; k<j; k++)
					printf(", %d", block_num[k]);
			}
			else
				;

			// 더블 인다이렉트 블록 

			if(Inode.double_indirect!=0)
			{
				fseek(ifp, 0, 0);

				fseek(ifp, 128+64+128+sizeof(struct inode)*512+128*(Inode.single-131), 0);
				fread(indirectinode, sizeof(unsigned long long), 16, ifp);

				int i=0x3FF; // 000...0011 1111 1111
				int j=0;  
				int block_num[96]={0};

				for(j=0; j<96; j++)
				{
					block_num[j]=(indirectinode[j/6]>>((j%6)*10))&i;

					if(block_num[j]==0)
						break;
				}
				for(int k=0; k<j; k++)
				{
					fseek(ifp, 0, 0);

					fseek(ifp, 128 + 64 + 128 + sizeof(struct inode)*512 + 128*(block_num[k]-131), 0);
					fread(indirectinode2, sizeof(unsigned long long), 16, ifp);

					int i=0x3FF;
					int h=0;
					int block_num2[96]={0};

					for(h=0; h<96; h++)
					{
						block_num2[j]=(indirectinode2[j/6]>>((j%6)*10))&i;

						if(block_num2[j]==0)
							break;
					}
					for(int k=0; k<h; k++)
						printf(", %d", block_num2[k]);
				}
			}
			else
				;

		}
	}
	else
		printf("오류 : 입력 가능한 아이노드의 번호는 0번부터 511번까지 입니다.\n");

	return;
}

