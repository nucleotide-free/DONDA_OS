#include "OS.h"

//Ϊ�����ļ���Ŀ¼��ʼ��i���
void createInitINode(int useINode, int type, int filelen)
{

}

//�����ļ�
int createFile(string fileName) 
{

}

//�����ļ��ĵ�һ��������
int createFirstIndexBlock() {        

}

//Ϊ�´������ļ�����һ��i���
int createiNode() 
{              
	if (fileSystem.superBlock.free_diskblock_num == 0) {//û�п��д��̿�
		cout << "û�п��д��̿飡\n";
		return -1;
	}
	if (fileSystem.superBlock.free_iNode_num == 0) {//û�п���i�ڵ�
		cout << "û�п��д��̿飡\n";
		return -1;
	}
	//����һ��i�ڵ�

}

int checkExitsfd(string name) {}  //��ѯ��ǰĿ¼��һ�̶������ļ��±�
int* getIaddr(int indexnum) {}     //�õ���ɾ���ļ����������еĴ��̿������

//ɾ���ļ�
int freeFile(string fileName) {

}
//ɾ����ɾ���ļ���Ӧ��i��㼰��ָ��Ĵ��̿�
void deleteiNode(int pos)      
{

}
//����ɾ�����ɾ���ļ�������ļ�Ŀ¼
void findSinglesfd(int inodeNo) {

}
