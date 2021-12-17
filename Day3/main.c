#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define INPUT_BIT_LENGTH 5
#define INPUT_BIT_LENGTH 12

//#define FILE_LENGTH 12
#define FILE_LENGTH 1000

int main(int argc, char** argv) {

    if (argc != 2) {
        fprintf(stderr, "Usage %s <input file>\n", *argv);
        exit(1);
    }

    FILE* fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        fprintf(stderr, "Invalid file!\n");
        exit(2);
    }

    char file[FILE_LENGTH][INPUT_BIT_LENGTH + 1];
    char line[INPUT_BIT_LENGTH + 1];
    int i = 0;
    while (fscanf(fp, "%s", line) != EOF) {
        strcpy(file[i], line);
        i++;
    }
    fclose(fp);

    char gamma_rate[INPUT_BIT_LENGTH];
    for (int col = 0; col < INPUT_BIT_LENGTH; col++) {
        int sum = 0;
        for (int row = 0; row < FILE_LENGTH; row++) {
            sum += file[row][col] - '0';
        }

        if (sum > FILE_LENGTH / 2) {
            gamma_rate[col] = '1';
        }
        else {
            gamma_rate[col] = '0';
        }
    }

    for (int i = 0; i < INPUT_BIT_LENGTH; i++) {
        printf("%c", gamma_rate[i]);
    }
    printf("\n");
    for (int i = 0; i < INPUT_BIT_LENGTH; i++) {
        if (gamma_rate[i] == '0') {
            gamma_rate[i] = '1';
        }
        else {
            gamma_rate[i] = '0';
        }
        printf("%c", gamma_rate[i]);
    }

    return 0;
}