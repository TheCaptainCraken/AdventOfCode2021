#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct bingo_number_s {
    int number;
    struct bingo_number_s* next;
}bingo_number_t;

void Append(bingo_number_t** head, bingo_number_t* new) {
    if (*head == NULL) {
        *head = new;
    }
    else {
        bingo_number_t* current = *head;

        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
}

bingo_number_t* GenerateList(char* string_input) {

    bingo_number_t* list = NULL;

    int index = 0;
    while (2 + 2 == 4) {
        char number[2];
        int i = 0;
        while (*(string_input + index) != ',' && *(string_input + index) != '\0') {
            number[i] = *(string_input + index);
            i++;
            index++;
        }
        if (i == 1) {
            number[1] = number[0];
            number[0] = '0';
        }

        bingo_number_t* new_number = (bingo_number_t*)malloc(sizeof(bingo_number_t));
        new_number->next = NULL;
        new_number->number = atoi(number);
        Append(&list, new_number);
        if (*(string_input + index) == '\0') {
            break;
        }
        index++;
    }
    return list;
}

int main(int argc, char** argv) {

    FILE* fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        fprintf(stderr, "Usage %s <input file>\n", *argv);
        exit(EXIT_FAILURE);
    }

    char numbers[1000];
    fscanf(fp, "%s", numbers);

    bingo_number_t* head = GenerateList(numbers);

    int bingo_matrix[5][5];
    while (fscanf(fp, "\n%d %d %d %d %d", &bingo_matrix[0][0], &bingo_matrix[0][1], &bingo_matrix[0][2], &bingo_matrix[0][3], &bingo_matrix[0][4]) != EOF) {
        for (int row = 1; row < 5; row++) {
            fscanf(fp, "\n%d %d %d %d %d", &bingo_matrix[row][0], &bingo_matrix[row][1], &bingo_matrix[row][2], &bingo_matrix[row][3], &bingo_matrix[row][4]);
        }
    }



    free(head);
    fclose(fp);
    return 0;
}