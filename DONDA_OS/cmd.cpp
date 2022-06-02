#include "OS.h"

vector<string> command_0 = { "paste", "ls", "cd/", "cd..", "cls", "format", "logout", "bitmap", "exit", "help", "ushow","fshow","changepass", "showpassword"};
vector<string> command_1 = { "link","find","cut","copy","mkdir","cd","deld","create","delf","write","read","open","close"};
vector<string> command_2 = { "rename" };

//��ʾ����Ŀ¼
void commandCategory()
{
	textColor(15);
	cout << "\nCOMMANDS:" << endl;
	cout << "\t�ļ�����" << endl;
	cout << "\t\t����:\trename  [old name]  [new name]" << endl;
	cout << "\t\t����:\tlink  [name]" << endl;
	cout << "\t\t����:\tfind  [name]" << endl;
	cout << "\t\t����:\tcut   [name]" << endl;
	cout << "\t\t����:\tcopy  [name]" << endl;
	cout << "\t\tճ��:\tpaste" << endl;
	cout << "\tĿ¼����" << endl;
	cout << "\t\t����Ŀ¼:\tmkdir [name]" << endl;
	cout << "\t\t��ʾĿ¼:\tls" << endl;
	cout << "\t\t�л�Ŀ¼:\tcd    [name]" << endl;
	cout << "\t\t���ظ�Ŀ¼:\tcd/" << endl;
	cout << "\t\tɾ��Ŀ¼:\tdeld  [name]" << endl;
	cout << "\t\t�����ϼ�Ŀ¼:\tcd.." << endl;
	cout << "\t�ļ���д" << endl;
	cout << "\t\t�����ļ�:\tcreate [name]" << endl;
	cout << "\t\tɾ���ļ�:\tdelf   [name]" << endl;
	cout << "\t\t���ļ�:\topen   [name]" << endl;
	cout << "\t\t�ر��ļ�:\tclose  [name]" << endl;
	cout << "\t\t��д�ļ�:\twrite  [name]" << endl;
	cout << "\t\t��ȡ�ļ�:\tread   [name]" << endl;
	cout << "\t��������" << endl;
	cout << "\t\t����:\t\tcls" << endl;
	cout << "\t\t��ʽ��:\t\tformat" << endl;
	cout << "\t\tע����¼:\tlogout" << endl;
	cout << "\t\tλʾͼ:\t\tbitmap" << endl;
	cout << "\t\t�ر�ϵͳ:\texit" << endl;
	cout << "\t\t��ʾ����:\thelp" << endl;
	cout << "\t\t��ʾ�û��ļ��򿪱�:\tushow" << endl;
	cout << "\t\t�޸�����:\tchangepass" << endl;
	cout << "\t\t��ʾ����:\tshowpassword" << endl;
};

