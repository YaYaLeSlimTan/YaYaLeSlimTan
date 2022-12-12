#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "tablePrint.h"


//定义单个学生成绩的结构体
typedef struct student {
	int num;//学号
	char name[20];//名字
	int CGrade;//C语言成绩
	int algorithm;//算法成绩
	int database;//数据库成绩
	int sum;//总成绩
}student;

//学生数组100个学生
student stu[MAX_COUNT];
int currentCount = 0;

//打印一个表格式的菜单
void menu()
{
	system("cls");//先把屏幕清空
	printTableHead(MENU_WIDTH);//打印表头
	printTableMidInfo(MENU_WIDTH, " ");//空出一行
	printTableMidInfo(MENU_WIDTH, "学生信息管理系统");
	printTableMidInfo(MENU_WIDTH, " ");//空出一行

	const char* subMenus[] = {
		"1. 输入学生信息",
		"2. 查找学生信息",
		"3. 删除学生信息",
		"4. 修改学生信息",
		"5. 插入学生信息",
		"6. 学生成绩排名",
		"7. 统计学生总数",
		"8. 显示所有信息",
		"0. 退出系统 "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
	};
	
	int count = sizeof(subMenus) / sizeof(subMenus[0]);	//count记录有多少个字符串
	
	for (int i = 0; i < count; i++)
	{
		printTableMidInfo(MENU_WIDTH, subMenus[i]);		//打印字符串数组1-8
	}
	
	printTableMidInfo(MENU_WIDTH, " ");		//这里表尾还没封口
	printTableTail(MENU_WIDTH);		//封口表尾
	printMidInfo("请输入0-8：");
	//printMidInfo(" ");

}

//初始化窗口大小，学生结构体
void Init()
{
	char cmd[128];  //数组128个字节
	sprintf(cmd, "mode con lines=%d cols=%d", WIN_HEIGHT, WIN_WIDTH);//高25宽80
	system(cmd);		//控制台窗口大小生效
	
	system("color 1f");//执行控制台命令改为蓝底白字

	menu();		//打印菜单

	memset(stu, 0, sizeof(stu));//将数组stu全部初始化为0
	
	//创建一个文件data.txt
	FILE* fp = fopen("data.txt", "rb");//r：只读  b：二进制编码
	if (fp == NULL) {//学生为0
		currentCount = 0;
		return;
	}
	int i = 0, ret;
	while (!feof(fp)) {		//feof返回值为1，则文件读取结束，读到空格那些的
		//一次读一个结构体，读一次，读取成功则返回值为1，否则0
		ret = fread(&stu[i], sizeof(student), 1, fp);
		if (ret)i++;	//读成功了，i++读取下一个结构体
	}
}

//case1的输入接口
student InputInfo() {
	student s;
	rewind(stdin);

	printf("学号：");
	scanf("%d", &s.num);
	
	printf("姓名：");
	scanf("%s", &s.name);
	
	printf("C语言成绩：");
	scanf("%d", &s.CGrade);

	printf("算法成绩：");
	scanf("%d", &s.algorithm);

	printf("数据库成绩：");
	scanf("%d", &s.database);

	s.sum = s.algorithm + s.CGrade + s.database;//总成绩

	return s;//以结构体的方式返回
}

//返回-1表示没有这个学生
//返回>=0表示学生在stu数组中
//顺序查找（按照学号）
int SearchStu(int num) {
	for (int i = 0; i < currentCount; i++) {
		if (stu[i].num == num)return i;
	}
	return -1;
}

//输入任意键确认
void waitConfirm() {
	//先把缓冲区里的“空格”和“回车”之类的全部清空
	//fflush(stdin);//vs2015以上的版本可以用
	rewind(stdin);
	getch();	//等待一个字符（不一定是回车）
}

//覆盖保存（其实这里的文件操作我看的不是很懂，我是跟着老师敲的
//但我明白他的作用是将存到stu[]数组的文件保存到data.txt这个文件中
bool save() {
	//覆盖式写入操作
	FILE* fp = fopen("data.txt", "wb");
	if (fp == NULL) {
		return false;
	}

	for (int i = 0; i < currentCount; i++) {
		int ret = fwrite(&stu[i], sizeof(student), 1, fp);
		if (ret != 1) {
			fclose(fp);
			return false;
		}
	}

	fclose(fp);//用完一定要关掉文件指针，会越用越少
	return true;

}

