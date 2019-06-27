/**
@file      project_telegraphic_translator.c
@brief     ����߰�� �����\n
		<�߰�Ⱑ Ŀ������ ���ϴ� ���� �����ΰ�?>
@author    Minseon Shin(20161430,�Źμ�)
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
	@return �Լ� ���� ���� ����
*/

int main(void)
{
	fp = fopen("sample_input.txt", "r");
	if (fp == NULL) {
		printf("file open error\n");
		return -1;
	}
	int NumberOfTrial;   ///< NumberOfTrial : ����Ƚ��
	char tel_ar[106][106] = { 0, };   ///< ����߰�� ���� �迭(telegraphic translator_array), ũ��� 100x100 + ����߰�� �������� -3 ~ +3

	fscanf(fp, "\n%d", &NumberOfTrial);
	
	if (NumberOfTrial < 1) {			///< �Է¹��� Ƚ���� 0 �����ϋ� ERROR �޼��� ���.
		printf("ERROR : number of trial is lower than 1. Please check.\n");
		return -1;
	}

	Translator_as_trial(tel_ar, NumberOfTrial);
	
	fclose(fp);
	return 0;
}

/**
	@brief ��� �� �߰�⸦ ã�� Ŀ���ϴ� ���� Ŀ�� ���ϴ� ���� ã�� Ŀ�����ϴ� ���� ���� ��Ÿ��.
	@param ar[106][106]: �߰�⸦ �˻��� ���
	@param ROW : �˻��� ����� ���� ��
	@param COL : �˻��� ����� ���� ��
	@return �߰�Ⱑ Ŀ�� ���� ���ϴ� ���� ��
*/
int count_missing_house(char ar[106][106], int ROW, int COL)
{
	int missing_house = 0;		///< missing_house : �߰�Ⱑ ���� ���ϴ� ���� ��

	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++) {
			if (*(*(ar + i) + j) == 'A') {         ///< tel_ar[i][j] == 'A'�϶� 
				*(*(ar + i) + j) = 'X';				///< �ڱ��ڽ��� ���� 'X'�� �ٲٰ�
				for (int l = i - 3; l <= i + 3; l++) {      ///< ���� ���� +3, �Ʒ��� -3 ��ŭ X�� �ٲ�
					if (*(*(ar + l) + j) == 'A' || *(*(ar + l) + j) == 'B' || *(*(ar + l) + j) == 'C') break;   ///< �� 'A''B''C'�� ������� PASS
					else *(*(ar + l) + j) = 'X';
				}
				for (int m = j - 3; m <= j + 3; m++) {      ///< ���� ���� +3, �Ʒ��� -3 ��ŭ X�� �ٲ�
					if (*(*(ar + i) + m) == 'A' || *(*(ar + i) + m) == 'B' || *(*(ar + i) + m) == 'C') break;    ///< �� 'A''B''C'�� ������� PASS
					else *(*(ar + i) + m) = 'X';
				}
			}
			if (*(*(ar + i) + j) == 'B') {         ///< tel_ar[i][j] == 'B'�϶� 
				*(*(ar + i) + j) = 'X';			///< �ڱ��ڽ��� ���� 'X'�� �ٲٰ�
				for (int l = i - 2; l <= i + 2; l++) {  ///< ���� ���� +2, �Ʒ��� -2 ��ŭ X�� �ٲ�
					if (*(*(ar + l) + j) == 'A' || *(*(ar + l) + j) == 'B' || *(*(ar + l) + j) == 'C') break;    ///< �� 'A''B''C'�� ������� PASS
					else *(*(ar + l) + j) = 'X';
				}
				for (int m = j - 2; m <= j + 2; m++) {   ///< ���� ���� +2, �Ʒ��� -2 ��ŭ X�� �ٲ�
					if (*(*(ar + i) + m) == 'A' || *(*(ar + i) + m) == 'B' || *(*(ar + i) + m) == 'C') break;    ///< �� 'A''B''C'�� ������� PASS
					else *(*(ar + i) + m) = 'X';
				}
			}
			if (*(*(ar + i) + j) == 'C') {         ///< tel_ar[i][j] == 'C'�϶� 
				*(*(ar + i) + j) = 'X';				///< �ڱ��ڽ��� ���� 'X'�� �ٲٰ�
				for (int l = i - 1; l <= i + 1; l++) {   ///< ���� ���� +1, �Ʒ��� -1 ��ŭ X�� �ٲ�
					if (*(*(ar + l) + j) == 'A' || *(*(ar + l) + j) == 'B' || *(*(ar + l) + j) == 'C') break;   ///< �� 'A''B''C'�� ������� PASS
					else *(*(ar + l) + j) = 'X';
				}
				for (int m = j - 1; m <= j + 1; m++) {   ///< ���� ���� +1, �Ʒ��� -1 ��ŭ X�� �ٲ�
					if (*(*(ar + i) + m) == 'A' || *(*(ar + i) + m) == 'B' || *(*(ar + i) + m) == 'C') break;    ///< �� 'A''B''C'�� ������� PASS
					else *(*(ar + i) + m) = 'X';
				}
			}
		}
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			if (ar[i][j] == 'H')      ///< ��ü ����� ������ 'H'�� ������ +1
				missing_house++;

	return missing_house;
}
/**
	@brief	����߰�Ⱑ Ŀ������ ���ϴ� ���� ���� ���
	@param ar[106][106] : �߰�⸦ �˻��� ���
	@param ROW :	�˻��� ����� ���� ��
	@param COL :	�˻��� ����� ���� ��
	@return			�߰�Ⱑ Ŀ�� ���� ���ϴ� ���� ���� ����ϴ� �Լ�
*/
int print_missing_house_array(char ar[106][106], int ROW, int COL)
{
	int k = 0;	///< Translator_as_trial �� trial ���� ������.
	int house[10] = { 0, };
	house[k] = 0;   ///< ��� �ȵ� �� �迭 �ʱ�ȭ.
	house[k] = count_missing_house(ar, ROW, COL);

	return printf("%d\n", house[k]);   ///< ��� �ȵ� ���� �� ���

}
/**
@brief		����õ���ŭ ��İ˻縦 ���� �߰�� Ŀ�� ���ϴ� ���� ���� ���.
@param		ar[106][106] : �߰�⸦ �˻��� ���
@param		trial : �˻��� ����� ����Ƚ��
@return		�߰�Ⱑ Ŀ�� ���� ���ϴ� ���� �� ����ϴ� �Լ�
*/
int Translator_as_trial(char ar[106][106], int trial)
{
	int ROW, COL;
	for (int k = 0; k < trial; k++) {   ///<  k�� ����Ƚ����ŭ �ݺ�.

		fscanf(fp, "\n%d", &ROW);      ///< ���Ͽ��� �� �ҷ���.
		fscanf(fp, "\n%d", &COL);      ///< ���Ͽ��� �� �ҷ���.

		if (ROW < 1 || COL < 1) {		///< ��� ���� �� �� 0���Ϸ� �޾Ƶ������ �����޼��� ���.
			printf("ERROR : Row or column is lower than 1. please check.");
			return -1;
		}

		for (int i = 0; i < ROW; i++)
			for (int j = 0; j < COL; j++)
				fscanf(fp, "\n%c", &ar[i][j]);      ///< ���Ͽ��� ��� �ҷ���.

		print_missing_house_array(ar, ROW, COL, k);
	}
}