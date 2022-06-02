#include "OS.h"

//Ϊ�����ļ���Ŀ¼ ��ʼ��i���
void createInitINode(int iNode_id, int type)
{
	fileSystem.iNode[iNode_id].id = iNode_id;//i�ڵ��id�������������id
	fileSystem.iNode[iNode_id].type = type;	 //�ļ����� 0-��ͨ 1-Ŀ¼
	fileSystem.iNode[iNode_id].owner = user.user_id;//�ļ�������
	for (int i = 1; i <= 8; i++) 
		fileSystem.iNode[iNode_id].auth[i] = 0;//ȫ��user����Ȩ��
	fileSystem.iNode[iNode_id].auth[user.user_id] = 1;//����������Ȩ��

	fileSystem.iNode[iNode_id].file_len = 0;//�ļ�����
	fileSystem.iNode[iNode_id].link_count = 0;//���Ӵ��� = 0
	fileSystem.iNode[iNode_id].last_visited_time = getTime();//���һ�δ�ȡʱ�䣨��ǰʱ�䣩
	for (int i = 0; i < ADDR_NUM; i++)
		fileSystem.iNode[iNode_id].i_addr[i] = -1;//ʹ�õĴ�����Դ
}

//Ϊ�´������ļ�����һ��i��㣬����i�ڵ��ţ�-1Ϊû�ҵ�
int createiNode(int type)
{
	int iNode_id = -1;//�µ�i�ڵ���
	for (int i = 0; i < INODE_BITMAP_ROW; i++) {
		for (int j = 0; j < INODE_BITMAP_COL; j++) {
			if (fileSystem.superBlock.iNode_bitmap[i][j] == 0) {//��λʾͼ���ҵ�һ�����е�i�ڵ�
				fileSystem.superBlock.iNode_bitmap[i][j] = 1;//����Ϊ��ռ��
				iNode_id = i * INODE_BITMAP_COL + j;
				fileSystem.superBlock.free_iNode_num--;//����i�ڵ��� -1
				break;
			}
		}
		if (iNode_id != -1)break;
	}
	createInitINode(iNode_id, type);//Ϊ�����ļ���Ŀ¼��ʼ��i��㣬����Ϊ0����ʾ�ļ�������Ϊ0����ʼ��i���
	return iNode_id;
}

//����SFDĿ¼��
void createSFD(int iNode_id, string name) {
	SFD_ITEM temp;
	temp.file_name = name;		//�ļ�������
	temp.file_id = iNode_id;			//SFD_ITEM��id����i�ڵ��id
	temp.type = 0;				//���ɵ�����ͨĿ¼��
	fileSystem.SFD[sfd_pointer].sfd_list.push_back(temp);		//�����sfd_item���뵱ǰĿ¼��SFD�µ�sfd_list����
	fileSystem.SFD[sfd_pointer].sfd_num++;		//��ǰĿ¼��SFD�µ�sfd_item����
}

//�����ļ���1-�ɹ���0-ʧ��
int createFile(string fileName)
{
	if (fileSystem.superBlock.free_diskblock_num == 0 || fileSystem.superBlock.free_iNode_num == 0) {
		return 1;//û�п��д��̿���߿���i�ڵ㣡
	}
	for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {//��ѯ�Ƿ�����
		if (fileName == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name) {
			return 2;//�ļ�����ͻ
		}
	}
	int iNode_id = createiNode(0);//���䵽һ��i�ڵ�
	createSFD(iNode_id, fileName);
	return 0;
}

//ɾ���ļ�
void deleteFile(string fileName) 
{
	int iNode_id = findiNodeByName(fileName);
	deleteDiskBlock(iNode_id);//���մ��̿�
	deleteiNode(iNode_id);//����i�ڵ�
	deleteSFD_ITEM(iNode_id);//����SFD����
}

