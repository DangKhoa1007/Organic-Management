#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function_name.h"
int menu2IO() {
	int subChoice;
	printf("\n========== MENU QUAN LY LO HANG ==========\n");
	printf("1. Enter ID to delete");
	printf("2. Delete All\n");
	printf("\n");
	printf("\n");
	printf("Nhap lua chon cua ban: ");
	scanf("%d", &subChoice);
	while (getchar() != '\n');
	return subChoice;
}
void addIO() {
	FILE *f1;
	char batchID[50];
	char name[50];
	int totalCount;
	int batchTemp;
	char batchState[50];

	printf("Enter Batch ID: ");
	fgets(batchID, sizeof(batchID), stdin);
	batchID[strcspn(batchID,"\n")] = '\0';

	printf("Enter Batch Name: ");
	fgets(name, sizeof(name), stdin);
	name[strcspn(name, "\n")] = '\0';

	printf("Enter number of unit: ");
	scanf("%d", &totalCount);
	while (getchar() != '\n');

	printf("Enter Tempurature: ");
	scanf("%d", &batchTemp);
	while (getchar() != '\n');

	printf("Enter Batch State: ");
	fgets(batchState, sizeof(batchState), stdin);
	batchState[strcspn(batchState, "\n")] = '\0';

	f1 = fopen("data.txt", "a"); //append = add infor into final line of file
	if (f1 == NULL) {
		printf("Cannot open file to add! \n");
	}
	fprintf(f1, "%s|%s|%d|%d|%s\n", batchID, name, totalCount, batchTemp, batchState);
	fclose(f1);
	printf("Add information successfull\n");
}

void printIO() {
	FILE *f1;
	char batchID[50];
	char name[50];
	int totalCount;
	int batchTemp;
	char batchState[50];

	f1 = fopen("data.txt", "r");
	if(f1 == NULL) {
		printf("Khong mo duoc file\n");
		return;
	}
	while (1) {
		int kq = fscanf(f1, "%49[^|]|%49[^|]|%d|%d|%49[^\n]",
		                batchID,
		                name,
		                &totalCount,
		                &batchTemp,
		                batchState);

		if (kq != 5)
			break;

		printf("BatchID:%1s \t Name:%2s \t Number of Unit:%2d \t Temperature:%2d \t State:%3s\n",
		       batchID,
		       name,
		       totalCount,
		       batchTemp,
		       batchState);
	}
	fclose(f1);
}
void deleteIO() {
	FILE *f1, *f2;
	char batchID[50], idXoa[50];
	char name[50];
	int totalCount;
	int batchTemp;
	char batchState[50];

	printf("Nhap Batch ID can xoa: ");
	scanf("%s", idXoa);
	while (getchar() != '\n');

	f1 = fopen("data.txt", "r");
	f2 = fopen("temp.txt", "w");

	while (fscanf(f1, "%49[^|]|%49[^|]|%d|%d|%49[^\n]%*c",
	              batchID,
	              name,
	              &totalCount,
	              &batchTemp,
	              batchState) == 5) {
		printf("So sanh: '%s' voi '%s'\n", batchID, idXoa);
		
		if (strcmp(batchID, idXoa) != 0) {
			fprintf(f2, "%s|%s|%d|%d|%s\n",
			        batchID,
			        name,
			        totalCount,
			        batchTemp,
			        batchState);
		}
	}
	fclose(f1);
	fclose(f2);

	remove("data.txt");
	rename("temp.txt", "data.txt");

	printf("Xoa thanh cong!\n");
}
void deleteAllIO() {
	// Mở file ở chế độ "w" sẽ tự động xóa sạch toàn bộ nội dung file cũ
	FILE *f1 = fopen("data.txt", "w");

	if (f1 == NULL) {
		printf("Khong the mo file de xoa tat ca du lieu!\n");
		return;
	}

	fclose(f1);
	printf("Da xoa toan bo du lieu thanh cong!\n");
}
void searchByID() {
	FILE *f1;
	char batchID[50], idTim[50];
	char name[50];
	int totalCount;
	int batchTemp;
	char batchState[50];
	int found = 0; // Biến đánh dấu có tìm thấy hay không
	printf("Nhap Batch ID can tim kiem: ");
	fgets(idTim, sizeof(idTim), stdin);
	idTim[strcspn(idTim, "\n")] = '\0';
	f1 = fopen("data.txt", "r");
	if (f1 == NULL) {
		printf("Khong the mo file data.txt!\n");
		return;
	}
	while (fscanf(f1, "%49[^|]|%49[^|]|%d|%d|%49[^\n]",
	              batchID,
	              name,
	              &totalCount,
	              &batchTemp,
	              batchState) == 5) {
		if (strcmp(batchID, idTim) == 0) {
			printf("\n========== KET QUA TIM KIEM ==========\n");
			printf("BatchID:%s \t Name:%s \t Number of Unit:%d \t Temperature:%d \t State:%s\n",
			       batchID,
			       name,
			       totalCount,
			       batchTemp,
			       batchState);
			found = 1;
			break; // Đã tìm thấy thì dừng vòng lặp ngay lập tức
		}
	}
	fclose(f1);
	if (!found) {
		printf("Khong tim thay lo hang nao co ID: %s\n", idTim);
	}
}