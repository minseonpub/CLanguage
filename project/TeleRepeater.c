/**
	@file	TeleRepeater.c
	@brief	����߰�� ���� \n
			�߰�Ⱑ Ŀ������ ���ϴ� ���� �� ���ΰ�? \n
			�߰�� ���� : 
			A�� �߰��(�����¿� 3ĭ�� Ŀ��)\n
			B�� �߰��(�����¿� 2ĭ�� Ŀ��)\n
			C�� �߰��(�����¿� 1ĭ�� Ŀ��)\n
			H: ��\n
			X: ����\n
			�ִ� ���� ���� ���̴� 100
	@author	Kim Beomhee(nakaldi@gmail.com)
	@date	2016-11-22
*/

#include <stdio.h>
///> arr �迭 ����� �� �ִ밪 
#define ROW_SIZE 100	
///> arr �迭 ����� �� �ִ밪
#define COL_SIZE 100	
///> �׽�Ʈ���̽� �ִ밪(�ִ� �ݺ�Ƚ��)
#define MAXIMUM_TESTCASE 10	
///> A�� �߰���� Ŀ�� ����
#define COVER_AREA_OF_A 3 
///> B�� �߰���� Ŀ�� ����
#define COVER_AREA_OF_B 2 
///> C�� �߰���� Ŀ�� ����, ���� ���� ������ ���� �����Ͽ���
#define COVER_AREA_OF_C 1 

///>���� ���� row�� 0���� �ʱ�ȭ, ���� ũ��� ���
int row = 0;
///>���� ���� col�� 0���� �ʱ�ȭ, ���� ũ��� ���
int col = 0;
///>���� ���� temp�� 0���� �ʱ�ȭ, �ӽ� ������ excludeNewline()���� ���
int temp = 0;
///>���� ���� testCase�� 0���� �ʱ�ȭ, �׽�Ʈ���̽� �ݺ�Ƚ���� ���
int testCase = 0;

int fileExceptionHandling(int x);

int scanTestCase(int x);

int scanRowColArr(char(*a)[COL_SIZE], int x);

char excludeNewline(int x);

int applyAlgorithm(char(*a)[COL_SIZE]);

int changeHToX(char(*a)[COL_SIZE], int i, int j, int k);

int printResult(char(*a)[COL_SIZE]);


