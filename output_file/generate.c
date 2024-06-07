#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

// 스도쿠 퍼즐을 생성하는 함수
void generate_sudoku(int sudoku[9][9]) {
    // 간단한 스도쿠 퍼즐 생성
    srand(time(NULL));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = (i * 3 + i / 3 + j) % 9 + 1;
        }
    }
}

int main() {
    int sudoku[9][9];
    int solution[9][9];
    generate_sudoku(solution); // 완성된 스도쿠 퍼즐 생성

    // 빈 셀을 포함한 스도쿠 퍼즐 생성
    // 우선 solution을 sudoku에 복사
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = solution[i][j];
        }
    }
    for (int i = 0; i < 20; i++) {
        int row = rand() % 9;
        int col = rand() % 9;
        sudoku[row][col] = 0;
    }

    // 생성된 스도쿠 문제 퍼즐을 표준 출력으로 출력
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }

    // 정답 스도쿠 퍼즐을 파일에 저장
    FILE *file = fopen("solution.txt", "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fprintf(file, "%d ", solution[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file); // 파일 닫기

    return 0;
}