//���մ��̿�
void deleteDiskBlock(int iNode_id)
{
	for (int i = 0; i < 10; i++) {//����ֱ�ӵ�ַ�Ĵ��̿�
		if (fileSystem.iNode[iNode_id].i_addr[i] != -1) {//���̿鱻����
			int diskBlock_id = fileSystem.iNode[iNode_id].i_addr[i];
			fileSystem.diskBlock[diskBlock_id].content = "";//��մ��̿�����
			fileSystem.diskBlock[diskBlock_id].content_len = 0;
			FreeABlock(diskBlock_id);//���մ��̿�
		}
	}
	int diskBlock_id;
	if ((diskBlock_id = fileSystem.iNode[iNode_id].i_addr[10]) != -1) {//һ������
		vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[diskBlock_id].content);//��ȡһ�������еĴ��̿���
		for (int i = 0; i < index_block_level1.size(); i++) {//ÿһ�����
			fileSystem.diskBlock[index_block_level1[i]].content = "";//��մ��̿�����
			fileSystem.diskBlock[index_block_level1[i]].content_len = 0;
			FreeABlock(index_block_level1[i]);	//���մ��̿�
			
		}
	}
	if ((diskBlock_id = fileSystem.iNode[iNode_id].i_addr[11]) != -1) {//��������
		vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[diskBlock_id].content);//��ȡһ�������еĴ��̿���
		for (int i = 0; i < index_block_level1.size(); i++) {//ÿһ�����
			vector<int> index_block_level2 = ReadIndexBlock(fileSystem.diskBlock[index_block_level1[i]].content);//��ȡ���������еĴ��̿���
			for (int j = 0; j < index_block_level2.size(); j++) {
				fileSystem.diskBlock[index_block_level2[j]].content = "";//��մ��̿�����
				fileSystem.diskBlock[index_block_level2[j]].content_len = 0;
				FreeABlock(index_block_level2[j]);	//���մ��̿�
			}
		}
	}
	if ((diskBlock_id = fileSystem.iNode[iNode_id].i_addr[12]) != -1) {//��������
		vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[diskBlock_id].content);//��ȡһ�������еĴ��̿���
		for (int i = 0; i < index_block_level1.size(); i++) {//ÿһ�����
			vector<int> index_block_level2 = ReadIndexBlock(fileSystem.diskBlock[index_block_level1[i]].content);//��ȡ���������еĴ��̿���
			for (int j = 0; j < index_block_level2.size(); j++) {
				vector<int> index_block_level3 = ReadIndexBlock(fileSystem.diskBlock[index_block_level1[i]].content);//��ȡ���������еĴ��̿���
				for (int k = 0; k < index_block_level3.size(); k++) {
					fileSystem.diskBlock[index_block_level3[k]].content = "";//��մ��̿�����
					fileSystem.diskBlock[index_block_level3[k]].content_len = 0;
					FreeABlock(index_block_level3[k]);	//���մ��̿�
				}
			}
		}
	}
}

//ɾ����i���
void deleteiNode(int iNode_id)      
{	
	
	createInitINode(iNode_id, 0);
	fileSystem.iNode[iNode_id].id = 0;//i�ڵ��id�������������id
	fileSystem.iNode[iNode_id].owner = 0;//�ļ�������
	for (int i = 1; i <= 8; i++)
		fileSystem.iNode[iNode_id].auth[i] = 0;//ȫ��user����Ȩ��
	fileSystem.iNode[iNode_id].last_visited_time = "";//���һ�δ�ȡʱ�䣨��ǰʱ�䣩

	fileSystem.superBlock.free_iNode_num++;//���нڵ�++
	fileSystem.superBlock.iNode_bitmap[iNode_id / INODE_BITMAP_COL][iNode_id % INODE_BITMAP_COL] = 0;//�ͷ�λʾͼ��Դ
}

//����SFD����
void deleteSFD_ITEM(int file_id)
{
	for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {
		if (fileSystem.SFD[sfd_pointer].sfd_list[i].file_id == file_id) {
			fileSystem.SFD[sfd_pointer].sfd_list.erase(fileSystem.SFD[sfd_pointer].sfd_list.begin() + i);//ɾ����sfd��
			fileSystem.SFD[sfd_pointer].sfd_num--;
		}
	}
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
	ss << now_time.tm_year + 1900 << "/" << now_time.tm_mon + 1 << "/"
		<< now_time.tm_mday << "," << now_time.tm_hour << ":"
		<< now_time.tm_min << ":" << now_time.tm_sec;
	return  ss.str();
}

//���ļ�
void openFile(string fileName) 
{
	int diNode_id = findiNodeByName(fileName);		//�ҵ�����iNode_id
	if (fileSystem.iNode[diNode_id].type == 1){
		cout << "Ŀ¼�ļ����ɴ򿪣�" << endl;
		return;
	}
	if (checkOpen(diNode_id))
	{
		for (int i = 0; i < user.file_Uopened.size(); i++)//��ǰ�û����û��򿪱�����û�и�iNode_id
		{
			if (diNode_id == user.file_Uopened[i])//���û��򿪹�����ļ�
			{
				return;
			}
		}
		user.file_Uopened.push_back(diNode_id);//��ǰ�û����ļ�������ŵ���iNode_id
		userList[user.user_id].file_Uopened.push_back(diNode_id);//ȫ���û����ļ�������ŵ���iNode_id
	}
	else{
	MEM_BFD_ITEM m_iNode = initMEM_iNode(diNode_id);	//��ʼ���ڴ�i�ڵ�;
	mem_iNode[m_iNode.id % NHINO] = m_iNode;		//ָ��Ҫ�����iNode��hash������
	user.file_Uopened.push_back(m_iNode.id);//��ǰ�û����ļ�������ŵ���iNode_id
	userList[user.user_id].file_Uopened.push_back(m_iNode.id);//ȫ���û����ļ�������ŵ���iNode_id
	FILE_OPEND file_opened = { fileName ,0,m_iNode.id };	//�޸�ϵͳ���ļ���
	file_opend_list.push_back(file_opened);
	}
}

