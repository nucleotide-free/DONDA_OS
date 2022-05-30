#include "OS.h"


//创建一个目录
int createDir(string fileName) {
	if (fileSystem.superBlock.free_iNode_num == 0|| fileSystem.superBlock.free_sfd_item_num == 0) {
		cout << "i节点或目录空间不足，创建失败！\n";
		return 0;
	}
	
	int flag_fileName = -1;//查询是否重名
	for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++)
		if (fileName == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name)
			flag_fileName = 1;

	if (flag_fileName == -1) {//没有重名
		int iNode_id = createiNode(1);//创建目录文件的i节点;
		if (iNode_id == -1) {
			cout << "内存空间不足，分配i节点失败！\n";
			return 0;
		}
		int sfd_id = -1;//新的i节点编号
		for (int i = 0; i < SFD_BITMAP_ROW; i++)
			for (int j = 0; j < SFD_BITMAP_COL; j++)
				if (fileSystem.superBlock.SFD_bitmap[i][j] == 0) {//查位示图，找到一个空闲的i节点
					fileSystem.superBlock.SFD_bitmap[i][j] = 1;//设置为被占用
					sfd_id = i * SFD_BITMAP_COL + j;
					fileSystem.superBlock.free_sfd_item_num--;//空闲i节点数 -1
					break;
				}
		createSFD(iNode_id, fileName);
		cout << "创建成功！\n";
		return 1;
	}
	cout << "目录名冲突！\n";
	return 0;
}

//级联删除一个目录及其子目录和子文件
int deleteDir(string name) {
	return 1;
}


//删除一个i结点
void deleteINodeOne(int useINode) {
	
}


