#include "OS.h"

//�����ı������ɫ
void textcolor(int color)//10��ɫ  14��ɫ   12��ɫ
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void login() {
	system("cls");
	textcolor(10);
	cout << "\t\t-------------------------------------------------------------------------------" << endl;
	cout << "\t\t-----------               ��ӭʹ�� DONDA_OS �ļ�ϵͳ                -----------" << endl;
	cout << "\t\t-------------------------------------------------------------------------------" << endl;

	while (1)
	{
		cout << "";
	}
}