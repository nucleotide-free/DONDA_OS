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
