#include <stdio.h>
int main(void)
{
	int a=0;
	FILE *ifp=fopen("****.bin", "rb");

	unsigned long long sb_block[16]={0};


	// 데이터블록 사용여부 체크
	
	scanf("%d", a);

	fseek(ifp, 128+64, 0);
	fread(sb_block, sizeof(unsigned long long), 16, ifp);

	int i=1;

	if((sb_block[a/64]&(i<<=(a%64)))==0)
		printf("사용중인 데이터블록이 아닙니다.");
	else
		printf("사용중인 데이터블록 입니다.");

	return 0;
}
