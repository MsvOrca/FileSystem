#include <stdio.h>
int main(void)
{
	FILE *ifp=fopen("****.bin", "rb");

	int inode_num=0;

	// 아이노드
	
	struct time{
		int year;
		short month;
		short date;
		short hour;
		short min;
		short sec;
	};
	struct inode{
		_Bool ForD;                          // 파일 종류
		struct time time;                    // 파일 생성 시간
		int File_size;                       // 파일 크기
		short direct;                        // 다이렉트 블록
		short single;                        // 싱글 인다이렉트 블록
		short double_indirect;               // 더블 인다이렉트 블록
	};
	struct inode Inode={0};

	// 지정된 번호의 아이노드 출력

	fseek(ifp, 128+64+128+sizeof(struct inode)*inode_num, 0);  // 0,1,2번의 데이터블록의 크기 : 128, 64, 128
	fread(&Inode, sizeof(struct inode), 1, ifp);
}

