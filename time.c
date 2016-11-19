#include <stdio.h>
#include <time.h>
#include <stdlib.h>
typedef struct{
	char current[20];//아이노드에 넣을 구조체 예시
}Inode;
void INPUT_TIME(char *current){
	struct tm *t;
	time_t timer;
	int len;
	timer = time(NULL);
	t = localtime(&timer);

	len = sprintf(current, "%d",t -> tm_year + 1900);
	*(current + len) = '/';
	len++;
	len += sprintf(current + len, "%d", t -> tm_mon + 1);
	*(current + len) = '/';
	len++;
	len += sprintf(current + len, "%d", t -> tm_mday);
	*(current + len) = ' ';
	len++;
	len += sprintf(current + len, "%d", t -> tm_hour);
	*(current + len) = ':';
	len++;
	len += sprintf(current + len, "%d", t -> tm_min);
	*(current + len) = ':';
	len++;
	len += sprintf(current + len, "%d", t -> tm_sec);
}
int main()
{
	Inode test;

	INPUT_TIME(test.current);

	printf("%s", test.current);
	return 0;
}
