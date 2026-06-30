#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "function_name.h"

#define MAX_LINE 200
#define MAX_RECORDS 1000

typedef struct {
	char batchID[50];
	char name[50];
	int totalCount;
	int batchTemp;
	char batchState[50];
	char destination[50];
	char deliveryStatus[20];
} Batch;

// Doc toan bo file data.txt vao mang Batch, tra ve so luong doc duoc
static int loadAll(Batch arr[], int maxRecords) {
	FILE *f1 = fopen("data.txt", "r");
	if (f1 == NULL) {
		return 0;
	}
	int count = 0;
	while (count < maxRecords &&
	        fscanf(f1, "%49[^|]|%49[^|]|%d|%d|%49[^|]|%49[^|]|%19[^\n]%*c",
	               arr[count].batchID,
	               arr[count].name,
	               &arr[count].totalCount,
	               &arr[count].batchTemp,
	               arr[count].batchState,
	               arr[count].destination,
	               arr[count].deliveryStatus) == 7) {
		count++;
	}
	fclose(f1);
	return count;
}

// Ghi toan bo mang Batch ra file data.txt (ghi de)
static void saveAll(Batch arr[], int count) {
	FILE *f1 = fopen("data.txt", "w");
	if (f1 == NULL) {
		printf("Khong the mo file de luu!\n");
		return;
	}
	for (int i = 0; i < count; i++) {
		fprintf(f1, "%s|%s|%d|%d|%s|%s|%s\n",
		        arr[i].batchID,
		        arr[i].name,
		        arr[i].totalCount,
		        arr[i].batchTemp,
		        arr[i].batchState,
		        arr[i].destination,
		        arr[i].deliveryStatus);
	}
	fclose(f1);
}

static void printHeader() {
	printf("%-10s %-15s %-8s %-6s %-10s %-15s %-12s\n",
	       "BatchID", "Name", "Qty", "Temp", "State", "Destination", "Delivery");
	printf("------------------------------------------------------------------------------\n");
}

static void printRow(Batch *b) {
	printf("%-10s %-15s %-8d %-6d %-10s %-15s %-12s\n",
	       b->batchID, b->name, b->totalCount, b->batchTemp,
	       b->batchState, b->destination, b->deliveryStatus);
}

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
	char destination[50];
	char deliveryStatus[20];

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

	printf("Enter Batch State (Fresh/ Dried): ");
	fgets(batchState, sizeof(batchState), stdin);
	batchState[strcspn(batchState, "\n")] = '\0';

	printf("Enter Batch Origin: ");
	fgets(batch_origin, sizeof(batch_origin), stdin);
	batch_origin[strcspn(batch_origin, "\n")] = '\0';
	printf("Enter Destination: ");
	fgets(destination, sizeof(destination), stdin);
	destination[strcspn(destination, "\n")] = '\0';

	// Lo hang moi luon bat dau o trang thai Pending
	strcpy(deliveryStatus, "Pending");

	f1 = fopen("data.txt", "a"); //append = add infor into final line of file
	if (f1 == NULL) {
		printf("Cannot open file to add! \n");
		return; // tránh ghi/đóng file NULL gây crash
	}
	fprintf(f1, "%s|%s|%d|%d|%s|%s\n", batchID, name, totalCount, batchTemp, batchState, batch_origin);
	return;

	fprintf(f1, "%s|%s|%d|%d|%s|%s|%s\n",
	        batchID, name, totalCount, batchTemp, batchState, destination, deliveryStatus);
	fclose(f1);
	printf("Add information successfull (Delivery status mac dinh: Pending)\n");
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
		Batch arr[MAX_RECORDS];
		int count = loadAll(arr, MAX_RECORDS);

		if (count == 0) {
			printf("Khong co du lieu hoac khong mo duoc file!\n");
			return;
		}

		printf("\n========== DANH SACH LO HANG ==========\n");
		printHeader();
		for (int i = 0; i < count; i++) {
			printRow(&arr[i]);
		}
	}
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
	char destination[50];
	char deliveryStatus[20];

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



	while (fscanf(f1, "%49[^|]|%49[^|]|%d|%d|%49[^|]|%49[^|]|%19[^\n]%*c",
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
			        batch_origin,
			        destination,
			        deliveryStatus);
			{
				printf("So sanh: '%s' voi '%s'\n", batchID, idXoa);

				if (strcmp(batchID, idXoa) != 0) {
					fprintf(f2, "%s|%s|%d|%d|%s|%s|%s\n",
					        batchID,
					        name,
					        totalCount,
					        batchTemp,
					        batchState,
					        batch_origin,
					        destination,
					        deliveryStatus);
				}
			}
			fclose(f1);
			fclose(f2);

			remove("data.txt");
			rename("temp.txt", "data.txt");

			printf("Xóa thành công!\n");
		}
	}
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
			Batch arr[MAX_RECORDS];
			int count = loadAll(arr, MAX_RECORDS);
			char idTim[50];
			int found = 0;

			printf("Nhap Batch ID can tim kiem: ");
			fgets(idTim, sizeof(idTim), stdin);
			idTim[strcspn(idTim, "\n")] = '\0';

			if (count == 0) {
				printf("Khong co du lieu hoac khong mo duoc file data.txt!\n");
				return;
			}

			for (int i = 0; i < count; i++) {
				if (strcmp(arr[i].batchID, idTim) == 0) {
					printf("\n========== KET QUA TIM KIEM ==========\n");
					printHeader();
					printRow(&arr[i]);
					found = 1;
					break;
				}
			}

			if (!found) {
				printf("Không có lô hàng nào có ID: %s\n", idTim);
			}
		}
	}
}
// ============================================================
// CHUC NANG MOI 1: GROUP BY DESTINATION
// Gom nhom cac lo hang theo diem den (destination)
// ============================================================
void groupByDestination() {
	Batch arr[MAX_RECORDS];
	int count = loadAll(arr, MAX_RECORDS);

	if (count == 0) {
		printf("Khong co du lieu de gom nhom!\n");
		return;
	}

	char doneDest[MAX_RECORDS][50];
	int doneCount = 0;

	printf("\n========== GOM NHOM THEO DESTINATION ==========\n");

	for (int i = 0; i < count; i++) {
		// Kiem tra destination nay da xu ly chua
		int already = 0;
		for (int j = 0; j < doneCount; j++) {
			if (strcmp(doneDest[j], arr[i].destination) == 0) {
				already = 1;
				break;
			}
		}
		if (already) continue;

		// Danh dau da xu ly destination nay
		strcpy(doneDest[doneCount], arr[i].destination);
		doneCount++;

		printf("\n>>> Destination: %s\n", arr[i].destination);
		printHeader();

		int totalQty = 0;
		int totalBatches = 0;
		for (int k = 0; k < count; k++) {
			if (strcmp(arr[k].destination, arr[i].destination) == 0) {
				printRow(&arr[k]);
				totalQty += arr[k].totalCount;
				totalBatches++;
			}
		}
		printf("---> So lo hang: %d | Tong so luong: %d\n", totalBatches, totalQty);
	}
}

