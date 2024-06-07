#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 행이 유효한지 검사하는 함수
bool is_valid_row(int sudoku[9][9], int row) {
    bool nums[10] = { false };
    for (int col = 0; col < 9; col++) {
        int num = sudoku[row][col];
        if (num < 1 || num > 9 || nums[num]) {
            return false;
        }
        nums[num] = true;
    }
    return true;
}

// 열이 유효한지 검사하는 함수
bool is_valid_col(int sudoku[9][9], int col) {
    bool nums[10] = { false };
    for (int row = 0; row < 9; row++) {
        int num = sudoku[row][col];
        if (num < 1 || num > 9 || nums[num]) {
            return false;
        }
        nums[num] = true;
    }
    return true;
}

// 3x3 서브 그리드가 유효한지 검사하는 함수
bool is_valid_subgrid(int sudoku[9][9], int startRow, int startCol) {
    // 1부터 9까지의 숫자의 출현 여부를 추적하기 위한 배열
    bool nums[10] = { false };
    
    // 3x3 서브 그리드 내의 모든 셀을 순회
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            // 현재 셀의 숫자를 가져옴
            int num = sudoku[startRow + row][startCol + col];
            
            // 숫자가 1보다 작거나 9보다 크거나 이미 본 숫자라면 유효하지 않음
            if (num < 1 || num > 9 || nums[num]) {
                return false;
            }
            // 해당 숫자가 나타났음을 기록
            nums[num] = true;
        }
    }
    return true; // 3x3 서브 그리드가 유효함
}

// 스도쿠 퍼즐이 유효한지 검사하는 함수
bool validate_sudoku(int sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        if (!is_valid_row(sudoku, i) || !is_valid_col(sudoku, i)) {
            return false;
        }
    }
    for (int row = 0; row < 9; row += 3) {
        for (int col = 0; col < 9; col += 3) {
            if (!is_valid_subgrid(sudoku, row, col)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int sudoku[9][9];

    // solution.txt 파일을 읽기 모드로 열기
    FILE *file = fopen("solution.txt", "r");
    if (file == NULL) { // 파일 열기 실패 시 오류 처리
        perror("fopen");
        return EXIT_FAILURE;
    }

    // 파일에서 스도쿠 퍼즐 읽기
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fscanf(file, "%d", &sudoku[i][j]);
        }
    }
    fclose(file); // 파일 닫기

    // 스도쿠 퍼즐 유효성 검사 및 결과 출력
    if (validate_sudoku(sudoku)) {
        printf("이 스도쿠 퍼즐은 valid합니다.\n");
    } else {
        printf("이 스도쿠 퍼즐은 valid하지 않습니다.\n");
    }

    return 0;
}