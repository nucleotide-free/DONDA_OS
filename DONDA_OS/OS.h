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
#define NADDR 10		//ÿ��i�ڵ����ָ��10�飬addr[0]~addr[9]
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

struct SFD_item {
	string file_name;	//�ļ���
	int file_id;		//�����ڵ���ID
};

struct BFD_item {		//i�ڵ�
	int file_id;

};

#endif