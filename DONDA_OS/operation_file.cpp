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

void createSFD(DISK_BFD_ITEM iNode,string name) {
	SFD_ITEM temp;
	temp.file_name = name;		//�ļ�������
	temp.file_id = iNode.id;			//SFD_ITEM��id����i�ڵ��id
	fileSystem.SFD[sfd_pointer].sfd_list.push_back(temp);		//�����sfd_item���뵱ǰĿ¼��SFD�µ�sfd_list����
	fileSystem.SFD[sfd_pointer].sfd_num++;		//��ǰĿ¼��SFD�µ�sfd_item����
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
