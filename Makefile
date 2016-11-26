filesystem : func.h f1.c f2.c my_fs.c
	gcc -o my_fs my_fs.c f1.c f2.c func.h
