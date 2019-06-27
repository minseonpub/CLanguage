/**
@file	Communication_repeater.c
@brief	프로그래밍 기초 및 실습 통신중계기 과제
@author	ChangWu Byeon(camelcriket@gmail.com)
@date	2016-11-26	12:20:00
*/
#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 100
///> MAX 최대 행,열의 개수

void read_file();
void write_file();
void check(char(*repeater)[MAX + 1], int cnt, int* hcnt, int row, int column);
int search(char(*repeater)[MAX + 1], int row, int column);

/**
	@brief	main function
	@param	void
	@return	함수 정상 실행 여부
*/
int main()
{
	int input = 0, stop = 0;

	printf("* Communication repeater *\n");

	while (stop == 0)
	{
		printf("1 . 파일 읽기\n2 . 파일 쓰기(WIP)\n3. 종료\nEnter : ");
		scanf_s("%d", &input);

		switch (input)
		{
		case(1):read_file();
			break;
		case(2):write_file();
			break;
		case(3):printf("프로그램을 종료합니다.\n");
			stop = 1;
			break;
		default:printf("다른 값을 입력하셨습니다. 다시 입력하세요.\n");
			continue;
		}
	}
	return 0;
}

/**
	@brief	파일 읽기, 변수에 저장
	@param	void
	@return	함수 정상 실행 여부
	@todo	파일 이름 입력 시 정상적인 입력 여부 그리고 마지막 리셋 시 모든 값이 -1로 고정.
*/
void read_file()
{
	///> testcase 통신중계기 종류의 수
	///> row 행의 개수
	///> column 열의 개수
	///> result[MAX] 최종 결과 저장
	///> fname[31] 파일 이름 저장
	///> repeater[MAX+1][MAX+1] 통신중계기 좌표 저장
	///> error[MAX] 에러 발생 여부 저장
	///> fp 파일의 주소 저장
	int testcase = 0, row = 0, column = 0, result[MAX] = { 0 };
	char fname[31] = { 0 }, repeater[MAX + 1][MAX + 1] = { 0 }, error[MAX] = { 0 };
	FILE* fp = NULL;

	printf("파일의 이름을 입력하세요.\nEnter (30): ");
	scanf_s("%s", fname, sizeof(fname));
	while (getchar() != '\n');

	fp = fopen(fname, "r");

	if (fp == NULL)
	{
		printf("파일을 읽는데 실패하였습니다.\n");
		return -1;
	}

	fscanf(fp, "%d", &testcase);

	for (int i = 0; i < testcase; i++)
	{
		fscanf(fp, "%d%d", &row, &column);
		if ((row <= 0 || row > MAX) || (column <= 0 || column > MAX))
		{
			printf("%d번째 통신중계기의 행이나 열이 허용범위(1~%d)에 포함되지 않습니다!\n", i + 1, MAX);
			error[i] = 1;
			continue;
		}

		printf("* %d번째 통신 중계기 *\n%d행\t%d열\n", i + 1, row, column);

		for (int x = 0; x < row; x++)
		{
			if (isdigit(repeater[x][0]))
			{
				printf("행의 길이가 맞지 않습니다!\n");
				error[i] = 1;
				break;
			}

			fscanf(fp, "%s", &repeater[x][0]);

			if (repeater[x][column] != '\0')
			{
				printf("열의 길이가 맞지 않습니다!\n");
				error[i] = 1;
				break;
			}

			for (int y = 0; y < column; y++) putch(repeater[x][y]);
			printf("\n");
		}

		if (error[i] == 0) result[i] = search(repeater, row, column);
		if (result[i] == -1) error[i] = 1;

		memset(repeater, 0, sizeof(repeater));
	}
	
	for (int i = 0; i < testcase; i++)
	{
		if (error[i] != 0) continue;
		Sleep(500);
		printf("%d번째 통신중계기는 집 %d개가 중계기로부터 영향을 받지 못합니다.\n", i + 1, result[i]);
	}

	return;
}

/**
	@brief	새로운 통신중계기 파일 생성
	@return	함수 정상 실행 여부
	@todo	파일 제작 구현
*/
void write_file()
{
	printf("Work In Progress.\n");

	return 0;
}

/**
	@brief	입력된 통신 중계기 좌표 스캔
	@param	(*repeater)[MAX+1] 통신 중계기 좌표의 주소
	@param	row 통신 중계기 행의 수
	@param	column 통신 중계기 열의 수
	@return	통신 중계기로부터 영향을 받지 못하는 집의 개수. 오류 시 -1 반환
	@todo	-
*/
int search(char (*repeater)[MAX + 1],int row, int column)
{
	///> hcnt 통신중계기의 영향을 받지 않은 집의 개수
	int hcnt = 0;
	
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			switch (repeater[x][y])
			{
			case('H'):hcnt += 1;
				break;
			case('A'):check(repeater, 3, &hcnt, x, y);
				break;
			case('B'):check(repeater, 2, &hcnt, x, y);
				break;
			case('C'):check(repeater, 1, &hcnt, x, y);
				break;
			case('X'):
				break;
			default:
				printf("X, H, A, B, C 가 아닌 다른 입력값이 포함되어 있습니다!\n");
				return -1;
			}
		}
	}

	return hcnt;
}

/**
	@brief	지정 범위만큼 H를 스캔하여 제거
	@param	(*repeater)[MAX+1] 통신 중계기의 좌표의 주소
	@param	cnt 스캔 범위
	@param	hcnt 통신중계기의 영향을 받지 않은 집의 개수의 좌표
	@param	row 통신 중계기의 스캔된 행의 값
	@param	column 통신 중계기의 스캔된 열의 값
	@return	함수 정상 실행 여부
	@todo	문장의 간소화 및 정리
*/
void check(char (*repeater)[MAX + 1],int cnt,int* hcnt,int row,int column)
{
	for (int i = 1; i <= cnt; i++)
	{
		if (row - i < 0) break;
		if (repeater[row - i][column] == 'H')
		{
			repeater[row - i][column] = 'X';
			--*hcnt;
		}
	}
	for (int i = 1; i <= cnt; i++)
	{
		if (column - i < 0) break;
		if (repeater[row][column - i] == 'H')
		{
			repeater[row][column - i] = 'X';
			--*hcnt;
		}
	}
	for (int i = 1; i <= cnt; i++)
	{
		if (row != MAX && repeater[row + i][column] == 'H')
		{
			repeater[row + i][column] = 'X';
		}
		if (row + i >= MAX || repeater[row + i + 1][column] == 0) break;
	}
	for (int i = 1; i <= cnt; i++)
	{
		if (column != MAX && repeater[row][column + i] == 'H')
		{
			repeater[row][column + i] = 'X';
		}
		if (column + i >= MAX || repeater[row][column + i + 1] == 0) break;
	}

	return;
}
