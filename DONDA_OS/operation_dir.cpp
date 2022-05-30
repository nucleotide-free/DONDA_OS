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
		createSFD(iNode_id, fileName);
		cout << "创建成功！\n";
		return 1;
	}
	cout << "文件名冲突！\n";
	return 0;
}

//级联删除一个目录及其子目录和子文件
int deleteDir(string name) {
	
}


//删除一个i结点
void deleteINodeOne(int useINode) {
	
}


