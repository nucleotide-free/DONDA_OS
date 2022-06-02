#include "OS.h"


//初始化超级块
void initSuperBlock(){

	freopen_s(&stream,"Data\\superBlock.txt", "r", stdin);//文件重定向
	//————————————————————————————————————————
	fileSystem.superBlock.iNode_num = D_INODE_NUM;	//磁盘i节点数量
	cin >> fileSystem.superBlock.free_iNode_num;	//空闲i节点数
	for (int i = 0; i < INODE_BITMAP_ROW; i++)		//初始化i节点位示图，全部被占用-1
		for (int j = 0; j < INODE_BITMAP_COL; j++)
			fileSystem.superBlock.iNode_bitmap[i][j] = 1;
	for (int i = 0; i < fileSystem.superBlock.free_iNode_num; i++) {//读文件，输入空闲的i节点块号
		int block_no;	//磁盘块号
		cin >> block_no;
		fileSystem.superBlock.iNode_bitmap[block_no / INODE_BITMAP_COL][block_no % INODE_BITMAP_COL] = 0;//空闲
	}
	//————————————————————————————————————————
	fileSystem.superBlock.sfd_item_num = SFD_NUM;	//目录节点数量
	cin >> fileSystem.superBlock.free_sfd_item_num;	//空闲目录节点数
	for (int i = 0; i < SFD_BITMAP_ROW; i++)		//初始化目录节点位示图，全部被占用-1
		for (int j = 0; j < SFD_BITMAP_COL; j++)
			fileSystem.superBlock.SFD_bitmap[i][j] = 1;
	for (int i = 0; i < fileSystem.superBlock.free_sfd_item_num; i++) {//读文件，输入空闲的目录节点块号
		int block_no;	//磁盘块号
		cin >> block_no;
		fileSystem.superBlock.SFD_bitmap[block_no / SFD_BITMAP_COL][block_no % SFD_BITMAP_COL] = 0;//空闲
	}
	//————————————————————————————————————————
	fileSystem.superBlock.diskblock_num = DISKBLOCK_NUM;//磁盘块数量
	cin >> fileSystem.superBlock.free_diskblock_num;	//空闲磁盘块数量
	fileSystem.superBlock.stack_size = 1;				//初始化栈内空闲块数量
	fileSystem.superBlock.free_diskblock_id.clear();	//清空id数组
	while (!fileSystem.superBlock.free_block_stack.empty()) {//清空栈
		fileSystem.superBlock.free_block_stack.pop();
	}
	fileSystem.superBlock.free_block_stack.push(-1);	//最后一个组长块，底层元素为 -1（没有更多空闲资源）
	for (int i = 0; i < fileSystem.superBlock.free_diskblock_num; i++) {//成组链接
		int block_id;	//磁盘块号
		cin >> block_id;
		fileSystem.superBlock.free_diskblock_id.push_back(block_id);//存入空闲磁盘块数组

		if (fileSystem.superBlock.stack_size < 50) {
			fileSystem.superBlock.stack_size++;
			fileSystem.superBlock.free_block_stack.push(block_id);//放入
		}
		else {//存成组长块，放入磁盘
			for (int j = 0; j < 50; j++) {
				fileSystem.diskBlock[i].content += to_string(fileSystem.superBlock.free_block_stack.top()) + " ";//存入磁盘文件
				fileSystem.superBlock.free_block_stack.pop();//弹栈
				fileSystem.diskBlock[i].content_len++;//修改文件长度
			}
			fileSystem.superBlock.stack_size = 1;
			fileSystem.superBlock.free_block_stack.push(block_id);
		}
	}
	std::fclose(stdin);//关闭重定向输入
	freopen_s(&stream, "CON", "r", stdin);//重定向到控制台
	cin.clear();//清空缓冲区
}

//初始化SFD
void initSFD() {

	for (int i = 0; i < SFD_NUM; i++) {//清空SFD数组
		fileSystem.SFD[i].sfd_num = 0;
		fileSystem.SFD[i].sfd_list.clear();
	}
	for (int i = 1; i <= 8; i++) {		
		SFD_ITEM sfd_item;	//单目录
		sfd_item.file_name = "root" + to_string(i);
		sfd_item.file_id = i;
		fileSystem.SFD[0].sfd_list.push_back(sfd_item);   //每个用户的文件目录下生成sfd动态数组
		fileSystem.SFD[0].sfd_num++;
	}
	sfd_stack.push_back(0);

	freopen_s(&stream, "Data\\SFD.txt", "r", stdin);
	int SFD_id;
	while (cin >> SFD_id) {
		cin >> fileSystem.SFD[SFD_id].sfd_num;	//SFD子项的数量
		for (int j = 0; j < fileSystem.SFD[SFD_id].sfd_num; j++) {	//SFD子项的具体信息
			SFD_ITEM sfd_item;
			cin >> sfd_item.file_name;
			cin >> sfd_item.file_id;
			fileSystem.SFD[SFD_id].sfd_list.push_back(sfd_item);	//再读取目录块的文件名
		}

	}
	std::fclose(stdin);//关闭重定向输入
	freopen_s(&stream, "CON", "r", stdin);//重定向到控制台
	cin.clear();//清空缓冲区
}

