#include<stdio.h>
#include<windows.h>
#include "batch_Functions.h"



void quanlikhohangMenu() {
    printf("\n========== QUAN LY KHO HANG ==========\n");
    printf("1. Thêm sản phẩm\n");
    printf("2. Hiển thị kho hàng\n");
    printf("3. Tìm kiếm hàng\n");
    printf("0. Thoát\n");
    printf("======================================\n");
    printf("Lựa chọn của bạn: ");
}

int main(){
	SetConsoleOutputCP(65001);
	quanlikhohangMenu();
	FILE *fptr;
	fptr
	int option;
	scanf("%d", &option);
	getchar();
	if( option != 0 ){
		batch(option);
	}
	return 0;
}