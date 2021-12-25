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
int CountLines(const char* file_path);
bool StringComparePlusExtraCrisp(char* string1, char* string2);
bool IsSubString(char* sub, char* master);
bool IsCharInString(char character, char* string);

int main(int argc, char** argv) {
    if (argc != 2) {
        ThrowError("Usage <input file>\n");
    }

    FILE* fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        ThrowError("Can't open the specified file!\n");
    }

    char input[14][8];

    char zero[8];
    char one[8];
    char two[8];
    char three[8];
    char four[8];
    char five[8];
    char six[8];
    char seven[8];
    char eight[8];
    char nine[8];

    char waste[8];

    int sum = 0;

    while (fscanf(fp, "%s", input[0]) != EOF) {

        for (int i = 1; i < PART1; i++) {
            fscanf(fp, "%s", input[i]);
        }
        fscanf(fp, "%s", waste);
        for (int i = 0; i < PART2; i++) {
            fscanf(fp, "%s", input[PART1 + i]);
        }

        //finding the constant ones
        for (int i = 0; i < PART1; i++) {
            switch (strlen(input[i])) {
            case ONE:
                strcpy(one, input[i]);
                break;
            case FOUR:
                strcpy(four, input[i]);
                break;
            case SEVEN:
                strcpy(seven, input[i]);
                break;
            case EIGHT:
                strcpy(eight, input[i]);
                break;
            default:
                break;
            }
        }

        //finding 3
        for (int i = 0; i < PART1; i++) {
            if (strlen(input[i]) == 5 && IsSubString(one, input[i])) {
                strcpy(three, input[i]);
                break;
            }
        }

        //finding 6
        for (int i = 0; i < PART1; i++) {
            if (strlen(input[i]) == 6 && (IsCharInString(one[0], input[i]) != IsCharInString(one[1], input[i]))) {
                strcpy(six, input[i]);
                break;
            }
        }

        //finding 9
        for (int i = 0; i < PART1; i++) {
            if (strlen(input[i]) == 6 && IsSubString(four, input[i])) {
                strcpy(nine, input[i]);
                break;
            }
        }

        //finding 5
        for (int i = 0; i < PART1; i++) {
            if (strlen(input[i]) == 5 && IsSubString(input[i], six)) {
                strcpy(five, input[i]);
                break;
            }
        }

        //finding 2
        for (int i = 0; i < PART1; i++) {
            if (strlen(input[i]) == 5 && !StringComparePlusExtraCrisp(input[i], five) & !StringComparePlusExtraCrisp(input[i], three)) {
                strcpy(two, input[i]);
                break;
            }
        }

        //finding 0
        for (int i = 0; i < PART1; i++) {
            if (strlen(input[i]) == 6 && !StringComparePlusExtraCrisp(input[i], six) & !StringComparePlusExtraCrisp(input[i], nine)) {
                strcpy(zero, input[i]);
                break;
            }
        }
        printf("\n");
        char string_number[5];
        for (int i = PART1; i < PART1 + PART2; i++) {
            if (StringComparePlusExtraCrisp(input[i], one)) {
                string_number[i - PART1] = '1';
            }
            else if (StringComparePlusExtraCrisp(input[i], two)) {
                string_number[i - PART1] = '2';
            }
            else if (StringComparePlusExtraCrisp(input[i], three)) {
                string_number[i - PART1] = '3';
            }
            else if (StringComparePlusExtraCrisp(input[i], four)) {
                string_number[i - PART1] = '4';
            }
            else if (StringComparePlusExtraCrisp(input[i], five)) {
                string_number[i - PART1] = '5';
            }
            else if (StringComparePlusExtraCrisp(input[i], six)) {
                string_number[i - PART1] = '6';
            }
            else if (StringComparePlusExtraCrisp(input[i], seven)) {
                string_number[i - PART1] = '7';
            }
            else if (StringComparePlusExtraCrisp(input[i], eight)) {
                string_number[i - PART1] = '8';
            }
            else if (StringComparePlusExtraCrisp(input[i], nine)) {
                string_number[i - PART1] = '9';
            }
            else if (StringComparePlusExtraCrisp(input[i], zero)) {
                string_number[i - PART1] = '0';
            }
            else {
                printf("?");
            }
        }
        string_number[4] = '\0';
        sum += atoi(string_number);
    }
    printf("=> %d", sum);
}

void ThrowError(const char* error_message) {
    fprintf(stderr, error_message);
    exit(EXIT_FAILURE);
}

int CountLines(const char* file_path) {
    FILE* fp = fopen(file_path, "r");
    if (fp == NULL) {
        ThrowError("Can't open the file to read the lines\n");
    }

    char current_char;
    int count = 1;
    do {
        current_char = getc(fp);
        if (current_char == '\n') {
            count++;
        }
    } while (current_char != EOF);

    return count;
}

bool StringComparePlusExtraCrisp(char* string1, char* string2) {
    const int len = strlen(string1);
    if (len != strlen(string2)) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        bool was_found = false;
        for (int j = 0; j < len; j++) {
            if (string1[i] == string2[j]) {
                was_found = true;
                break;
            }
        }
        if (was_found == false) {
            return false;
        }
    }

    return true;
}

bool IsSubString(char* sub, char* master) {
    const int len_sub = strlen(sub);
    const int len_master = strlen(master);

    for (int i = 0; i < len_sub; i++) {
        bool found = false;
        for (int j = 0; j < len_master; j++) {
            if (sub[i] == master[j]) {
                found = true;
                break;
            }
        }
        if (found == false) {
            return false;
        }
    }
    return true;
}
bool IsCharInString(char character, char* string) {
    const int len = strlen(string);

    for (int i = 0; i < len; i++) {
        if (character == string[i]) {
            return true;
        }
    }
    return false;
}