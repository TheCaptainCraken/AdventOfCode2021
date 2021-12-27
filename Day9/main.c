#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void ThrowError(const char* message);
int GetXLen(char* path);
int GetYLen(char* path);
int** CreateArray(int x, int y);
void FreeArray(int** array, int y);
void PrintArray(int** array, int x, int y);
bool IsLowPoint(int row, int col, int x_len, int y_len, int** array);
bool PositionExists(int row, int col, int x_len, int y_len);

int main(int argc, char** argv) {

    if (argc != 2) {
        ThrowError("Not Using the program right!\n");
    }

    FILE* fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        ThrowError("Can't open the file!\n");
    }

    int x_len = GetXLen(*(argv + 1));
    int y_len = GetYLen(*(argv + 1));
    int** array = CreateArray(x_len, y_len);

    for (int i = 0; i < y_len; i++) {
        for (int j = 0; j < x_len; j++) {
            int number = getc(fp) - '0';
            array[i][j] = number;
        }
        getc(fp);
    }
    fclose(fp);
    int sum = 0;

    for (int row = 0; row < y_len; row++) {
        for (int col = 0; col < x_len; col++) {
            if (IsLowPoint(row, col, x_len, y_len, array)) {
                sum += array[row][col] + 1;
            }
        }
    }

    printf("=> %d\n", sum);

    FreeArray(array, y_len);
    exit(EXIT_SUCCESS);
}

void ThrowError(const char* message) {
    fprintf(stderr, message);
    exit(EXIT_FAILURE);
}

int GetXLen(char* path) {
    FILE* fp = fopen(path, "r");
    if (fp == NULL) {
        ThrowError("Can't open the file\n");
    }

    char line[500];
    fscanf(fp, "%s\n", line);
    fclose(fp);
    return strlen(line);
}

int GetYLen(char* path) {
    FILE* fp = fopen(path, "r");
    if (fp == NULL) {
        ThrowError("Can't open the file\n");
    }
    int lines_count = 0;

    while (2 + 2 == 4) {
        char current = getc(fp);
        if (current == '\n') {
            lines_count++;
        }
        if (current == EOF) {
            lines_count++;
            break;
        }
    }

    fclose(fp);
    return lines_count;
}

int** CreateArray(int x, int y) {
    int** return_array = (int**)malloc(sizeof(int*) * y);
    if (return_array == NULL) {
        ThrowError("Can't create array master");
    }
    for (int i = 0; i < x; i++) {
        *(return_array + i) = (int*)malloc(sizeof(int) * x);
        if (*(return_array + i) == NULL) {
            ThrowError("Can't allocate array piece");
        }
    }

    return return_array;
}

void FreeArray(int** array, int y) {
    for (int i = 0; i < y; i++) {
        free(*(array + i));
    }
    free(array);
}

void PrintArray(int** array, int x, int y) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}