//初始化I节点
void initINode() {
	freopen_s(&stream, "Data\\iNode.txt", "r", stdin);//文件重定向
	for (int i = 0; i < D_INODE_NUM; i++){
		if (fileSystem.superBlock.iNode_bitmap[i / INODE_BITMAP_COL][i % INODE_BITMAP_COL] == 1) {//该i节点被占用
			cin >> fileSystem.iNode[i].id;		//i节点的ID
			cin >> fileSystem.iNode[i].type;	//文件类型
			cin >> fileSystem.iNode[i].owner;	//文件拥有者
			for (int j = 1; j <= 8; j++)
				cin >> fileSystem.iNode[i].auth[j];	//authorization
			cin >> fileSystem.iNode[i].file_len;	//文件长度
			cin >> fileSystem.iNode[i].link_count;	//文件链接次数
			cin >> fileSystem.iNode[i].last_visited_time;	//最近一次存取时间
			if (fileSystem.iNode[i].type == 0)		//0-普通文件，存磁盘
				for (int j = 0; j < ADDR_NUM; j++)
					cin >> fileSystem.iNode[i].i_addr[j];	//磁盘块号，指向diskBlock
		}
	}
	std::fclose(stdin);//关闭重定向输入
	freopen_s(&stream, "CON", "r", stdin);//重定向到控制台
	cin.clear();//清空缓冲区
}

//初始化磁盘块
void initDiskBlock() {
	ifstream file;
	file.open("Data\\DiskBlock.txt", ios::in);
	if (!file.is_open()) {//打开文件成功
		cout << "打开DiskBlock文件失败！";
		exit(0);
	}
	string content;
	for (int i = 0; i < 512; i++)
	{
		if (!count(fileSystem.superBlock.free_diskblock_id.begin(), fileSystem.superBlock.free_diskblock_id.end(), i))//判断i是否存在超级块中的空闲磁盘块vector中，若没有就读文件。
		{
			file >> fileSystem.diskBlock[i].content_len;		//先读取文件的大小
			char content;
			content = file.get();
			while((content = file.get()) != '$')
			 {
				fileSystem.diskBlock[i].content +=  content;  //文件内容
			 }
		}
	}
	file.close();
}

//初始化用户信息列表
void initUsers()
{
	freopen_s(&stream, "Data\\USER.txt", "r", stdin);//读取8个用户的信息
	for (int i = 1; i <= 8; i++) {
		userList[i].user_id = i;
		cin >> userList[i].user_name;
		cin >> userList[i].password;
	}
	std::fclose(stdin);//关闭重定向输入
	freopen_s(&stream, "CON", "r", stdin);//重定向到控制台
	cin.clear();//清空缓冲区
}

void init()
{
	initUsers();
	initSuperBlock();
	initSFD();
	initINode();
	initDiskBlock();
	initMEM_iNode_list();
}

//格式化
void format()
{
	ofstream file;
	file.open("Data\\USER.txt", ios::out | ios::trunc);	//用户 - 格式化
	if (file.is_open()) {//打开文件成功
		for (int i = 1; i <= 8; i++) {
			file << "user" << i << " ";
			file << i << endl;
		}
	}
	file.close();

	file.open("Data\\iNode.txt", ios::out | ios::trunc);	//格式化iNode
	if (file.is_open()) {//打开文件成功
		file << "0 1 0  0 0 0 0 0 0 0 0  8 0 2022/5/30,14:21:30\n";
		file << "1 1 1  1 0 0 0 0 0 0 0  0 0 2022/5/30,14:21:31\n";
		file << "2 1 2  0 1 0 0 0 0 0 0  0 0 2022/5/30,14:21:32\n";
		file << "3 1 3  0 0 1 0 0 0 0 0  0 0 2022/5/30,14:21:33\n";
		file << "4 1 4  0 0 0 1 0 0 0 0  0 0 2022/5/30,14:21:34\n";
		file << "5 1 5  0 0 0 0 1 0 0 0  0 0 2022/5/30,14:21:35\n";
		file << "6 1 6  0 0 0 0 0 1 0 0  0 0 2022/5/30,14:21:36\n";
		file << "7 1 7  0 0 0 0 0 0 1 0  0 0 2022/5/30,14:21:37\n";
		file << "8 1 8  0 0 0 0 0 0 0 1  0 0 2022/5/30,14:21:38\n";

	}
	file.close();

	file.open("Data\\superBlock.txt", ios::out | ios::trunc);	//超级块 - 格式化
	if (file.is_open()) {//打开文件成功
		file << "119\n";
		for (int i = 9; i < 128; i++)//空闲i节点
			file << i << "    ";
		file << "\n503\n";
		for (int i = 9; i < 512; i++)//空闲SFD
			file << i << "    ";
		file << "\n512\n";
		for (int i = 0; i < 512; i++)//空闲磁盘块
			file << i << "    ";
	}
	file.close();

	file.open("Data\\DiskBlock.txt", ios::out | ios::trunc);	//磁盘块 - 格式化
	if (!file.is_open()) {//打开文件成功
		cout << "格式化磁盘文件出错！";
		exit(0);
	}
	file.close();

	file.open("Data\\SFD.txt", ios::out | ios::trunc);	//SFD - 格式化
	if (!file.is_open()) {//打开文件成功
		cout << "格式化SFD文件出错！";
		exit(0);
	}
	file.close();
}

void initMEM_iNode_list() {
	for (int i = 0; i < NHINO; i++) {
		MEM_BFD_ITEM m_iNode;
		m_iNode.id = 0;
		m_iNode.type = 99;		//文件类型 0-普通 1-目录
		mem_iNode[i] = m_iNode;
	}
}



