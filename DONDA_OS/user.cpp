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

	freopen_s(&stream, "Data\\USER.txt", "r", stdin);
	for (int i = 1; i <= 8; i++)
	{
			user_list[i].user_id = i;
			cin >> user_list[i].user_name;
			cin >> user_list[i].password;
	}
	std::fclose(stdin);//�ر��ض�������
	freopen_s(&stream, "CON", "r", stdin);
	cin.clear();

	while (1) {

		cout << "\n\t\t���¼�ļ�ϵͳ��";
		cin>>
	}
}