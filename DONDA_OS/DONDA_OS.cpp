#include "OS.h"

FILE* stream;           //输入重定向
string clip_fileName;   //剪切板中文件的名字
string clipBoard;		//剪切板
SFD_ITEM link_board;    //保存需要连接的数据
FILE_SYSTEM fileSystem; //文件系统
USER user;              //当前用户
USER userList[9];       //所有用户
int sfd_pointer;		//sfd指针--指向当前的sfd目录
vector<int> sfd_stack;	//目录栈
MEM_BFD_ITEM mem_iNode[NHINO];//内存i节点区，数量为128块
vector<FILE_OPEND> file_opend_list;		//系统打开文件表

void main()
{ 
    init();
    login();
    //format();
}



