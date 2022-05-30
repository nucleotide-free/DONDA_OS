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
    string buffer;      //用于存放读出来的内容
    int iNode_id = findiNodeByName(fileName);
    if (iNode_id == -1) {
        cout << "文件不存在！\n";
        return;
    }
    if (fileSystem.iNode[iNode_id].auth[user.user_id] == 0) {
        cout << "权限不足，无法修改文件！\n";
        return;
    }
    buffer = contentBuffer(iNode_id);
    ofstream tempFile;
    tempFile.open("Temp\\" + fileName + ".txt", ios::out | ios::app);
    if (tempFile.is_open()) {//新建临时文件成功
        tempFile << buffer;
    }
    tempFile.close();
    string str = "vim Temp\\" + fileName + ".txt";      //vim - M file :以只读的方式打开文件，不可以强制保存
    system(str.data());
}

//读指定文件名的文件
void readFile(string fileName)
{
    string buffer;      //用于存放读出来的内容
    int iNode_id = findiNodeByName(fileName);
    if (iNode_id == -1) {
        cout << "文件不存在！\n";
        return;
    }

    buffer = contentBuffer(iNode_id);
    ofstream tempFile;
    tempFile.open("Temp\\" + fileName + ".txt", ios::out | ios::app);
    if (tempFile.is_open()) {//新建临时文件成功
        tempFile << buffer;
    }
    tempFile.close();
    string str = "vim -M Temp\\" + fileName + ".txt";      //vim - M file :以只读的方式打开文件，不可以强制保存
    system(str.data());
}

vector<int> ReadIndexBlock(string content) {        //一级索引读取索引块
    vector<int> Index_block;
    int temp;
    //从流（cin）中输出东西到字符串s中
    stringstream st;  //字符串流
    st << content;  //输入s字符串到流（st）中
    while (st >> temp)
        Index_block.push_back(temp);
    return Index_block;
}

string contentBuffer(int iNode_id) {
    string buffer;
    for (int i = 0; i <= (fileSystem.iNode[iNode_id].file_len - 1) / BLOCKSIZ; i++) {       //读iNode的索引数组的直接索引
        int block_addr = fileSystem.iNode[iNode_id].i_addr[i];      //索引数组取出来的地址，即存放文件的磁盘块号
        buffer += fileSystem.diskBlock[block_addr].content;     //向buffer中不断加入磁盘块的内容
    }

    //一级索引
    if (fileSystem.iNode[iNode_id].file_len > BLOCKSIZ * 10) {
        vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[10].content);       //读取一级索引中的磁盘块块号
        for (int i = 0; i < index_block_level1.size(); i++) {
            buffer += fileSystem.diskBlock[index_block_level1[i]].content;     //向buffer中不断加入索引块指向的磁盘块的内容
        }

    }
    //二级索引
    if (fileSystem.iNode[iNode_id].file_len > BLOCKSIZ * BLOCKSIZ / 4 + 10 * BLOCKSIZ) {
        vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[11].content);       //读取二级索引中的索引块号
        for (int i = 0; i < index_block_level1.size(); i++) {
            vector<int> index_block_level2 = ReadIndexBlock(fileSystem.diskBlock[i].content);       //读取二级索引中的一级索引中的磁盘块块号
            for (int j = 0; j < index_block_level2.size(); j++) {
                buffer += fileSystem.diskBlock[index_block_level2[j]].content;     //向buffer中不断加入索引块指向的磁盘块的内容
            }
        }
    }
    //三级索引
    if (fileSystem.iNode[iNode_id].file_len > BLOCKSIZ * BLOCKSIZ * BLOCKSIZ / 16 + BLOCKSIZ * BLOCKSIZ / 4 + 10 * BLOCKSIZ) {
        vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[12].content);       //读取二级索引中的索引块号
        for (int i = 0; i < index_block_level1.size(); i++) {
            vector<int> index_block_level2 = ReadIndexBlock(fileSystem.diskBlock[i].content);       //读取二级索引中的一级索引中的磁盘块块号
            for (int j = 0; j < index_block_level2.size(); j++) {
                vector<int> index_block_level3 = ReadIndexBlock(fileSystem.diskBlock[j].content);       //读取三级索引中的二级索引中的一级索引中的磁盘块块号
                for (int k = 0; k < index_block_level3.size(); k++) {
                    buffer += fileSystem.diskBlock[index_block_level3[k]].content;     //向buffer中不断加入索引块指向的磁盘块的内容
                }
            }
        }
    }
    return buffer;
}