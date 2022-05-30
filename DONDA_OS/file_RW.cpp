#include "OS.h"

//通过文件名，找它的i节点
int findiNodeByName(string fileName)
{
    for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {
        if (fileName == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name)
            return fileSystem.SFD[sfd_pointer].sfd_list[i].file_id;
    }
    return -1;
}

//写指定文件名的文件
void writeFile(string fileName)
{
    int iNode_id = findiNodeByName(fileName);
    if (iNode_id == -1) {
        cout << "文件不存在！\n";
        return;
    }
    if (fileSystem.iNode[iNode_id].auth[user.user_id] == 0) {
        cout << "权限不足，无法修改文件！\n";
        return;
    }
    ofstream tempFile;
    tempFile.open("Temp\\" + fileName + ".txt", ios::out | ios::app);
    if (tempFile.is_open()) {//新建临时文件成功
        
    }
    tempFile.close();
    string str = "vim Temp\\" + fileName + ".txt";
	system(str.data());

	system("Pause");
}