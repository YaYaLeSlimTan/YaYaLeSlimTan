#include <stdio.h>
#include <string.h>
#include "tablePrint.h"

void printTableHead(int tableWidth) {//50
	int margin = (WIN_WIDTH - tableWidth) / 2;//窗口80表头50
	for (int i = 0; i < margin; i++) printf(" ");//0-14输出空格
	printf("┌");
	for (int i = 0; i < tableWidth - 2; i++)printf("─");
	printf("┐\n"); 
}



void printTableTail(int tableWidth) {//50
	int margin = (WIN_WIDTH - tableWidth) / 2;//表格左边缘
	for (int i = 0; i < margin; i++) printf(" ");//左边缘0-14
	printf("└");//15
	for (int i = 0; i < tableWidth - 2; i++)printf("─");//表格中16-64
	printf("┘\n");//65
}

//打印行
void printTableRow(int tableWidth, char cols[][COL_LEN_MAX], int n) {
	int margin = (WIN_WIDTH - tableWidth) / 2;
	for (int i = 0; i < margin; i++) printf(" ");

	int colWidth = (tableWidth - (n + 1)) / n;

	for (int i = 0; i < n; i++) {//打印每一列，中间有空行
		printf("│");

		int leftSpan = (colWidth - strlen(cols[i])) / 2;
		int rightSpan = colWidth - leftSpan - strlen(cols[i]);

		for (int j = 0; j < leftSpan; j++) printf(" ");
		printf("%s", cols[i]);
		for (int j = 0; j < rightSpan; j++) printf(" ");
	}

	printf("│\n");
}


void printTableHead(int tableWidth, int cols) {//78
	int margin = (WIN_WIDTH - tableWidth) / 2;
	int spanLen = (tableWidth - (cols + 1)) / cols;
	for (int i = 0; i < margin; i++) printf(" ");

	printf("┌");
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < spanLen; j++) {
			printf("─");
		}

		if (i < cols - 1) {
			printf("┬");
		}
		else {
			printf("┐");
		}
	}
	printf("\n");
}

void printTableTail(int tableWidth, int cols) {
	int margin = (WIN_WIDTH - tableWidth) / 2;
	int spanLen = (tableWidth - (cols + 1)) / cols;
	for (int i = 0; i < margin; i++) printf(" ");

	//└─┴─┘
	printf("└");
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < spanLen; j++) {
			printf("─");
		}

		if (i < cols - 1) {
			printf("┴");
		}
		else {
			printf("┘");
		}
	}
	printf("\n");
}

void printTableMidLine(int tableWidth, int cols) {
	int margin = (WIN_WIDTH - tableWidth) / 2;
	int spanLen = (tableWidth - (cols + 1)) / cols;
	for (int i = 0; i < margin; i++) printf(" ");

	printf("├");
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < spanLen; j++) {
			printf("─");
		}

		if (i < cols - 1) {
			printf("┼");
		}
		else {
			printf("┤");
		}
	}
	printf("\n");
}


void printTableMidInfo(int tableWidth, const char* str) {//50 字符串常量
	int margin = (WIN_WIDTH - tableWidth) / 2;//15
	for (int i = 0; i < margin; i++) printf(" ");//0-14
	printf("│");

	int len1 = (tableWidth - 2 - strlen(str)) / 2;//表头内字符串左边缘长度
	for (int i = 0; i < len1; i++) printf(" ");//字符串左边缘全部置为" "

	printf("%s", str);

	int len2 = tableWidth - 2 - len1 - strlen(str);//表头内字符串右边缘空白部分
	for (int i = 0; i < len2; i++) printf(" ");//字符串右边缘

	printf("│\n");//
}

void printMidInfo(const char* str) {//控制台窗口居中输出字符串
	int margin = (WIN_WIDTH - strlen(str)) / 2;	//（80-字符串长度）得到单边缘长度
	for (int i = 0; i < margin; i++) printf(" ");//字符串左边全都置为" "
	printf("%s", str); //打印字符串
}