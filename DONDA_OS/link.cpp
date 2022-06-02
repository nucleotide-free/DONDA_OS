#include "OS.H"

//�½�����
void createLink(string fileName)
{
	int sfd_item_id = findSFD_item_idByName(fileName);
	if (fileSystem.SFD[sfd_pointer].sfd_list[sfd_item_id].type == 1) {
		cout << "�����ļ������ٴ����ӣ�\n";
		return;
	}
	int iNode_id = findiNodeByName(fileName);		//�ҵ�����iNode_id
	if (fileSystem.iNode[iNode_id].type == 1) {
		cout << "Ŀ¼�ļ����ɱ����ӣ�" << endl;
		return;
	}
	cout << "׼��link�ļ�" << fileName << endl;
	link_board.file_id = iNode_id;//�������Ӱ��������
	link_board.file_name = fileName;
	link_board.type = 1;//�½�����Ϊ��������
}

//ճ�������ļ�����ǰĿ¼
void pasteLink()
{
	if (link_board.file_id != -1) {
		fileSystem.SFD[sfd_pointer].sfd_list.push_back(link_board);//�����sfd_item���뵱ǰĿ¼��SFD�µ�sfd_list����
		fileSystem.SFD[sfd_pointer].sfd_num++;//��ǰĿ¼��SFD�µ�sfd_item����
		link_board.file_id = -1;//�����������
		cout << "���������ļ��ɹ���\n";
	}
}

int findSFD_item_idByName(string fileName)
{
	for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++)
		if (fileSystem.SFD[sfd_pointer].sfd_list[i].file_name == fileName)
			return i;
	return -1;
}

//ɾ�����ӣ��ж��Ƿ��������ļ�
void deleteLink(string fileName)
{
	int iNode_id = findiNodeByName(fileName);
	int sfd_item_id = findSFD_item_idByName(fileName);
	if (fileSystem.SFD[sfd_pointer].sfd_list[sfd_item_id].type != 0) {//��һ�������ļ���ʧЧ�ļ�
		for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {
			if (fileSystem.SFD[sfd_pointer].sfd_list[i].file_id == iNode_id && fileSystem.SFD[sfd_pointer].sfd_list[i].type == 1) {
				fileSystem.SFD[sfd_pointer].sfd_list.erase(fileSystem.SFD[sfd_pointer].sfd_list.begin() + i);//ɾ����sfd��
				fileSystem.SFD[sfd_pointer].sfd_num--;
			}
		}
	}
	else {//��ͨ�ļ�
		for (int i = 1; i < SFD_NUM; i++) {
			if (fileSystem.superBlock.SFD_bitmap[i / SFD_BITMAP_COL][i % SFD_BITMAP_COL] == 1 && fileSystem.SFD[i].sfd_num != 0) {//��i�ڵ㱻ռ��
				for (int j = 0; j < fileSystem.SFD[i].sfd_num; j++) {
					if (fileSystem.SFD[i].sfd_list[j].type == 1 && fileSystem.SFD[i].sfd_list[j].file_id == iNode_id) {
						fileSystem.SFD[i].sfd_list[j].type = -1;//����ָ���ԭ�ļ���ʧЧ��type = -1
					}

				}
			}
		}
	}
}

//����ļ��Ƿ�ʧЧ,1-ʧЧ��0-����
int checkValid(string fileName)
{
	int sfd_item_id = findSFD_item_idByName(fileName);
	if (fileSystem.SFD[sfd_pointer].sfd_list[sfd_item_id].type == -1) {
		cout << "ԭ�ļ���ʧЧ��\n";
		return 1;
	}
	return 0;
}