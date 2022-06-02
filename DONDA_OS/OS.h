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
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include <string.h>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <direct.h>


using namespace std;

//�û�
struct USER {
	int user_id;		//�û�id
	string password;	//�û�����
	string user_name;	//��½�õ��û���
	vector<int> file_Uopened;		//�û����ļ�������ŵ���iNode_id
};

//��ͨ���̿飬���ļ�
struct DISK_BLOCK
{
	string content = "";	//�ļ�����
	int content_len = 0;	//�ļ���С���ڿ���ռ���˶��Ŀռ䣩���СΪ512�����content_len����С��512
};

//�ļ�Ŀ¼��
struct SFD_ITEM {
	string file_name;	//�ļ���
	int type;		//0--��ͨ���ͣ�1--��������
	int file_id;		//�����ڵ���ID
};

//Ŀ¼�ṹ
struct SFD {
	int sfd_num;		//SFD_ITEM������
	vector<SFD_ITEM> sfd_list;		//Ŀ¼�µ�Ŀ¼��SFD_ITEM��
};

//ϵͳ�ļ��򿪱����
struct FILE_OPEND {
	string fileName;	//�ļ�����		
	int f_count;		//���ʴ���
	int f_inode;		//��Ӧ��iNode
};

//����i�ڵ�
struct DISK_BFD_ITEM {		
	int id;					//�ļ�����ʶ����ָ���SFD��ID
	int type;				//�ļ����� 0--��ͨ 1--Ŀ¼
	int owner;				//�ļ�������id
	int auth[9];			//8���û��Ĵ�ȡȨ��  0--��Ȩ��  1--��Ȩ��
	int file_len;			//�ļ�����
	int link_count;			//�ļ����Ӽ���
	string last_visited_time;	//���һ�δ�ȡʱ��
	int i_addr[ADDR_NUM];		//�������飨�����ַ--���̿�ţ�
};

//�ڴ�i�ڵ�
struct MEM_BFD_ITEM {
	int id;					//�ļ�����ʶ����ָ���SFD��ID
	int type;				//�ļ����� 0--��ͨ 1--Ŀ¼
	int owner;				//�ļ�������id
	int auth[9];			//8���û��Ĵ�ȡȨ��  0--��Ȩ��  1--��Ȩ��
	int file_len;			//�ļ�����
	int link_count;			//�ļ����Ӽ���
	string last_visited_time;	//���һ�δ�ȡʱ��
	int i_addr[ADDR_NUM];		//�������飨�����ַ--���̿�ţ�

	int index_num;			//�����ڵ���--hash����ڵ��
	int status_lock;		//0--unlocked��1--дlocked ,2--��locked
	int status_mod;			//0--unmod��1--mod
	int shared_count;		//�������

	//struct MEM_BFD_ITEM* next;	//˫��hash����ڵ�ָ��--��һ��
	//struct MEM_BFD_ITEM* prev;	//˫��hash����ڵ�ָ��--��һ��
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
	DISK_BLOCK diskBlock[DISKBLOCK_NUM];	//�ļ���,����Ϊ512�� ,��Ϊ�����������һ����-1
};

extern FILE_SYSTEM fileSystem;	//���������ļ����ȫ�ֱ���
extern FILE* stream;
extern string clipBoard;		//���а�
extern string clip_fileName;	//���а����ļ�������
extern SFD_ITEM link_board;     //������Ҫ���ӵ�����
extern int sfd_pointer;			//sfdָ��--ָ��ǰ��sfdĿ¼
extern USER user;				//��ǰ�û�
extern USER userList[9];		//�����û�
extern vector<int> sfd_stack;	//Ŀ¼ջ
extern vector<FILE_OPEND> file_opend_list;		//ϵͳ���ļ���
extern MEM_BFD_ITEM mem_iNode[NHINO];	//�ڴ�i�ڵ���������Ϊ128��

//**************************��ʼ��ģ��***************************
void initSuperBlock();	//��ʼ��������
void initINode();       //��ʼ��i���
void initDiskBlock();   //��ʼ�����̿�
void initSFD();         //��ʼ��SFD
void initUsers();		//��ʼ���û���Ϣ
void init();            //��ʼ��
void format();			//��ʽ��
void initMEM_iNode_list();//��ʼ���ڴ�iNode��ϣ����

