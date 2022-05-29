#include "OS.h"

FILE* stream;           //输入重定向
FILE_SYSTEM fileSystem; //文件系统
USER user;              //当前用户

int main()
{ 
    login();
    init();
}



