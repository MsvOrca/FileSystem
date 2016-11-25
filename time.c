#include <stdio.h>
#include <time.h>
#include <stdlib.h>
typedef struct{//시간에 대한 구조체
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
}Touched;
typedef struct{
	Touched *made;//아이노드에 넣을 구조체 예시
}Inode;
void INPUT_TIME(Inode test, struct tm *t, time_t timer){

	test.made->year = t -> tm_year + 1900;
	test.made->mon = t -> tm_mon + 1;
	test.made->day = t -> tm_mday;
	test.made->hour = t -> tm_hour;
	test.made->min = t -> tm_min;
	test.made->sec = t -> tm_sec;

	return;
}
int main()
{
	Inode test;
	struct tm *t;
	time_t timer;
	timer = time(NULL);
	t = localtime(&timer);
	test.made = malloc(sizeof(Touched));

	INPUT_TIME(test, t, timer);

	printf("%d/%d/%d %d:%d:%d", test.made->year, test.made->mon, test.made->day, test.made->hour, test.made->min, test.made->sec);
	return 0;
}
