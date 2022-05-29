#pragma once
#ifndef OS_H
#define OS_H

#define BLOCKSIZ  512	//每块大小
#define SYSOPENFILE 40  //系统打开文件表最大项数
#define DIRNUM  128		//每个目录所包含的最大目录项数（文件数）
#define DIRSIZ  14		//每个目录项名字部分所占字节数，另加i节点号2个字节
#define PWDSIZ   12		//口令字
#define PWDNUM   32		//最多可设32个口令登录
#define NOFILE  20		//每个用户最多可打开20个文件，即用户打开文件最大次数
#define NADDR 13		//每个i节点最多指向13块，addr[0]~addr[9] 为直接地址，addr[10]为一次间址，addr[11]为二次间址，addr[12]为三次间址
#define NHINO  128		//共128个Hash链表，提供索引i节点（必须为2的幂）
#define USERNUM  10		//最多允许10个用户登录
#define DINODESIZ  32	//每个磁盘i节点所占字节
#define DINODEBLK  128	//所有磁盘i节点共占128个物理块
#define FILEBLK  512	//共有512个目录文件物理块
#define NICFREE  50		//超级块中空闲块数组的最大块数
#define NICINOD  50		//超级块中空闲节点的最大块数
#define DINODESTART 2*BLOCKSIZ  //i节点起始地址
#define DATASTART (2+DINODEBLK)*BLOCKSIZ //目录、文件区起始地址

#include <string>
#include<vector>

using namespace std;

//普通磁盘块，放文件
struct DISK_BLOCK
{
	string content;		//文件内容
	int content_len;	//文件大小（在块中占用了多大的空间）
};

//文件目录项
struct SFD_ITEM {
	string file_name;	//文件名
	int file_id;		//索引节点编号ID
};

//磁盘i节点
struct DISK_BFD_ITEM {		
	int id;					//文件主标识符
	int type;				//文件类型 0--普通 1--目录
	int auth[8];			//8个用户的存取权限  0--无权限  1--有权限
	int owner;				//文件创建者id
	int i_addr[NADDR];		//索引数组（物理地址--磁盘块号）
	int file_len;			//文件长度
	int link_count;			//文件链接计数
	int last_visited_time;	//最近一次存取时间
};

//内存i节点
struct MEM_BFD_ITEM {
	int id;					//文件主标识符
	int type;				//文件类型 0--普通 1--目录
	int auth[8];			//8个用户的存取权限  0--无权限  1--有权限
	int owner;				//文件创建者id
	int i_addr[NADDR];		//索引数组（物理地址--磁盘块号）
	int file_len;			//文件长度
	int link_count;			//文件链接计数
	int last_visited_time;	//最近一次存取时间

	int index_num;			//索引节点编号--hash链表节点号
	int status_lock;		//0--unlocked，1--locked
	int status_mod;			//0--unmod，1--mod
	int shared_count;		//共享计数

	struct MEM_BFD_ITEM* next;	//双向hash链表节点指针--下一个
	struct MEM_BFD_ITEM* prev;	//双向hash链表节点指针--上一个
};

//超级块
struct SPUERBLOCK
{
	int iNode_num;					//i节点的数量
	int free_iNode_num;				//空闲i节点数
	vector<int> free_iNode_id;		//空闲i节点的id数组

	int sfd_item_num;				//目录节点的数量
	int free_sfd_item_num;			//空闲目录节点数
	vector<int> free_sfd_item_id;	//空闲目录节点的id数组

	int diskblock_num;				//磁盘块的数量
	int free_diskblock_num;			//空闲磁盘块数
	vector<int> free_diskblock_id;	//空闲磁盘块的id数组，用作超级块放入内存的栈
};

//磁盘文件卷
struct FILE_SYSTEM {
	SPUERBLOCK superBlock;			//超级块
	DISK_BFD_ITEM iNode[DINODEBLK];	//磁盘索引结点区，数量为128块
	vector<SFD_ITEM> SFD[FILEBLK];	//目录块,数量为512块
	DISK_BLOCK diskBlock[FILEBLK];	//文件块,数量为512块
};

FILE_SYSTEM fileSystem;		//操作磁盘文件卷的全局变量
#endif