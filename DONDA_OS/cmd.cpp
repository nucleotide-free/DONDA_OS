#include "OS.h"

vector<string> command_0 = { "paste","lpaste", "ls", "cd/", "cd..", "cls", "format", "logout", "bitmap", "exit", "help", "ushow","fshow","chpd", "shpd"};
vector<string> command_1 = { "link","find","cut","copy","mkdir","cd","rmd","create","rmf","write","read","open","close"};
vector<string> command_2 = { "rename" };

//显示命令目录
void commandCategory()
{
	RGBColor(0);
	cout << "\nCOMMANDS:" << endl;
	cout << "\t文件操作" << endl;
	cout << "\t\t更名:\trename  [old name]  [new name]" << endl;
	cout << "\t\t链接:\tlink    [name]" << endl;
	cout << "\t\t查找:\tfind    [name]" << endl;
	cout << "\t\t剪切:\tcut     [name]" << endl;
	cout << "\t\t复制:\tcopy    [name]" << endl;
	cout << "\t\t粘贴:\tpaste" << endl;
	cout << "\t\t粘贴链接:\tlpaste" << endl;
	cout << "\t目录操作" << endl;
	cout << "\t\t创建目录:\tmkdir [name]" << endl;
	cout << "\t\t显示目录:\tls" << endl;
	cout << "\t\t切换目录:\tcd    [name]" << endl;
	cout << "\t\t返回根目录:\tcd/" << endl;
	cout << "\t\t删除目录:\trmd   [name]" << endl;
	cout << "\t\t返回上级目录:\tcd.." << endl;
	cout << "\t文件读写" << endl;
	cout << "\t\t创建文件:\tcreate [name]" << endl;
	cout << "\t\t删除文件:\trmf    [name]" << endl;
	cout << "\t\t打开文件:\topen   [name]" << endl;
	cout << "\t\t关闭文件:\tclose  [name]" << endl;
	cout << "\t\t改写文件:\twrite  [name]" << endl;
	cout << "\t\t读取文件:\tread   [name]" << endl;
	cout << "\t其他操作" << endl;
	cout << "\t\t清屏:\t\tcls" << endl;
	cout << "\t\t格式化:\t\tformat" << endl;
	cout << "\t\t注销登录:\tlogout" << endl;
	cout << "\t\t位示图:\t\tbitmap" << endl;
	cout << "\t\t关闭系统:\texit" << endl;
	cout << "\t\t显示帮助:\thelp" << endl;
	cout << "\t\t用户打开文件表:\tushow" << endl;
	cout << "\t\t系统打开文件表:\tfshow" << endl;
	cout << "\t\t修改密码:\tchpd" << endl;
	cout << "\t\t显示密码:\tshpd\n" << endl;
};

bool EnableVTMode(void) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
		return false;
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode))
		return false;
	return true;
}

//RGB颜色
void RGBColor(int i) {
	switch (i)
	{
	case 0:cout << "\x1B[38;2;243;243;243m"; break;//白色 122, 193, 47
	case 1:cout << "\x1B[38;2;108;141;183m"; break;//蓝色 108, 141, 183
	case 2:cout << "\x1B[38;2;122;193;47m"; break;//绿色 122, 193, 47
	case 3:cout << "\x1B[38;2;255;0;0m"; break;//红色 255, 0, 0
	case 4:cout << "\x1B[38;2;165;21;53m"; break;//红色2 165, 21, 53
	}
}

