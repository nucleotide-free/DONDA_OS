#include "OS.h"

//设置文本输出颜色
void textcolor(int color)//10绿色  14黄色   12红色
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void login() {
	system("cls");
	textcolor(10);
	cout << "\t\t-------------------------------------------------------------------------------" << endl;
	cout << "\t\t-----------               欢迎使用 DONDA_OS 文件系统                -----------" << endl;
	cout << "\t\t-------------------------------------------------------------------------------" << endl;

	while (1)
	{
		cout << "";
	}
}