//case8要用每打印一页的接口
void showPage(int StartIndex, int EndIndex) {//每页的起始下标和结束下标，0开始，如第二页是10-19
	if (EndIndex >= currentCount) {//如果给的结束下标比实际学生数还大，如19>14
		EndIndex = currentCount - 1;//那就10-14
	}

	if (EndIndex - StartIndex + 1 > RECORDER_PER_PAGE) {//比如[10-19]，则20-10+1>10
		EndIndex = StartIndex + RECORDER_PER_PAGE - 1;//10+10-1=19
	}
	//以上两个if都是为了增加代码健壮性
	
	char head[6][COL_LEN_MAX] = {"学号","姓名","C语言成绩","算法","数据库","总分"};
	system("cls");
	printTableHead(TABLE_WIDTH, 6);//打印表头，6列
	printTableRow(TABLE_WIDTH, head, sizeof(head) / sizeof(head[0]));//打印信息表行
	printTableMidLine(TABLE_WIDTH, 6);

	char row[6][COL_LEN_MAX];	//[列][行]
	//循环打印RECORDER_PER_PAGE=10次
	for (int i = StartIndex; i <= EndIndex; i++) {
		sprintf(row[0], "%d", stu[i].num);
		sprintf(row[1], "%s", stu[i].name);
		sprintf(row[2], "%d", stu[i].CGrade);
		sprintf(row[3], "%d", stu[i].algorithm);
		sprintf(row[4], "%d", stu[i].database);
		sprintf(row[5], "%d", stu[i].sum);

		printTableRow(TABLE_WIDTH,row,6);//打印有学生数据的行
		if (i < EndIndex)printTableMidLine(TABLE_WIDTH, 6);//判断是不是最后一行
		else printTableTail(TABLE_WIDTH, 6);
	}
}

//√ case 1
void input()
{
	char str[20];
	while(1) {
		system("cls");
		printf("输入学生信息(y/n):");
		rewind(stdin);
		scanf("%s", str);
		if (strcmp(str, "Y") != 0 && strcmp(str, "y"))break;//不输入学生信息

		student s = InputInfo();
		if (SearchStu(s.num) >= 0) {
			printf("学号[%d]已经存在!\n", s.num);
			waitConfirm();
			continue;//清屏重输入
		}

		stu[currentCount++] = s;//将这个结点赋值给stu[]
		if (save())printf("保存成功\n");
		else printf("保存失败\n");
		waitConfirm();
	}
}

//√ case 2
void search()
{
	int stunum = 0;
	system("cls");
	printf("请输入学号:");
	scanf("%d", &stunum);
	bool i = SearchStu(stunum);
	if (i<0) {		//i=false
		printf("没有找到这名学生！\n");
		return;
	}
	char row[6][COL_LEN_MAX];
	char head[][COL_LEN_MAX] = { "学号", "姓名", "C 语言", "算法", "数据库", "总分" };
	printTableHead(TABLE_WIDTH, 6);
	printTableRow(TABLE_WIDTH, head, sizeof(head) / sizeof(head[0]));
	printTableMidLine(TABLE_WIDTH, 6);
	sprintf(row[0], "%d", stu[i].num);
	sprintf(row[1], "%s", stu[i].name);
	sprintf(row[2], "%d", stu[i].CGrade);
	sprintf(row[3], "%d", stu[i].algorithm);
	sprintf(row[4], "%d", stu[i].database);
	sprintf(row[5], "%d", stu[i].sum);
	printTableRow(TABLE_WIDTH, row, 6);
	printTableTail(TABLE_WIDTH, 6);
}

//case 3
void del()
{
	FILE* fp;
	int snum = 0;
	char str[16] = "";
	system("cls");
	printf("请输入学号:");
	scanf("%d", &snum);
	bool i = SearchStu(snum);
	if (!i) {		//i=0
		printf("没有找到这名学生!\n");
		return;
	}
	printf("找到这条记录，是否删除？(y/n)");
	scanf("%s", str);
	if (strcmp(str, "Y") == 0 || strcmp(str, "y") == 0) {
		for (int j = i; j < currentCount; j++) {
			stu[j] = stu[j + 1];
		}
		currentCount--;
		if (save()) {
			printf("删除成功！\n");
		}
		else {
			printf("保存文件失败！\n");
		}
	}
	else {
		printf("取消删除！\n");
	}
}

