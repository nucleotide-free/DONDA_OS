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

int findiNodeById(int sfd_pointer,string fileName)
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
    tempFile.open("Temp\\" + fileName + ".txt", ios::out | ios::trunc);
    if (tempFile.is_open()) {//新建临时文件成功
        tempFile << buffer;
    }
    tempFile.close();
    string str = "vim Temp\\" + fileName + ".txt";      //vim 
    system(str.data());     

    tempToDiskBlock(fileName);
}

//把temp文件里的内容写到磁盘块中
void tempToDiskBlock(string fileName)
{
    string content;
    ifstream tempFile;
    tempFile.open("Temp\\"+fileName+".txt", ios::in);
    if (tempFile.is_open()) {//新建临时文件成功
        stringstream s;
        s << tempFile.rdbuf();
        content = s.str();       //读文件
    }
    tempFile.close();
    fileSystem.iNode[findiNodeByName(fileName)].file_len = content.size();      //修改iNode节点中的文件长度
    int block_num;      //文件内容需要申请的磁盘块数量
    block_num = (content.size() - 1) / BLOCKSIZ + 1;
    for (int i = 0; i < block_num; i++)     //给文件分配磁盘快
    {
        int block_id=AllocateOneBlock();        //分配的磁盘块号
        fileSystem.iNode[findiNodeByName(fileName)].i_addr[i] = block_id;     //通过文件名找到将分配的磁盘块号写入该文件iNode的索引数组
        if (i != block_num - 1) {
            fileSystem.diskBlock[block_id].content = content.substr(i * BLOCKSIZ, BLOCKSIZ);        //每个磁盘块的内容都来自于content对应位置的子串
            fileSystem.diskBlock[block_id].content_len = BLOCKSIZ;        //每个磁盘块的内容大小都512，因为已经写满了
        }
        else {
            fileSystem.diskBlock[block_id].content = content.substr(i * BLOCKSIZ);      //最后一个磁盘块的内容都来自于content对应位置的子串
            fileSystem.diskBlock[block_id].content_len = content.length()-(i * BLOCKSIZ);      //最后一个磁盘块的内容大小不是512
        }
    }


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
    tempFile.open("Temp\\" + fileName + ".txt", ios::out | ios::trunc);
    if (tempFile.is_open()) {//新建临时文件成功
        tempFile << buffer;
    }
    tempFile.close();
    string str = "vim -M Temp\\" + fileName + ".txt";      //vim - M file :以只读的方式打开文件，不可以强制保存
    system(str.data());
}

//一级索引读取索引块
vector<int> ReadIndexBlock(string content) {        
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
        int block_addr = fileSystem.iNode[iNode_id].i_addr[10];
        vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[block_addr].content);       //读取一级索引中的磁盘块块号
        for (int i = 0; i < index_block_level1.size(); i++) {
            buffer += fileSystem.diskBlock[index_block_level1[i]].content;     //向buffer中不断加入索引块指向的磁盘块的内容
        }

    }
    //二级索引
    if (fileSystem.iNode[iNode_id].file_len > BLOCKSIZ * BLOCKSIZ / 4 + 10 * BLOCKSIZ) {
        int block_addr = fileSystem.iNode[iNode_id].i_addr[11];
        vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[block_addr].content);       //读取二级索引中的索引块号
        for (int i = 0; i < index_block_level1.size(); i++) {
            vector<int> index_block_level2 = ReadIndexBlock(fileSystem.diskBlock[index_block_level1[i]].content);       //读取二级索引中的一级索引中的磁盘块块号
            for (int j = 0; j < index_block_level2.size(); j++) {
                buffer += fileSystem.diskBlock[index_block_level2[j]].content;     //向buffer中不断加入索引块指向的磁盘块的内容
            }
        }
    }
    //三级索引
    if (fileSystem.iNode[iNode_id].file_len > BLOCKSIZ * BLOCKSIZ * BLOCKSIZ / 16 + BLOCKSIZ * BLOCKSIZ / 4 + 10 * BLOCKSIZ) {
        int block_addr = fileSystem.iNode[iNode_id].i_addr[12];
        vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[block_addr].content);       //读取二级索引中的索引块号
        for (int i = 0; i < index_block_level1.size(); i++) {
            vector<int> index_block_level2 = ReadIndexBlock(fileSystem.diskBlock[index_block_level1[i]].content);       //读取二级索引中的一级索引中的磁盘块块号
            for (int j = 0; j < index_block_level2.size(); j++) {
                vector<int> index_block_level3 = ReadIndexBlock(fileSystem.diskBlock[index_block_level2[j]].content);       //读取三级索引中的二级索引中的一级索引中的磁盘块块号
                for (int k = 0; k < index_block_level3.size(); k++) {
                    buffer += fileSystem.diskBlock[index_block_level3[k]].content;     //向buffer中不断加入索引块指向的磁盘块的内容
                }
            }
        }
    }
    return buffer;
}

//文件重命名
void renameFile(string fileName1, string fileName2)
{
    for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {//检查文件是否重名
        if (fileName2 == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name) {
            cout << "错误！文件名" + fileName2 + "已存在！";
            return;//文件名冲突
        }
    }

    for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) { //查找该文件
        if (fileName1 == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name) {
            int iNode_id = fileSystem.SFD[sfd_pointer].sfd_list[i].file_id;     //获取iNode_id
            if (fileSystem.iNode[iNode_id].auth[user.user_id] == 0) {   //检查用户权限
                cout << "权限不足，无法修改文件！\n";
                return;
            }
            fileSystem.SFD[sfd_pointer].sfd_list[i].file_name = fileName2;//文件重命名成功
            return;
        }
    }
    cout << "文件不存在！\n";
    return;
}