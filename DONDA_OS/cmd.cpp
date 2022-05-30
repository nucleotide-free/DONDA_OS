#include "OS.h"

vector<string> command_0 = { "paste", "ls", "cd/", "cd..", "cls", "format", "logout", "bitmap", "exit", "help", "changepass", "showpassword" };
vector<string> command_1 = { "link","find","cut","copy","mkdir","cd","deld","create","delf","write","read" };
vector<string> command_2 = { "rename" };

//��ʾ����Ŀ¼
void commandCategory()
{
	textColor(10);
	cout << "\nCOMMANDS:" << endl;
	cout << "\t�ļ�����" << endl;
	cout << "\t\t����:\trname [old name] [new name]" << endl;
	cout << "\t\t����:\tlink   [name]" << endl;
	cout << "\t\t����:\tfind  [name]" << endl;
	cout << "\t\t����:\tcut   [name]" << endl;
	cout << "\t\t����:\tcopy [name]" << endl;
	cout << "\t\tճ��:\tpaste" << endl;
	cout << "\tĿ¼����" << endl;
	cout << "\t\t����Ŀ¼:\tmkdir [name]" << endl;
	cout << "\t\t��ʾĿ¼:\tls" << endl;
	cout << "\t\t�л�Ŀ¼:\tcd		[name]" << endl;
	cout << "\t\t���ظ�Ŀ¼:\tcd/" << endl;
	cout << "\t\tɾ��Ŀ¼:\tdeld  [name]" << endl;
	cout << "\t\t�����ϼ�Ŀ¼:\tcd.." << endl;
	cout << "\t�ļ���д" << endl;
	cout << "\t\t�����ļ�:\tcreate [name]" << endl;
	cout << "\t\tɾ���ļ�:\tdelf [name]" << endl;
	cout << "\t\t��д�ļ�:\twrite [name]" << endl;
	cout << "\t\t��ȡ�ļ�:\tread [name]" << endl;
	cout << "\t��������" << endl;
	cout << "\t\t����:	\tcls" << endl;
	cout << "\t\t��ʽ��:\tformat" << endl;
	cout << "\t\tע����¼:\tlogout" << endl;
	cout << "\t\tλʾͼ:\tbitmap" << endl;
	cout << "\t\t�ر�ϵͳ:\texit" << endl;
	cout << "\t\t��ʾ����:\thelp" << endl;
	cout << "\t\t�޸�����:\tchangepass" << endl;
	cout << "\t\t��ʾ����:\tshowpassword" << endl;
};

//����������������ʵ�ִ󲿷������������
void display() {
	system("cls");
	commandCategory();
	string file_list;		//���ڼ�¼�û����򿪵��ļ���Ŀ¼���б������������ʾ������ǰ

	int command_type = -1;//ָ������
	string instruction, fileName1, fileName2;//����� ָ��ļ���1���ļ���2
	while (1)
	{
		while (1) {
			cout << user.user_name << "@DONDA_OS:";
			cout << file_list << "$ ";
			//input_command(instruction, fileName1, fileName2);//�û�����ָ��
			if (input_command(instruction, fileName1, fileName2) != -1)//ָ����Ч
				break;
		}
		//*********************************  �ļ����� ********************************* 
		if (instruction == "rname") {//������

		}
		else if (instruction == "link") {//����

		}
		else if (instruction == "find") {//����

		}
		else if (instruction == "cut") {//����

		}
		else if (instruction == "copy") {//����

		}
		else if (instruction == "paste") {//ճ��

		}
		//*********************************Ŀ¼���� ********************************* 
		else if (instruction == "mkdir") {//����Ŀ¼

		}
		else if (instruction == "ls") {//��ʾĿ¼
			if (fileSystem.SFD[sfd_pointer].sfd_num==0) {
				cout << "������" << endl;
				return;
			}
			for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {		//ɨ�赱ǰsfd�б��жԵ�sfd_item��filename����ʾ����
				cout << fileSystem.SFD[sfd_pointer].sfd_list[i].file_name+"\t";
				if(fileSystem.iNode[sfd_pointer].type){		//ͨ����ȡiNode[sfd_pointer]��typeֵ��
					cout << "dir\n";
				}
				else {
					cout << "file\n";
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
				sfd_stack.push_back(fileSystem.SFD[sfd_pointer]);		//����ǰĿ¼sfd����Ŀ¼ջ
			}
			else {
				cout << "�����ڵ�Ŀ¼������ʧ�ܣ�\n";
			}
		}
		else if (instruction == "cd/") {//���ظ�Ŀ¼
			sfd_pointer = 0;		//��Ŀ¼sfd��sfdָ��
			sfd_stack.clear();		//���Ŀ¼ջ
			sfd_stack.push_back(fileSystem.SFD[sfd_pointer]);	//��ջ��ѹ���Ŀ¼

			file_list.clear();		//�ļ���ʾ�ַ������
		}
		else if (instruction == "cd..") {//�����ϼ�Ŀ¼
			sfd_stack.pop_back();		//����Ŀ¼ջ
			sfd_stack.front();

			file_list.clear();		//�ļ���ʾ�ַ������
		}
		else if (instruction == "deld") {//ɾ��Ŀ¼

		}
		//********************************* �ļ���д ********************************
		else if (instruction == "create") {//�����ļ�
			if (fileSystem.iNode[sfd_pointer].auth[user.user_id] == 0) {
				cout << "����ʧ�ܣ����û�Ȩ�޲��㣡\n";
				continue;
			}
			int iNode_id = createFile(fileName1);
			if( iNode_id > -1){//�����ɹ�
				cout << "�Ƿ�Ҫ���ļ���д�붫��[Y,N]��";
				while (1) {
					char ch = _getch();//�û�����
					cout << ch << endl;
					if (ch == 'N' || ch == 'n')
						break;//��д��ֱ���˳�
					else if (ch == 'Y' || ch == 'y') {//д�ļ�
						writeFile(fileName1);
						break;
					}
					else
						cout << "���벻�Ϸ�������������[Y,N]��";
				}
				
			}	
		}
		else if (instruction == "delf") {//ɾ���ļ�

		}
		else if (instruction == "write") {//��д�ļ�
			writeFile(fileName1);
		}
		else if (instruction == "read") {//��ȡ�ļ�

		}
		//********************************* �������� ********************************
		else if (instruction == "cls") {//����
			system("cls");
		}
		else if (instruction == "format") {//��ʽ��

		}
		else if (instruction == "logout") {//ע����¼
			cout << "ע���ɹ���\n";
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
			return;
		}
		else if (instruction == "help") {//��ʾ����
			commandCategory();
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
	cin >> instruction;//����ָ��
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
	case 1:cin >> fileName1; break;//�����ļ���1
	case 2:cin >> fileName1 >> fileName2; break;//�����ļ���1��2
	case -1:cout << "��Чָ�����help��ȡ������\n";
	}
	return command_type;
}

//����������ɫ
void textColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}