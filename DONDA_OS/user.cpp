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

void RGBColor(int i) {
	switch (i)
	{
	case 1:cout << "\x1B[38;2;108;141;183m"; break;//��ɫ
	case 2:cout << "\x1B[38;2;108;141;183m"; break;
	default:
		break;
	}
	
}

void login() {    
	system("cls");
	RGBColor(1);
	cout << "\n\t\t-------------------------------------------------------------------------------" << endl;
	cout << "\t\t-----------               ��ӭʹ�� DONDA_OS �ļ�ϵͳ                -----------" << endl;
	cout << "\t\t-------------------------------------------------------------------------------" << endl;

	while (1) {
		user.user_id = 0;//�û���ʼ��
		user.password = "";
		user.file_Uopened.clear();

		cout << "\n\t\t���¼�ļ�ϵͳ��";
		textColor(7);
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
			textColor(4);
			cout << "\n\t\t���û������ڣ�\n";
			continue;
		}
		textColor(11);
		cout << "\n\t\t���������룺";
		textColor(7);
		char temp[30];
		char* temp1 = temp;
		string psw = getpassword(temp1);
		textColor(4);
		if (psw != user.password) 
			cout << "\n\t\t�������\n";
		else {	//��¼�ɹ�
			getchar();//���ջس�
			user.file_Uopened = userList[user.user_id].file_Uopened;//�����û����ļ���
			link_board.file_id = -1;//���Ӱ����
			clip_fileName = "";//���а����
			clipBoard = "";
			display();//��¼�ɹ��󣬽���ϵͳ����
		}
	}
}