#include "OS.h"

//Ϊ�����ļ���Ŀ¼��ʼ��i���
void createInitINode(int iNode_id, int type, int filelen)
{
	fileSystem.iNode[iNode_id].id = iNode_id;//i�ڵ��id�������������id
	fileSystem.iNode[iNode_id].type = type;	 //�ļ����� 0-��ͨ 1-Ŀ¼
	fileSystem.iNode[iNode_id].owner = user.user_id;//�ļ�������
	for (int i = 1; i <= 8; i++) 
		fileSystem.iNode[iNode_id].auth[i] = 0;//ȫ��user����Ȩ��
	fileSystem.iNode[iNode_id].auth[user.user_id] = 1;//����������Ȩ��

	fileSystem.iNode[iNode_id].file_len = filelen;//�ļ�����
	fileSystem.iNode[iNode_id].link_count = 0;//���Ӵ��� = 0
	fileSystem.iNode[iNode_id].last_visited_time = 0;//���һ�δ�ȡʱ�䣨��ǰʱ�䣩
	for (int i = 0; i < ADDR_NUM; i++)
		fileSystem.iNode[iNode_id].i_addr[i] = -1;//ʹ�õĴ�����Դ
}

//�����ļ�
int createFile(string fileName) 
{

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

int createSFD(DISK_BFD_ITEM iNode,string name) {
	SFD_ITEM temp;
	temp.file_name = name;		//�ļ�������
	temp.file_id = iNode.id;			//SFD_ITEM��id����i�ڵ��id
	fileSystem.SFD[sfd_pointer].sfd_list.push_back(temp);		//�����sfd_item���뵱ǰĿ¼��SFD�µ�sfd_list����
	fileSystem.SFD[sfd_pointer].sfd_num++;		//��ǰĿ¼��SFD�µ�sfd_item����++
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
