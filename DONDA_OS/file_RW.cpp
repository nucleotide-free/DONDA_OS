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

int findiNodeById(int sfd_pointer,string fileName)
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
    tempFile.open("Temp\\" + fileName + ".txt", ios::out | ios::trunc);
    if (tempFile.is_open()) {//�½���ʱ�ļ��ɹ�
        tempFile << buffer;
    }
    tempFile.close();
    string str = "vim Temp\\" + fileName + ".txt";      //vim 
    system(str.data());     

    tempToDiskBlock(fileName);
}

//��temp�ļ��������д�����̿���
void tempToDiskBlock(string fileName)
{
    string content;
    ifstream tempFile;
    tempFile.open("Temp\\"+fileName+".txt", ios::in);
    if (tempFile.is_open()) {//�½���ʱ�ļ��ɹ�
        stringstream s;
        s << tempFile.rdbuf();
        content = s.str();       //���ļ�
    }
    tempFile.close();
    fileSystem.iNode[findiNodeByName(fileName)].file_len = content.size();      //�޸�iNode�ڵ��е��ļ�����
    int block_num;      //�ļ�������Ҫ����Ĵ��̿�����
    block_num = (content.size() - 1) / BLOCKSIZ + 1;
    for (int i = 0; i < block_num; i++)     //���ļ�������̿�
    {
        int block_id=AllocateOneBlock();        //����Ĵ��̿��
        fileSystem.iNode[findiNodeByName(fileName)].i_addr[i] = block_id;     //ͨ���ļ����ҵ�������Ĵ��̿��д����ļ�iNode����������
        if (i != block_num - 1) {
            fileSystem.diskBlock[block_id].content = content.substr(i * BLOCKSIZ, BLOCKSIZ);        //ÿ�����̿�����ݶ�������content��Ӧλ�õ��Ӵ�
            fileSystem.diskBlock[block_id].content_len = BLOCKSIZ;        //ÿ�����̿�����ݴ�С��512����Ϊ�Ѿ�д����
        }
        else {
            fileSystem.diskBlock[block_id].content = content.substr(i * BLOCKSIZ);      //���һ�����̿�����ݶ�������content��Ӧλ�õ��Ӵ�
            fileSystem.diskBlock[block_id].content_len = content.length()-(i * BLOCKSIZ);      //���һ�����̿�����ݴ�С����512
        }
    }


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
    tempFile.open("Temp\\" + fileName + ".txt", ios::out | ios::trunc);
    if (tempFile.is_open()) {//�½���ʱ�ļ��ɹ�
        tempFile << buffer;
    }
    tempFile.close();
    string str = "vim -M Temp\\" + fileName + ".txt";      //vim - M file :��ֻ���ķ�ʽ���ļ���������ǿ�Ʊ���
    system(str.data());
}

//һ��������ȡ������
vector<int> ReadIndexBlock(string content) {        
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
        int block_addr = fileSystem.iNode[iNode_id].i_addr[10];
        vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[block_addr].content);       //��ȡһ�������еĴ��̿���
        for (int i = 0; i < index_block_level1.size(); i++) {
            buffer += fileSystem.diskBlock[index_block_level1[i]].content;     //��buffer�в��ϼ���������ָ��Ĵ��̿������
        }

    }
    //��������
    if (fileSystem.iNode[iNode_id].file_len > BLOCKSIZ * BLOCKSIZ / 4 + 10 * BLOCKSIZ) {
        int block_addr = fileSystem.iNode[iNode_id].i_addr[11];
        vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[block_addr].content);       //��ȡ���������е��������
        for (int i = 0; i < index_block_level1.size(); i++) {
            vector<int> index_block_level2 = ReadIndexBlock(fileSystem.diskBlock[index_block_level1[i]].content);       //��ȡ���������е�һ�������еĴ��̿���
            for (int j = 0; j < index_block_level2.size(); j++) {
                buffer += fileSystem.diskBlock[index_block_level2[j]].content;     //��buffer�в��ϼ���������ָ��Ĵ��̿������
            }
        }
    }
    //��������
    if (fileSystem.iNode[iNode_id].file_len > BLOCKSIZ * BLOCKSIZ * BLOCKSIZ / 16 + BLOCKSIZ * BLOCKSIZ / 4 + 10 * BLOCKSIZ) {
        int block_addr = fileSystem.iNode[iNode_id].i_addr[12];
        vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[block_addr].content);       //��ȡ���������е��������
        for (int i = 0; i < index_block_level1.size(); i++) {
            vector<int> index_block_level2 = ReadIndexBlock(fileSystem.diskBlock[index_block_level1[i]].content);       //��ȡ���������е�һ�������еĴ��̿���
            for (int j = 0; j < index_block_level2.size(); j++) {
                vector<int> index_block_level3 = ReadIndexBlock(fileSystem.diskBlock[index_block_level2[j]].content);       //��ȡ���������еĶ��������е�һ�������еĴ��̿���
                for (int k = 0; k < index_block_level3.size(); k++) {
                    buffer += fileSystem.diskBlock[index_block_level3[k]].content;     //��buffer�в��ϼ���������ָ��Ĵ��̿������
                }
            }
        }
    }
    return buffer;
}

//�ļ�������
void renameFile(string fileName1, string fileName2)
{
    for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {//����ļ��Ƿ�����
        if (fileName2 == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name) {
            cout << "�����ļ���" + fileName2 + "�Ѵ��ڣ�";
            return;//�ļ�����ͻ
        }
    }

    for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) { //���Ҹ��ļ�
        if (fileName1 == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name) {
            int iNode_id = fileSystem.SFD[sfd_pointer].sfd_list[i].file_id;     //��ȡiNode_id
            if (fileSystem.iNode[iNode_id].auth[user.user_id] == 0) {   //����û�Ȩ��
                cout << "Ȩ�޲��㣬�޷��޸��ļ���\n";
                return;
            }
            fileSystem.SFD[sfd_pointer].sfd_list[i].file_name = fileName2;//�ļ��������ɹ�
            return;
        }
    }
    cout << "�ļ������ڣ�\n";
    return;
}