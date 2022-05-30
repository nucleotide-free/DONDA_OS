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
    string buffer;      //���ڴ�Ŷ�����������
    int iNode_id = findiNodeByName(fileName);
    if (iNode_id == -1) {
        cout << "�ļ������ڣ�\n";
        return;
    }
    if (fileSystem.iNode[iNode_id].auth[user.user_id] == 0) {
        cout << "Ȩ�޲��㣬�޷��޸��ļ���\n";
        return;
    }
    buffer = contentBuffer(iNode_id);
    ofstream tempFile;
    tempFile.open("Temp\\" + fileName + ".txt", ios::out | ios::app);
    if (tempFile.is_open()) {//�½���ʱ�ļ��ɹ�
        tempFile << buffer;
    }
    tempFile.close();
    string str = "vim Temp\\" + fileName + ".txt";      //vim - M file :��ֻ���ķ�ʽ���ļ���������ǿ�Ʊ���
    system(str.data());
}

//��ָ���ļ������ļ�
void readFile(string fileName)
{
    string buffer;      //���ڴ�Ŷ�����������
    int iNode_id = findiNodeByName(fileName);
    if (iNode_id == -1) {
        cout << "�ļ������ڣ�\n";
        return;
    }

    buffer = contentBuffer(iNode_id);
    ofstream tempFile;
    tempFile.open("Temp\\" + fileName + ".txt", ios::out | ios::app);
    if (tempFile.is_open()) {//�½���ʱ�ļ��ɹ�
        tempFile << buffer;
    }
    tempFile.close();
    string str = "vim -M Temp\\" + fileName + ".txt";      //vim - M file :��ֻ���ķ�ʽ���ļ���������ǿ�Ʊ���
    system(str.data());
}

vector<int> ReadIndexBlock(string content) {        //һ��������ȡ������
    vector<int> Index_block;
    int temp;
    //������cin��������������ַ���s��
    stringstream st;  //�ַ�����
    st << content;  //����s�ַ���������st����
    while (st >> temp)
        Index_block.push_back(temp);
    return Index_block;
}

string contentBuffer(int iNode_id) {
    string buffer;
    for (int i = 0; i <= (fileSystem.iNode[iNode_id].file_len - 1) / BLOCKSIZ; i++) {       //��iNode�����������ֱ������
        int block_addr = fileSystem.iNode[iNode_id].i_addr[i];      //��������ȡ�����ĵ�ַ��������ļ��Ĵ��̿��
        buffer += fileSystem.diskBlock[block_addr].content;     //��buffer�в��ϼ�����̿������
    }

    //һ������
    if (fileSystem.iNode[iNode_id].file_len > BLOCKSIZ * 10) {
        vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[10].content);       //��ȡһ�������еĴ��̿���
        for (int i = 0; i < index_block_level1.size(); i++) {
            buffer += fileSystem.diskBlock[index_block_level1[i]].content;     //��buffer�в��ϼ���������ָ��Ĵ��̿������
        }

    }
    //��������
    if (fileSystem.iNode[iNode_id].file_len > BLOCKSIZ * BLOCKSIZ / 4 + 10 * BLOCKSIZ) {
        vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[11].content);       //��ȡ���������е��������
        for (int i = 0; i < index_block_level1.size(); i++) {
            vector<int> index_block_level2 = ReadIndexBlock(fileSystem.diskBlock[i].content);       //��ȡ���������е�һ�������еĴ��̿���
            for (int j = 0; j < index_block_level2.size(); j++) {
                buffer += fileSystem.diskBlock[index_block_level2[j]].content;     //��buffer�в��ϼ���������ָ��Ĵ��̿������
            }
        }
    }
    //��������
    if (fileSystem.iNode[iNode_id].file_len > BLOCKSIZ * BLOCKSIZ * BLOCKSIZ / 16 + BLOCKSIZ * BLOCKSIZ / 4 + 10 * BLOCKSIZ) {
        vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[12].content);       //��ȡ���������е��������
        for (int i = 0; i < index_block_level1.size(); i++) {
            vector<int> index_block_level2 = ReadIndexBlock(fileSystem.diskBlock[i].content);       //��ȡ���������е�һ�������еĴ��̿���
            for (int j = 0; j < index_block_level2.size(); j++) {
                vector<int> index_block_level3 = ReadIndexBlock(fileSystem.diskBlock[j].content);       //��ȡ���������еĶ��������е�һ�������еĴ��̿���
                for (int k = 0; k < index_block_level3.size(); k++) {
                    buffer += fileSystem.diskBlock[index_block_level3[k]].content;     //��buffer�в��ϼ���������ָ��Ĵ��̿������
                }
            }
        }
    }
    return buffer;
}