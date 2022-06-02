#include "OS.H"

//新建连接
void createLink(string fileName)
{
	int sfd_item_id = findSFD_item_idByName(fileName);
	if (fileSystem.SFD[sfd_pointer].sfd_list[sfd_item_id].type == 1) {
		cout << "链接文件不可再次链接！\n";
		return;
	}
	int iNode_id = findiNodeByName(fileName);		//找到磁盘iNode_id
	if (fileSystem.iNode[iNode_id].type == 1) {
		cout << "目录文件不可被链接！" << endl;
		return;
	}
	cout << "准备link文件" << fileName << endl;
	link_board.file_id = iNode_id;//更新链接包里的内容
	link_board.file_name = fileName;
	link_board.type = 1;//新建表项为链接类型
}

//粘贴链接文件到当前目录
void pasteLink()
{
	if (link_board.file_id != -1) {
		fileSystem.SFD[sfd_pointer].sfd_list.push_back(link_board);//将这个sfd_item放入当前目录的SFD下的sfd_list当中
		fileSystem.SFD[sfd_pointer].sfd_num++;//当前目录的SFD下的sfd_item数量
		link_board.file_id = -1;//清空链接数据
		cout << "创建连接文件成功！\n";
	}
}

int findSFD_item_idByName(string fileName)
{
	for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++)
		if (fileSystem.SFD[sfd_pointer].sfd_list[i].file_name == fileName)
			return i;
	return -1;
}

//删除连接，判断是否是链接文件
void deleteLink(string fileName)
{
	int iNode_id = findiNodeByName(fileName);
	int sfd_item_id = findSFD_item_idByName(fileName);
	if (fileSystem.SFD[sfd_pointer].sfd_list[sfd_item_id].type != 0) {//是一个链接文件、失效文件
		for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {
			if (fileSystem.SFD[sfd_pointer].sfd_list[i].file_id == iNode_id && fileSystem.SFD[sfd_pointer].sfd_list[i].type == 1) {
				fileSystem.SFD[sfd_pointer].sfd_list.erase(fileSystem.SFD[sfd_pointer].sfd_list.begin() + i);//删除该sfd项
				fileSystem.SFD[sfd_pointer].sfd_num--;
			}
		}
	}
	else {//普通文件
		for (int i = 1; i < SFD_NUM; i++) {
			if (fileSystem.superBlock.SFD_bitmap[i / SFD_BITMAP_COL][i % SFD_BITMAP_COL] == 1 && fileSystem.SFD[i].sfd_num != 0) {//该i节点被占用
				for (int j = 0; j < fileSystem.SFD[i].sfd_num; j++) {
					if (fileSystem.SFD[i].sfd_list[j].type == 1 && fileSystem.SFD[i].sfd_list[j].file_id == iNode_id) {
						fileSystem.SFD[i].sfd_list[j].type = -1;//链接指向的原文件已失效，type = -1
					}

				}
			}
		}
	}
}

//检查文件是否失效,1-失效，0-正常
int checkValid(string fileName)
{
	int sfd_item_id = findSFD_item_idByName(fileName);
	if (fileSystem.SFD[sfd_pointer].sfd_list[sfd_item_id].type == -1) {
		cout << "原文件已失效！\n";
		return 1;
	}
	return 0;
}