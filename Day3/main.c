#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct element_s {
    char number[80];
    struct element_s* next;
}element_t;


void Error(const char* error_message);
void Append(element_t** head, char* string);
void Print(element_t* head);
void DeleteIfNotContainsAtIndex(element_t** head, int index, char bit);
int GetLen(element_t* head);
char MostCommonBitAtIndex(element_t* head, int index);

int main(int argc, char** argv) {

    if (argc != 2) {
        Error("Usage <input file>\n");
    }

    FILE* fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        Error("Can't open the file you specified!\n");
    }

    element_t* list_head = NULL;

    char current_number[80];
    while (fscanf(fp, "%s\n", current_number) != EOF) {
        Append(&list_head, current_number);
    }
    int index = 0;
    while (GetLen(list_head) > 1) {
        DeleteIfNotContainsAtIndex(&list_head, index, MostCommonBitAtIndex(list_head, index));
        index++;
    }
    Print(list_head);
    exit(EXIT_SUCCESS);
}

void Error(const char* error_message) {
    fprintf(stderr, error_message);
    exit(EXIT_FAILURE);
}

void Print(element_t* head) {
    element_t* current = head;

    while (current != NULL) {
        printf("%s\n", current->number);
        current = current->next;
    }
}

void Append(element_t** head, char* string) {
    element_t* next_element = (element_t*)malloc(sizeof(element_t));
    if (next_element == NULL) {
        Error("Sorry but malloca failed lol.\n");
    }

    next_element->next = NULL;
    strcpy(next_element->number, string);

    if (*head == NULL) {
        *head = next_element;
    }
    else {
        element_t* current = *head;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = next_element;
    }
}

int GetLen(element_t* head) {
    element_t* current = head;
    int sum = 0;
    while (current != NULL) {
        sum++;
        current = current->next;
    }

    return sum;
}

void DeleteIfNotContainsAtIndex(element_t** head, int index, char bit) {
    element_t* current = *head;
    if (current->number[index] == bit) {
        *head = current->next;
    }
    while (current->next != NULL) {
        if (current->next->number[index] == bit) {
            current->next = current->next->next;
        }
        else {
            current = current->next;
        }
    }
}

char MostCommonBitAtIndex(element_t* head, int index) {
    int len = GetLen(head);
    int sum = 0;
    element_t* current = head;

    while (current != NULL) {
        sum += (current->number[index] - '0');
        current = current->next;
    }

    if (sum * 2 >= len) {
        return '0';
    }
    else {
        return '1';
    }
}