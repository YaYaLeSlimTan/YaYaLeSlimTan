#pragma once

#define WIN_WIDTH 80	//控制台窗口宽度

#define WIN_HEIGHT 25	//控制台窗口高度

#define TABLE_WIDTH 78	//信息列表的宽度

#define MENU_WIDTH  50	//菜单宽度

#define COL_LEN_MAX 64	//每列最大宽度

#define MAX_COUNT 100	//最大学生数

#define RECORDER_PER_PAGE 10	//信息列表每页最多几行

void printTableHead(int tableWidth);
void printTableTail(int tableWidth);
void printTableRow(int tableWidth, char cols[][COL_LEN_MAX], int n);
void printTableHead(int tableWidth, int cols);
void printTableTail(int tableWidth, int cols);
void printTableMidLine(int tableWidth, int cols);
void printTableMidInfo(int tableWidth, const char* str);
void printMidInfo(const char* str);