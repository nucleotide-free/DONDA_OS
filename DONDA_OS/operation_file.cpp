#include "OS.h"

//Ϊ�����ļ���Ŀ¼ ��ʼ��i���
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
	fileSystem.iNode[iNode_id].last_visited_time = getTime();//���һ�δ�ȡʱ�䣨��ǰʱ�䣩
	for (int i = 0; i < ADDR_NUM; i++)
		fileSystem.iNode[iNode_id].i_addr[i] = -1;//ʹ�õĴ�����Դ
}

//�����ļ�
int createFile(string fileName) 
{
	int name_fileName = -1;
	for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++)
	{
		if (fileName == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name)
		{
			name_fileName = 1;
		}
	};
	return 0;
}


//Ϊ�´������ļ�����һ��i��㣬����i�ڵ��ţ�-1Ϊû�ҵ�
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
	
	int iNode_id = -1;//�µ�i�ڵ���
	for(int i =0;i< INODE_BITMAP_ROW;i++)
		for(int j=0;j< INODE_BITMAP_COL;j++)
			if (fileSystem.superBlock.iNode_bitmap[i][j] == 0) {//��λʾͼ���ҵ�һ�����е�i�ڵ�
				fileSystem.superBlock.iNode_bitmap[i][j] = 1;//����Ϊ��ռ��
				iNode_id = i * INODE_BITMAP_COL + j;
				fileSystem.superBlock.free_iNode_num--;//����i�ڵ��� -1
				break;
			}
	createInitINode(iNode_id, 0, 0);//Ϊ�����ļ���Ŀ¼��ʼ��i��㣬����Ϊ0����ʾ�ļ�������Ϊ0����ʼ��i���
	return iNode_id;
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
	return 0;
}
//ɾ����ɾ���ļ���Ӧ��i��㼰��ָ��Ĵ��̿�
void deleteiNode(int pos)      
{

}
//����ɾ�����ɾ���ļ�������ļ�Ŀ¼
void findSinglesfd(int inodeNo) {

}

//��ȡ��ǰʱ��
string getTime() {		
	time_t time_seconds = time(0);
	tm now_time;
	localtime_s(&now_time, &time_seconds);

	std::stringstream ss;
	ss << now_time.tm_year + 1900 << "-" << now_time.tm_mon + 1 << "-"
		<< now_time.tm_mday << "," << now_time.tm_hour << ":"
		<< now_time.tm_min << ":" << now_time.tm_hour;
	return  ss.str();
}