//界面主函数，用来实现大部分输入输出功能
void display() {
	system("cls");
	commandCategory();//输入提示信息（目录help）
	string file_list;		//用于记录用户所打开的文件或目录的列表，组成链条，显示到输入前
	string path;		//find显示文件路径
	int command_type = -1;//指令类型
	string instruction, fileName1, fileName2;//输入的 指令、文件名1、文件名2
	while (1)
	{
		while (1) {
			RGBColor(2); cout << user.user_name + "@DONDA_OS";
			RGBColor(0); cout << ":";
			RGBColor(1); cout << file_list;
			RGBColor(0); cout << "$";
			if (input_command(instruction, fileName1, fileName2) != -1)//指令有效
				break;
		}
		//*********************************  文件操作 ********************************* 
		if (instruction == "rename") {//重命名
			renameFile(fileName1, fileName2);
		}
		else if (instruction == "link") {//链接
			if (checkValid(fileName1))continue;//文件失效
			createLink(fileName1);
		}
		else if (instruction == "find") {//查找
			path.clear();
			cout << "文件名" << "\t\t" << "文件路径"  << "\t\t" << "文件大小" << endl;
			find(fileName1, path,0);
		}
		else if (instruction == "cut") {//剪切
			if (checkValid(fileName1))continue;//文件失效
			cut(fileName1);
		}
		else if (instruction == "copy") {//复制
			if (checkValid(fileName1))continue;//文件失效
			copy(fileName1);
		}
		else if (instruction == "paste") {//粘贴
			paste();
		}
		else if (instruction == "lpaste") {//粘贴链接
			pasteLink();
		}
		//*********************************目录操作 ********************************* 
		else if (instruction == "mkdir") {//创建目录
			if (fileSystem.iNode[sfd_pointer].auth[user.user_id] == 0) {
				RGBColor(3);
				cout << "错误：创建失败，user"<<user.user_id<<"权限不足！\n";
				continue;
			}
			int tips = createDir(fileName1);//返回创建情况的提示信息
			if (tips == 1)
				cout << "错误：i节点或目录空间不足，创建失败！\n";
			else if (tips == 2)
				cout << "错误：目录名冲突！\n";
			else if (tips == 3)
				cout << "错误：内存空间不足，分配i节点失败！\n";
			else {
				cout << "创建成功！\n";
			}
		}
		else if (instruction == "ls") {//显示目录
			if (fileSystem.SFD[sfd_pointer].sfd_num==0) {
				cout << "无内容" << endl;
				continue;
			}
			RGBColor(1); cout << "名称\t\t修改日期\t\t类型\t大小\n";
			for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {		//扫描当前sfd列表中对的sfd_item的filename并显示出来
				cout << fileSystem.SFD[sfd_pointer].sfd_list[i].file_name+"\t\t";//文件名
				int file_id = fileSystem.SFD[sfd_pointer].sfd_list[i].file_id;	//文件id(指向iNode)
				cout << fileSystem.iNode[file_id].last_visited_time + "\t";		//修改日期
				if(fileSystem.iNode[file_id].type){//获取文件类型
					cout << "dir\n";	//目录文件
				}
				else {
					cout << "file\t";	//文本文档
					cout << fileSystem.iNode[file_id].file_len << endl;//文件长度
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
				sfd_stack.push_back(sfd_pointer);		//将当前目录sfd推入目录栈
			}
			else {
				cout << "不存在的目录，操作失败！\n";
			}
		}
		else if (instruction == "cd/") {//返回根目录
			sfd_pointer = 0;		//根目录sfd的sfd指针
			sfd_stack.clear();		//清空目录栈
			sfd_stack.push_back(sfd_pointer);	//向栈中压入根目录

			file_list.clear();		//文件显示字符串清空
		}
		else if (instruction == "cd..") {//返回上级目录
			if (sfd_stack.size() == 1)
			{
				continue;
			}
			if(sfd_stack.size()!=1)
				sfd_stack.pop_back();		//弹出目录栈
			sfd_pointer = sfd_stack.back();
			file_list.erase(file_list.find_last_of("\\"), file_list.length());		//文件显示字符串清空
		}
		else if (instruction == "rmd") {//删除目录
			deleteDir(findiNodeByName(fileName1));
		}
		//********************************* 文件读写 ********************************
		else if (instruction == "create") {//创建文件
			if (fileSystem.iNode[sfd_pointer].auth[user.user_id] == 0) {
				cout << "该用户权限不足，创建失败！\n";
				continue;
			}
			int tips = createFile(fileName1);//返回创建情况的提示信息
			if (tips == 1)
				cout << "没有空闲磁盘块或者空闲i节点！\n";
			else if (tips == 2)
				cout << "文件名冲突！\n";
			else {
				cout << "创建成功！是否要向文件里写入内容[Y,N]？";
				while (1) {
					char ch = _getch();//用户输入
					cout << ch << endl;
					if (ch == 'N' || ch == 'n')//不写，直接退出
						break;
					else if (ch == 'Y' || ch == 'y') {//写文件
						openFile(fileName1);
						writeFile(fileName1);
						break;
					}
					else
						cout << "输入不合法，请重新输入[Y,N]：";
				}
			}	
		}
		else if (instruction == "rmf") {//删除文件
			int iNode_id = findiNodeByName(fileName1);
			if (iNode_id == -1) {
				cout << "文件不存在！\n";
				continue;
			}
			openFile(fileName1);
			closeFIle(fileName1);
			if(deleteLink(fileName1))//删除链接文件（含判断）
				deleteFile(fileName1);
			cout << "删除成功！\n";
		}
		else if (instruction == "open") {//打开文件
			int iNode_id = findiNodeByName(fileName1);
			if (iNode_id == -1) {
				cout << "文件不存在！\n";
				continue;
			}
			if (checkValid(fileName1))continue;//文件失效
			openFile(fileName1);
		}
		else if (instruction == "close") {//关闭文件
			int iNode_id = findiNodeByName(fileName1);
			if (iNode_id == -1) {
				cout << "文件不存在！\n";
				continue;
			}
			closeFIle(fileName1);
		}
		else if (instruction == "write") {//改写文件
			if (checkValid(fileName1))continue;//文件失效
			writeFile(fileName1);
		}
		else if (instruction == "read") {//读取文件
			if (checkValid(fileName1))continue;//文件失效
			readFile(fileName1);
		}
		//********************************* 其他操作 ********************************
		else if (instruction == "cls") {//清屏
			system("cls");
		}
		else if (instruction == "format") {//格式化
			format();
			init();
			sfd_pointer = 0;		//根目录sfd的sfd指针
			sfd_stack.clear();		//清空目录栈
			sfd_stack.push_back(sfd_pointer);	//向栈中压入根目录
			file_list.clear();		//文件显示字符串清空
			cout << "格式化成功！\n";
		}
		else if (instruction == "logout") {//注销登录
			cout << "注销成功！\n";
			sfd_pointer = 0;
			saveFileSystem();
			login();
		}
		else if (instruction == "bitmap") {//位示图
			RGBColor(1); cout << "\n\t    [ i节点位示图 ]\n" << endl; RGBColor(0);
			cout << "┌──────────────────────────────────┐\n";
			for (int i = 0; i < INODE_BITMAP_ROW; i++) {
				cout << "│  ";
				for (int j = 0; j < INODE_BITMAP_COL; j++) {
					if (fileSystem.superBlock.iNode_bitmap[i][j] == 1) RGBColor(4); 
					else RGBColor(0);
					cout << fileSystem.superBlock.iNode_bitmap[i][j] << " ";
				}
				cout << "│\n";
			}
			cout << "└──────────────────────────────────┘\n";
			RGBColor(1); cout << "\n\t\t\t[ SFD位示图 ]\n" << endl; RGBColor(0);
			cout << "┌──────────────────────────────────────────────────────────────────┐\n";
			for (int i = 0; i < SFD_BITMAP_ROW; i++) {
				cout << "│  ";
				for (int j = 0; j < SFD_BITMAP_COL; j++) {
					if (fileSystem.superBlock.SFD_bitmap[i][j] == 1) RGBColor(4);
					else RGBColor(0);
					cout << fileSystem.superBlock.SFD_bitmap[i][j] << " ";
				}	
				cout << "│\n";
			}
			cout << "└──────────────────────────────────────────────────────────────────┘\n\n\n";
		}
		else if (instruction == "exit") {//关闭系统
		sfd_pointer = 0;
			saveFileSystem();
			system("cls");
			cout << "\n已成功退出 DONDA_OS 文件系统！\n";
			exit(0);
		}
		else if (instruction == "help") {//显示帮助
			commandCategory();
		}
		else if (instruction == "ushow") {//显示用户文件打开表
			for (int i = 1; i < 9; i++){
				cout << userList[i].user_name << ":\n";
				for (int j = 0; j < userList[i].file_Uopened.size(); j++){
					for (int k = 0; k < file_opend_list.size(); k++){
						if (userList[i].file_Uopened[j] == file_opend_list[k].f_inode) {
							RGBColor(1); cout << file_opend_list[k].fileName << "   "; RGBColor(0);
						}
					}
				}
				cout << "\n";
			}
		}
		else if (instruction == "fshow") {//显示系统文件打开表
			showSystemFileOpen();
		}
		else if (instruction == "chpd") {//修改密码
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
							userList[user.user_id].password = user.password;//修改全部用户列表中的密码
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
		else if (instruction == "shpd") {//显示密码
			cout << "用户名：" << user.user_name << endl;
			cout << "密码：" << user.password << endl;
		}
	}

}

//用户输入命令，及判断
int input_command(string& instruction, string& fileName1, string& fileName2)
{
	string line, more = "";
	getline(cin, line);//获取一行的输入

	int flag = 1;
	for (int i = 0; i < line.size(); i++) 
		if (line[i] != ' ')flag = 0;
	if (flag)return -1;//只有个空格或回车，直接返回

	stringstream st;  //字符串流
	st << line;  //输入s字符串到流（st）中

	int command_type = -1;//判断指令的类型
	if (st >> instruction) {
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
	}	
	switch (command_type)
	{
	case 0:
		if (st >> more) {//输入了多余参数
			cout << instruction + "：参数格式不正确\n";
			return -1;
		}
		break;
	case 1:
		if (st >> fileName1) {//输入文件名1
			if (st >> more) {//输入了多余参数
				cout << instruction + "：参数格式不正确\n";
				return -1;
			}
			break;
		}
		else {
			cout << instruction + "：参数格式不正确\n";
			return -1;
		}		
	case 2:
		if (st >> fileName1 >> fileName2) {//输入文件名1、2
			if (st >> more) {//输入了多余参数
				cout << instruction + "：参数格式不正确\n";
				return -1;
			}
			break;
		}
		else {
			cout << instruction + "：参数格式不正确\n";
			return -1;
		}
	case -1:
		cout << "无效指令，输入help获取帮助！\n";
	}
	return command_type;
}
