#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "tetris.h"

#define FILENAME "tetris_quicksave.bin"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./modify [score/lines/next_piece] [value]\n");
        return 1;
    }

    char *param = argv[1];
    char *value = argv[2];

    TetrisGameState game;

    FILE *file = fopen(FILENAME, "r+b");

    if (!file) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    fread(&game, sizeof(TetrisGameState), 1, file);

    switch (*param) {
        case 's':
            game.score = strtoul(value, NULL, 10);
            break;
        case 'l':
            {
                unsigned long long val = strtoul(value, NULL, 10);
                if (val > UINT_MAX) {
                    printf("Error: Value too large for lines.\n");
                    return 1;
                }
                game.lines = (unsigned int) val;
            }
            break;
        case 'n':
            {
                unsigned int val = atoi(value);
                if (val > 18) {
                    printf("Error: Invalid piece number.\n");
                    return 1;
                }
                game.next_piece = val;
            }
            break;
        default:
            printf("Error: Invalid parameter.\n");
            return 1;
    }

    fseek(file, 0, SEEK_SET);
    fwrite(&game, sizeof(TetrisGameState), 1, file);
    fclose(file);

    return 0;
}
