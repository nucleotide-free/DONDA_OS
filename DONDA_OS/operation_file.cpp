#include "OS.h"

//为创建文件或目录初始化i结点
void createInitINode(int useINode, int type, int filelen)
{

}

//创建文件
int createFile(string fileName) 
{

}

//创建文件的第一个索引块
int createFirstIndexBlock() {        

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

void createSFD(DISK_BFD_ITEM iNode,string name) {
	SFD_ITEM temp;
	temp.file_name = name;		//文件名输入
	temp.file_id = iNode.id;			//SFD_ITEM的id等于i节点的id
	fileSystem.SFD[sfd_pointer].sfd_list.push_back(temp);		//将这个sfd_item放入当前目录的SFD下的sfd_list当中
	fileSystem.SFD[sfd_pointer].sfd_num++;		//当前目录的SFD下的sfd_item数量
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

string getTime() {
	time_t time_seconds = time(0);
	tm now_time;
	localtime_s(&now_time, &time_seconds);

	std::stringstream ss;
	ss << now_time.tm_year + 1900 << "-" << now_time.tm_mon + 1 << "-"
		<< now_time.tm_mday << "," << now_time.tm_hour << ":"
		<< now_time.tm_min << ":" << now_time.tm_hour;
	std::cout << ss.str() << std::endl;
}
