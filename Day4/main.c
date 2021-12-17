#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEN 5

typedef struct bingo_number_s {
    int number;
    struct bingo_number_s* next;
}bingo_number_t;

typedef struct bingo_table_s {
    int table[LEN][LEN];
    bool marked_table[LEN][LEN];

    struct bingo_table_s* next;
}bingo_table_t;

void PrintListNumbers(bingo_number_t* head);
void PrintListTables(bingo_table_t* head);

void AppendNumbers(bingo_number_t** head, int number);
void AppendTables(bingo_table_t** head, int table[5][5]);

void CopyTables(int start[5][5], int end[5][5]);
void InitBoolTable(bool table[5][5]);

void AddEntryIf(bingo_table_t* table, int entry);
bool CheckVictory(bingo_table_t* table);
bool IsLastOneStanding(bingo_table_t* head);
int GetLen(bingo_table_t* head);


int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage %s <input file>\n", *argv);
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        fprintf(stderr, "Invalid file used! [%s]\n", *(argv + 1));
        exit(EXIT_FAILURE);
    }

    bingo_number_t* numbers_head = NULL;
    bingo_table_t* tables_head = NULL;

    int n;
    char c = ' ';
    while (c != '\n') {
        fscanf(fp, "%d", &n);
        AppendNumbers(&numbers_head, n);
        c = getc(fp);
    }

    int matrix[LEN][LEN];
    while (getc(fp) != EOF) {
        for (int row = 0; row < LEN; row++) {
            for (int col = 0; col < LEN; col++) {
                fscanf(fp, "%d", &matrix[row][col]);
            }
        }
        AppendTables(&tables_head, matrix);
    }

    bingo_number_t* current = numbers_head;
    while (current != NULL) {
        bingo_table_t* current_table = tables_head;

        while (current_table != NULL) {
            AddEntryIf(current_table, current->number);
            if (CheckVictory(current_table) && IsLastOneStanding(tables_head)) {
                int sum = 0;
                for (int row = 0; row < LEN; row++) {
                    for (int col = 0; col < LEN; col++) {
                        sum += (current_table->table[row][col] * !(current_table->marked_table[row][col]));
                    }
                }
                int answ = sum * current->number;
                printf("=> %d\n", answ);
                exit(EXIT_SUCCESS);
            }

            current_table = current_table->next;
        }
        current = current->next;
    }
    PrintListTables(tables_head);
    exit(EXIT_SUCCESS);
}

void PrintListNumbers(bingo_number_t* head) {
    bingo_number_t* current = head;

    while (current != NULL) {
        printf("=> %d\n", current->number);
        current = current->next;
    }
}

void PrintListTables(bingo_table_t* head) {
    bingo_table_t* current = head;
    while (current != NULL) {
        for (int row = 0; row < LEN; row++) {
            for (int col = 0; col < LEN; col++) {
                printf("%d\t", current->table[row][col]);
            }
            printf("\n");
        }
        for (int row = 0; row < LEN; row++) {
            for (int col = 0; col < LEN; col++) {
                printf("%d\t", current->marked_table[row][col]);
            }
            printf("\n");
        }
        printf("\n\n");
        current = current->next;
    }
}

void AppendNumbers(bingo_number_t** head, int number) {

    bingo_number_t* new_element = (bingo_number_t*)malloc(sizeof(bingo_number_t));
    if (new_element == NULL) {
        fprintf(stderr, "Error while allocating memory!\n");
        exit(EXIT_FAILURE);
    }
    new_element->number = number;
    new_element->next = NULL;

    if (*head == NULL) {
        *head = new_element;
    }
    else {
        bingo_number_t* current = *head;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = new_element;
    }
}

void AppendTables(bingo_table_t** head, int table[5][5]) {
    bingo_table_t* new_element = (bingo_table_t*)malloc(sizeof(bingo_table_t));
    if (new_element == NULL) {
        fprintf(stderr, "Allocation error!\n");
        exit(EXIT_FAILURE);
    }

    CopyTables(table, new_element->table);
    InitBoolTable(new_element->marked_table);
    new_element->next = NULL;
    if (*head == NULL) {
        *head = new_element;
    }
    else {
        bingo_table_t* current = *head;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = new_element;
    }
}

void CopyTables(int start[5][5], int end[5][5]) {
    for (int row = 0; row < LEN; row++) {
        for (int col = 0; col < LEN; col++) {
            end[row][col] = start[row][col];
        }
    }
}

void InitBoolTable(bool table[5][5]) {
    for (int row = 0; row < LEN; row++) {
        for (int col = 0; col < LEN; col++) {
            table[row][col] = false;
        }
    }
}

void AddEntryIf(bingo_table_t* table, int entry) {
    for (int row = 0; row < LEN; row++) {
        for (int col = 0; col < LEN; col++) {
            if (table->table[row][col] == entry) {
                table->marked_table[row][col] = true;
            }
        }
    }
}

bool CheckVictory(bingo_table_t* table) {
    for (int i = 0; i < LEN; i++) {
        int sumx = 0, sumy = 0;
        for (int j = 0; j < LEN; j++) {
            sumx += table->marked_table[i][j];
            sumy += table->marked_table[j][i];
        }

        if (sumx == 5 || sumy == 5) {
            return true;
        }
    }
    return false;
}

int GetLen(bingo_table_t* head) {
    bingo_table_t* current = head;
    int sum = 0;
    while (current != NULL) {
        sum++;
        current = current->next;
    }

    return sum;
}

bool IsLastOneStanding(bingo_table_t* head) {
    int sum = GetLen(head);

    bingo_table_t* current = head;
    while (current != NULL) {
        sum -= CheckVictory(current);

        current = current->next;
    }

    if (sum == 0) {
        return true;
    }
    else {
        return false;
    }
}