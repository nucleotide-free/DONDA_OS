#pragma once
#ifndef OS_H
#define OS_H


#define D_INODE_NUM  128	//����i�ڵ㣬��ռ128�������
#define INODE_BITMAP_ROW 8	//i���λʾͼ������ 8
#define INODE_BITMAP_COL 16	//i���λʾͼ������ 16

#define SFD_NUM  512		//Ŀ¼�ڵ㣬��ռ512�������
#define SFD_BITMAP_ROW 16	//Ŀ¼���λʾͼ������ 16
#define SFD_BITMAP_COL 32	//Ŀ¼���λʾͼ������ 32

#define DISKBLOCK_NUM  512	//���̿����� 512

#define BLOCKSIZ  512	//ÿ���С
#define SYSOPENFILE 40  //ϵͳ���ļ����������
#define DIRNUM  128		//ÿ��Ŀ¼�����������Ŀ¼�������ļ�����
#define DIRSIZ  14		//ÿ��Ŀ¼�����ֲ�����ռ�ֽ��������i�ڵ��2���ֽ�
#define PWDSIZ   12		//������
#define PWDNUM   32		//������32�������¼
#define NOFILE  20		//ÿ���û����ɴ�20���ļ������û����ļ�������

#define ADDR_NUM 13		//ÿ��i�ڵ����ָ��13�飬addr[0]~addr[9] Ϊֱ�ӵ�ַ��addr[10]Ϊһ�μ�ַ��addr[11]Ϊ���μ�ַ��addr[12]Ϊ���μ�ַ
#define NHINO  128		//��128��Hash�����ṩ����i�ڵ㣨����Ϊ2���ݣ�
#define USERNUM  10		//�������10���û���¼
#define DINODESIZ  32	//ÿ������i�ڵ���ռ�ֽ�


#define NICFREE  50		//�������п��п������������
#define NICINOD  50		//�������п��нڵ��������
#define DINODESTART 2*BLOCKSIZ  //i�ڵ���ʼ��ַ
#define DATASTART (2+D_INODE_NUM)*BLOCKSIZ //Ŀ¼���ļ�����ʼ��ַ

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <stack>
#include <stdio.h>
#include <fstream>
#include <sstream>


using namespace std;

//��ͨ���̿飬���ļ�
struct DISK_BLOCK
{
	string content="";		//�ļ�����
	int content_len=0;	//�ļ���С���ڿ���ռ���˶��Ŀռ䣩
};

//�ļ�Ŀ¼��
struct SFD_ITEM {
	string file_name;	//�ļ���
	int file_id;		//�����ڵ���ID
};

//Ŀ¼�ṹ
struct SFD {
	int sfd_num;		//SFD_ITEM������
	vector<SFD_ITEM> sfd_list;		//Ŀ¼�µ�Ŀ¼��SFD_ITEM��
};

//����i�ڵ�
struct DISK_BFD_ITEM {		
	int id;					//�ļ�����ʶ��
	int type;				//�ļ����� 0--��ͨ 1--Ŀ¼
	int owner;				//�ļ�������id
	int auth[8];			//8���û��Ĵ�ȡȨ��  0--��Ȩ��  1--��Ȩ��
	int file_len;			//�ļ�����
	int link_count;			//�ļ����Ӽ���
	int last_visited_time;	//���һ�δ�ȡʱ��
	int i_addr[ADDR_NUM];		//�������飨�����ַ--���̿�ţ�
	int sfd_id;				//1-Ŀ¼�ļ��ģ�ָ���SFD��ID
};

//�ڴ�i�ڵ�
struct MEM_BFD_ITEM {
	int id;					//�ļ�����ʶ��
	int type;				//�ļ����� 0--��ͨ 1--Ŀ¼
	int auth[8];			//8���û��Ĵ�ȡȨ��  0--��Ȩ��  1--��Ȩ��
	int owner;				//�ļ�������id
	int i_addr[ADDR_NUM];		//�������飨�����ַ--���̿�ţ�
	int file_len;			//�ļ�����
	int link_count;			//�ļ����Ӽ���
	int last_visited_time;	//���һ�δ�ȡʱ��

	int index_num;			//�����ڵ���--hash����ڵ��
	int status_lock;		//0--unlocked��1--locked
	int status_mod;			//0--unmod��1--mod
	int shared_count;		//�������

	struct MEM_BFD_ITEM* next;	//˫��hash����ڵ�ָ��--��һ��
	struct MEM_BFD_ITEM* prev;	//˫��hash����ڵ�ָ��--��һ��
};

//������
struct SPUERBLOCK
{
	int iNode_num;					//i�ڵ������
	int free_iNode_num;				//����i�ڵ���
	int iNode_bitmap[INODE_BITMAP_ROW][INODE_BITMAP_COL];	//i�ڵ�λʾͼ [16][8]  0--Ϊ���У�1--Ϊ��ռ��

	int sfd_item_num;				//Ŀ¼�ڵ������
	int free_sfd_item_num;			//����Ŀ¼�ڵ���
	int SFD_bitmap[SFD_BITMAP_ROW][SFD_BITMAP_COL];		//Ŀ¼�ڵ�λʾͼ  0--Ϊ���У�1--Ϊ��ռ��

	int diskblock_num;				//���̿������
	int free_diskblock_num;			//���д��̿���
	vector<int> free_diskblock_id;	//���д��̿��id����
	//��������ڴ�ջ
	int stack_size = 1;				//��������ڴ�ջ���0
	stack<int> free_block_stack;	//�ڴ�ջ
};

//�����ļ���
struct FILE_SYSTEM {
	SPUERBLOCK superBlock;			//������
	DISK_BFD_ITEM iNode[D_INODE_NUM];	//�������������������Ϊ128��
	SFD SFD[SFD_NUM];	//Ŀ¼��,����Ϊ512��
	DISK_BLOCK diskBlock[DISKBLOCK_NUM + 1];	//�ļ���,����Ϊ512��
};

extern FILE_SYSTEM fileSystem;		//���������ļ����ȫ�ֱ���


//**************************��ʼ��ģ��***************************
void initSuperBlock();      //��ʼ��������
void initINode();           //��ʼ��i���
void initDiskBlock();       //��ʼ�����̿�
void initSFD();             //��ʼ��SFD
void init();                //��ʼ��

#endif