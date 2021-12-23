#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define PART1 10
#define PART2 4

#define ONE 2
#define FOUR 4
#define SEVEN 3
#define EIGHT 7

void ThrowError(const char* error_message);

int main(int argc, char** argv) {
    if (argc != 2) {
        ThrowError("Usage <input file>\n");
    }

    FILE* fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        ThrowError("Can't open the specified file!\n");
    }

    int count = 0;

    char input[8];
    while (fscanf(fp, "%s", input) != EOF) {
        for (int i = 1; i < PART1; i++) {
            fscanf(fp, "%s", input);
        }
        fscanf(fp, "%s", input);
        for (int i = 0; i < PART2; i++) {
            fscanf(fp, "%s", input);
            int len = strlen(input);
            if (len == ONE || len == FOUR || len == SEVEN || len == EIGHT) {
                count++;
            }
        }
    }

    printf("=> %d\n", count);

}

void ThrowError(const char* error_message) {
    fprintf(stderr, error_message);
    exit(EXIT_FAILURE);
}