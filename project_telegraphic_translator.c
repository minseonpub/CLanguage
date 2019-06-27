/**
@file      project_telegraphic_translator.c
@brief     통신중계기 만들기\n
		<중계기가 커버하지 못하는 집은 몇집인가?>
@author    Minseon Shin(20161430,신민선)
@date      2016-11-28
*/

#include <stdio.h>
int count_missing_house(char ar[106][106], int ROW, int COL);
int print_missing_house_array(char ar[106][106], int ROW, int COL);
int Translator_as_trial(char ar[106][106], int trial);

FILE *fp = NULL;		///< fp variable

/**
	@brief	main function
	@param	void
	@return 함수 실행 정상 여부
*/

int main(void)
{
	fp = fopen("sample_input.txt", "r");
	if (fp == NULL) {
		printf("file open error\n");
		return -1;
	}
	int NumberOfTrial;   ///< NumberOfTrial : 시행횟수
	char tel_ar[106][106] = { 0, };   ///< 통신중계기 받을 배열(telegraphic translator_array), 크기는 100x100 + 통신중계기 오차범위 -3 ~ +3

	fscanf(fp, "\n%d", &NumberOfTrial);
	
	if (NumberOfTrial < 1) {			///< 입력받은 횟수가 0 이하일떄 ERROR 메세지 출력.
		printf("ERROR : number of trial is lower than 1. Please check.\n");
		return -1;
	}

	Translator_as_trial(tel_ar, NumberOfTrial);
	
	fclose(fp);
	return 0;
}

/**
	@brief 행렬 속 중계기를 찾아 커버하는 집과 커버 못하는 집을 찾고 커버못하는 집의 수를 나타냄.
	@param ar[106][106]: 중계기를 검사할 행렬
	@param ROW : 검사할 행렬의 행의 수
	@param COL : 검사할 행렬의 열의 수
	@return 중계기가 커버 하지 못하는 집의 수
*/
int count_missing_house(char ar[106][106], int ROW, int COL)
{
	int missing_house = 0;		///< missing_house : 중계기가 닿지 못하는 집의 수

	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++) {
			if (*(*(ar + i) + j) == 'A') {         ///< tel_ar[i][j] == 'A'일때 
				*(*(ar + i) + j) = 'X';				///< 자기자신은 먼저 'X'로 바꾸고
				for (int l = i - 3; l <= i + 3; l++) {      ///< 행이 위로 +3, 아래로 -3 만큼 X로 바꿈
					if (*(*(ar + l) + j) == 'A' || *(*(ar + l) + j) == 'B' || *(*(ar + l) + j) == 'C') break;   ///< 단 'A''B''C'가 있을경우 PASS
					else *(*(ar + l) + j) = 'X';
				}
				for (int m = j - 3; m <= j + 3; m++) {      ///< 열이 위로 +3, 아래로 -3 만큼 X로 바꿈
					if (*(*(ar + i) + m) == 'A' || *(*(ar + i) + m) == 'B' || *(*(ar + i) + m) == 'C') break;    ///< 단 'A''B''C'가 있을경우 PASS
					else *(*(ar + i) + m) = 'X';
				}
			}
			if (*(*(ar + i) + j) == 'B') {         ///< tel_ar[i][j] == 'B'일때 
				*(*(ar + i) + j) = 'X';			///< 자기자신은 먼저 'X'로 바꾸고
				for (int l = i - 2; l <= i + 2; l++) {  ///< 행이 위로 +2, 아래로 -2 만큼 X로 바꿈
					if (*(*(ar + l) + j) == 'A' || *(*(ar + l) + j) == 'B' || *(*(ar + l) + j) == 'C') break;    ///< 단 'A''B''C'가 있을경우 PASS
					else *(*(ar + l) + j) = 'X';
				}
				for (int m = j - 2; m <= j + 2; m++) {   ///< 열이 위로 +2, 아래로 -2 만큼 X로 바꿈
					if (*(*(ar + i) + m) == 'A' || *(*(ar + i) + m) == 'B' || *(*(ar + i) + m) == 'C') break;    ///< 단 'A''B''C'가 있을경우 PASS
					else *(*(ar + i) + m) = 'X';
				}
			}
			if (*(*(ar + i) + j) == 'C') {         ///< tel_ar[i][j] == 'C'일때 
				*(*(ar + i) + j) = 'X';				///< 자기자신은 먼저 'X'로 바꾸고
				for (int l = i - 1; l <= i + 1; l++) {   ///< 행이 위로 +1, 아래로 -1 만큼 X로 바꿈
					if (*(*(ar + l) + j) == 'A' || *(*(ar + l) + j) == 'B' || *(*(ar + l) + j) == 'C') break;   ///< 단 'A''B''C'가 있을경우 PASS
					else *(*(ar + l) + j) = 'X';
				}
				for (int m = j - 1; m <= j + 1; m++) {   ///< 열이 위로 +1, 아래로 -1 만큼 X로 바꿈
					if (*(*(ar + i) + m) == 'A' || *(*(ar + i) + m) == 'B' || *(*(ar + i) + m) == 'C') break;    ///< 단 'A''B''C'가 있을경우 PASS
					else *(*(ar + i) + m) = 'X';
				}
			}
		}
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			if (ar[i][j] == 'H')      ///< 전체 행렬을 돌려서 'H'가 있으면 +1
				missing_house++;

	return missing_house;
}
/**
	@brief	통신중계기가 커버하지 못하는 집의 수를 출력
	@param ar[106][106] : 중계기를 검사할 행렬
	@param ROW :	검사할 행렬의 행의 수
	@param COL :	검사할 행렬의 열의 수
	@return			중계기가 커버 하지 못하는 집의 수를 출력하는 함수
*/
int print_missing_house_array(char ar[106][106], int ROW, int COL)
{
	int k = 0;	///< Translator_as_trial 의 trial 변수 연결자.
	int house[10] = { 0, };
	house[k] = 0;   ///< 배당 안된 집 배열 초기화.
	house[k] = count_missing_house(ar, ROW, COL);

	return printf("%d\n", house[k]);   ///< 배당 안된 집의 수 출력

}
/**
@brief		시행시도만큼 행렬검사를 돌려 중계기 커버 못하는 집의 수를 출력.
@param		ar[106][106] : 중계기를 검사할 행렬
@param		trial : 검사할 행렬의 시행횟수
@return		중계기가 커버 하지 못하는 집의 수 출력하는 함수
*/
int Translator_as_trial(char ar[106][106], int trial)
{
	int ROW, COL;
	for (int k = 0; k < trial; k++) {   ///<  k가 시행횟수만큼 반복.

		fscanf(fp, "\n%d", &ROW);      ///< 파일에서 행 불러옴.
		fscanf(fp, "\n%d", &COL);      ///< 파일에서 열 불러옴.

		if (ROW < 1 || COL < 1) {		///< 행과 열의 수 가 0이하로 받아드렸을때 에러메세지 출력.
			printf("ERROR : Row or column is lower than 1. please check.");
			return -1;
		}

		for (int i = 0; i < ROW; i++)
			for (int j = 0; j < COL; j++)
				fscanf(fp, "\n%c", &ar[i][j]);      ///< 파일에서 행렬 불러옴.

		print_missing_house_array(ar, ROW, COL, k);
	}
}