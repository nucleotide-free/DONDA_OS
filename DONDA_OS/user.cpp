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
	USER user_list[9];      //8���û�
	freopen_s(&stream, "Data\\USER.txt", "r", stdin);
	for (int i = 1; i <= 8; i++) {
		user_list[i].user_id = i;
		cin >> user_list[i].user_name;
		cin >> user_list[i].password;
	}
	std::fclose(stdin);//�ر��ض�������
	cin.clear();
	freopen_s(&stream, "CON", "r", stdin);
	

	system("cls");
	textColor(10);
	cout << "\t\t-------------------------------------------------------------------------------" << endl;
	cout << "\t\t-----------               ��ӭʹ�� DONDA_OS �ļ�ϵͳ                -----------" << endl;
	cout << "\t\t-------------------------------------------------------------------------------" << endl;

	while (1) {
		cout << "\n\t\t���¼�ļ�ϵͳ��";
		cin >> user.user_name;	//�����û���
		for (int i = 1; i < 9; i++) {
			if(user.user_name == user_list[i].user_name){//������û�������
				user.user_id = user_list[i].user_id;
				user.password = user_list[i].password;
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
		if (psw != user.password) {
			cout << "�������";
			user.user_id = 0;//�û���ʼ��
		}else {
			cout << "��¼�ɹ���";
			break;
		}
	}
}