//************************** �û�ģ�� *****************************
void login();					//��¼
char* getpassword(char* pasw);	//�������뻯

//************************** ����ģ�� *****************************
void commandCategory();		//��ʾ����Ŀ¼
void display();				//����������������ʵ�ִ󲿷������������
void textColor(int color);	//����������ɫ
int input_command(string& instruction, string& fileName1, string& fileName2);//�û�����������ж�

//************************** �����ģ�� *****************************
void FreeABlock(int BlockNo);		//��������--���տ��п�
int AllocateOneBlock();				//��������--������п�
int ReadABlock(stack<int> free_block_stack, int block_num);	//��ȡ�鳤��

//**************************�ļ��Ĵ�����ɾ��ģ��*****************************
int createFile(string fileName);				//�����ļ�
void createInitINode(int iNode_id, int type);	//��ʼ��i���
int createiNode(int type);						//����һ��i���
void createSFD(int iNode_id, string name);		//����һ��SFD���
string getTime();								//��ȡ��ǰʱ��

void deleteFile(string fileName);		//ɾ���ļ�
void deleteDiskBlock(int iNode_id);		//���մ��̿�
void deleteSFD_ITEM(int file_id);		//����SFD����
void deleteiNode(int iNode_id);			//����i���
//void findSinglesfd(int inodeNo);		//����ɾ�����ɾ���ļ�������ļ�Ŀ¼

void openFile(string fileName);			//���ļ�
void closeFIle(string fileName);		//�ر��ļ�
int checkOpen(int iNode_id);			//����ļ��Ƿ񱻴�
MEM_BFD_ITEM initMEM_iNode(int iNode_id); 	 //����iNode�����ڴ棬��ʼ���ڴ�iNode
void updateFileOpened(MEM_BFD_ITEM m_iNode, string fileName);//�޸��û����ļ����ϵͳ���ļ���
int checkUserOpen(int iNode_id);		//����ļ��Ƿ�ĳ���û���

void showSystemFileOpen();

//************************** �ļ��Ķ�дģ�� *****************************
int findiNodeByName(string fileName);		//ͨ���ļ�����������i�ڵ�
int findiNodeByName(int std_pointer,string fileName);  //ͨ��iNode_id��������i�ڵ�
int findSFD_item_idByName(string fileName);	//ͨ���ļ�����������sfd_item_id

void writeFile(string fileName);			//дָ���ļ������ļ�
void readFile(string fileName);				//���ļ����ݺ���
void tempToDiskBlock(string fileName);		//��temp�ļ��������д�����̿���
string contentBuffer(int iNode_id);			//��������ָ��Ĵ��̿������д��buffer
vector<int> ReadIndexBlock(string content);	//һ��������ȡ������
void renameFile(string fileName1, string fileName2);	//�ļ�������
void find(string fileName1, string file_list,int temp);		//�����ļ�·��

//************************** Ŀ¼�Ĵ�����ɾ��ģ�� *****************************
int createDir(string fileName);		//����һ��Ŀ¼
void deleteDir(int id);				//����ɾ��һ��Ŀ¼������Ŀ¼�����ļ�
void deleteSFD(int iNode_id);		//ɾ��һ����SFD

//************************** ���а� ********************************
void cut(string fileName);		//�����ļ�
int copy(string fileName);		//�����ļ�
void paste();					//ճ���ļ�

//************************* link ******************************
void createLink(string fileName);//�½�����
void pasteLink();//ճ�������ļ�����ǰĿ¼
int deleteLink(string fileName);	//ɾ�����ӣ��ж��Ƿ��������ļ�
int checkValid(string fileName);	//����ļ��Ƿ�ʧЧ,1-ʧЧ��0-����

//************************** �����ļ�ϵͳ *****************************
void saveFileSystem();	//�����ļ�ϵͳ
void saveUser();		//�����û���Ϣ
void saveSuperBlcok();	//���泬�������Ϣ
void saveiNode();		//����i�ڵ���Ϣ
void saveSFD();			//����SFD
void saveDiskBlock();	//������̿�

#endif
