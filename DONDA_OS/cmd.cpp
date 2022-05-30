#include "OS.h"

vector<string> command_0 = { "paste", "ls", "cd/", "cd..", "cls", "format", "logout", "bitmap", "exit", "help", "changepass", "showpassword" };
vector<string> command_1 = { "link","find","cut","copy","mkdir","cd","deld","create","delf","write","read" };
vector<string> command_2 = { "rename" };

//显示命令目录
void commandCategory()
{
	textColor(10);
	cout << "--------------------------------------------------------------------------------" << endl;
	Sleep(20);    //程序延时100ms
	cout << "-----------                        命令提示                          -----------" << endl;
	Sleep(20);    //程序延时100ms
	cout << "---------------------------------文件/目录操作----------------------------------" << endl;
	Sleep(10);    //程序延时100ms
	cout << "-----------  - 更名:     rname <O> <N>#  - 链接: link   <name>      ------------" << endl;
	Sleep(10);    //程序延时100ms
	cout << "-----------  - 查找:     find  <name> #  - 剪切: cut    <name>       -----------" << endl;
	Sleep(10);    //程序延时100ms
	cout << "-----------  - 复制:     copy  <name> #  - 粘贴: paste               -----------" << endl;
	Sleep(20);    //程序延时100ms
	cout << "---------------------------------目录操作---------------------------------------" << endl;
	Sleep(10);    //程序延时100ms
	cout << "-----------  - 创建目录: mkdir <name> #  - 显示目录:     ls         ------------" << endl;
	Sleep(10);    //程序延时100ms
	cout << "-----------  - 切换目录: cd    <name> #  - 返回根目录:   cd/        ------------" << endl;
	Sleep(10);    //程序延时100ms
	cout << "-----------  - 删除目录: deld  <name> #  - 返回上级目录: cd..       ------------" << endl;
	Sleep(20);    //程序延时100ms
	cout << "----------------------------------文件操作--------------------------------------" << endl;
	Sleep(10);    //程序延时100ms
	cout << "------------  - 创建文件: create <name>#  - 删除文件: delf <name>    -----------" << endl;
	Sleep(10);    //程序延时100ms
	cout << "------------  - 改写文件: write <name> #  - 读取文件: read <name>    -----------" << endl;
	Sleep(20);    //程序延时100ms
	cout << "----------------------------------其他操作--------------------------------------" << endl;
	Sleep(10);    //程序延时100ms
	cout << "------------  - 清屏:     cls          #  - 格式化:   format         -----------" << endl;
	Sleep(10);    //程序延时100ms
	cout << "------------  - 注销登录: logout       #  - 位示图:   print          -----------" << endl;
	Sleep(10);    //程序延时100ms
	cout << "------------  - 自动补全: Tab          #  - 关闭系统: exit           -----------" << endl;
	Sleep(10);    //程序延时100ms
	cout << "------------  - 重新输入: ↑           #  - 显示帮助: help           -----------" << endl;
	Sleep(10);    //程序延时100ms
	cout << "------------  - 修改密码: changepass   #  - 显示密码: showpassword   -----------" << endl;
	Sleep(10);    //程序延时100ms
	cout << "--------------------------------------------------------------------------------" << endl;
}

//界面主函数，用来实现大部分输入输出功能
void display() {
	system("cls");
	string tips = "@" + user.user_name + ":\\";
	int command_type = -1;//指令类型
	string instruction, fileName1, fileName2;//输入的 指令、文件名1、文件名2
	while (1)
	{
		while (1) {
			cout << tips << ">";//当前所处文件
			input_command(instruction, fileName1, fileName2);//用户输入指令
			if (command_type != -1)//指令有效
				break;
		}
		//*********************************  文件操作 ********************************* 
		if (instruction == "rname") {//重命名

		}
		else if (instruction == "link") {//链接

		}
		else if (instruction == "find") {//查找

		}
		else if (instruction == "cut") {//剪切

		}
		else if (instruction == "copy") {//复制

		}
		else if (instruction == "paste") {//粘贴

		}
		//*********************************目录操作 ********************************* 
		else if (instruction == "mkdir") {//创建目录

		}
		else if (instruction == "ls") {//显示目录

		}
		else if (instruction == "cd") {//切换目录

		}
		else if (instruction == "cd/") {//返回根目录

		}
		else if (instruction == "cd..") {//返回上级目录

		}
		else if (instruction == "deld") {//删除目录

		}
		//********************************* 文件读写 ********************************
		else if (instruction == "create") {//创建文件

		}
		else if (instruction == "delf") {//删除文件

		}
		else if (instruction == "write") {//改写文件

		}
		else if (instruction == "read") {//读取文件

		}
		//********************************* 其他操作 ********************************
		else if (instruction == "cls") {//清屏

		}
		else if (instruction == "format") {//格式化

		}
		else if (instruction == "logout") {//注销登录

		}
		else if (instruction == "bitmap") {//位示图

		}
		else if (instruction == "exit") {//关闭系统

		}
		else if (instruction == "help") {//显示帮助

		}
		else if (instruction == "changepass") {//修改密码

		}
		else if (instruction == "showpassword") {//显示密码

		}

	}
}

int input_command(string& instruction, string& fileName1, string& fileName2)//用户输入命令，及判断
{
	cin >> instruction;//输入指令
	int command_type = -1;//判断指令的类型
	for (int i = 0; i < command_0.size(); i++) {
		if (command_0[i] == instruction) {//指令 没有操作数
			command_type = 0; break;
		}
	}
	if (command_type == -1)//没找到，继续找
		for (int i = 0; i < command_1.size(); i++) {
			if (command_1[i] == instruction) {//指令 一个操作数
				command_type = 1; break;
			}
		}
	if (command_type == -1)//没找到，继续找
		for (int i = 0; i < command_2.size(); i++) {
			if (command_2[i] == instruction) {//指令 两个操作数
				command_type = 2; break;
			}
		}
	switch (command_type)
	{
	case 1:cin >> fileName1; break;//输入文件名1
	case 2:cin >> fileName1 >> fileName2; break;//输入文件名1、2
	case -1:cout << "无效指令，输入help获取帮助！\n";
	}
	return command_type;
}


//设置字体颜色
void textColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}