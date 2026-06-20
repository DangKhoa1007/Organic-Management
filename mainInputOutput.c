#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function_name.h"

int main() {
	int choice, subChoice;
    
    // Vòng lặp Menu cho phép người dùng chọn chức năng
    while (1) {
        printf("\n========== MENU QUAN LY LO HANG ==========\n");
        printf("1. Them thong tin lo hang (Add IO)          \n");
        printf("2. In thong tin cac lo hang (Print IO)      \n");
        printf("3. How you want to remove (Remove IO)       \n");
        printf("4. Search batch by ID                       \n");
        printf("5. Thoat chuong trinh                       \n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Xóa bộ đệm sau khi nhập số
        
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
                printf("Da thoat chuong trinh.\n");
                exit(0);
            default:
                printf("Lua chon khong hop le! Vui long nhap lai.\n");
        }
    }
    return 0;
}