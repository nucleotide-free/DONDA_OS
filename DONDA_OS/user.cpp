#include "OS.h"

//�������뻯
char* getpassword(char* pasw)
{
	char ch;
	int i = 0;
	while ((ch = _getch()) != '\r') {
		if (i > 0 && ch == '\b') {
			--i;
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
		else if (i < 18) {
			pasw[i++] = ch;
			putchar('*');
		}
	}
	pasw[i] = '\0';
	putchar('\n');
	return pasw;
}

void login() {    
	system("cls");
	textColor(11);
	cout << "\t\t-------------------------------------------------------------------------------" << endl;
	cout << "\t\t-----------               ��ӭʹ�� DONDA_OS �ļ�ϵͳ                -----------" << endl;
	cout << "\t\t-------------------------------------------------------------------------------" << endl;

	while (1) {
		user.user_id = 0;//�û���ʼ��
		cout << "\n\t\t���¼�ļ�ϵͳ��";
		cin >> user.user_name;	//�����û���
		if (user.user_name == ":wq") {//�˳�ϵͳ
			return;
		}
		for (int i = 1; i < 9; i++) {
			if(user.user_name == userList[i].user_name){//������û�������
				user.user_id = userList[i].user_id;
				user.password = userList[i].password;
			}
		}
		if (user.user_id == 0) {
			cout << "���û������ڣ�";
			continue;
		}

		cout << "\n\t\t���������룺";
		char temp[30];
		char* temp1 = temp;

		string psw = getpassword(temp1);
		if (psw != user.password) 
			cout << "\n\t\t�������\n";
		else {
			cout << "\t\t��¼�ɹ���\n";
			display();//��¼�ɹ��󣬽���ϵͳ����
			break;
		}
	}
}