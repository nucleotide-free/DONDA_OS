#include "OS.h"

using namespace std;

//��ʼ��������
void initSuperBlock(){
	FILE* stream1;
	freopen_s(&stream1,"superBlock.txt", "r", stdin);//�ļ��ض���

	fileSystem.superBlock.iNode_num = D_INODE_NUM;	//����i�ڵ�����
	cin >> fileSystem.superBlock.free_iNode_num;	//�ռ�i�ڵ���
	for (int i = 0; i < INODE_BITMAP_ROW; i++)		//��ʼ��i�ڵ�λʾͼ��ȫ����ռ��-1
		for (int j = 0; j < INODE_BITMAP_COL; j++)
			fileSystem.superBlock.iNode_bitmap[i][j] = 1;
	for (int i = 0; i < fileSystem.superBlock.free_iNode_num; i++) {//���ļ���������е�i�ڵ���
		int block_no;
		cin >> block_no;
		fileSystem.superBlock.iNode_bitmap[block_no / INODE_BITMAP_COL][block_no % INODE_BITMAP_COL] = 0;//����
	}

	fileSystem.superBlock.sfd_item_num = SFD_NUM;	//Ŀ¼�ڵ�����
	cin >> fileSystem.superBlock.free_sfd_item_num;	//����Ŀ¼�ڵ���
	for (int i = 0; i < SFD_BITMAP_ROW; i++)		//��ʼ��Ŀ¼�ڵ�λʾͼ��ȫ����ռ��-1
		for (int j = 0; j < SFD_BITMAP_COL; j++)
			fileSystem.superBlock.SFD_bitmap[i][j] = 1;
	for (int i = 0; i < fileSystem.superBlock.free_sfd_item_num; i++) {//���ļ���������е�Ŀ¼�ڵ���
		int block_no;
		cin >> block_no;
		fileSystem.superBlock.SFD_bitmap[block_no / SFD_BITMAP_COL][block_no % SFD_BITMAP_COL] = 0;//����
	}

	fclose(stdin);//�ر��ض�������


}

//��ʼ��SFD
void initSFD() {

}

//��ʼ��I�ڵ�
void initINode() {

}

//��ʼ�����̿�
void initDiskBlock() {
	freopen("DiskBlock.txt", "r", stdin);
	string content;
	int  content_len;
	for (int i = 0; i < 512; i++)
	{
		if (!count(fileSystem.superBlock.free_diskblock_id.begin(), fileSystem.superBlock.free_diskblock_id.end(), i))//�ж�i�Ƿ���ڳ������еĿ��д��̿�vector�У���û�оͶ��ļ���
		{
			cin >> fileSystem.diskBlock[i].content_len;		//�ȶ�ȡ�ļ��Ĵ�С
			{
				string content;
				for (int j = 0; j < fileSystem.diskBlock[i].content_len; j++)
				{
					cin >> content;//�ٻ�ȡ�ļ����ݡ�
					fileSystem.diskBlock[i].content = " " + fileSystem.diskBlock[i].content + " " + content + " ";  //�ļ�����
				}
			}
		}
	}
}