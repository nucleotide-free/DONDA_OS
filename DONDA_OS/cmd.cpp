#include "OS.h"

vector<string> command_0 = { "paste", "ls", "cd/", "cd..", "cls", "format", "logout", "bitmap", "exit", "help", "changepass", "showpassword" };
vector<string> command_1 = { "link","find","cut","copy","mkdir","cd","deld","create","delf","write","read" };
vector<string> command_2 = { "rename" };

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
	system("cls");
	commandCategory();
	string file_list;		//用于记录用户所打开的文件或目录的列表，组成链条，显示到输入前

	int command_type = -1;//指令类型
	string instruction, fileName1, fileName2;//输入的 指令、文件名1、文件名2
	while (1)
	{
		while (1) {
			cout << user.user_name << "@DONDA_OS:";
			cout << file_list << "$ ";
			//input_command(instruction, fileName1, fileName2);//用户输入指令
			if (input_command(instruction, fileName1, fileName2) != -1)//指令有效
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
			if (fileSystem.SFD[sfd_pointer].sfd_num==0) {
				cout << "无内容" << endl;
				return;
			}
			for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {		//扫描当前sfd列表中对的sfd_item的filename并显示出来
				cout << fileSystem.SFD[sfd_pointer].sfd_list[i].file_name+"\t";
				if(fileSystem.iNode[sfd_pointer].type){		//通过获取iNode[sfd_pointer]的type值来
					cout << "dir\n";
				}
				else {
					cout << "file\n";
				}
			}

		}
		else if (instruction == "cd") {//切换目录
			int fileName_check = 0;		//检查目录中是否存在名为fileName1的目录，1--存在，0--不存在
			int file_check = 0;		//检查cd的是文件还是目录，0--文件，1--目录
			for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {
				if (fileName1 == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name) {
					fileName_check = 1;		//存在
					sfd_pointer = fileSystem.SFD[sfd_pointer].sfd_list[i].file_id;		//将当前的目录sfd指针设为将要进入的目录sfd的id
					break;
				}
			}
			if (fileSystem.iNode[sfd_pointer].type)		//检查iNode中将要cd的文件或目录的type是否为文件
					file_check = 1;		//存在	
			if (fileName_check&& file_check) {
				file_list = file_list + "\\" + fileName1;
				sfd_stack.push_back(fileSystem.SFD[sfd_pointer]);		//将当前目录sfd推入目录栈
			}
			else {
				cout << "不存在的目录，操作失败！\n";
			}
		}
		else if (instruction == "cd/") {//返回根目录
			sfd_pointer = 0;		//根目录sfd的sfd指针
			sfd_stack.clear();		//清空目录栈
			sfd_stack.push_back(fileSystem.SFD[sfd_pointer]);	//向栈中压入根目录

			file_list.clear();		//文件显示字符串清空
		}
		else if (instruction == "cd..") {//返回上级目录
			sfd_stack.pop_back();		//弹出目录栈
			sfd_stack.front();

			file_list.clear();		//文件显示字符串清空
		}
		else if (instruction == "deld") {//删除目录

		}
		//********************************* 文件读写 ********************************
		else if (instruction == "create") {//创建文件
			if (fileSystem.iNode[sfd_pointer].auth[user.user_id] == 0) {
				cout << "创建失败！该用户权限不足！\n";
				continue;
			}
			int iNode_id = createFile(fileName1);
			if( iNode_id > -1){//创建成功
				cout << "是否要向文件里写入东西[Y,N]？";
				while (1) {
					char ch = _getch();//用户输入
					cout << ch << endl;
					if (ch == 'N' || ch == 'n')
						break;//不写，直接退出
					else if (ch == 'Y' || ch == 'y') {//写文件
						writeFile(fileName1);
						break;
					}
					else
						cout << "输入不合法，请重新输入[Y,N]：";
				}
				
			}	
		}
		else if (instruction == "delf") {//删除文件

		}
		else if (instruction == "write") {//改写文件
			writeFile(fileName1);
		}
		else if (instruction == "read") {//读取文件

		}
		//********************************* 其他操作 ********************************
		else if (instruction == "cls") {//清屏
			system("cls");
		}
		else if (instruction == "format") {//格式化

		}
		else if (instruction == "logout") {//注销登录
			cout << "注销成功！\n";
			login();
		}
		else if (instruction == "bitmap") {//位示图
			cout << "\t[ i节点位示图 ]\n" << endl;
			for (int i = 0; i < INODE_BITMAP_ROW; i++) {
				for (int j = 0; j < INODE_BITMAP_COL; j++) 
					cout << fileSystem.superBlock.iNode_bitmap[i][j] << " ";
				cout << endl;
			}
			cout << "\n\t[ SFD位示图 ]\n" << endl;
			for (int i = 0; i < SFD_BITMAP_ROW; i++) {
				for (int j = 0; j < SFD_BITMAP_COL; j++)
					cout << fileSystem.superBlock.SFD_bitmap[i][j] << " ";
				cout << endl;
			}
			cout << "\n\n";
		}
		else if (instruction == "exit") {//关闭系统
			return;
		}
		else if (instruction == "help") {//显示帮助
			commandCategory();
		}
		else if (instruction == "changepass") {//修改密码
			char temp[30];
			char* temp1 = temp;
			cout << "用户名：" << user.user_name << endl;
			while (1) {
				cout << "当前密码：";
				string psw = getpassword(temp1);
				if (psw != user.password) {
					cout << "密码错误！是否继续输入[Y,N]? ";
					char ch = _getch();
					cout << ch << endl;
					if (ch == 'Y' || ch == 'y')
						continue;
					else if (ch == 'N'|| ch == 'n')
						break;
				}
				else {//旧密码正确
					while (1) {
						cout << "新密码：";
						psw = getpassword(temp1);
						cout << "确认密码：";
						string psw2 = getpassword(temp1);
						if (psw == psw2) { //两次输入的密码一致
							cout << "修改成功！\n";
							user.password = psw;
							break;
						}
						else {//输入的密码不一致
							cout << "两次输入的密码不一致！是否继续输入[Y,N]? ";
							char ch = _getch();
							cout << ch << endl;
							if (ch == 'Y' || ch == 'y')
								continue;
							else if (ch == 'N' || ch == 'n')
								break;
						}
					}
					break;
				}
			}
		}
		else if (instruction == "showpassword") {//显示密码
			cout << "用户名：" << user.user_name << endl;
			cout << "密码：" << user.password << endl;
		}
	}
}

//用户输入命令，及判断
int input_command(string& instruction, string& fileName1, string& fileName2)
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