// ============================================================
// CHUC NANG MOI 2: TRACK DELIVERY
// Xem trang thai giao hang theo ID, cho phep cap nhat trang thai
// ============================================================
void trackDelivery() {
	Batch arr[MAX_RECORDS];
	int count = loadAll(arr, MAX_RECORDS);
	char idTim[50];
	int foundIndex = -1;

	if (count == 0) {
		printf("Khong co du lieu de tra cuu!\n");
		return;
	}

	printf("Nhap Batch ID can theo doi giao hang: ");
	fgets(idTim, sizeof(idTim), stdin);
	idTim[strcspn(idTim, "\n")] = '\0';

	for (int i = 0; i < count; i++) {
		if (strcmp(arr[i].batchID, idTim) == 0) {
			foundIndex = i;
			break;
		}
	}

	if (foundIndex == -1) {
		printf("Khong tim thay lo hang nao co ID: %s\n", idTim);
		return;
	}

	printf("\n========== TRANG THAI GIAO HANG ==========\n");
	printf("BatchID    : %s\n", arr[foundIndex].batchID);
	printf("Ten        : %s\n", arr[foundIndex].name);
	printf("Destination: %s\n", arr[foundIndex].destination);
	printf("Trang thai : %s\n", arr[foundIndex].deliveryStatus);

	printf("\nBan co muon cap nhat trang thai giao hang khong? (1 = Co, 0 = Khong): ");
	int update;
	scanf("%d", &update);
	while (getchar() != '\n');

	if (update == 1) {
		printf("\nChon trang thai moi:\n");
		printf("1. Pending\n");
		printf("2. Shipping\n");
		printf("3. Delivered\n");
		printf("Nhap lua chon: ");
		int statusChoice;
		scanf("%d", &statusChoice);
		while (getchar() != '\n');

		switch (statusChoice) {
			case 1:
				strcpy(arr[foundIndex].deliveryStatus, "Pending");
				break;
			case 2:
				strcpy(arr[foundIndex].deliveryStatus, "Shipping");
				break;
			case 3:
				strcpy(arr[foundIndex].deliveryStatus, "Delivered");
				break;
			default:
				printf("Lua chon khong hop le, giu nguyen trang thai cu.\n");
				return;
		}
		saveAll(arr, count);
		printf("Cap nhat trang thai giao hang thanh cong: %s\n", arr[foundIndex].deliveryStatus);
	}
}

// ============================================================
// CHUC NANG MOI 3: SORT BY BATCH ID
// Sap xep cac lo hang theo Batch ID (tang dan / giam dan)
// ============================================================
void sortByID() {
	Batch arr[MAX_RECORDS];
	int count = loadAll(arr, MAX_RECORDS);

	if (count == 0) {
		printf("Khong co du lieu de sap xep!\n");
		return;
	}

	printf("Chon kieu sap xep:\n");
	printf("1. Tang dan (A -> Z)\n");
	printf("2. Giam dan (Z -> A)\n");
	printf("Nhap lua chon: ");
	int order;
	scanf("%d", &order);
	while (getchar() != '\n');

	// Sap xep noi bot (bubble sort) theo batchID
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - 1 - i; j++) {
			int cmp = strcmp(arr[j].batchID, arr[j + 1].batchID);
			int needSwap = 0;

			if (order == 2) {
				if (cmp < 0) needSwap = 1; // giam dan
			} else {
				if (cmp > 0) needSwap = 1; // tang dan (mac dinh)
			}

			if (needSwap) {
				Batch tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}

	// Luu lai thu tu moi vao file
	saveAll(arr, count);

	printf("\n========== DANH SACH SAU KHI SAP XEP ==========\n");
	printHeader();
	for (int i = 0; i < count; i++) {
		printRow(&arr[i]);
	}
	printf("\nDa sap xep va luu lai vao data.txt thanh cong!\n");
}
