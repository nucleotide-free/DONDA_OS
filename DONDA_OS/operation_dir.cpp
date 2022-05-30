#include "OS.h"


//����һ��Ŀ¼
int createDir(string fileName) {
	if (fileSystem.superBlock.free_iNode_num == 0|| fileSystem.superBlock.free_sfd_item_num == 0) {
		cout << "i�ڵ��Ŀ¼�ռ䲻�㣬����ʧ�ܣ�\n";
		return 0;
	}
	
	int flag_fileName = -1;//��ѯ�Ƿ�����
	for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++)
		if (fileName == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name)
			flag_fileName = 1;

	if (flag_fileName == -1) {//û������
		int iNode_id = createiNode(1);//����Ŀ¼�ļ���i�ڵ�;
		if (iNode_id == -1) {
			cout << "�ڴ�ռ䲻�㣬����i�ڵ�ʧ�ܣ�\n";
			return 0;
		}
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
		cout << "�����ɹ���\n";
		return 1;
	}
	cout << "Ŀ¼����ͻ��\n";
	return 0;
}

//����ɾ��һ��Ŀ¼������Ŀ¼�����ļ�
int deleteDir(string name) {
	return 1;
}


//ɾ��һ��i���
void deleteINodeOne(int useINode) {
	
}


