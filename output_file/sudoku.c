#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

// 함수 선언
void display_sudoku();
void play_sudoku();
void read_sudoku_from_pipe(int pipe_fd[2], int sudoku[9][9]);

int main() {
    pid_t pid;
    int pipe_fd[2];

    // 파이프 생성
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 프로세스 생성
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // 자식 프로세스
        close(pipe_fd[0]); // 파이프의 읽기 끝을 닫음
        dup2(pipe_fd[1], STDOUT_FILENO); // 파이프의 쓰기 끝을 표준 출력으로 복제
        execlp("./generate", "generate", NULL); // 외부 프로그램 실행
        perror("execlp");
        exit(EXIT_FAILURE);
    } else { // 부모 프로세스
        close(pipe_fd[1]); // 파이프의 쓰기 끝을 닫음
        int sudoku[9][9];
        read_sudoku_from_pipe(pipe_fd, sudoku); // 파이프로부터 스도쿠 퍼즐 읽기
        
        // 생성된 스도쿠 퍼즐을 파일에 저장
        FILE *file = fopen("sudoku.txt", "w");
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                fprintf(file, "%d ", sudoku[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file); // 파일 닫기

        display_sudoku(); // 생성된 스도쿠 퍼즐 표시
        play_sudoku(sudoku); // 사용자가 퍼즐을 풀 수 있게 함

        // 스도쿠 퍼즐 유효성 검사
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // 자식 프로세스
            execlp("./validate", "validate", NULL); // 외부 프로그램 실행
            perror("execlp");
            exit(EXIT_FAILURE);
        } else { // 부모 프로세스
            wait(NULL); // 자식 프로세스가 종료될 때까지 대기
        }
    }

    return 0;
}

// 파이프로부터 스도쿠 퍼즐 읽기
void read_sudoku_from_pipe(int pipe_fd[2], int sudoku[9][9]) {
    FILE *stream = fdopen(pipe_fd[0], "r");
    if (stream == NULL) {
        perror("fdopen");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fscanf(stream, "%d", &sudoku[i][j]);
        }
    }
    fclose(stream);
}

void play_sudoku(int sudoku[9][9]) {
    int user_sudoku[9][9];

    // 초기 퍼즐 상태 복사
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            user_sudoku[i][j] = sudoku[i][j];
        }
    }

    // 사용자 입력 받기
    printf("좌표에 알맞은 숫자를 채워넣어보세요.\n");
    printf(". 으로 표시되어 있는 곳에 숫자를 채워넣으면 됩니다!\n");

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (user_sudoku[i][j] == 0) {
                printf("이 좌표의 숫자는? (%d, %d): ", i + 1, j + 1);
                scanf("%d", &user_sudoku[i][j]);
            }
        }
    }

    // 정답인지 아닌지 확인
    int correct = 1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (user_sudoku[i][j] != sudoku[i][j]) {
                correct = 0;
                break;
            }
        }
        if (!correct) break;
    }

    if (correct) {
        printf("정답입니다! 축하드립니다!\n");
    } else {
        printf("어디선가 잘못 된 것 같네요...다시 풀어보시겠어요?\n");
    }
}