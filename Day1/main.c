#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Length 2000

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage %s <input file>!\n", *argv);
    }

    FILE* fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Error!\n");
        return 1;
    }

    int input[Length];
    for (int i = 0; i < Length; i++) {
        fscanf(fp, "%d", &input[i]);
    }
    fclose(fp);

    int counter = 0;

    for (int top_index = 0; top_index < Length - 3; top_index++) {
        int suma = 0, sumb = 0;
        for (int i = top_index, j = top_index + 1; i < top_index + 3, j < top_index + 4; i++, j++) {
            suma += input[i];
            sumb += input[j];
        }
        if (sumb > suma) {
            counter++;
        }
    }

    printf("=> %d", counter++);

    return 0;
}