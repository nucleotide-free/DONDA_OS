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

	freopen_s(&stream, "Data\\USER.txt", "r", stdin);
	for (int i = 1; i <= 8; i++)
	{
			user_list[i].user_id = i;
			cin >> user_list[i].user_name;
			cin >> user_list[i].password;
	}
	std::fclose(stdin);//关闭重定向输入
	freopen_s(&stream, "CON", "r", stdin);
	cin.clear();

	while (1) {

		cout << "\n\t\t请登录文件系统：";
		cin>>
	}
}