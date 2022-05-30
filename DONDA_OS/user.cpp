#include "OS.h"

//密码掩码化
char* getpassword(char* pasw)
{
	char ch;
	int i = 0;
	while ((ch = _getch()) != '\r') {
		if (i > 0 && ch == '\b') {
			--i;
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
		else if (i < 18) {
			pasw[i++] = ch;
			putchar('*');
		}
	}
	pasw[i] = '\0';
	putchar('\n');
	return pasw;
}

void login() {
	USER user_list[9];      //8个用户
	freopen_s(&stream, "Data\\USER.txt", "r", stdin);
	for (int i = 1; i <= 8; i++) {
		user_list[i].user_id = i;
		cin >> user_list[i].user_name;
		cin >> user_list[i].password;
	}
	std::fclose(stdin);//关闭重定向输入
	cin.clear();
	freopen_s(&stream, "CON", "r", stdin);
	

	system("cls");
	textColor(10);
	cout << "\t\t-------------------------------------------------------------------------------" << endl;
	cout << "\t\t-----------               欢迎使用 DONDA_OS 文件系统                -----------" << endl;
	cout << "\t\t-------------------------------------------------------------------------------" << endl;

	while (1) {
		cout << "\n\t\t请登录文件系统：";
		cin >> user.user_name;	//输入用户名
		for (int i = 1; i < 9; i++) {
			if(user.user_name == user_list[i].user_name){//输入的用户名存在
				user.user_id = user_list[i].user_id;
				user.password = user_list[i].password;
			}
		}
		if (user.user_id == 0) {
			cout << "该用户不存在！";
			continue;
		}

		cout << "\n\t\t请输入密码：";
		char temp[30];
		char* temp1 = temp;

		string psw = getpassword(temp1);
		if (psw != user.password) {
			cout << "密码错误！";
			user.user_id = 0;//用户初始化
		}else {
			cout << "登录成功！";
			break;
		}
	}
}
