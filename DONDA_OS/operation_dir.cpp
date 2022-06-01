#include "OS.h"


//����һ��Ŀ¼
int createDir(string fileName) {
	if (fileSystem.superBlock.free_iNode_num == 0 || fileSystem.superBlock.free_sfd_item_num == 0) {
		return 1;//i�ڵ��Ŀ¼�ռ䲻�㣬����ʧ�ܣ�
	}
	for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {		//��ѯ�Ƿ�����
		if (fileName == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name) {
			return 2;//Ŀ¼����ͻ
		}
	}
	int iNode_id = createiNode(1);//����Ŀ¼�ļ���i�ڵ�;
	if (iNode_id == -1) 
		return 3;//�ڴ�ռ䲻�㣬����i�ڵ�ʧ�ܣ�
	
	int sfd_id = -1;//�µ�i�ڵ���
	for (int i = 0; i < SFD_BITMAP_ROW; i++)
		for (int j = 0; j < SFD_BITMAP_COL; j++)
			if (fileSystem.superBlock.SFD_bitmap[i][j] == 0) {//��λʾͼ���ҵ�һ�����е�i�ڵ�
				fileSystem.superBlock.SFD_bitmap[i][j] = 1;//����Ϊ��ռ��
				sfd_id = i * SFD_BITMAP_COL + j;
				fileSystem.superBlock.free_sfd_item_num--;//����i�ڵ��� -1
				break;
			}
	createSFD(iNode_id, fileName);
	return 0;
}

//����ɾ��һ��Ŀ¼������Ŀ¼�����ļ�
int deleteDir(string name) {
	
}


//ɾ��һ��i���
void deleteINodeOne(int useINode) {
	
}


