#include "OS.h"

//�����û���Ϣ
void saveUser()
{
	freopen_s(&stream, "Data\\USER.txt", "w", stdin);
	for (int i = 1; i <= 8; i++) {
		userList[i].user_id = i;
		cout << userList[i].user_name << " ";
		cout << userList[i].password << endl;
	}
	std::fclose(stdin);//�ر��ض�������
	cin.clear();
	freopen_s(&stream, "CON", "r", stdin);
}

//���泬�������Ϣ
void saveSuperBlcok()
{
	ofstream file;
	file.open("Data\\superBlock.txt", ios::out | ios::trunc);
	if (file.is_open()) {//���ļ��ɹ�
		file << fileSystem.superBlock.free_iNode_num << endl;//����i�ڵ�����
		for (int i = 0; i < INODE_BITMAP_ROW; i++) {//����i�ڵ�λʾͼ
			for (int j = 0; j < INODE_BITMAP_COL; j++) {
				if (fileSystem.superBlock.iNode_bitmap[i][j] == 0)//д�����i�ڵ��ID
					file << i * INODE_BITMAP_COL + j << " ";
			}
		}
		file << endl;
		
		file << fileSystem.superBlock.free_sfd_item_num << endl;//����Ŀ¼�ڵ�����
		for (int i = 0; i < SFD_BITMAP_ROW; i++) {//����Ŀ¼�ڵ�λʾͼ
			for (int j = 0; j < SFD_BITMAP_COL; j++) {
				if (fileSystem.superBlock.SFD_bitmap[i][j] == 0)//д�����Ŀ¼�ڵ��ID
					file << i * SFD_BITMAP_COL + j << " ";
			}
		}
		file << endl;

		file << fileSystem.superBlock.free_diskblock_num << endl;//���д��̿�����
		int block_id;
		fileSystem.superBlock.free_diskblock_id.clear();
		while ((block_id = AllocateOneBlock()) != -1) {//�������п��п飬�������ŵ��ļ�
			file << block_id << " ";
			fileSystem.superBlock.free_diskblock_id.push_back(block_id);
		}
	}
	file.close();
}

//����i�ڵ���Ϣ
void saveiNode()
{
	ofstream file;
	file.open("Data\\iNode.txt", ios::out | ios::trunc);
	if (!file.is_open()) {//���ļ��ɹ�
		cout << "����iNode�ļ�ʧ�ܣ�";
		exit(0);
	}
	for (int i = 0; i < D_INODE_NUM; i++) {
		if (fileSystem.superBlock.iNode_bitmap[i / INODE_BITMAP_COL][i % INODE_BITMAP_COL] == 1) {//��i�ڵ㱻ռ��
			file << fileSystem.iNode[i].id << " ";		//i�ڵ��ID
			file << fileSystem.iNode[i].type << " ";	//�ļ�����
			file << fileSystem.iNode[i].owner << "  ";	//�ļ�ӵ����
			for (int j = 1; j <= 8; j++)
				file << fileSystem.iNode[i].auth[j] << " ";			//authorization
			file << " " << fileSystem.iNode[i].file_len << " ";		//�ļ�����
			file << fileSystem.iNode[i].link_count << " ";			//�ļ����Ӵ���
			file << fileSystem.iNode[i].last_visited_time << "  ";	//���һ�δ�ȡʱ��
			if (fileSystem.iNode[i].type == 0)		//0-��ͨ�ļ��������
				for (int j = 0; j < ADDR_NUM; j++)
					file << fileSystem.iNode[i].i_addr[j]<< " ";	//���̿�ţ�ָ��diskBlock
			file << endl;
		}
	}
	file.close();
}

//����SFD
void saveSFD()
{
	ofstream file;
	file.open("Data\\SFD.txt", ios::out | ios::trunc);
	if (!file.is_open()) {//���ļ��ɹ�
		cout << "����SFD�ļ�ʧ�ܣ�";
		exit(0);
	}
	for (int i = 0; i < SFD_NUM; i++) {
		if (fileSystem.superBlock.SFD_bitmap[i / SFD_BITMAP_COL][i % SFD_BITMAP_COL] == 1) {//��i�ڵ㱻ռ��
			file << fileSystem.SFD[i].sfd_num;
			for (int j = 0; j < fileSystem.SFD[i].sfd_num; j++) {
				file << " " << fileSystem.SFD[i].sfd_list[j].file_name << " ";
				file << " " << fileSystem.SFD[i].sfd_list[j].file_id << " ";
			}
		}
	}
	file.close();
}

//������̿�
void saveDiskBlock()
{
	ofstream file;
	file.open("Data\\DiskBlock.txt", ios::out | ios::trunc);
	if (!file.is_open()) {//���ļ��ɹ�
		cout << "����iNode�ļ�ʧ�ܣ�";
		exit(0);
	}

	string content;
	for (int i = 1; i <= 512; i++)
	{
		if (!count(fileSystem.superBlock.free_diskblock_id.begin(), fileSystem.superBlock.free_diskblock_id.end(), i))//�ж�i�Ƿ���ڳ������еĿ��д��̿�vector�У���û�оͶ��ļ���
		{
			file << fileSystem.diskBlock[i].content_len << " ";		//�ȶ�ȡ�ļ��Ĵ�С
			{
				string content;
				for (int j = 0; j < fileSystem.diskBlock[i].content_len; j++)
				{
					file << content;//�ٻ�ȡ�ļ����ݡ�
					fileSystem.diskBlock[i].content = " " + fileSystem.diskBlock[i].content + " " + content + " ";  //�ļ�����
				}
			}
		}
	}
	file.close();
}

//�����ļ�ϵͳ
void saveFileSystem()
{
	saveUser();
	saveSuperBlcok();
	saveiNode();
	saveSFD();
	saveDiskBlock();
}