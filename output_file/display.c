#include <stdio.h>
#include <stdlib.h>

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

// 사용자가 풀 스도쿠 퍼즐을 파일로부터 읽어와서 표시하는 함수
void display_sudoku() {
    FILE *file = fopen("sudoku.txt", "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int sudoku[9][9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (fscanf(file, "%d", &sudoku[i][j]) != 1) {
                perror("fscanf");
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file); // 파일 닫기

    // 스도쿠 퍼즐 출력
    printf("스도쿠 퍼즐:\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0) {
                printf(". ");
            } else {
                printf("%d ", sudoku[i][j]);
            }
        }
        printf("\n");
    }
}