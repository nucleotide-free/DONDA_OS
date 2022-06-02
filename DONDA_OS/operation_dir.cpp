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
	for (int i = 0; i < SFD_BITMAP_ROW; i++) {
		for (int j = 0; j < SFD_BITMAP_COL; j++)
			if (fileSystem.superBlock.SFD_bitmap[i][j] == 0) {//��λʾͼ���ҵ�һ�����е�i�ڵ�
				fileSystem.superBlock.SFD_bitmap[i][j] = 1;//����Ϊ��ռ��
				sfd_id = i * SFD_BITMAP_COL + j;
				fileSystem.superBlock.free_sfd_item_num--;//����i�ڵ��� -1
				break;
			}
		if (sfd_id != -1)break;
	}
	createSFD(iNode_id, fileName);
	return 0;
}

//����ɾ��һ��Ŀ¼������Ŀ¼�����ļ�
void deleteDir(int id) {
	int iNode_id = id;
	int SFD_id = fileSystem.iNode[iNode_id].id;
	//if(fileSystem.iNode[iNode_id].type==0)
	for (int i = 0; i < fileSystem.SFD[SFD_id].sfd_num; i++)
	{
		string sub_file_name = fileSystem.SFD[SFD_id].sfd_list[i].file_name;		//Ҫɾ����Ŀ¼�е��ļ���Ŀ¼��
		int sub_iNode_id = findiNodeByName(id,sub_file_name);
		if (fileSystem.iNode[sub_iNode_id].type == 0) {		//���iNode_typeΪ0������ͨ�ļ�����ֱ��ɾ��
			deleteDiskBlock(sub_iNode_id);	//���մ��̿�
			deleteiNode(sub_iNode_id);		//����i�ڵ�
			deleteSFD_ITEM(sub_iNode_id);	//����SFD����
		}
		else 
			deleteDir(sub_iNode_id);		//���iNode_typeΪ1����Ŀ¼�ļ����͵ݹ����
	}
	deleteiNode(iNode_id);		//ɾ����ǰĿ¼��iNode
	deleteSFD_ITEM(iNode_id);	
	deleteSFD(iNode_id);
}

//ɾ��һ����SFD
void deleteSFD(int iNode_id)
{
	fileSystem.SFD[iNode_id].sfd_num = 0;
	fileSystem.SFD[iNode_id].sfd_list.clear();
	fileSystem.superBlock.SFD_bitmap[iNode_id / SFD_BITMAP_COL][iNode_id % SFD_BITMAP_COL] = 0;//�ͷ�λʾͼ��Դ
	fileSystem.superBlock.free_sfd_item_num++;
}

