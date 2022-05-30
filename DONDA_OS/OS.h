#pragma once
#ifndef OS_H
#define OS_H


#define D_INODE_NUM  128	//磁盘i节点，共占128个物理块
#define INODE_BITMAP_ROW 8	//i结点位示图的行数 8
#define INODE_BITMAP_COL 16	//i结点位示图的列数 16

#define SFD_NUM  512		//目录节点，共占512个物理块
#define SFD_BITMAP_ROW 16	//目录结点位示图的行数 16
#define SFD_BITMAP_COL 32	//目录结点位示图的列数 32

#define DISKBLOCK_NUM  512	//磁盘块数量 512

#define BLOCKSIZ  512	//每块大小
#define SYSOPENFILE 40  //系统打开文件表最大项数
#define DIRNUM  128		//每个目录所包含的最大目录项数（文件数）
#define DIRSIZ  14		//每个目录项名字部分所占字节数，另加i节点号2个字节
#define PWDSIZ   12		//口令字
#define PWDNUM   32		//最多可设32个口令登录
#define NOFILE  20		//每个用户最多可打开20个文件，即用户打开文件最大次数

#define ADDR_NUM 13		//每个i节点最多指向13块，addr[0]~addr[9] 为直接地址，addr[10]为一次间址，addr[11]为二次间址，addr[12]为三次间址
#define NHINO  128		//共128个Hash链表，提供索引i节点（必须为2的幂）
#define USERNUM  10		//最多允许10个用户登录
#define DINODESIZ  32	//每个磁盘i节点所占字节


#define NICFREE  50		//超级块中空闲块数组的最大块数
#define NICINOD  50		//超级块中空闲节点的最大块数
#define DINODESTART 2*BLOCKSIZ  //i节点起始地址
#define DATASTART (2+D_INODE_NUM)*BLOCKSIZ //目录、文件区起始地址

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include <string.h>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>


using namespace std;

struct USER {
	int user_id;		//用户id
	string password;	//用户密码
	string user_name;	//登陆用的用户名
};



//普通磁盘块，放文件
struct DISK_BLOCK
{
	string content = "";	//文件内容
	int content_len = 0;	//文件大小（在块中占用了多大的空间）
};

//文件目录项
struct SFD_ITEM {
	string file_name;	//文件名
	int file_id;		//索引节点编号ID
};

//目录结构
struct SFD {
	int sfd_num;		//SFD_ITEM的数量
	vector<SFD_ITEM> sfd_list;		//目录下的目录（SFD_ITEM）
};

//磁盘i节点
struct DISK_BFD_ITEM {		
	int id;					//文件主标识符，指向的SFD的ID
	int type;				//文件类型 0--普通 1--目录
	int owner;				//文件创建者id
	int auth[8];			//8个用户的存取权限  0--无权限  1--有权限
	int file_len;			//文件长度
	int link_count;			//文件链接计数
	string last_visited_time;	//最近一次存取时间
	int i_addr[ADDR_NUM];		//索引数组（物理地址--磁盘块号）
};

//内存i节点
struct MEM_BFD_ITEM {
	int id;					//文件主标识符
	int type;				//文件类型 0--普通 1--目录
	int auth[8];			//8个用户的存取权限  0--无权限  1--有权限
	int owner;				//文件创建者id
	int i_addr[ADDR_NUM];		//索引数组（物理地址--磁盘块号）
	int file_len;			//文件长度
	int link_count;			//文件链接计数
	string last_visited_time;	//最近一次存取时间

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
	int iNode_bitmap[INODE_BITMAP_ROW][INODE_BITMAP_COL];	//i节点位示图 [16][8]  0--为空闲，1--为被占用

	int sfd_item_num;				//目录节点的数量
	int free_sfd_item_num;			//空闲目录节点数
	int SFD_bitmap[SFD_BITMAP_ROW][SFD_BITMAP_COL];		//目录节点位示图  0--为空闲，1--为被占用

	int diskblock_num;				//磁盘块的数量
	int free_diskblock_num;			//空闲磁盘块数
	vector<int> free_diskblock_id;	//空闲磁盘块的id数组
	//超级块的内存栈
	int stack_size = 1;				//超级块的内存栈深度0
	stack<int> free_block_stack;	//内存栈
};

//磁盘文件卷
struct FILE_SYSTEM {
	SPUERBLOCK superBlock;			//超级块
	DISK_BFD_ITEM iNode[D_INODE_NUM];	//磁盘索引结点区，数量为128块
	SFD SFD[SFD_NUM];	//目录块,数量为512块
	DISK_BLOCK diskBlock[DISKBLOCK_NUM + 1];	//文件块,数量为512块
};

extern FILE_SYSTEM fileSystem;		//操作磁盘文件卷的全局变量
extern FILE* stream;
extern int sfd_pointer;		//sfd指针--指向当前的sfd目录
extern USER user;			//当前用户

//**************************初始化模块***************************
void initSuperBlock();      //初始化超级块
void initINode();           //初始化i结点
void initDiskBlock();       //初始化磁盘块
void initSFD();             //初始化SFD
void init();                //初始化

//**************************用户模块*****************************
void login();               //登录用户名
void logout();              //登出
int getInodeNum();            //获得当前目录的i结点号
int checkFileAuth(string filename); //检查当前用户的读写权限
int checkDirAuth(string filename);  //检查当前用户对目录的读写权限

//**************************界面模块*****************************
void dis_help();			//显示帮助
void display();				//界面主函数，用来实现大部分输入输出功能
void textcolor(int color);	//设置字体颜色
int checkIn(string in);		//用来检测命令是否存在以及指令的种类

//**************************块管理模块*****************************
int AllocateOneBlock();			//成组链接--分配空闲块
int ReadABlock(stack<int> free_block_stack, int block_num);
void FreeABlock(int BlockNo);		//成组链接--回收空闲块

//**************************文件的创建与删除模块*****************************
void createInitINode(int iNode_id, int type, int filelen);	//为创建文件或目录初始化i结点
int createiNode(int type);			//为新创建的文件分配一个i结点
void createSFD(int iNode_id, string name);              //为新创建的文件分配一个i结点
int createFile(string fileName);    //创建文件
string getTime();

int* getIaddr(int indexnum);		 //得到待删除文件的索引块中的磁盘块号数组
int freeFile(string fileName);       //删除指定名字的文件
void deleteINode(int pos);			//删除待删除文件对应的i结点及其指向的磁盘块
void findSinglesfd(int inodeNo);	//遍历删除与待删除文件共享的文件目录

//**************************目录的创建与删除模块*****************************
int createDir(string fileName);			//创建一个目录
int deleteDir(string name);		//级联删除一个目录及其子目录和子文件
void deleteINodeOne(int useINode);			//删除一个i结点


#endif