#pragma once
#ifndef OS_H
#define OS_H

#define BLOCKSIZ  512	//ÿ���С
#define SYSOPENFILE 40  //ϵͳ���ļ����������
#define DIRNUM  128		//ÿ��Ŀ¼�����������Ŀ¼�������ļ�����
#define DIRSIZ  14		//ÿ��Ŀ¼�����ֲ�����ռ�ֽ��������i�ڵ��2���ֽ�
#define PWDSIZ   12		//������
#define PWDNUM   32		//������32�������¼
#define NOFILE  20		//ÿ���û����ɴ�20���ļ������û����ļ�������
#define NADDR 13		//ÿ��i�ڵ����ָ��13�飬addr[0]~addr[9] Ϊֱ�ӵ�ַ��addr[10]Ϊһ�μ�ַ��addr[11]Ϊ���μ�ַ��addr[12]Ϊ���μ�ַ
#define NHINO  128		//��128��Hash�����ṩ����i�ڵ㣨����Ϊ2���ݣ�
#define USERNUM  10		//�������10���û���¼
#define DINODESIZ  32	//ÿ������i�ڵ���ռ�ֽ�
#define DINODEBLK  32	//���д���i�ڵ㹲ռ32�������
#define FILEBLK  512	//����512��Ŀ¼�ļ������
#define NICFREE  50		//�������п��п������������
#define NICINOD  50		//�������п��нڵ��������
#define DINODESTART 2*BLOCKSIZ  //i�ڵ���ʼ��ַ
#define DATASTART (2+DINODEBLK)*BLOCKSIZ //Ŀ¼���ļ�����ʼ��ַ

#include <string>

using namespace std;

struct SFD_ITEM {
	string file_name;	//�ļ���
	int file_id;		//�����ڵ���ID
};

struct DISK_BFD_ITEM {		//����i�ڵ�
	int id;		//�ļ�����ʶ��
	int type;		//�ļ����� 0--��ͨ 1--Ŀ¼
	int auth[8];		//8���û��Ĵ�ȡȨ��  0--��Ȩ��  1--��Ȩ��
	int owner;		//�ļ�������id
	int i_addr[NADDR];		//�������飨�����ַ--���̿�ţ�
	int file_len;		//�ļ�����
	int link_count;		//�ļ����Ӽ���
	int last_visited_time;		//���һ�δ�ȡʱ��
};
struct MEM_BFD_ITEM {		//�ڴ�i�ڵ�

	int id;		//�ļ�����ʶ��
	int type;		//�ļ����� 0--��ͨ 1--Ŀ¼
	int auth[8];		//8���û��Ĵ�ȡȨ��  0--��Ȩ��  1--��Ȩ��
	int owner;		//�ļ�������id
	int i_addr[NADDR];		//�������飨�����ַ--���̿�ţ�
	int file_len;		//�ļ�����
	int link_count;		//�ļ����Ӽ���
	int last_visited_time;		//���һ�δ�ȡʱ��

	int index_num;		//�����ڵ���--hash����ڵ��
	int status_lock;		//0--unlocked��1--locked
	int status_mod;		//0--unmod��1--mod
	int shared_count;		//�������

	struct MEM_BFD_ITEM* next;		//˫��hash����ڵ�ָ��--��һ��
	struct MEM_BFD_ITEM* prev;		//˫��hash����ڵ�ָ��--��һ��

};

#endif