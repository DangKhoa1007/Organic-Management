#include <stdio.h>
#include <string.h>
#include "batch_Functions.h"
#include <windows.h>

void batch(int option) {
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	char qua[100];
	do {
		printf("Nhập loại quả bạn muốn thêm: ");
		fgets(qua, 100, stdin);
		printf("Loại quả bạn đã nhập là: %s\n", qua);
		
		if( getchar() ) {
			printf("Enter thêm 1 lần nữa để thoát chương trình");
			if ( getchar() ) {
				break;
			}
		}
	} while( option !=0 );
}