//case 4
void modify()
{
	int snum;
	system("cls");
	printf("请输入要修改的学生的学号: ");
	scanf("%d", &snum);
	int i = SearchStu(snum);
	if (i<0) {
		printf("没有找到这名学生!\n");
		return;
	}
	printf("找到了这名学生, 可以修改他的信息！\n");
	printf("姓名:");
	scanf("%s", stu[i].name);
	printf("C 语言:");
	scanf("%d", &stu[i].CGrade);
	printf("算法:");
	scanf("%d", &stu[i].algorithm);
	printf("数据库:");
	scanf("%d", &stu[i].database);
	stu[i].sum = stu[i].CGrade + stu[i].algorithm + stu[i].database;
	if (save()) {
		printf("修改成功！\n");
	}
	else {
		printf("保存文件失败！\n");
	}
}

//case 5
void insert() {
	int stunum;
	system("cls");
	printf("请输入要插入的位置(学号):");//如果要按照下标currentCount-1插入
	scanf("%d", &stunum);
	int destIndex = SearchStu(stunum);//返回要插入位置的下标,0开始
	if (destIndex < 0) {
		printf("没有这名学生，插入位置错误!\n");
		return;
	}
	student t = InputInfo();
	int i = SearchStu(t.num);
	if (i>=0) {
		printf("学号[%d]已经存在! \n", t.num);
		return;
	}
	for (int j = currentCount - 1; j > destIndex; j--) {//j初始是最后一位学生下标
														//destIndex是被后插位置下标
		stu[j + 1] = stu[j];					   //destIndex后面的元素逐个后移一位
	}

	stu[destIndex + 1] = t;
	currentCount++;
	if (save()) printf("插入成功！\n");
	else printf("保存文件失败！\n");
}

//case 8
void show() {
	system("cls");

	if (currentCount == 0) {
		printf("还没有学生信息\n");
		return;
	}

	//100个学生，每页10个（100+10-1）/ 10 = 10...9，即i=[0,9]共10页
	//下面这个算法是老师讲的，我花了好一段时间才理解
	int pageCount = (currentCount + RECORDER_PER_PAGE - 1) / RECORDER_PER_PAGE;
	for (int i = 0; i < pageCount; i++) {//0-9共10页
		showPage(i * RECORDER_PER_PAGE, (i + 1) * RECORDER_PER_PAGE - 1);
		char buff[40];
		sprintf(buff, "共%d页 第[%d]页", pageCount, i + 1);
		printMidInfo(buff);//输出页码标识

		if (i < pageCount - 1) {		//不是最后一页
			waitConfirm();			//要按键盘上任意值才会翻页
		}
	}
}

//case 6
void sort() {
	if (currentCount == 0) {
		printf("还没有学生记录！\n");
		return;
	}
	for (int i = 0; i < currentCount - 1; i++) {
		for (int j = i + 1; j < currentCount; j++) {
			if (stu[i].sum < stu[j].sum) {
				struct student t = stu[i];
				stu[i] = stu[j];
				stu[j] = t;
			}
		}
	}
	if (!save()) {
		printf("排序后，保存文件失败！\n");
	}
	else {
		show();
	}
}

//case 7
void total() {
	system("cls");
	printf("学生总数为%d", currentCount);
}


int main()
{
	//目前学生人数，这个位置在函数后面会未产生标识符
	//int currentCount = 0;
	
	//初始化窗口,stu数组
	Init();
	
	//选择菜单项
	int n = -1;
	scanf("%d", &n);	//输入了一个"1"和"回车"
	
	//选择功能
	while (1) {
		switch (n)//进入对应输入的选项
		{
		case 1:input(); break;		//break退出switch循环
		case 2:search(); break;
		case 3:del(); break;
		case 4:modify(); break;
		case 5:insert(); break;
		case 6:sort(); break;
		case 7:total(); break;
		case 8:show(); break;
		case 0:exit(0);		//exit退出while循环
		default:printf("输错了你个反骨仔\n"); break;		//退出系统
		}

		//等待确认(不用system("pause")是因为会打印“按任意键继续...”
		waitConfirm();
		menu();

		scanf("%d", &n);
	}	
	
	return 0;
}