/**
	@brief		���� �Լ�
	@exception	fileExceptionHandling() �Լ����� 1�� ��ȯ�� ��� ������ ����
	@param		void
	@remark		������ �ҷ��� ����ó��, 100*100 2���� �迭�� ����, scanTestCase()�� �׽�Ʈ���̽��� �Է¹޾� ������ �� ��ŭ �ݺ���.\n
				scanRowColArr(), applyAlgorithm(), printResult()
	@return		�Լ� ���� ���� ����
*/
int main(void) {
	///> FILE�� ����Ű�� ������ fp ����
	FILE* fp;
	fp = fopen("sample_input.txt", "r");
	if( fileExceptionHandling(fp) ) return -1;

	///>100�� 100���� �������� �迭arr�� 0���� �ʱ�ȭ
	char arr[ROW_SIZE][COL_SIZE] = { 0, };
	
	scanTestCase(fp);

	// �׽�Ʈ ���̽� 0�� �ƴҶ� �ݺ�, �ѹ� �Ҷ����� 1 ����
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
	@brief		���� ���� ó�� �Լ�
	@param		x �μ� ������ �ּ��� fp�� ����
	@remark		fp�� ���� �μ� x�� ��� ���� �� ���� �޽����� �Բ� 1�� ��ȯ, ���� �Լ��� main()�Լ������� ������ ������
	@return		�Լ� ���� ���� ����
*/
int fileExceptionHandling(int x) {
	if (x == NULL) {
		printf("fopen errer : check that \"sample_input.txt\" exists in current folder");
		return 1;
	}
	else return 0;
}



/**
	@brief		�׽�Ʈ���̽��� ��ĵ�ϰ� �ִ� �ݺ�Ƚ���� �����ϴ� �Լ�
	@param		x �μ� ������ �ּ��� fp�� ����
	@remark		�׽�Ʈ���̽��� ��ĵ�Ͽ� MAXIMUM_TESTCASE ���� ũ�� �׽�Ʈ ���̽��� ���� MAXIMUM_TESTCASE �� ������
	@return		�Լ� ���� ���� ����
*/
int scanTestCase(int x) {
	fscanf(x, "%d", &testCase);
	if (testCase > MAXIMUM_TESTCASE) testCase = MAXIMUM_TESTCASE;
	return 0;
}



/**
	@brief		��� ���� ũ�� ��ĵ�ϰ�, ����� ���� ��ĵ�Ͽ� �迭�� �����ϴ� �Լ�
	@param		a �μ� 2���� �迭�� arr�� ����
	@param		x �μ� ������ �ּ��� fp�� ����
	@remark		��� �� ũ���� ���Ͽ��� ��ĵ, ������ �����ϴ� �Լ� excludeNewline()�� ����Ͽ� ���󰪸� �迭�� ������
	@return		�Լ� ���� ���� ����
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
	@brief		����� ���� ��ĵ�ϰ� ������ �����ϰ� ��ȯ�ϴ� �Լ�
	@exception	��ĵ�� ���� ���๮���� �� excludeNewline() �Լ��� ȣ����
	@param		x �μ� ������ �ּ��� fp�� ����
	@remark		���Ͽ��� ����� ���� ��ĵ�Ͽ� ���๮�ڰ� �ƴϸ� ��ȯ, ���๮�ڸ� excludeNewline()�����
	@return		���� ���� temp ������ �����Ͽ� ��ȯ
*/
char excludeNewline(int x) {
	fscanf(x, "%c", &temp);
	if (temp != '\n') return temp;
	else return excludeNewline(x);
}



/**
	@brief		�߰�Ⱑ Ŀ���ϴ� ���� �����ϴ� �˰����� �����ϴ� �Լ�
	@param		a �μ� 2���� �迭�� arr�� ����
	@remark		printResult()�Լ����� �߰���� Ŀ�� ������ ��ġ�� ���ϴ� 'H'�� ������ ���µ�, �߰�Ⱑ Ŀ���ϴ� 'H'�� ������ �����ϱ� ����\n
				�� ��ĸ��� �߰���� ���ο� A|B|C ���� �˻��ϰ� �� �߰�⿡ ���� Ŀ�� ���� COVER_AREA_OF_* �� ���� k�� ũ�⸦ �����ϰ�,\n
				�߰�Ⱑ Ŀ���ϴ� ������ H�� X�� ��ȭ��Ű�� �Լ� changeHToX()�� �θ�
	@return		�Լ� ���� ���� ����
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
	@brief		�߰�Ⱑ Ŀ���ϴ� ������ 'H'��  'X'�� �ٲٴ� �Լ�
	@param		a �μ� 2���� �迭�� arr�� ����
	@param		i �μ� ���� �Լ��� �������� i�� ����,\n���� ���ϰ� ���� �Լ� applyAlgorithm()���� 1���� row���� 1�� �����ϸ� �ݺ���
	@param		j �μ� ���� �Լ��� �������� i�� ����,\n���� ���ϰ� �����Լ����� 1���� col���� 1�� �����ϸ� �ݺ���
	@param		k �μ� ���� �Լ��� �������� k�� ����,\n�߰�Ⱑ Ŀ���ϴ� ������ ���ϰ� ���� �Լ����� 1���� COVER_AREA_OF_*���� 1�� �����ϸ� �ݺ���
	@remark		���������� ������� ��->��->��->�� �� �ð���� ������ Ŀ�� ������ ũ�� k �� ������ ��Ŀ� �ִ� 'H'�� 'X'�� ��ȭ��Ŵ\n
				�� �Լ��� ���� �Լ����� ������ �ݺ���
	@return		�Լ� ���� ���� ����
*/
int changeHToX(char(*a)[COL_SIZE], int i, int j, int k) {
	if (a[i - k][j] == 'H') a[i - k][j] = 'X';
	if (a[i][j + k] == 'H') a[i][j + k] = 'X';
	if (a[i + k][j] == 'H') a[i + k][j] = 'X';
	if (a[i][j - k] == 'H') a[i][j - k] = 'X';
	return 0;
}



/**
	@brief		�߰�Ⱑ Ŀ������ ���� 'H'�� ������ ���� ����� ����ϴ� �Լ�
	@param		a �μ� 2���� �迭�� arr�� ����
	@remark		��ĵ���� ��� ũ�⸸ŭ �ݺ��Ͽ� 'H'�� Ȯ���� ������ result �� 1�� �߰���\n
				�ݺ��� ������ �� 'H'�� ������ �����
	@return		�Լ� ���� ���� ����
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