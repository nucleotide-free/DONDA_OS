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
	fileSystem.superBlock.stack_size = 1;				//��ʼ��ջ�ڿ��п�����
	fileSystem.superBlock.free_diskblock_id.clear();	//���id����
	while (!fileSystem.superBlock.free_block_stack.empty()) {//���ջ
		fileSystem.superBlock.free_block_stack.pop();
	}
	fileSystem.superBlock.free_block_stack.push(-1);	//���һ���鳤�飬�ײ�Ԫ��Ϊ -1��û�и��������Դ��
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
	freopen_s(&stream, "CON", "r", stdin);//�ض��򵽿���̨
	cin.clear();//��ջ�����
}

//��ʼ��SFD
void initSFD() {

	for (int i = 0; i < SFD_NUM; i++) {//���SFD����
		fileSystem.SFD[i].sfd_num = 0;
		fileSystem.SFD[i].sfd_list.clear();
	}
	for (int i = 1; i <= 8; i++) {		
		SFD_ITEM sfd_item;	//��Ŀ¼
		sfd_item.file_name = "root" + to_string(i);
		sfd_item.file_id = i;
		fileSystem.SFD[0].sfd_list.push_back(sfd_item);   //ÿ���û����ļ�Ŀ¼������sfd��̬����
		fileSystem.SFD[0].sfd_num++;
	}
	sfd_stack.push_back(0);

	freopen_s(&stream, "Data\\SFD.txt", "r", stdin);
	int SFD_id;
	while (cin >> SFD_id) {
		cin >> fileSystem.SFD[SFD_id].sfd_num;	//SFD���������
		for (int j = 0; j < fileSystem.SFD[SFD_id].sfd_num; j++) {	//SFD����ľ�����Ϣ
			SFD_ITEM sfd_item;
			cin >> sfd_item.file_name;
			cin >> sfd_item.file_id;
			fileSystem.SFD[SFD_id].sfd_list.push_back(sfd_item);	//�ٶ�ȡĿ¼����ļ���
		}

	}
	std::fclose(stdin);//�ر��ض�������
	freopen_s(&stream, "CON", "r", stdin);//�ض��򵽿���̨
	cin.clear();//��ջ�����
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
	freopen_s(&stream, "CON", "r", stdin);//�ض��򵽿���̨
	cin.clear();//��ջ�����
}

//��ʼ�����̿�
void initDiskBlock() {
	ifstream file;
	file.open("Data\\DiskBlock.txt", ios::in);
	if (!file.is_open()) {//���ļ��ɹ�
		cout << "��DiskBlock�ļ�ʧ�ܣ�";
		exit(0);
	}
	string content;
	for (int i = 0; i < 512; i++)
	{
		if (!count(fileSystem.superBlock.free_diskblock_id.begin(), fileSystem.superBlock.free_diskblock_id.end(), i))//�ж�i�Ƿ���ڳ������еĿ��д��̿�vector�У���û�оͶ��ļ���
		{
			file >> fileSystem.diskBlock[i].content_len;		//�ȶ�ȡ�ļ��Ĵ�С
			char content;
			content = file.get();
			while((content = file.get()) != '$')
			 {
				fileSystem.diskBlock[i].content +=  content;  //�ļ�����
			 }
		}
	}
	file.close();
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
	freopen_s(&stream, "CON", "r", stdin);//�ض��򵽿���̨
	cin.clear();//��ջ�����
}

void init()
{
	initUsers();
	initSuperBlock();
	initSFD();
	initINode();
	initDiskBlock();
	initMEM_iNode_list();
}

//��ʽ��
void format()
{
	ofstream file;
	file.open("Data\\USER.txt", ios::out | ios::trunc);	//�û� - ��ʽ��
	if (file.is_open()) {//���ļ��ɹ�
		for (int i = 1; i <= 8; i++) {
			file << "user" << i << " ";
			file << i << endl;
		}
	}
	file.close();

	file.open("Data\\iNode.txt", ios::out | ios::trunc);	//��ʽ��iNode
	if (file.is_open()) {//���ļ��ɹ�
		file << "0 1 0  0 0 0 0 0 0 0 0  8 0 2022/5/30,14:21:30\n";
		file << "1 1 1  1 0 0 0 0 0 0 0  0 0 2022/5/30,14:21:31\n";
		file << "2 1 2  0 1 0 0 0 0 0 0  0 0 2022/5/30,14:21:32\n";
		file << "3 1 3  0 0 1 0 0 0 0 0  0 0 2022/5/30,14:21:33\n";
		file << "4 1 4  0 0 0 1 0 0 0 0  0 0 2022/5/30,14:21:34\n";
		file << "5 1 5  0 0 0 0 1 0 0 0  0 0 2022/5/30,14:21:35\n";
		file << "6 1 6  0 0 0 0 0 1 0 0  0 0 2022/5/30,14:21:36\n";
		file << "7 1 7  0 0 0 0 0 0 1 0  0 0 2022/5/30,14:21:37\n";
		file << "8 1 8  0 0 0 0 0 0 0 1  0 0 2022/5/30,14:21:38\n";

	}
	file.close();

	file.open("Data\\superBlock.txt", ios::out | ios::trunc);	//������ - ��ʽ��
	if (file.is_open()) {//���ļ��ɹ�
		file << "119\n";
		for (int i = 9; i < 128; i++)//����i�ڵ�
			file << i << "    ";
		file << "\n503\n";
		for (int i = 9; i < 512; i++)//����SFD
			file << i << "    ";
		file << "\n512\n";
		for (int i = 0; i < 512; i++)//���д��̿�
			file << i << "    ";
	}
	file.close();

	file.open("Data\\DiskBlock.txt", ios::out | ios::trunc);	//���̿� - ��ʽ��
	if (!file.is_open()) {//���ļ��ɹ�
		cout << "��ʽ�������ļ�����";
		exit(0);
	}
	file.close();

	file.open("Data\\SFD.txt", ios::out | ios::trunc);	//SFD - ��ʽ��
	if (!file.is_open()) {//���ļ��ɹ�
		cout << "��ʽ��SFD�ļ�����";
		exit(0);
	}
	file.close();
}

void initMEM_iNode_list() {
	for (int i = 0; i < NHINO; i++) {
		MEM_BFD_ITEM m_iNode;
		m_iNode.id = 0;
		m_iNode.type = 99;		//�ļ����� 0-��ͨ 1-Ŀ¼
		mem_iNode[i] = m_iNode;
	}
}



