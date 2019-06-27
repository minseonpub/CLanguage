/**
	@file	TeleRepeater.c
	@brief	통신중계기 과제 \n
			중계기가 커버하지 못하는 집은 몇 집인가? \n
			중계기 종류 : 
			A급 중계기(상하좌우 3칸씩 커버)\n
			B급 중계기(상하좌우 2칸씩 커버)\n
			C급 중계기(상하좌우 1칸씩 커버)\n
			H: 집\n
			X: 없음\n
			최대 가로 세로 길이는 100
	@author	Kim Beomhee(nakaldi@gmail.com)
	@date	2016-11-22
*/

#include <stdio.h>
///> arr 배열 선언시 행 최대값 
#define ROW_SIZE 100	
///> arr 배열 선언시 열 최대값
#define COL_SIZE 100	
///> 테스트케이스 최대값(최대 반복횟수)
#define MAXIMUM_TESTCASE 10	
///> A급 중계기의 커버 범위
#define COVER_AREA_OF_A 3 
///> B급 중계기의 커버 범위
#define COVER_AREA_OF_B 2 
///> C급 중계기의 커버 범위, 이하 유지 보수를 위해 정의하였음
#define COVER_AREA_OF_C 1 

///>전역 변수 row를 0으로 초기화, 행의 크기로 사용
int row = 0;
///>전역 변수 col를 0으로 초기화, 열의 크기로 사용
int col = 0;
///>전역 변수 temp를 0으로 초기화, 임시 변수로 excludeNewline()에서 사용
int temp = 0;
///>전역 변수 testCase를 0으로 초기화, 테스트케이스 반복횟수로 사용
int testCase = 0;

int fileExceptionHandling(int x);

int scanTestCase(int x);

int scanRowColArr(char(*a)[COL_SIZE], int x);

char excludeNewline(int x);

int applyAlgorithm(char(*a)[COL_SIZE]);

int changeHToX(char(*a)[COL_SIZE], int i, int j, int k);

int printResult(char(*a)[COL_SIZE]);


/**
	@brief		메인 함수
	@exception	fileExceptionHandling() 함수에서 1을 반환할 경우 비정상 종료
	@param		void
	@remark		파일을 불러와 예외처리, 100*100 2차원 배열을 선언, scanTestCase()로 테스트케이스를 입력받아 다음을 그 만큼 반복함.\n
				scanRowColArr(), applyAlgorithm(), printResult()
	@return		함수 실행 정상 여부
*/
int main(void) {
	///> FILE을 가리키는 포인터 fp 선언
	FILE* fp;
	fp = fopen("sample_input.txt", "r");
	if( fileExceptionHandling(fp) ) return -1;

	///>100행 100열의 지역변수 배열arr를 0으로 초기화
	char arr[ROW_SIZE][COL_SIZE] = { 0, };
	
	scanTestCase(fp);

	// 테스트 케이스 0이 아닐때 반복, 한번 할때마다 1 감소
	while (testCase != 0) {
		testCase -= 1;


		scanRowColArr(arr, fp);
		

		applyAlgorithm(arr);
		

		printResult(arr);
		}
	
	fclose(fp);

	return 0;
}



/**
	@brief		파일 예외 처리 함수
	@param		x 인수 파일의 주소인 fp를 받음
	@remark		fp를 받은 인수 x가 비어 있을 때 오류 메시지와 함께 1을 반환, 상위 함수인 main()함수에서는 비정상 종료함
	@return		함수 실행 정상 여부
*/
int fileExceptionHandling(int x) {
	if (x == NULL) {
		printf("fopen errer : check that \"sample_input.txt\" exists in current folder");
		return 1;
	}
	else return 0;
}



/**
	@brief		테스트케이스를 스캔하고 최대 반복횟수를 설정하는 함수
	@param		x 인수 파일의 주소인 fp를 받음
	@remark		테스트케이스를 스캔하여 MAXIMUM_TESTCASE 보다 크면 테스트 케이스의 값을 MAXIMUM_TESTCASE 로 설정함
	@return		함수 실행 정상 여부
*/
int scanTestCase(int x) {
	fscanf(x, "%d", &testCase);
	if (testCase > MAXIMUM_TESTCASE) testCase = MAXIMUM_TESTCASE;
	return 0;
}