//����������������ʵ�ִ󲿷������������
void display() {
	system("cls");
	commandCategory();//������ʾ��Ϣ��Ŀ¼help��
	string file_list;		//���ڼ�¼�û����򿪵��ļ���Ŀ¼���б������������ʾ������ǰ
	int command_type = -1;//ָ������
	string instruction, fileName1, fileName2;//����� ָ��ļ���1���ļ���2
	while (1)
	{
		while (1) {
			cout << user.user_name << "@DONDA_OS:";
			cout << file_list << "$ ";
			if (input_command(instruction, fileName1, fileName2) != -1)//ָ����Ч
				break;
		}
		//*********************************  �ļ����� ********************************* 
		if (instruction == "rename") {//������
			renameFile(fileName1, fileName2);
		}
		else if (instruction == "link") {//����

		}
		else if (instruction == "find") {//����

		}
		else if (instruction == "cut") {//����
			cut(fileName1);
		}
		else if (instruction == "copy") {//����
			copy(fileName1);
		}
		else if (instruction == "paste") {//ճ��
			paste();
		}
		//*********************************Ŀ¼���� ********************************* 
		else if (instruction == "mkdir") {//����Ŀ¼
			if (fileSystem.iNode[sfd_pointer].auth[user.user_id] == 0) {
				cout << "����ʧ�ܣ����û�Ȩ�޲��㣡\n";
				continue;
			}
			int tips = createDir(fileName1);//���ش����������ʾ��Ϣ
			if (tips == 1)
				cout << "i�ڵ��Ŀ¼�ռ䲻�㣬����ʧ�ܣ�\n";
			else if (tips == 2)
				cout << "Ŀ¼����ͻ��\n";
			else if (tips == 3)
				cout << "�ڴ�ռ䲻�㣬����i�ڵ�ʧ�ܣ�\n";
			else
				cout << "�����ɹ���\n";
			//���뵽��Ŀ¼��

		}
		else if (instruction == "ls") {//��ʾĿ¼
			if (fileSystem.SFD[sfd_pointer].sfd_num==0) {
				cout << "������" << endl;
				continue;
			}
			cout << "����\t\t�޸�����\t\t����\t��С\n";
			for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {		//ɨ�赱ǰsfd�б��жԵ�sfd_item��filename����ʾ����
				cout << fileSystem.SFD[sfd_pointer].sfd_list[i].file_name+"\t\t";//�ļ���
				int file_id = fileSystem.SFD[sfd_pointer].sfd_list[i].file_id;	//�ļ�id(ָ��iNode)
				cout << fileSystem.iNode[file_id].last_visited_time + "\t";		//�޸�����
				if(fileSystem.iNode[file_id].type){//��ȡ�ļ�����
					cout << "dir\n";	//Ŀ¼�ļ�
				}
				else {
					cout << "file\t";	//�ı��ĵ�
					cout << fileSystem.iNode[file_id].file_len << endl;//�ļ�����
				}
			}
		}
		else if (instruction == "cd") {//�л�Ŀ¼
			int fileName_check = 0;		//���Ŀ¼���Ƿ������ΪfileName1��Ŀ¼��1--���ڣ�0--������
			int file_check = 0;		//���cd�����ļ�����Ŀ¼��0--�ļ���1--Ŀ¼
			for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {
				if (fileName1 == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name) {
					fileName_check = 1;		//����
					sfd_pointer = fileSystem.SFD[sfd_pointer].sfd_list[i].file_id;		//����ǰ��Ŀ¼sfdָ����Ϊ��Ҫ�����Ŀ¼sfd��id
					break;
				}
			}
			if (fileSystem.iNode[sfd_pointer].type)		//���iNode�н�Ҫcd���ļ���Ŀ¼��type�Ƿ�Ϊ�ļ�
					file_check = 1;		//����	
			if (fileName_check&& file_check) {
				file_list = file_list + "\\" + fileName1;
				sfd_stack.push_back(sfd_pointer);		//����ǰĿ¼sfd����Ŀ¼ջ
			}
			else {
				cout << "�����ڵ�Ŀ¼������ʧ�ܣ�\n";
			}
		}
		else if (instruction == "cd/") {//���ظ�Ŀ¼
			sfd_pointer = 0;		//��Ŀ¼sfd��sfdָ��
			sfd_stack.clear();		//���Ŀ¼ջ
			sfd_stack.push_back(sfd_pointer);	//��ջ��ѹ���Ŀ¼

			file_list.clear();		//�ļ���ʾ�ַ������
		}
		else if (instruction == "cd..") {//�����ϼ�Ŀ¼
			if (sfd_stack.size() == 1)
			{
				continue;
			}
			if(sfd_stack.size()!=1)
				sfd_stack.pop_back();		//����Ŀ¼ջ
			sfd_pointer = sfd_stack.back();
			file_list.erase(file_list.find_last_of("\\"), file_list.length());		//�ļ���ʾ�ַ������
		}
		else if (instruction == "deld") {//ɾ��Ŀ¼
			
			deleteDir(findiNodeByName(fileName1));
		}
		//********************************* �ļ���д ********************************
		else if (instruction == "create") {//�����ļ�
			if (fileSystem.iNode[sfd_pointer].auth[user.user_id] == 0) {
				cout << "���û�Ȩ�޲��㣬����ʧ�ܣ�\n";
				continue;
			}
			int tips = createFile(fileName1);//���ش����������ʾ��Ϣ
			if (tips == 1)
				cout << "û�п��д��̿���߿���i�ڵ㣡\n";
			else if (tips == 2)
				cout << "�ļ�����ͻ��\n";
			else {
				cout << "�����ɹ����Ƿ�Ҫ���ļ���д������[Y,N]��";
				while (1) {
					char ch = _getch();//�û�����
					cout << ch << endl;
					if (ch == 'N' || ch == 'n')//��д��ֱ���˳�
						break;
					else if (ch == 'Y' || ch == 'y') {//д�ļ�
						openFile(fileName1);
						writeFile(fileName1);
						break;
					}
					else
						cout << "���벻�Ϸ�������������[Y,N]��";
				}
			}	
		}
		else if (instruction == "delf") {//ɾ���ļ�
			deleteFile(fileName1);
			cout << "ɾ���ɹ���\n";
		}
		else if (instruction == "open") {//���ļ�
			int iNode_id = findiNodeByName(fileName1);
			if (iNode_id == -1) {
				cout << "�ļ������ڣ�\n";
				continue;
			}
			openFile(fileName1);
		}
		else if (instruction == "close") {//�ر��ļ�
			int iNode_id = findiNodeByName(fileName1);
			if (iNode_id == -1) {
				cout << "�ļ������ڣ�\n";
				continue;
			}
			closeFIle(fileName1);
		}
		else if (instruction == "write") {//��д�ļ�
			writeFile(fileName1);
		}
		else if (instruction == "read") {//��ȡ�ļ�
			readFile(fileName1);
		}
		//********************************* �������� ********************************
		else if (instruction == "cls") {//����
			system("cls");
		}
		else if (instruction == "format") {//��ʽ��
			format();
			init();
			sfd_pointer = 0;		//��Ŀ¼sfd��sfdָ��
			sfd_stack.clear();		//���Ŀ¼ջ
			sfd_stack.push_back(sfd_pointer);	//��ջ��ѹ���Ŀ¼
			file_list.clear();		//�ļ���ʾ�ַ������
			cout << "��ʽ���ɹ���\n";
		}
		else if (instruction == "logout") {//ע����¼
			cout << "ע���ɹ���\n";
			sfd_pointer = 0;
			saveFileSystem();
			login();
		}
		else if (instruction == "bitmap") {//λʾͼ
			cout << "\t[ i�ڵ�λʾͼ ]\n" << endl;
			for (int i = 0; i < INODE_BITMAP_ROW; i++) {
				for (int j = 0; j < INODE_BITMAP_COL; j++) 
					cout << fileSystem.superBlock.iNode_bitmap[i][j] << " ";
				cout << endl;
			}
			cout << "\n\t[ SFDλʾͼ ]\n" << endl;
			for (int i = 0; i < SFD_BITMAP_ROW; i++) {
				for (int j = 0; j < SFD_BITMAP_COL; j++)
					cout << fileSystem.superBlock.SFD_bitmap[i][j] << " ";
				cout << endl;
			}
			cout << "\n\n";
		}
		else if (instruction == "exit") {//�ر�ϵͳ
		sfd_pointer = 0;
			saveFileSystem();
			system("cls");
			cout << "\n�ѳɹ��˳� DONDA_OS �ļ�ϵͳ��\n";
			system("rd Temp");
			system("md Temp");
			exit(0);
		}
		else if (instruction == "help") {//��ʾ����
			commandCategory();
		}
		else if (instruction == "ushow") {//��ʾ����
		for (int i = 1; i < 9; i++)
			{
			cout << userList[i].user_name << ":\n";
			for (int j = 0; j < userList[i].file_Uopened.size(); j++)
				{
				for (int k = 0; k < file_opend_list.size(); k++)
				{
					if (userList[i].file_Uopened[j] == file_opend_list[k].f_inode) {
						cout << file_opend_list[k].fileName << " ";
					}
				}
				}
			cout <<"\n";
			}
		}
		else if (instruction == "fshow") {//��ʾ����
		showSystemFileOpen();
		}
		else if (instruction == "changepass") {//�޸�����
			char temp[30];
			char* temp1 = temp;
			cout << "�û�����" << user.user_name << endl;
			while (1) {
				cout << "��ǰ���룺";
				string psw = getpassword(temp1);
				if (psw != user.password) {
					cout << "��������Ƿ��������[Y,N]? ";
					char ch = _getch();
					cout << ch << endl;
					if (ch == 'Y' || ch == 'y')
						continue;
					else if (ch == 'N'|| ch == 'n')
						break;
				}
				else {//��������ȷ
					while (1) {
						cout << "�����룺";
						psw = getpassword(temp1);
						cout << "ȷ�����룺";
						string psw2 = getpassword(temp1);
						if (psw == psw2) { //�������������һ��
							cout << "�޸ĳɹ���\n";
							user.password = psw;
							userList[user.user_id].password = user.password;//�޸�ȫ���û��б��е�����
							break;
						}
						else {//��������벻һ��
							cout << "������������벻һ�£��Ƿ��������[Y,N]? ";
							char ch = _getch();
							cout << ch << endl;
							if (ch == 'Y' || ch == 'y')
								continue;
							else if (ch == 'N' || ch == 'n')
								break;
						}
					}
					break;
				}
			}
		}
		else if (instruction == "showpassword") {//��ʾ����
			cout << "�û�����" << user.user_name << endl;
			cout << "���룺" << user.password << endl;
		}
	}

}

