#include "OS.H"

//�½�����
void createLink(string fileName)
{
	cout << "׼��link�ļ�" << fileName << endl;

	int iNode_id = findiNodeByName(fileName);
	link_board.file_id = iNode_id;//�������Ӱ��������
	link_board.file_name = fileName;
	link_board.type = 1;//�½�����Ϊ��������
}

//ճ�������ļ�����ǰĿ¼
void pasteLink()
{
	fileSystem.SFD[sfd_pointer].sfd_list.push_back(link_board);//�����sfd_item���뵱ǰĿ¼��SFD�µ�sfd_list����
	fileSystem.SFD[sfd_pointer].sfd_num++;//��ǰĿ¼��SFD�µ�sfd_item����
	link_board.file_id = -1;//�����������
	cout << "���������ļ��ɹ���\n";
}

//ɾ������
void deleteLink(string fileName)
{
	deleteSFD_ITEM(findiNodeByName(fileName));
}