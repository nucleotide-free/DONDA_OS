#include<iostream>
#include<vector>
#include<string>
#include "OS.h"

using namespace std;

//初始化超级块
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
		if (!count(fileSystem.superBlock.free_diskblock_id.begin(), fileSystem.superBlock.free_diskblock_id.end(), i))//判断i是否存在超级块中的空闲磁盘块vector中，若没有就读文件。
		{
			cin >> fileSystem.diskBlock[i].content_len;		//先读取文件的大小
			{
				string content;
				for (int j = 0; j < fileSystem.diskBlock[i].content_len; j++)
				{
					cin >> content;//再获取文件内容。
					fileSystem.diskBlock[i].content = " " + fileSystem.diskBlock[i].content + " " + content + " ";  //文件内容
				}
			}
		}
	}
}