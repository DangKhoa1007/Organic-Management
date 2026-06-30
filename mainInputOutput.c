#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "function_name.h"

enum product_Status{
	Fresh, Dried
};

int main() {
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	
	int choice, subChoice;
	
    // Vong lap Menu cho phep nguoi dung chon chuc nang
    while (1) {
        printf("\n========== MENU QUAN LY LO HANG ==========\n");
        printf("1. Them thong tin lo hang (Add IO)          \n");
        printf("2. In thong tin cac lo hang (Print IO)      \n");
        printf("3. How you want to remove (Remove IO)       \n");
        printf("4. Search batch by ID                       \n");
        printf("5. Gom nhom theo Destination (Group By)      \n");
        printf("6. Theo doi giao hang (Track Delivery)       \n");
        printf("7. Sap xep theo Batch ID (Sort)               \n");
        printf("8. Thoat chuong trinh                       \n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Xoa bo dem sau khi nhap so

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
                groupByDestination();
			case 6:
				trackDelivery();
				break;
			case 7:
				sortByID();
				break;
			case 8:
                printf("Da thoat chuong trinh.\n");
                exit(0);
				break;
            default:
                printf("Lựa chọn không hợp lệ! Vui lòng nhập lại.\n");
        }
    }
    return 0;
}

