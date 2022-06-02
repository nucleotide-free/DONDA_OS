#include "OS.h"

//剪切
void cut(string fileName)
{
    if (copy(fileName) == -1)//把文件内容复制到剪切板
        return;
    deleteFile(fileName);//删除文件
}

//复制
int copy(string fileName)
{
    int iNode_id = findiNodeByName(fileName);
    if (iNode_id == -1 || fileSystem.iNode[iNode_id].type == 1) {
        cout << "错误：文件不存在！\n";
        return -1;
    }
    clip_fileName = fileName;   //剪切板中文件的名字
    ClipBoard = contentBuffer(iNode_id);    //读取文件内容，放入剪切板
    return 0;
}

//粘贴
void paste()
{
    int iNode_id = findiNodeByName(clip_fileName);
    if (fileSystem.iNode[iNode_id].auth[user.user_id] == 0) {
        cout << "错误：用户权限不足，无法粘贴文件到当前目录！\n";
        return;
    }
    int res = createFile(clip_fileName);//新建一个同名文件
    if (res == 1) {
        cout << "错误：剩余内存空间不足，新建文件失败！\n";
        return;
    }
    else if (res == 2) {
        cout << "错误：文件名冲突！\n";
        return;
    }

    //把剪贴板的内容写到磁盘
    string content = ClipBoard;

    fileSystem.iNode[findiNodeByName(clip_fileName)].file_len = content.size();      //修改iNode节点中的文件长度
    int block_num;      //文件内容需要申请的磁盘块数量
    block_num = (content.size() - 1) / BLOCKSIZ + 1;
    for (int i = 0; i < block_num; i++)     //给文件分配磁盘快
    {
        int block_id = AllocateOneBlock();        //分配的磁盘块号
        fileSystem.iNode[findiNodeByName(clip_fileName)].i_addr[i] = block_id;     //通过文件名找到将分配的磁盘块号写入该文件iNode的索引数组
        if (i != block_num - 1) {
            fileSystem.diskBlock[block_id].content = content.substr(i * BLOCKSIZ, BLOCKSIZ);        //每个磁盘块的内容都来自于content对应位置的子串
            fileSystem.diskBlock[block_id].content_len = BLOCKSIZ;        //每个磁盘块的内容大小都512，因为已经写满了
        }
        else {
            fileSystem.diskBlock[block_id].content = content.substr(i * BLOCKSIZ);      //最后一个磁盘块的内容都来自于content对应位置的子串
            fileSystem.diskBlock[block_id].content_len = content.length() - (i * BLOCKSIZ);      //最后一个磁盘块的内容大小不是512
        }
    }
}