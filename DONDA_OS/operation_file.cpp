#include "OS.h"

//为创建文件或目录初始化i结点
void createInitINode(int iNode_id, int type, int filelen)
{
	fileSystem.iNode[iNode_id].id = iNode_id;//i节点的id，即在数组里的id
	fileSystem.iNode[iNode_id].type = type;	 //文件类型 0-普通 1-目录
	fileSystem.iNode[iNode_id].owner = user.user_id;//文件创立者
	for (int i = 1; i <= 8; i++) 
		fileSystem.iNode[iNode_id].auth[i] = 0;//全部user都无权限
	fileSystem.iNode[iNode_id].auth[user.user_id] = 1;//仅创立者有权限

	fileSystem.iNode[iNode_id].file_len = filelen;//文件长度
	fileSystem.iNode[iNode_id].link_count = 0;//链接次数 = 0
	fileSystem.iNode[iNode_id].last_visited_time = 0;//最后一次存取时间（当前时间）
	for (int i = 0; i < ADDR_NUM; i++)
		fileSystem.iNode[iNode_id].i_addr[i] = -1;//使用的磁盘资源
}

//创建文件
int createFile(string fileName) 
{

}


//为新创建的文件分配一个i结点
int createiNode() 
{              
	if (fileSystem.superBlock.free_diskblock_num == 0) {//没有空闲磁盘块
		cout << "没有空闲磁盘块！\n";
		return -1;
	}
	if (fileSystem.superBlock.free_iNode_num == 0) {//没有空闲i节点
		cout << "没有空闲磁盘块！\n";
		return -1;
	}
	//分配一个i节点

}

int createSFD(DISK_BFD_ITEM iNode,string name) {
	SFD_ITEM temp;
	temp.file_name = name;		//文件名输入
	temp.file_id = iNode.id;			//SFD_ITEM的id等于i节点的id
	fileSystem.SFD[sfd_pointer].sfd_list.push_back(temp);		//将这个sfd_item放入当前目录的SFD下的sfd_list当中
	fileSystem.SFD[sfd_pointer].sfd_num++;		//当前目录的SFD下的sfd_item数量++
}

int checkExitsfd(string name) {}  //查询当前目录下一固定名的文件下标
int* getIaddr(int indexnum) {}     //得到待删除文件的索引块中的磁盘块号数组

//删除文件
int freeFile(string fileName) {

}
//删除待删除文件对应的i结点及其指向的磁盘块
void deleteiNode(int pos)      
{

}
//遍历删除与待删除文件共享的文件目录
void findSinglesfd(int inodeNo) {

}
