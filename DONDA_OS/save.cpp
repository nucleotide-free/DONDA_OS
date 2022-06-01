#include "OS.h"

//保存用户信息
void saveUser()
{
	ofstream file;
	file.open("Data\\USER.txt", ios::out | ios::trunc);
	if (file.is_open()) {//打开文件成功
		for (int i = 1; i <= 8; i++) {
			file << userList[i].user_name << " ";
			file << userList[i].password << endl;
		}
	}
	file.close();
}

//保存超级块的信息
void saveSuperBlcok()
{
	ofstream file;
	file.open("Data\\superBlock.txt", ios::out | ios::trunc);
	if (file.is_open()) {//打开文件成功
		file << fileSystem.superBlock.free_iNode_num << endl;//空闲i节点数量
		for (int i = 0; i < INODE_BITMAP_ROW; i++) {//遍历i节点位示图
			for (int j = 0; j < INODE_BITMAP_COL; j++) {
				if (fileSystem.superBlock.iNode_bitmap[i][j] == 0)//写入空闲i节点的ID
					file << i * INODE_BITMAP_COL + j << "    ";
			}
		}
		file << endl;
		
		file << fileSystem.superBlock.free_sfd_item_num << endl;//空闲目录节点数量
		for (int i = 0; i < SFD_BITMAP_ROW; i++) {//遍历目录节点位示图
			for (int j = 0; j < SFD_BITMAP_COL; j++) {
				if (fileSystem.superBlock.SFD_bitmap[i][j] == 0)//写入空闲目录节点的ID
					file << i * SFD_BITMAP_COL + j << "    ";
			}
		}
		file << endl;

		file << fileSystem.superBlock.free_diskblock_num << endl;//空闲磁盘块数量
		for (int i = 0; i < fileSystem.superBlock.free_diskblock_id.size(); i++) {//输出块号到文件
			file << fileSystem.superBlock.free_diskblock_id[i] << "    ";
		}
	}
	file.close();
}

//保存i节点信息
void saveiNode()
{
	ofstream file;
	file.open("Data\\iNode.txt", ios::out | ios::trunc);
	if (!file.is_open()) {//打开文件成功
		cout << "保存iNode文件失败！";
		exit(0);
	}
	for (int i = 0; i < D_INODE_NUM; i++) {
		if (fileSystem.superBlock.iNode_bitmap[i / INODE_BITMAP_COL][i % INODE_BITMAP_COL] == 1) {//该i节点被占用
			file << fileSystem.iNode[i].id << " ";		//i节点的ID
			file << fileSystem.iNode[i].type << " ";	//文件类型
			file << fileSystem.iNode[i].owner << "  ";	//文件拥有者
			for (int j = 1; j <= 8; j++)
				file << fileSystem.iNode[i].auth[j] << " ";			//authorization
			file << " " << fileSystem.iNode[i].file_len << " ";		//文件长度
			file << fileSystem.iNode[i].link_count << " ";			//文件链接次数
			file << fileSystem.iNode[i].last_visited_time << "  ";	//最近一次存取时间
			if (fileSystem.iNode[i].type == 0)		//0-普通文件，存磁盘
				for (int j = 0; j < ADDR_NUM; j++)
					file << fileSystem.iNode[i].i_addr[j]<< " ";	//磁盘块号，指向diskBlock
			file << endl;
		}
	}
	file.close();
}

//保存SFD
void saveSFD()
{
	ofstream file;
	file.open("Data\\SFD.txt", ios::out | ios::trunc);
	if (!file.is_open()) {//打开文件成功
		cout << "保存SFD文件失败！";
		exit(0);
	}
	for (int i = 1; i < SFD_NUM; i++) {
		if (fileSystem.superBlock.SFD_bitmap[i / SFD_BITMAP_COL][i % SFD_BITMAP_COL] == 1) {//该i节点被占用
			file << fileSystem.SFD[i].sfd_num;
			for (int j = 0; j < fileSystem.SFD[i].sfd_num; j++) {
				file << " " << fileSystem.SFD[i].sfd_list[j].file_name << " ";
				file << " " << fileSystem.SFD[i].sfd_list[j].file_id << " ";
			}
		}
	}
	file.close();
}

//保存磁盘块
void saveDiskBlock()
{
	ofstream file;
	file.open("Data\\DiskBlock.txt", ios::out | ios::trunc);
	if (!file.is_open()) {//打开文件成功
		cout << "保存DiskBlock文件失败！";
		exit(0);
	}

	string content;
	for (int i = 1; i <= 512; i++)
	{
		if (!count(fileSystem.superBlock.free_diskblock_id.begin(), fileSystem.superBlock.free_diskblock_id.end(), i))//判断i是否存在超级块中的空闲磁盘块vector中，若没有就读文件。
		{
			file << fileSystem.diskBlock[i].content_len << " ";		//先保存文件占用磁盘块的大小
					file << " " <<fileSystem.diskBlock[i].content << " " ;//再获取文件内容。
		}
	}
	file.close();
}

//保存文件系统
void saveFileSystem()
{
	saveUser();
	saveSuperBlcok();
	saveiNode();
	saveSFD();
	saveDiskBlock();
}