//�û�����������ж�
int input_command(string& instruction, string& fileName1, string& fileName2)
{
	char ch;
	int i = 0;
	instruction = "";//�����ַ���
	while (ch = getchar()) {//����ָ��
		if (i==0 && ch == '\n')return -1;//��һ���ַ������س���
		else if (ch == ' ' || ch == '\n')break;
		else instruction += ch;
		i++;
	}
	int command_type = -1;//�ж�ָ�������
	for (int i = 0; i < command_0.size(); i++) {
		if (command_0[i] == instruction) {//ָ�� û�в�����
			command_type = 0; break;
		}
	}
	if (command_type == -1)//û�ҵ���������
		for (int i = 0; i < command_1.size(); i++) {
			if (command_1[i] == instruction) {//ָ�� һ��������
				command_type = 1; break;
			}
		}
	if (command_type == -1)//û�ҵ���������
		for (int i = 0; i < command_2.size(); i++) {
			if (command_2[i] == instruction) {//ָ�� ����������
				command_type = 2; break;
			}
		}
	switch (command_type)
	{
	case 1:cin >> fileName1; getchar(); break;//�����ļ���1
	case 2:cin >> fileName1 >> fileName2; getchar(); break;//�����ļ���1��2
	case -1:cout << "��Чָ�����help��ȡ������\n"; break;
	}
	return command_type;
}

//����������ɫ
void textColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
} 