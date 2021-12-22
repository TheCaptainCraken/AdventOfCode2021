#include <stdio.h>
#include <stdlib.h>
#include "LinkedLists.h"

int FindMax(Node* head);

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage %s <input file>\n", *argv);
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open %s\n", *(argv + 1));
        exit(EXIT_FAILURE);
    }

    Node* list_head = NULL;

    int n;
    while (fscanf(fp, "%d,", &n) != EOF) {
        Append(&list_head, n);
    }

    int target = FindMax(list_head);

    int best_so_far = CalcFuel(list_head, 0);

    for (int i = 1; i < target; i++) {
        int current = CalcFuel(list_head, i);

        if (current < best_so_far) {
            best_so_far = current;
        }
    }

    printf("=> %d\n", best_so_far);

    exit(EXIT_SUCCESS);
}