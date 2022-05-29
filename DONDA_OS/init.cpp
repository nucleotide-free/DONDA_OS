#include "OS.h"

using namespace std;

//初始化超级块
void initSuperBlock(){
	FILE* stream1;
	freopen_s(&stream1,"superBlock.txt", "r", stdin);//文件重定向

	fileSystem.superBlock.iNode_num = D_INODE_NUM;	//磁盘i节点数量
	cin >> fileSystem.superBlock.free_iNode_num;	//空间i节点数
	for (int i = 0; i < INODE_BITMAP_ROW; i++)		//初始化i节点位示图，全部被占用-1
		for (int j = 0; j < INODE_BITMAP_COL; j++)
			fileSystem.superBlock.iNode_bitmap[i][j] = 1;
	for (int i = 0; i < fileSystem.superBlock.free_iNode_num; i++) {//读文件，输入空闲的i节点块号
		int block_no;
		cin >> block_no;
		fileSystem.superBlock.iNode_bitmap[block_no / INODE_BITMAP_COL][block_no % INODE_BITMAP_COL] = 0;//空闲
	}

	fileSystem.superBlock.sfd_item_num = SFD_NUM;	//目录节点数量
	cin >> fileSystem.superBlock.free_sfd_item_num;	//空闲目录节点数
	for (int i = 0; i < SFD_BITMAP_ROW; i++)		//初始化目录节点位示图，全部被占用-1
		for (int j = 0; j < SFD_BITMAP_COL; j++)
			fileSystem.superBlock.SFD_bitmap[i][j] = 1;
	for (int i = 0; i < fileSystem.superBlock.free_sfd_item_num; i++) {//读文件，输入空闲的目录节点块号
		int block_no;
		cin >> block_no;
		fileSystem.superBlock.SFD_bitmap[block_no / SFD_BITMAP_COL][block_no % SFD_BITMAP_COL] = 0;//空闲
	}

	fclose(stdin);//关闭重定向输入


}

//初始化SFD
void initSFD() {

}

//初始化I节点
void initINode() {

}

//初始化磁盘块
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