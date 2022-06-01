#include "OS.h"

FILE* stream;           //输入重定向
FILE_SYSTEM fileSystem; //文件系统
USER user;              //当前用户
USER userList[9];       //所有用户
int sfd_pointer;		//sfd指针--指向当前的sfd目录
vector<SFD> sfd_stack;	//目录栈

int main()
{ 
    for (int i = 0; i < 512; i++)
        cout << i << "    ";
    /*init();
    login();
    system("cls");
    cout << "已成功退出 DONDA_OS 文件系统！";*/
}



