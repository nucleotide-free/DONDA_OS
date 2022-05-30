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
	string file_list;		//���ڼ�¼�û����򿪵��ļ���Ŀ¼���б��������������ʾ������ǰ

	int command_type = -1;//ָ������
	string instruction, fileName1, fileName2;//����� ָ��ļ���1���ļ���2
	while (1)
	{
		while (1) {
			cout << user.user_name << "@DONDA_OS:";
			cout << file_list << "$ ";
			input_command(instruction, fileName1, fileName2);//�û�����ָ��
			if (command_type != -1)//ָ����Ч
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

		}
		else if (instruction == "cd") {//�л�Ŀ¼

		}
		else if (instruction == "cd/") {//���ظ�Ŀ¼

		}
		else if (instruction == "cd..") {//�����ϼ�Ŀ¼

		}
		else if (instruction == "deld") {//ɾ��Ŀ¼

		}
		//********************************* �ļ���д ********************************
		else if (instruction == "create") {//�����ļ�

		}
		else if (instruction == "delf") {//ɾ���ļ�

		}
		else if (instruction == "write") {//��д�ļ�

		}
		else if (instruction == "read") {//��ȡ�ļ�

		}
		//********************************* �������� ********************************
		else if (instruction == "cls") {//����

		}
		else if (instruction == "format") {//��ʽ��

		}
		else if (instruction == "logout") {//ע����¼

		}
		else if (instruction == "bitmap") {//λʾͼ

		}
		else if (instruction == "exit") {//�ر�ϵͳ

		}
		else if (instruction == "help") {//��ʾ����
			commandCategory();
		}
		else if (instruction == "changepass") {//�޸�����

		}
		else if (instruction == "showpassword") {//��ʾ����

		}

	}
}

int input_command(string& instruction, string& fileName1, string& fileName2)//�û�����������ж�
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