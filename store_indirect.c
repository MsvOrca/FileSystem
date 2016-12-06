#include <stdio.h>
void store_indirect(unsigned long long *);

int main(void)
{
	unsigned long long block_num[96]={0};                 // indirectinode에 패킹할 블록넘버들 (single의 경우 96개까지 가능)
														  // long long에 패킹하기 위해선 60비트까지 연산가능해야 함 > ull에 블록넘버 저장

	store_indirect(block_num);

	return 0;
}





   // 데이터를 한 번에 저장하면서 저장된 블록 넘버들을 block_num에 저장해놓은 뒤
   // 이 넘버들을 차례로 direct, single_indirect 필요하다면 double_indirect까지 저장해준다.
   //
   // 더블 인다이렉트는 이 짓을 해놓은 블록 넘버들을 block_num에 저장해서 이 짓을 또 하면 됨.





void store_indirect(unsigned long long *block_num)        // block_num 배열을 인자로 넘겨준다.
{
	FILE *ifp=fopen("****.bin", "rb");                    // 파일 포인터는 데이터를 저장하는 함수 내에서 선언할 것으로 예상 (일단 적어놈, 지워도 됨)

	unsigned long long indirectinode[16]={0};             // 10bit씩 6개 패킹

	int store=0;                                          // indirectinode를 저장할 블록의 넘버
	int k=0;
	
	for(int i=0; i<16; i++)                               // 16개의 ull에 저장
		for(int j=0; j<6; j++)                            // 한 개의 ull에 6개까지 저장
		{
			indirectinode[i]|=(block_num[k]<<(j*10));     // indirectinode에 저장하고자 하는 블록 넘버를 왼쪽으로 10bit씩 이동해가며 저장
			k++;                                        
		}

	fseek(ifp, 2+64+128+(32*512)+(128*store), 0);         // 32 : 아이노드 구조체의 크기

	fwrite(&store, sizeof(int), 1, ifp);				  // 저장하고 싶은 번호의 블록만큼 지시자를 옮긴 뒤 저장

	return;
}
