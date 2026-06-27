#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "function_name.h"

int menu2IO() {
	int subChoice;
	printf("\n========== MENU QUẢN LÝ LÔ HÀNG ==========\n");
	printf("1. Nhập ID bạn muốn xóa\n");
	printf("2. Delete All\n");
	printf("\n");
	printf("\n");
	printf("Nhập lựa chọn của bạn: ");
	while (scanf("%d", &subChoice) != 1) {
		printf("Lựa chọn không hợp lệ, vui lòng nhập số: ");
		while (getchar() != '\n'); // xóa input rác trong buffer
	}
	while (getchar() != '\n');
	return subChoice;
}

void addIO() {
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	FILE *f1;
	char batchID[50];
	char name[50];
	int totalCount;
	int batchTemp;
	char batchState[50];
	char batch_origin[50];

	printf("Enter Batch ID: ");
	fgets(batchID, sizeof(batchID), stdin);
	batchID[strcspn(batchID,"\n")] = '\0';

	printf("Enter Batch Name: ");
	fgets(name, sizeof(name), stdin);
	name[strcspn(name, "\n")] = '\0';
	printf("Enter number of unit(kg/box): ");
	scanf("%d", &totalCount);
	while (getchar() != '\n');

	printf("Enter Tempurature: ");
	scanf("%d", &batchTemp);
	while (getchar() != '\n');

	printf("Enter Batch State: ");
	fgets(batchState, sizeof(batchState), stdin);
	batchState[strcspn(batchState, "\n")] = '\0';

	printf("Enter Batch Origin: ");
	fgets(batch_origin, sizeof(batch_origin), stdin);
	batch_origin[strcspn(batch_origin, "\n")] = '\0';

	f1 = fopen("data.txt", "a"); //append = add infor into final line of file
	if (f1 == NULL) {
		printf("Cannot open file to add! \n");
		return; // tránh ghi/đóng file NULL gây crash
	}
	fprintf(f1, "%s|%s|%d|%d|%s|%s\n", batchID, name, totalCount, batchTemp, batchState, batch_origin);
	fclose(f1);
	printf("Add information successfull\n");
}

void printIO() {
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);

	FILE *f1;
	char batchID[50];
	char name[50];
	int totalCount;
	int batchTemp;
	char batchState[50];
	char batch_origin[50];

	f1 = fopen("data.txt", "r");
	if(f1 == NULL) {
		printf("Không mở được file\n");
		return;
	}
	while (1) {
		int kq = fscanf(f1, "%49[^|]|%49[^|]|%d|%d|%49[^|]|%49[^\n]",
		                batchID,
		                name,
		                &totalCount,
		                &batchTemp,
		                batchState,
		                batch_origin);

		if (kq != 6)
			break;

		// Bỏ qua ký tự '\n' còn sót lại cuối dòng để vòng lặp đọc đúng dòng kế tiếp
		int c = fgetc(f1);
		if (c != '\n' && c != EOF) ungetc(c, f1);

		printf("BatchID:%1s \t Name:%2s \t Number of Unit:%2d \t Temperature:%2d \t State:%3s \t Origin: %3s\n",
		       batchID,
		       name,
		       totalCount,
		       batchTemp,
		       batchState,
		       batch_origin
		      );
	}
	fclose(f1);
}
void deleteIO() {
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);

	FILE *f1, *f2;
	char batchID[50], idXoa[50];
	char name[50];
	int totalCount;
	int batchTemp;
	char batchState[50];
	char batch_origin[50];

	printf("Nhập batch ID cần xóa: ");
	scanf("%49s", idXoa);
	while (getchar() != '\n');

	f1 = fopen("data.txt", "r");
	if (f1 == NULL) {
		printf("Không thể mở file data.txt!\n");
		return;
	}
	f2 = fopen("temp.txt", "w");
	if (f2 == NULL) {
		printf("Không thể mở file tạm để xóa!\n");
		fclose(f1);
		return;
	}

	while (fscanf(f1, "%49[^|]|%49[^|]|%d|%d|%49[^|]|%49[^\n]",
	              batchID,
	              name,
	              &totalCount,
	              &batchTemp,
	              batchState,
	              batch_origin) == 6 ) {

		// Bỏ qua ký tự '\n' còn sót lại cuối dòng
		int c = fgetc(f1);
		if (c != '\n' && c != EOF) ungetc(c, f1);

		printf("So sanh: '%s' voi '%s'\n", batchID, idXoa);

		if (strcmp(batchID, idXoa) != 0) {
			fprintf(f2, "%s|%s|%d|%d|%s|%s\n",
			        batchID,
			        name,
			        totalCount,
			        batchTemp,
			        batchState,
			        batch_origin
			       );
		}
	}
	fclose(f1);
	fclose(f2);

	remove("data.txt");
	rename("temp.txt", "data.txt");

	printf("Xóa thành công!\n");
}
void deleteAllIO() {
	// Mở file ở chế độ "w" sẽ tự động xóa sạch toàn bộ nội dung file cũ
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);

	FILE *f1 = fopen("data.txt", "w");

	if (f1 == NULL) {
		printf("Không thể mở file để xóa tất cả dữ liệu!\n");
		return;
	}

	fclose(f1);
	printf("Đã xóa toàn bộ dữ liệu thành công!\n");
}
void searchByID() {
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);

	FILE *f1;
	char batchID[50], idTim[50];
	char name[50];
	int totalCount;
	int batchTemp;
	char batchState[50];
	char batch_origin[50];

	int found = 0; // Biến đánh dấu có tìm thấy hay không
	printf("Nhập batch ID cần tìm kiếm: ");
	fgets(idTim, sizeof(idTim), stdin);
	idTim[strcspn(idTim, "\n")] = '\0';
	f1 = fopen("data.txt", "r");
	if (f1 == NULL) {
		printf("Không thể mở file data.txt!\n");
		return;
	}
	while (fscanf(f1, "%49[^|]|%49[^|]|%d|%d|%49[^|]|%49[^\n]",
	              batchID,
	              name,
	              &totalCount,
	              &batchTemp,
	              batchState,
	              batch_origin) == 6) {

		// Bỏ qua ký tự '\n' còn sót lại cuối dòng
		int c = fgetc(f1);
		if (c != '\n' && c != EOF) ungetc(c, f1);

		if (strcmp(batchID, idTim) == 0) {
			printf("\n========== KẾT QUẢ TÌM KIẾM ==========\n");
			printf("BatchID:%s \t Name:%s \t Number of Unit:%d \t Temperature:%d \t State:%s \tOrigin:%s\n",
			       batchID,
			       name,
			       totalCount,
			       batchTemp,
			       batchState,
			       batch_origin);
			found = 1;
			break; // Đã tìm thấy thì dừng vòng lặp ngay lập tức
		}
	}
	fclose(f1);
	if (!found) {
		printf("Không có lô hàng nào có ID: %s\n", idTim);
	}
}