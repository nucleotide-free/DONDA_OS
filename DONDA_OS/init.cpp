#include<iostream>
#include<vector>
#include<string>
#include "OS.h"

using namespace std;

//��ʼ��������
void initSuperBlock(){		

	freopen("superBlock.txt","r", stdin);


}

void initSFD() {

}

void initINode() {

}

void initDiskBlock() {
	freopen("DiskBlock.txt", "r", stdin);
	string content;
	int  content_len;
	for (int i = 0; i < 512; i++)
	{
		if (!count(fileSystem.superBlock.free_diskblock_id.begin(), fileSystem.superBlock.free_diskblock_id.end(), i))//�ж�i�Ƿ���ڳ������еĿ��д��̿�vector�У���û�оͶ��ļ���
		{
			cin >> fileSystem.diskBlock[i].content_len;		//�ȶ�ȡ�ļ��Ĵ�С
			{
				string content;
				for (int j = 0; j < fileSystem.diskBlock[i].content_len; j++)
				{
					cin >> content;//�ٻ�ȡ�ļ����ݡ�
					fileSystem.diskBlock[i].content = " " + fileSystem.diskBlock[i].content + " " + content + " ";  //�ļ�����
				}
			}
		}
	}
}