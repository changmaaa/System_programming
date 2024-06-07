# Sudoku Puzzle Generator
Youtube Link : https://youtu.be/vEd6tEZr3c0


## Description
이 프로그램은 시스템 프로그래밍에서 배운 기법들을 사용하여 스도쿠 퍼즐을 생성하고 표시합니다. 파일 입/출력, 프로세스 생성, 파이프를 이용한 프로세스 간 통신(IPC), 그리고 `exec` 함수군의 사용을 시연합니다.

## Files
- `sudoku.c`: 프로세스 생성 및 IPC를 처리하는 메인 프로그램 파일.
- `generate.c`: 스도쿠 퍼즐을 생성하는 로직이 포함된 파일.
- `display.c`: 생성된 스도쿠 퍼즐을 파일로부터 읽어와서 표시하는 파일.
- `validate.c`: 생성된 스도쿠 퍼즐이 올바르게 생성되었는지 확인하는 파일.
- `Makefile`: 프로그램 빌드를 위한 명령어 모음.

## Build Instructions
```bash
make
