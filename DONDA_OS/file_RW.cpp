#include "OS.h"

//ͨ���ļ�����������i�ڵ�
int findiNodeByName(string fileName)
{
    for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {
        if (fileName == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name)
            return fileSystem.SFD[sfd_pointer].sfd_list[i].file_id;
    }
    return -1;
}

//дָ���ļ������ļ�
void writeFile(string fileName)
{
    int iNode_id = findiNodeByName(fileName);
    if (iNode_id == -1) {
        cout << "�ļ������ڣ�\n";
        return;
    }
    if (fileSystem.iNode[iNode_id].auth[user.user_id] == 0) {
        cout << "Ȩ�޲��㣬�޷��޸��ļ���\n";
        return;
    }
    ofstream tempFile;
    tempFile.open("Temp\\" + fileName + ".txt", ios::out | ios::app);
    if (tempFile.is_open()) {//�½���ʱ�ļ��ɹ�
        
    }
    tempFile.close();
    string str = "vim Temp\\" + fileName + ".txt";
	system(str.data());

	system("Pause");
}