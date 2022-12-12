#pragma once

#define WIN_WIDTH 80	//����̨���ڿ��

#define WIN_HEIGHT 25	//����̨���ڸ߶�

#define TABLE_WIDTH 78	//��Ϣ�б�Ŀ��

#define MENU_WIDTH  50	//�˵����

#define COL_LEN_MAX 64	//ÿ�������

#define MAX_COUNT 100	//���ѧ����

#define RECORDER_PER_PAGE 10	//��Ϣ�б�ÿҳ��༸��

void printTableHead(int tableWidth);
void printTableTail(int tableWidth);
void printTableRow(int tableWidth, char cols[][COL_LEN_MAX], int n);
void printTableHead(int tableWidth, int cols);
void printTableTail(int tableWidth, int cols);
void printTableMidLine(int tableWidth, int cols);
void printTableMidInfo(int tableWidth, const char* str);
void printMidInfo(const char* str);