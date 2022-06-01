#include "OS.h"


//��ʼ��������
void initSuperBlock(){

	freopen_s(&stream,"Data\\superBlock.txt", "r", stdin);//�ļ��ض���
	//��������������������������������������������������������������������������������
	fileSystem.superBlock.iNode_num = D_INODE_NUM;	//����i�ڵ�����
	cin >> fileSystem.superBlock.free_iNode_num;	//����i�ڵ���
	for (int i = 0; i < INODE_BITMAP_ROW; i++)		//��ʼ��i�ڵ�λʾͼ��ȫ����ռ��-1
		for (int j = 0; j < INODE_BITMAP_COL; j++)
			fileSystem.superBlock.iNode_bitmap[i][j] = 1;
	for (int i = 0; i < fileSystem.superBlock.free_iNode_num; i++) {//���ļ���������е�i�ڵ���
		int block_no;	//���̿��
		cin >> block_no;
		fileSystem.superBlock.iNode_bitmap[block_no / INODE_BITMAP_COL][block_no % INODE_BITMAP_COL] = 0;//����
	}
	//��������������������������������������������������������������������������������
	fileSystem.superBlock.sfd_item_num = SFD_NUM;	//Ŀ¼�ڵ�����
	cin >> fileSystem.superBlock.free_sfd_item_num;	//����Ŀ¼�ڵ���
	for (int i = 0; i < SFD_BITMAP_ROW; i++)		//��ʼ��Ŀ¼�ڵ�λʾͼ��ȫ����ռ��-1
		for (int j = 0; j < SFD_BITMAP_COL; j++)
			fileSystem.superBlock.SFD_bitmap[i][j] = 1;
	for (int i = 0; i < fileSystem.superBlock.free_sfd_item_num; i++) {//���ļ���������е�Ŀ¼�ڵ���
		int block_no;	//���̿��
		cin >> block_no;
		fileSystem.superBlock.SFD_bitmap[block_no / SFD_BITMAP_COL][block_no % SFD_BITMAP_COL] = 0;//����
	}
	//��������������������������������������������������������������������������������
	fileSystem.superBlock.diskblock_num = DISKBLOCK_NUM;//���̿�����
	cin >> fileSystem.superBlock.free_diskblock_num;	//���д��̿�����
	fileSystem.superBlock.stack_size = 1;			//��ʼ��ջ�ڿ��п�����
	fileSystem.superBlock.free_block_stack.push(0);	//���һ���鳤�飬�ײ�Ԫ��Ϊ 0��û�и��������Դ��
	for (int i = 0; i < fileSystem.superBlock.free_diskblock_num; i++) {//��������
		int block_id;	//���̿��
		cin >> block_id;
		fileSystem.superBlock.free_diskblock_id.push_back(block_id);//������д��̿�����

		if (fileSystem.superBlock.stack_size < 50) {
			fileSystem.superBlock.stack_size++;
			fileSystem.superBlock.free_block_stack.push(block_id);//����
		}
		else {//����鳤�飬�������
			for (int j = 0; j < 50; j++) {
				fileSystem.diskBlock[i].content += to_string(fileSystem.superBlock.free_block_stack.top()) + " ";//��������ļ�
				fileSystem.superBlock.free_block_stack.pop();//��ջ
				fileSystem.diskBlock[i].content_len++;//�޸��ļ�����
			}
			fileSystem.superBlock.stack_size = 1;
			fileSystem.superBlock.free_block_stack.push(block_id);
		}
	}
	std::fclose(stdin);//�ر��ض�������
	cin.clear();
}

//��ʼ��SFD
void initSFD() {

	for (int i = 1; i <= 8; i++) {		
		string tmps;
		stringstream ss;	
		ss << i;
		ss >> tmps;
		SFD_ITEM sfd_item;	//��Ŀ¼
		sfd_item.file_name = "root" + tmps;
		sfd_item.file_id = i;
		fileSystem.SFD[0].sfd_list.push_back(sfd_item);   //ÿ���û����ļ�Ŀ¼������sfd��̬����
		fileSystem.SFD[0].sfd_num++;
	}

	sfd_stack.push_back(fileSystem.SFD[0]);

	freopen_s(&stream, "Data\\SFD.txt", "r", stdin);
	for (int i = 1; i <= 512; i++)
	{
		if (fileSystem.superBlock.SFD_bitmap[i / SFD_BITMAP_COL][i % SFD_BITMAP_COL] != 0)//��SFDλʾͼ���ҵ��ǿ�SFD_ITEM�Ŀ��
		{
			int sfd_num=0;
			cin >> sfd_num; 
			fileSystem.SFD[i].sfd_num = sfd_num;
			for (int j = 0; j < fileSystem.SFD[i].sfd_num; j++) {
				SFD_ITEM sfd_item;
				cin >> sfd_item.file_name;
				cin >> sfd_item.file_id;
				fileSystem.SFD[i].sfd_list.push_back(sfd_item);		//�ٶ�ȡĿ¼����ļ���
			}
		}
	}
	std::fclose(stdin);//�ر��ض�������
	cin.clear();
}

//��ʼ��I�ڵ�
void initINode() {
	freopen_s(&stream, "Data\\iNode.txt", "r", stdin);//�ļ��ض���
	for (int i = 0; i < D_INODE_NUM; i++){
		if (fileSystem.superBlock.iNode_bitmap[i / INODE_BITMAP_COL][i % INODE_BITMAP_COL] == 1) {//��i�ڵ㱻ռ��
			cin >> fileSystem.iNode[i].id;		//i�ڵ��ID
			cin >> fileSystem.iNode[i].type;	//�ļ�����
			cin >> fileSystem.iNode[i].owner;	//�ļ�ӵ����
			for (int j = 1; j <= 8; j++)
				cin >> fileSystem.iNode[i].auth[j];	//authorization
			cin >> fileSystem.iNode[i].file_len;	//�ļ�����
			cin >> fileSystem.iNode[i].link_count;	//�ļ����Ӵ���
			cin >> fileSystem.iNode[i].last_visited_time;	//���һ�δ�ȡʱ��
			if (fileSystem.iNode[i].type == 0)		//0-��ͨ�ļ��������
				for (int j = 0; j < ADDR_NUM; j++)
					cin >> fileSystem.iNode[i].i_addr[j];	//���̿�ţ�ָ��diskBlock
		}
	}
	std::fclose(stdin);//�ر��ض�������
	cin.clear();
}

//��ʼ�����̿�
void initDiskBlock() {
	freopen_s(&stream, "Data\\DiskBlock.txt", "r", stdin);
	string content;
	for (int i = 1; i <= 512; i++)
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
	std::fclose(stdin);//�ر��ض�������
	cin.clear();
}

//��ʼ���û���Ϣ�б�
void initUsers()
{
	freopen_s(&stream, "Data\\USER.txt", "r", stdin);//��ȡ8���û�����Ϣ
	for (int i = 1; i <= 8; i++) {
		userList[i].user_id = i;
		cin >> userList[i].user_name;
		cin >> userList[i].password;
	}
	std::fclose(stdin);//�ر��ض�������
	cin.clear();
}

void init()
{
	initSuperBlock();
	initSFD();
	initINode();
	initDiskBlock();
	initUsers();
	freopen_s(&stream, "CON", "r", stdin);//�ض��򵽿���̨
	cin.clear();//��ջ�����
}