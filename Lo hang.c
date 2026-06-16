#include <stdio.h>
#include <string.h>
#define MAX 50

struct Batch {
    int id;
    char name[50];
    float unit;
    float temp;
    char state[20];
};

struct Batch batches[MAX];
int count = 0;


void loadDefaultData() {
    struct Batch defaults[] = {
        {1,  "Tao",        180, 8,  "fresh"},
        {2,  "Chuoi",      120, 22, "fresh"},
        {3,  "Xoai",       350, 10, "fresh"},
        {4,  "Nho kho",    50,  25, "dry"},
        {5,  "Man kho",    70,  24, "dry"},
        {6,  "Dua",        900, 7,  "fresh"},
        {7,  "Cha la kho", 40,  26, "dry"},
        {8,  "Cam",        220, 9,  "fresh"},
        {9,  "Mo kho",     60,  23, "dry"},
        {10, "Kiwi",       90,  6,  "fresh"},
    };
    int n = sizeof(defaults) / sizeof(defaults[0]);
    for (int i = 0; i < n; i++) {
        batches[i] = defaults[i];
    }
    count = n;
    printf("Loaded %d default batches.\n", count);
}

void addBatch() {
    printf("Enter Batch ID: ");
    scanf("%d", &batches[count].id);
    getchar();

    printf("Enter Batch Name: ");
    fgets(batches[count].name, sizeof(batches[count].name), stdin);
    batches[count].name[strcspn(batches[count].name, "\n")] = 0;

    printf("Enter Number of unit (g): ");
    scanf("%f", &batches[count].unit);

    printf("Enter Batch temp (C): ");
    scanf("%f", &batches[count].temp);
    getchar();

    printf("Enter Batch state (dry/fresh): ");
    fgets(batches[count].state, sizeof(batches[count].state), stdin);
    batches[count].state[strcspn(batches[count].state, "\n")] = 0;

    count++;
    printf("Batch added successfully!\n");
}

void displayBatches() {
    if (count == 0) {
        printf("No batches found.\n");
        return;
    }
    printf("\n%-5s %-15s %-12s %-12s %-10s\n", "ID", "Name", "Weight(kg)", "Temp(C)", "State");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-15s %-12.1f %-12.1f %-10s\n",
               batches[i].id,
               batches[i].name,
               batches[i].unit,
               batches[i].temp,
               batches[i].state);
    }
}

void searchBatch() {
    int id;
    printf("Enter Batch ID to search: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (batches[i].id == id) {
            printf("\nBatch Found!\n");
            printf("ID     : %d\n",   batches[i].id);
            printf("Name   : %s\n",   batches[i].name);
            printf("Weight : %.1f g\n", batches[i].unit);
            printf("Temp   : %.1f C\n", batches[i].temp);
            printf("State  : %s\n",   batches[i].state);
            return;
        }
    }
    printf("Batch not found.\n");
}

int main() {
    loadDefaultData(); 

    int choice;
    do {
        printf("\n===== Batch Management =====\n");
        printf("1. Add Batch\n");
        printf("2. Display Batches\n");
        printf("3. Search Batch\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBatch();       break;
            case 2: displayBatches(); break;
            case 3: searchBatch();    break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}