//����ļ��Ƿ񱻴�
int checkOpen(int iNode_id)
{
	if (iNode_id == mem_iNode[iNode_id % NHINO].id)
	{
		return 1;
	}
	return 0;
}

//����û����ļ���ı��򿪴���
int checkUserOpen(int iNode_id)
{
	int count = 0;
	for (int i = 1; i < 9; i++)
	{
		for (int j = 0; j < userList[i].file_Uopened.size(); j++)
		{
			if (userList[i].file_Uopened[j] == iNode_id) {
				count++;
			}
		}
	}
	return count;
}

//��ʼ���ڴ�i�ڵ�
MEM_BFD_ITEM  initMEM_iNode(int iNode_id) {
	MEM_BFD_ITEM m_iNode;
	m_iNode.id = fileSystem.iNode[iNode_id].id;//i�ڵ��id�������������id
	m_iNode.type = 0;		//�ļ����� 0-��ͨ 1-Ŀ¼
	m_iNode.owner = fileSystem.iNode[iNode_id].owner;//�ļ�������
	for (int i = 1; i <= 8; i++)
		m_iNode.auth[i] = fileSystem.iNode[iNode_id].auth[i];//Ȩ��

	m_iNode.file_len = fileSystem.iNode[iNode_id].file_len; // �ļ�����
	m_iNode.link_count = fileSystem.iNode[iNode_id].link_count;//���Ӵ���
	m_iNode.last_visited_time = getTime();//���һ�δ�ȡʱ�䣨��ǰʱ�䣩
	for (int i = 0; i < ADDR_NUM; i++)
		m_iNode.i_addr[i] = fileSystem.iNode[iNode_id].i_addr[i];//ʹ�õĴ�����Դ

	m_iNode.index_num = m_iNode.id % NHINO;//hash�����ڵ���
	m_iNode.status_lock = 0;//δ����
	m_iNode.status_mod = 0;//��δ���޸�
	m_iNode.shared_count = 1;//�������=1����һ���û���

	return m_iNode;
}

//�ر��ļ�
void closeFIle(string fileName)
{
	int diNode_id = findiNodeByName(fileName);	//�ҵ�����iNode_id

	if (fileSystem.iNode[diNode_id].type == 1){	//��ͼ�ر�Ŀ¼�ļ�
		cout << "Ŀ¼�ļ����ɹر�" << endl;
		return;
	}
	int count = checkUserOpen(diNode_id);//�ļ����򿪵Ĵ���
	if (count == 0) {
		cout << "û�д򿪸��ļ���\n";
		return;
	}
	for (int j = 0; j < userList[user.user_id].file_Uopened.size(); j++){
		if (userList[user.user_id].file_Uopened[j] == diNode_id) {
			userList[user.user_id].file_Uopened.erase(userList[user.user_id].file_Uopened.begin() + j);//�û��б��и��û����û����ļ���
			user.file_Uopened.erase(user.file_Uopened.begin() + j);//�޸ĵ�ǰ�û����û����ļ���

			if (count > 1)return;//�������һ���رո��ļ����ˣ�����Ҫ�������в�����ֱ�ӷ���
		}
	}
	//����ǰ�û����˸��ļ�
	
	MEM_BFD_ITEM m_iNode = mem_iNode[diNode_id % NHINO];//�ҵ���iNode_id��Ӧ��hash���е��ڴ�iNode

	//������̣����´���i Node������
	fileSystem.iNode[diNode_id].last_visited_time = m_iNode.last_visited_time;//���һ�η���ʱ��

	for (int i = 0; i < file_opend_list.size(); i++) {//����ϵͳ�򿪱�
		if (file_opend_list[i].fileName == fileName&& diNode_id== file_opend_list[i].f_inode) {
			file_opend_list.erase(file_opend_list.begin() + i);
			break;
		}
	}
	mem_iNode[diNode_id % NHINO].id = 0;//���hash���еĸ�����
}

//չʾϵͳ���ļ���
void showSystemFileOpen()
{
	cout << "\n\t\tϵͳ���ļ���\n";
	cout << "����������������������������������������������������������������������������������\n"; 
	cout << "�� �ļ���        ���ʴ���      i�ڵ��   ��\n";
	for (int i = 0; i < file_opend_list.size(); i++) {
		cout << "�� " + file_opend_list[i].fileName + "\t\t    " << file_opend_list[i].f_count << "\t\t" << file_opend_list[i].f_inode << "\t��\n";
	}
	cout << "����������������������������������������������������������������������������������\n\n";
	
}