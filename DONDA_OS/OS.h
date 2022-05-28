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
#define NADDR 10		//每个i节点最多指向10块，addr[0]~addr[9]
#define NHINO  128		//共128个Hash链表，提供索引i节点（必须为2的幂）
#define USERNUM  10		//最多允许10个用户登录
#define DINODESIZ  32	//每个磁盘i节点所占字节
#define DINODEBLK  32	//所有磁盘i节点共占32个物理块
#define FILEBLK  512	//共有512个目录文件物理块
#define NICFREE  50		//超级块中空闲块数组的最大块数
#define NICINOD  50		//超级块中空闲节点的最大块数
#define DINODESTART 2*BLOCKSIZ  //i节点起始地址
#define DATASTART (2+DINODEBLK)*BLOCKSIZ //目录、文件区起始地址

#include <string>

using namespace std;

struct SFD_item {
	string file_name;	//文件名
	int file_id;		//索引节点编号ID
};

struct BFD_item {		//i节点
	int file_id;

};

#endif