/**
	@brief		행과 열의 크기 스캔하고, 행렬의 값을 스캔하여 배열에 대입하는 함수
	@param		a 인수 2차원 배열인 arr를 받음
	@param		x 인수 파일의 주소인 fp를 받음
	@remark		행과 열 크기대로 파일에서 스캔, 개행을 제외하는 함수 excludeNewline()를 사용하여 정상값만 배열에 대입함
	@return		함수 실행 정상 여부
*/
int scanRowColArr(char(*a)[COL_SIZE], int x) {
	fscanf(x, "%d", &row);
	fscanf(x, "%d", &col);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			a[i][j] = excludeNewline(x);
		}
	}
	return 0;
}



/**
	@brief		행렬의 값을 스캔하고 개행을 제외하고 반환하는 함수
	@exception	스캔한 값이 개행문자일 때 excludeNewline() 함수를 호출함
	@param		x 인수 파일의 주소인 fp를 받음
	@remark		파일에서 행렬의 값을 스캔하여 개행문자가 아니면 반환, 개행문자면 excludeNewline()재귀함
	@return		정상 값을 temp 변수에 대입하여 반환
*/
char excludeNewline(int x) {
	fscanf(x, "%c", &temp);
	if (temp != '\n') return temp;
	else return excludeNewline(x);
}



/**
	@brief		중계기가 커버하는 집을 제외하는 알고리즘을 적용하는 함수
	@param		a 인수 2차원 배열인 arr를 받음
	@remark		printResult()함수에서 중계기의 커버 범위에 미치지 못하는 'H'의 개수를 세는데, 중계기가 커버하는 'H'를 셈에서 제외하기 위함\n
				각 행렬마다 중계기의 여부와 A|B|C 급을 검사하고 각 중계기에 따른 커버 범위 COVER_AREA_OF_* 에 따라 k의 크기를 설정하고,\n
				중계기가 커버하는 범위의 H을 X로 변화시키는 함수 changeHToX()을 부름
	@return		함수 실행 정상 여부
*/
int applyAlgorithm(char(*a)[COL_SIZE]) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (a[i][j] == 'A') {
				for (int k = 1; k <= COVER_AREA_OF_A; k++) {
					changeHToX(a, i, j, k);
				}
			}
			if (a[i][j] == 'B') {
				for (int k = 1; k <= COVER_AREA_OF_B; k++) {
					changeHToX(a, i, j, k);
				}
			}
			if (a[i][j] == 'C') {
				for (int k = 1; k <= COVER_AREA_OF_C; k++) {
					changeHToX(a, i, j, k);
				}
			}
		}
	}
	return 0;
}



/**
	@brief		중계기가 커버하는 범위의 'H'를  'X'로 바꾸는 함수
	@param		a 인수 2차원 배열인 arr를 받음
	@param		i 인수 상위 함수의 지역변수 i을 받음,\n행을 뜻하고 상위 함수 applyAlgorithm()에서 1부터 row까지 1씩 증가하며 반복함
	@param		j 인수 상위 함수의 지역변수 i을 받음,\n열을 뜻하고 상위함수에서 1부터 col까지 1씩 증가하며 반복함
	@param		k 인수 상위 함수의 지역변수 k을 받음,\n중계기가 커버하는 범위를 뜻하고 상위 함수에서 1부터 COVER_AREA_OF_*까지 1씩 증가하며 반복함
	@remark		위에서부터 순서대로 상->우->하->좌 의 시계방향 순서로 커버 범위의 크기 k 가 가감된 행렬에 있는 'H'를 'X'로 변화시킴\n
				이 함수는 상위 함수에서 여러번 반복됨
	@return		함수 실행 정상 여부
*/
int changeHToX(char(*a)[COL_SIZE], int i, int j, int k) {
	if (a[i - k][j] == 'H') a[i - k][j] = 'X';
	if (a[i][j + k] == 'H') a[i][j + k] = 'X';
	if (a[i + k][j] == 'H') a[i + k][j] = 'X';
	if (a[i][j - k] == 'H') a[i][j - k] = 'X';
	return 0;
}



/**
	@brief		중계기가 커버하지 못한 'H'의 개수를 세어 결과를 출력하는 함수
	@param		a 인수 2차원 배열인 arr를 받음
	@remark		스캔받은 행렬 크기만큼 반복하여 'H'를 확인할 때마다 result 에 1씩 추가함\n
				반복이 끝나면 총 'H'의 개수를 출력함
	@return		함수 실행 정상 여부
*/
int printResult(char(*a)[COL_SIZE]) {
	int result = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (a[i][j] == 'H') result += 1;
		}
	}
	printf("%d\n", result);
	return 0;
}