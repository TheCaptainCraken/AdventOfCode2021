#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define MAP_SIZE 10
#define MAP_SIZE 1000

//#define FILE_LEN 10
#define FILE_LEN 500

typedef struct coordinate_s {
    int x, y;
}coordinate_t;

typedef struct line_s {
    coordinate_t* start;
    coordinate_t* end;
}line_t;

void DrawLine(line_t* line, short map[MAP_SIZE][MAP_SIZE]);
line_t* GenerateLine(coordinate_t* coord1, coordinate_t* coord2);
void PrintLine(line_t* line);

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage %s <input file>\n", *argv);
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        fprintf(stderr, "Invalid file [%s]\n", *(argv + 1));
        exit(EXIT_FAILURE);
    }
    short map[MAP_SIZE][MAP_SIZE];
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            map[i][j] = 0;
        }
    }
    for (int i = 0; i < FILE_LEN; i++) {
        int x1, y1, x2, y2;

        fscanf(fp, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);

        coordinate_t* coord1 = (coordinate_t*)malloc(sizeof(coordinate_t));
        if (coord1 == NULL) {
            fprintf(stderr, "Allocation error while allocating coord1\n");
            exit(EXIT_FAILURE);
        }
        coord1->x = x1;
        coord1->y = y1;

        coordinate_t* coord2 = (coordinate_t*)malloc(sizeof(coordinate_t));
        if (coord2 == NULL) {
            fprintf(stderr, "Allocation error while allocating coord1\n");
            exit(EXIT_FAILURE);
        }
        coord2->x = x2;
        coord2->y = y2;

        line_t* line = GenerateLine(coord1, coord2);
        DrawLine(line, map);
    }
    int count = 0;
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[j][i] >= 2) {
                count++;
            }
        }
    }
    printf("=> %d\n", count);
    fclose(fp);

    exit(EXIT_SUCCESS);
}

void DrawLine(line_t* line, short map[MAP_SIZE][MAP_SIZE]) {
    int x1 = line->start->x;
    int y1 = line->start->y;

    int x2 = line->end->x;
    int y2 = line->end->y;

    int x_off = x1 - x2;
    int y_off = y1 - y2;

    while (x1 != x2 || y1 != y2) {
        map[x1][y1]++;
        if (x_off > 0) {
            x1--;
        }
        else if (x_off < 0) {
            x1++;
        }
        if (y_off < 0) {
            y1++;
        }
        else if (y_off > 0) {
            y1--;
        }
    }
    map[x1][y1]++;
}

line_t* GenerateLine(coordinate_t* coord1, coordinate_t* coord2) {
    line_t* new_line = (line_t*)malloc(sizeof(line_t));
    if (new_line == NULL) {
        fprintf(stderr, "Allocation error in GenerateLine\n");
        exit(EXIT_FAILURE);
    }
    new_line->start = coord1;
    new_line->end = coord2;

    return new_line;
}

void PrintLine(line_t* line) {
    printf("(%d, %d) => (%d, %d)\n", line->start->x, line->start->y, line->end->x, line->end->y);
}