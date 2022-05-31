#include "OS.h"

//为创建文件或目录 初始化i结点
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
	fileSystem.iNode[iNode_id].last_visited_time = getTime();//最后一次存取时间（当前时间）
	for (int i = 0; i < ADDR_NUM; i++)
		fileSystem.iNode[iNode_id].i_addr[i] = -1;//使用的磁盘资源
}

//为新创建的文件分配一个i结点，返回i节点编号，-1为没找到
int createiNode(int type)
{
	int iNode_id = -1;//新的i节点编号
	for (int i = 0; i < INODE_BITMAP_ROW; i++)
		for (int j = 0; j < INODE_BITMAP_COL; j++)
			if (fileSystem.superBlock.iNode_bitmap[i][j] == 0) {//查位示图，找到一个空闲的i节点
				fileSystem.superBlock.iNode_bitmap[i][j] = 1;//设置为被占用
				iNode_id = i * INODE_BITMAP_COL + j;
				fileSystem.superBlock.free_iNode_num--;//空闲i节点数 -1
				break;
			}
	createInitINode(iNode_id, type, 0);//为创建文件或目录初始化i结点，类型为0，表示文件，长度为0，初始化i结点
	return iNode_id;
}

void createSFD(int iNode_id, string name) {
	SFD_ITEM temp;
	temp.file_name = name;		//文件名输入
	temp.file_id = iNode_id;			//SFD_ITEM的id等于i节点的id
	fileSystem.SFD[sfd_pointer].sfd_list.push_back(temp);		//将这个sfd_item放入当前目录的SFD下的sfd_list当中
	fileSystem.SFD[sfd_pointer].sfd_num++;		//当前目录的SFD下的sfd_item数量
}

//创建文件，1-成功，0-失败
int createFile(string fileName)
{
	if (fileSystem.superBlock.free_diskblock_num == 0 || fileSystem.superBlock.free_iNode_num == 0) {
		return 1;//没有空闲磁盘块或者空闲i节点！
	}
	for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {//查询是否重名
		if (fileName == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name) {
			return 2;//文件名冲突
		}
	}
	int iNode_id = createiNode(0);//分配到一个i节点
	createSFD(iNode_id, fileName);
	return 0;
}

//int checkExitsfd(string name) {}  //查询当前目录下一固定名的文件下标
//int* getIaddr(int indexnum) {}     //得到待删除文件的索引块中的磁盘块号数组

//删除文件
int freeFile(string fileName) {
	return 0;
}
//删除待删除文件对应的i结点及其指向的磁盘块
void deleteiNode(int pos)      
{

}
//遍历删除与待删除文件共享的文件目录
void findSinglesfd(int inodeNo) {

}

//获取当前时间
string getTime() {		
	time_t time_seconds = time(0);
	tm now_time;
	localtime_s(&now_time, &time_seconds);

	std::stringstream ss;
	ss << now_time.tm_year + 1900 << "/" << now_time.tm_mon + 1 << "/"
		<< now_time.tm_mday << "," << now_time.tm_hour << ":"
		<< now_time.tm_min ;
	return  ss.str();
}
