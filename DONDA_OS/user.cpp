#include "OS.h"

void login() {
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
}