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

void RGBColor(int i) {
	switch (i)
	{
	case 1:cout << "\x1B[38;2;108;141;183m"; break;//蓝色
	case 2:cout << "\x1B[38;2;108;141;183m"; break;
	default:
		break;
	}
	
}

void login() {    
	system("cls");
	RGBColor(1);
	cout << "\n\t\t-------------------------------------------------------------------------------" << endl;
	cout << "\t\t-----------               欢迎使用 DONDA_OS 文件系统                -----------" << endl;
	cout << "\t\t-------------------------------------------------------------------------------" << endl;

	while (1) {
		user.user_id = 0;//用户初始化
		user.password = "";
		user.file_Uopened.clear();

		cout << "\n\t\t请登录文件系统：";
		textColor(7);
		cin >> user.user_name;	//输入用户名
		if (user.user_name == ":wq") {//退出系统
			return;
		}
		for (int i = 1; i < 9; i++) {
			if(user.user_name == userList[i].user_name){//输入的用户名存在
				user.user_id = userList[i].user_id;
				user.password = userList[i].password;
			}
		}
		if (user.user_id == 0) {
			textColor(4);
			cout << "\n\t\t该用户不存在！\n";
			continue;
		}
		textColor(11);
		cout << "\n\t\t请输入密码：";
		textColor(7);
		char temp[30];
		char* temp1 = temp;
		string psw = getpassword(temp1);
		textColor(4);
		if (psw != user.password) 
			cout << "\n\t\t密码错误！\n";
		else {	//登录成功
			getchar();//吸收回车
			user.file_Uopened = userList[user.user_id].file_Uopened;//更新用户打开文件表
			link_board.file_id = -1;//链接板清空
			clip_fileName = "";//剪切板清空
			clipBoard = "";
			display();//登录成功后，进入系统界面
		}
	}
}