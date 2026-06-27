#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "batch_Functions.h"

int main() {
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	int choice,subChoice;
    while (1) {
        printf("\n========== MENU QUẢN LÝ LÔ HÀNG ==========\n");
        printf("1. Thêm thông tin lô hàng (Add IO)          \n");
        printf("2. In thông tin các lô hàng (Print IO)      \n");
        printf("3. Xóa lô hàng (Remove IO)                  \n");
        printf("4. Tìm lô hàng dựa trên ID                  \n");
        printf("5. Thoát chương trình                       \n");
        printf("Nhập lựa chọn của bạn:"                        );
        scanf(" %d", &choice);
        while (getchar() != '\n');    // Xóa bộ đệm sau khi nhập số
        switch (choice) {
            case 1:
                addIO();
                break;
            case 2:
                printIO();
                break;
            case 3:
                subChoice = menu2IO();
                if(subChoice == 1){
                	deleteIO();
				}
				else if(subChoice == 2){
					deleteAllIO();
				}
				break;
			case 4:
				searchByID();
				break;
            case 5:
                printf("Đã thoát chương trình.\n");
                exit(0);
            default:
                printf("Lựa chọn không hợp lệ! Vui lòng nhập lại.\n");
        }
    }
    return 0;
}