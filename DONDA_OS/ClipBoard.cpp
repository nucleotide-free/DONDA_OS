#include "OS.h"

//����
void cut(string fileName)
{
    if (copy(fileName) == -1)//���ļ����ݸ��Ƶ����а�
        return;
    deleteFile(fileName);//ɾ���ļ�
}

//����
int copy(string fileName)
{
    int iNode_id = findiNodeByName(fileName);
    if (iNode_id == -1 || fileSystem.iNode[iNode_id].type == 1) {
        cout << "�����ļ������ڣ�\n";
        return -1;
    }
    clip_fileName = fileName;   //���а����ļ�������
    ClipBoard = contentBuffer(iNode_id);    //��ȡ�ļ����ݣ�������а�
    return 0;
}

//ճ��
void paste()
{
    int iNode_id = findiNodeByName(clip_fileName);
    if (fileSystem.iNode[iNode_id].auth[user.user_id] == 0) {
        cout << "�����û�Ȩ�޲��㣬�޷�ճ���ļ�����ǰĿ¼��\n";
        return;
    }
    int res = createFile(clip_fileName);//�½�һ��ͬ���ļ�
    if (res == 1) {
        cout << "����ʣ���ڴ�ռ䲻�㣬�½��ļ�ʧ�ܣ�\n";
        return;
    }
    else if (res == 2) {
        cout << "�����ļ�����ͻ��\n";
        return;
    }

    //�Ѽ����������д������
    string content = ClipBoard;

    fileSystem.iNode[findiNodeByName(clip_fileName)].file_len = content.size();      //�޸�iNode�ڵ��е��ļ�����
    int block_num;      //�ļ�������Ҫ����Ĵ��̿�����
    block_num = (content.size() - 1) / BLOCKSIZ + 1;
    for (int i = 0; i < block_num; i++)     //���ļ�������̿�
    {
        int block_id = AllocateOneBlock();        //����Ĵ��̿��
        fileSystem.iNode[findiNodeByName(clip_fileName)].i_addr[i] = block_id;     //ͨ���ļ����ҵ�������Ĵ��̿��д����ļ�iNode����������
        if (i != block_num - 1) {
            fileSystem.diskBlock[block_id].content = content.substr(i * BLOCKSIZ, BLOCKSIZ);        //ÿ�����̿�����ݶ�������content��Ӧλ�õ��Ӵ�
            fileSystem.diskBlock[block_id].content_len = BLOCKSIZ;        //ÿ�����̿�����ݴ�С��512����Ϊ�Ѿ�д����
        }
        else {
            fileSystem.diskBlock[block_id].content = content.substr(i * BLOCKSIZ);      //���һ�����̿�����ݶ�������content��Ӧλ�õ��Ӵ�
            fileSystem.diskBlock[block_id].content_len = content.length() - (i * BLOCKSIZ);      //���һ�����̿�����ݴ�С����512
        }
    }
}