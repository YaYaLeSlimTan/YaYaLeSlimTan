#include <stdio.h>
#include <string.h>
#include "tablePrint.h"

void printTableHead(int tableWidth) {//50
	int margin = (WIN_WIDTH - tableWidth) / 2;//����80��ͷ50
	for (int i = 0; i < margin; i++) printf(" ");//0-14����ո�
	printf("��");
	for (int i = 0; i < tableWidth - 2; i++)printf("��");
	printf("��\n"); 
}



void printTableTail(int tableWidth) {//50
	int margin = (WIN_WIDTH - tableWidth) / 2;//������Ե
	for (int i = 0; i < margin; i++) printf(" ");//���Ե0-14
	printf("��");//15
	for (int i = 0; i < tableWidth - 2; i++)printf("��");//�����16-64
	printf("��\n");//65
}

//��ӡ��
void printTableRow(int tableWidth, char cols[][COL_LEN_MAX], int n) {
	int margin = (WIN_WIDTH - tableWidth) / 2;
	for (int i = 0; i < margin; i++) printf(" ");

	int colWidth = (tableWidth - (n + 1)) / n;

	for (int i = 0; i < n; i++) {//��ӡÿһ�У��м��п���
		printf("��");

		int leftSpan = (colWidth - strlen(cols[i])) / 2;
		int rightSpan = colWidth - leftSpan - strlen(cols[i]);

		for (int j = 0; j < leftSpan; j++) printf(" ");
		printf("%s", cols[i]);
		for (int j = 0; j < rightSpan; j++) printf(" ");
	}

	printf("��\n");
}


void printTableHead(int tableWidth, int cols) {//78
	int margin = (WIN_WIDTH - tableWidth) / 2;
	int spanLen = (tableWidth - (cols + 1)) / cols;
	for (int i = 0; i < margin; i++) printf(" ");

	printf("��");
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < spanLen; j++) {
			printf("��");
		}

		if (i < cols - 1) {
			printf("��");
		}
		else {
			printf("��");
		}
	}
	printf("\n");
}

void printTableTail(int tableWidth, int cols) {
	int margin = (WIN_WIDTH - tableWidth) / 2;
	int spanLen = (tableWidth - (cols + 1)) / cols;
	for (int i = 0; i < margin; i++) printf(" ");

	//�����ة���
	printf("��");
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < spanLen; j++) {
			printf("��");
		}

		if (i < cols - 1) {
			printf("��");
		}
		else {
			printf("��");
		}
	}
	printf("\n");
}

void printTableMidLine(int tableWidth, int cols) {
	int margin = (WIN_WIDTH - tableWidth) / 2;
	int spanLen = (tableWidth - (cols + 1)) / cols;
	for (int i = 0; i < margin; i++) printf(" ");

	printf("��");
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < spanLen; j++) {
			printf("��");
		}

		if (i < cols - 1) {
			printf("��");
		}
		else {
			printf("��");
		}
	}
	printf("\n");
}


void printTableMidInfo(int tableWidth, const char* str) {//50 �ַ�������
	int margin = (WIN_WIDTH - tableWidth) / 2;//15
	for (int i = 0; i < margin; i++) printf(" ");//0-14
	printf("��");

	int len1 = (tableWidth - 2 - strlen(str)) / 2;//��ͷ���ַ������Ե����
	for (int i = 0; i < len1; i++) printf(" ");//�ַ������Եȫ����Ϊ" "

	printf("%s", str);

	int len2 = tableWidth - 2 - len1 - strlen(str);//��ͷ���ַ����ұ�Ե�հײ���
	for (int i = 0; i < len2; i++) printf(" ");//�ַ����ұ�Ե

	printf("��\n");//
}

void printMidInfo(const char* str) {//����̨���ھ�������ַ���
	int margin = (WIN_WIDTH - strlen(str)) / 2;	//��80-�ַ������ȣ��õ�����Ե����
	for (int i = 0; i < margin; i++) printf(" ");//�ַ������ȫ����Ϊ" "
	printf("%s", str); //��ӡ�ַ���
}