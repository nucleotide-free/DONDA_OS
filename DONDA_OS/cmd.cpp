#include "OS.h"

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
	string file_list;		//���ڼ�¼�û����򿪵��ļ���Ŀ¼���б������������ʾ������ǰ
	cout << user.user_name << "@File System\\>";
	if (file_list != " ") {
		cout << file_list << ">";
	}

}

//������������Ƿ�����Լ�ָ�������
int checkIn(string in)
{
	return 1;
}

//����������ɫ
void textColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}