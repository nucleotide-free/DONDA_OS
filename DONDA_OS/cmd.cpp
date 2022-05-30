#include "OS.h"

//显示命令目录
void commandCategory()
{
	textColor(10);
	cout << "\nCOMMANDS:" << endl;
	cout << "\t文件操作" << endl;
	cout << "\t\t更名:\trname [old name] [new name]" << endl;
	cout << "\t\t链接:\tlink   [name]" << endl;
	cout << "\t\t查找:\tfind  [name]" << endl;
	cout << "\t\t剪切:\tcut   [name]" << endl;
	cout << "\t\t复制:\tcopy [name]" << endl;
	cout << "\t\t粘贴:\tpaste" << endl;
	cout << "\t目录操作" << endl;
	cout << "\t\t创建目录:\tmkdir [name]" << endl;
	cout << "\t\t显示目录:\tls" << endl;
	cout << "\t\t切换目录:\tcd		[name]" << endl;
	cout << "\t\t返回根目录:\tcd/" << endl;
	cout << "\t\t删除目录:\tdeld  [name]" << endl;
	cout << "\t\t返回上级目录:\tcd.." << endl;
	cout << "\t文件读写" << endl;
	cout << "\t\t创建文件:\tcreate [name]" << endl;
	cout << "\t\t删除文件:\tdelf [name]" << endl;
	cout << "\t\t改写文件:\twrite [name]" << endl;
	cout << "\t\t读取文件:\tread [name]" << endl;
	cout << "\t其他操作" << endl;
	cout << "\t\t清屏:	\tcls" << endl;
	cout << "\t\t格式化:\tformat" << endl;
	cout << "\t\t注销登录:\tlogout" << endl;
	cout << "\t\t位示图:\tbitmap" << endl;
	cout << "\t\t关闭系统:\texit" << endl;
	cout << "\t\t显示帮助:\thelp" << endl;
	cout << "\t\t修改密码:\tchangepass" << endl;
	cout << "\t\t显示密码:\tshowpassword" << endl;
};

//界面主函数，用来实现大部分输入输出功能
void display() {
	string file_list;		//用于记录用户所打开的文件或目录的列表，组成链条，显示到输入前
	cout << user.user_name << "@File System\\>";
	if (file_list != " ") {
		cout << file_list << ">";
	}

}

//用来检测命令是否存在以及指令的种类
int checkIn(string in)
{
	return 1;
}

//设置字体颜色
void textColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}