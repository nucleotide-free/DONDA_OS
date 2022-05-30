#include "OS.h"

vector<string> command_0 = { "paste", "ls", "cd/", "cd..", "cls", "format", "logout", "bitmap", "exit", "help", "changepass", "showpassword" };
vector<string> command_1 = { "link","find","cut","copy","mkdir","cd","deld","create","delf","write","read" };
vector<string> command_2 = { "rename" };

//��ʾ����Ŀ¼
void commandCategory()
{
	textColor(10);
	cout << "--------------------------------------------------------------------------------" << endl;
	Sleep(20);    //������ʱ100ms
	cout << "-----------                        ������ʾ                          -----------" << endl;
	Sleep(20);    //������ʱ100ms
	cout << "---------------------------------�ļ�/Ŀ¼����----------------------------------" << endl;
	Sleep(10);    //������ʱ100ms
	cout << "-----------  - ����:     rname <O> <N>#  - ����: link   <name>      ------------" << endl;
	Sleep(10);    //������ʱ100ms
	cout << "-----------  - ����:     find  <name> #  - ����: cut    <name>       -----------" << endl;
	Sleep(10);    //������ʱ100ms
	cout << "-----------  - ����:     copy  <name> #  - ճ��: paste               -----------" << endl;
	Sleep(20);    //������ʱ100ms
	cout << "---------------------------------Ŀ¼����---------------------------------------" << endl;
	Sleep(10);    //������ʱ100ms
	cout << "-----------  - ����Ŀ¼: mkdir <name> #  - ��ʾĿ¼:     ls         ------------" << endl;
	Sleep(10);    //������ʱ100ms
	cout << "-----------  - �л�Ŀ¼: cd    <name> #  - ���ظ�Ŀ¼:   cd/        ------------" << endl;
	Sleep(10);    //������ʱ100ms
	cout << "-----------  - ɾ��Ŀ¼: deld  <name> #  - �����ϼ�Ŀ¼: cd..       ------------" << endl;
	Sleep(20);    //������ʱ100ms
	cout << "----------------------------------�ļ�����--------------------------------------" << endl;
	Sleep(10);    //������ʱ100ms
	cout << "------------  - �����ļ�: create <name>#  - ɾ���ļ�: delf <name>    -----------" << endl;
	Sleep(10);    //������ʱ100ms
	cout << "------------  - ��д�ļ�: write <name> #  - ��ȡ�ļ�: read <name>    -----------" << endl;
	Sleep(20);    //������ʱ100ms
	cout << "----------------------------------��������--------------------------------------" << endl;
	Sleep(10);    //������ʱ100ms
	cout << "------------  - ����:     cls          #  - ��ʽ��:   format         -----------" << endl;
	Sleep(10);    //������ʱ100ms
	cout << "------------  - ע����¼: logout       #  - λʾͼ:   print          -----------" << endl;
	Sleep(10);    //������ʱ100ms
	cout << "------------  - �Զ���ȫ: Tab          #  - �ر�ϵͳ: exit           -----------" << endl;
	Sleep(10);    //������ʱ100ms
	cout << "------------  - ��������: ��           #  - ��ʾ����: help           -----------" << endl;
	Sleep(10);    //������ʱ100ms
	cout << "------------  - �޸�����: changepass   #  - ��ʾ����: showpassword   -----------" << endl;
	Sleep(10);    //������ʱ100ms
	cout << "--------------------------------------------------------------------------------" << endl;
}

//����������������ʵ�ִ󲿷������������
void display() {
	system("cls");
	string tips = "@" + user.user_name + ":\\";
	int command_type = -1;//ָ������
	string instruction, fileName1, fileName2;//����� ָ��ļ���1���ļ���2
	while (1)
	{
		while (1) {
			cout << tips << ">";//��ǰ�����ļ�
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