#include <libchessviz/Moves.h>
#include <libchessviz/board_read.h>
#include <libchessviz/chessboard.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE* file;
    if (argc == 1) {
        return 1;
    }
    char* filename = argv[1];
    Chessboard chessboard;
    char str[50];
    char string[2 * (CHESSBOARD_SIZE + 1) * (1 + CHESSBOARD_SIZE) + 1];
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    Moves moves = {.num = 0};
    Errors error
            = {.index = 0,
               .isTrigger = 0,
               .desc = (char*)malloc(sizeof(char) * 50)};
    file = fopen(filename, "r");
    int isRight;
    while (fgets(str, 32, file) != NULL) {
        printf("%s", str);
        isRight = ParseStep(str, &error, &moves);
        if (isRight == 1 || error.isTrigger == 1) {
            printf("Error");
            return 0;
        }
    }

    for (int i = 0; i < moves.num; i++) {
        isRight = DoMove(&chessboard, moves.move[i], &error);
        if (isRight == 1 || error.isTrigger == 1) {
            printf("Error2");
            return 0;
        }
    }
    chessboardToString(&chessboard, string);
    printf("\n%s", string);
    return 0;
}