#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include"my_fs_function.h"

int main()
{
	 int INcase=0;

	 	 while(1)
	 	 {
			  int INcase=0;
	 //		  printf("[%s$]",directory);//now dir(pwd)
	 USER_INPUT();
	 switch(INcase)
	 {
		  case 1 : MY_LS();break;
		  case 2 : MY_CAT();break;
		  case 3 : MY_SHOWFILE();break;
		  case 4 : MY_PWD();break;
		  case 5 : MY_CD();break;
		  case 6 : MY_CP();break;
		  case 7 : MY_CPTO();break;
		  case 8 : MY_CPFROM();break;
		  case 9 : MY_MKDIR();break;
		  case 10 : MY_RMDIR();break;
		  case 11 : MY_RM();break;
		  case 12 : MY_MV();break;
		  case 13 : MY_TOUCH();break;
		  case 14 : MY_SHOWINODE();break;
		  case 15 : MY_SHOWBLOCK();break;
		  case 16 : MY_STATE();break;
		  case 17 : MY_TREE();break;
		  case 18 : COMMAND();break;
		  case 19 : return 0;
defalut : printf("myfs : %s : command not found.\n",Usrcmd);break;
	 }
	 	 }
	 return 0;
}
