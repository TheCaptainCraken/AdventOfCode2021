#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AMBIENT_MAX 9

void Error(const char* message);
void PrintAmbient(double ambient[AMBIENT_MAX]);
double GetNumberOfFishesAmbient(double ambient[AMBIENT_MAX]);

int main(int argc, char** argv) {

    if (argc != 3) {
        Error("Usage <input file> <number of cycles>\n");
    }

    FILE* fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        Error("Can't open the file you selected\n");
    }

    double ambient[AMBIENT_MAX];
    for (int i = 0; i < AMBIENT_MAX; i++) {
        ambient[i] = 0;
    }
    int current_age;
    while (fscanf(fp, "%d,", &current_age) != EOF) {
        ambient[current_age]++;
    }
    fclose(fp);

    int number_of_cycles = atoi(*(argv + 2));

    for (int i = 0; i < number_of_cycles; i++) {
        double base = ambient[0];
        for (int i = 1; i < AMBIENT_MAX; i++) {
            ambient[i - 1] = ambient[i];
        }

        ambient[6] += base;
        ambient[AMBIENT_MAX - 1] = base;
        if (i % 20 == 0) {
            printf("=> %lf\n", GetNumberOfFishesAmbient(ambient));
        }

    }
    printf("=> %lu\n", GetNumberOfFishesAmbient(ambient));
    printf("\n\n");
    for (int i = 0; i < AMBIENT_MAX; i++) {
        printf("%lf + ", ambient[i]);
    }
    exit(EXIT_SUCCESS);
}

void Error(const char* message) {
    fprintf(stderr, message);
    exit(EXIT_FAILURE);
}

void PrintAmbient(double ambient[AMBIENT_MAX]) {
    for (int i = 0; i < AMBIENT_MAX; i++) {
        printf("[%d] => %lf fishes\n", i, ambient[i]);
    }
    printf("\n");
}

double GetNumberOfFishesAmbient(double ambient[AMBIENT_MAX]) {
    double sum = 0;

    for (int i = 0; i < AMBIENT_MAX; i++) {
        sum += ambient[i];
    }

    return sum;
}