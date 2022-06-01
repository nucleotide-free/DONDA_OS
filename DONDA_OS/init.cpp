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
	fileSystem.superBlock.stack_size = 1;			//初始化栈内空闲块数量
	fileSystem.superBlock.free_block_stack.push(0);	//最后一个组长块，底层元素为 0（没有更多空闲资源）
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
	cin.clear();
}

//初始化SFD
void initSFD() {

	for (int i = 1; i <= 8; i++) {		
		string tmps;
		stringstream ss;	
		ss << i;
		ss >> tmps;
		SFD_ITEM sfd_item;	//单目录
		sfd_item.file_name = "root" + tmps;
		sfd_item.file_id = i;
		fileSystem.SFD[0].sfd_list.push_back(sfd_item);   //每个用户的文件目录下生成sfd动态数组
		fileSystem.SFD[0].sfd_num++;
	}

	sfd_stack.push_back(fileSystem.SFD[0]);

	freopen_s(&stream, "Data\\SFD.txt", "r", stdin);
	for (int i = 1; i <= 512; i++)
	{
		if (fileSystem.superBlock.SFD_bitmap[i / SFD_BITMAP_COL][i % SFD_BITMAP_COL] != 0)//在SFD位示图中找到非空SFD_ITEM的块号
		{
			int sfd_num=0;
			cin >> sfd_num; 
			fileSystem.SFD[i].sfd_num = sfd_num;
			for (int j = 0; j < fileSystem.SFD[i].sfd_num; j++) {
				SFD_ITEM sfd_item;
				cin >> sfd_item.file_name;
				cin >> sfd_item.file_id;
				fileSystem.SFD[i].sfd_list.push_back(sfd_item);		//再读取目录块的文件名
			}
		}
	}
	std::fclose(stdin);//关闭重定向输入
	cin.clear();
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
	cin.clear();
}

//初始化磁盘块
void initDiskBlock() {
	freopen_s(&stream, "Data\\DiskBlock.txt", "r", stdin);
	string content;
	for (int i = 1; i <= 512; i++)
	{
		if (!count(fileSystem.superBlock.free_diskblock_id.begin(), fileSystem.superBlock.free_diskblock_id.end(), i))//判断i是否存在超级块中的空闲磁盘块vector中，若没有就读文件。
		{
			cin >> fileSystem.diskBlock[i].content_len;		//先读取文件的大小
			{
				string content;
				for (int j = 0; j < fileSystem.diskBlock[i].content_len; j++)
				{
					cin >> content;//再获取文件内容。
					fileSystem.diskBlock[i].content = " " + fileSystem.diskBlock[i].content + " " + content + " ";  //文件内容
				}
			}
		}
	}
	std::fclose(stdin);//关闭重定向输入
	cin.clear();
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
	cin.clear();
}

void init()
{
	initSuperBlock();
	initSFD();
	initINode();
	initDiskBlock();
	initUsers();
	freopen_s(&stream, "CON", "r", stdin);//重定向到控制台
	cin.clear();//清空缓冲区
}