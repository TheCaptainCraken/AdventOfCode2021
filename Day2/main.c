#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage %s <input file>!\n", *argv);
    }

    FILE* fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Mistaken file\n");
        return 1;
    }

    char current_command[80];
    int magnitude;

    int aim = 0;
    int depth = 0;
    int position = 0;

    while (fscanf(fp, "%s %d\n", current_command, &magnitude) != EOF) {
        if (strcmp(current_command, "forward") == 0) {
            position += magnitude;
            depth += (aim * magnitude);
        }
        else if (strcmp(current_command, "up")) {
            aim += magnitude;
        }
        else if (strcmp(current_command, "down")) {
            aim -= magnitude;
        }
    }
    fclose(fp);

    printf("Depth => %d\nPosition => %d\nOutput => %d\n", depth, position, depth * position);

    return 0;
}