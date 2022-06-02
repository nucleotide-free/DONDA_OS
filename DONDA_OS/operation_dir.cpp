#include "OS.h"


//创建一个目录
int createDir(string fileName) {
	if (fileSystem.superBlock.free_iNode_num == 0 || fileSystem.superBlock.free_sfd_item_num == 0) {
		return 1;//i节点或目录空间不足，创建失败！
	}
	for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {		//查询是否重名
		if (fileName == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name) {
			return 2;//目录名冲突
		}
	}
	int iNode_id = createiNode(1);//创建目录文件的i节点;
	if (iNode_id == -1) 
		return 3;//内存空间不足，分配i节点失败！
	
	int sfd_id = -1;//新的i节点编号
	for (int i = 0; i < SFD_BITMAP_ROW; i++) {
		for (int j = 0; j < SFD_BITMAP_COL; j++)
			if (fileSystem.superBlock.SFD_bitmap[i][j] == 0) {//查位示图，找到一个空闲的i节点
				fileSystem.superBlock.SFD_bitmap[i][j] = 1;//设置为被占用
				sfd_id = i * SFD_BITMAP_COL + j;
				fileSystem.superBlock.free_sfd_item_num--;//空闲i节点数 -1
				break;
			}
		if (sfd_id != -1)break;
	}
	createSFD(iNode_id, fileName);
	return 0;
}

//级联删除一个目录及其子目录和子文件
void deleteDir(int id) {
	int iNode_id = id;
	int SFD_id = fileSystem.iNode[iNode_id].id;
	//if(fileSystem.iNode[iNode_id].type==0)
	for (int i = 0; i < fileSystem.SFD[SFD_id].sfd_num; i++)
	{
		string sub_file_name = fileSystem.SFD[SFD_id].sfd_list[i].file_name;		//要删除的目录中的文件或目录名
		int sub_iNode_id = findiNodeByName(id,sub_file_name);
		if (fileSystem.iNode[sub_iNode_id].type == 0) {		//如果iNode_type为0，即普通文件，就直接删除
			deleteDiskBlock(sub_iNode_id);	//回收磁盘块
			deleteiNode(sub_iNode_id);		//回收i节点
			deleteSFD_ITEM(sub_iNode_id);	//回收SFD子项
		}
		else 
			deleteDir(sub_iNode_id);		//如果iNode_type为1，即目录文件，就递归进入
	}
	deleteiNode(iNode_id);		//删除当前目录的iNode
	deleteSFD_ITEM(iNode_id);	
	deleteSFD(iNode_id);
}

//删除一整个SFD
void deleteSFD(int iNode_id)
{
	fileSystem.SFD[iNode_id].sfd_num = 0;
	fileSystem.SFD[iNode_id].sfd_list.clear();
	fileSystem.superBlock.SFD_bitmap[iNode_id / SFD_BITMAP_COL][iNode_id % SFD_BITMAP_COL] = 0;//释放位示图资源
	fileSystem.superBlock.free_sfd_item_num++;
}

